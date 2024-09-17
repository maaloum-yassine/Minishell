/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 04:56:13 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:39:04 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*ft_check_expand(t_data *s_data, char *arg)
{
	char	*tmp;

	tmp = NULL;
	tmp = arg;
	arg = ft_removed(tmp);
	free (tmp);
	if (arg[0] == '$' && ft_lenght(arg) == 1)
		return (arg);
	else if (arg[0] == '\0')
	{
		free (arg);
		return (NULL);
	}
	tmp = arg;
	arg = ft_expand_dblquote(s_data, arg);
	free (tmp);
	tmp = arg;
	arg = ft_expand(s_data, arg);
	free (tmp);
	return (arg);
}

static	void	ft_expand_s_file(t_data *s_dt, int *i)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	if (s_dt->s_cmd[*i].s_files[j])
	{
		while (s_dt->s_cmd[*i].s_files[j])
		{
			if (!(s_dt->s_cmd[*i].s_files[j]->type == 'H'))
			{
				tmp = ft_strdup(s_dt->s_cmd[*i].s_files[j]->file);
				s_dt->s_cmd[*i].s_files[j]->file
					= ft_check_expand(s_dt, s_dt->s_cmd[*i].s_files[j]->file);
				if (s_dt->s_cmd[*i].s_files[j]->file == NULL)
				{
					s_dt->s_cmd[*i].s_files[j]->file = tmp;
					s_dt->s_cmd[*i].s_files[j]->type = 'E';
				}
				else
					free (tmp);
			}
			j++;
		}
	}
}

static	void	ft_expand_arg(t_data *s_dt, int *i)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = 0;
	while (s_dt->s_cmd[*i].args[j])
	{
		tmp = ft_check_expand(s_dt, s_dt->s_cmd[*i].args[j]);
		if (tmp == NULL)
			s_dt->s_cmd[*i].args[j++] = ft_strdup("");
		else
			s_dt->s_cmd[*i].args[j++] = tmp;
	}
}

void	ft_handl_expand(t_data *s_dt)
{
	int		i;
	char	*tmp;

	i = -1;
	s_dt->s_xpd = malloc(sizeof(t_xpand));
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			tmp = ft_check_expand(s_dt, s_dt->s_cmd[i].command);
			if (tmp == NULL)
				s_dt->s_cmd[i].command = ft_strdup("");
			else
				s_dt->s_cmd[i].command = tmp;
			ft_expand_arg(s_dt, &i);
		}
		ft_expand_s_file(s_dt, &i);
	}
	ft_check_element(s_dt);
	ft_filter(s_dt);
	free (s_dt->s_xpd);
}
