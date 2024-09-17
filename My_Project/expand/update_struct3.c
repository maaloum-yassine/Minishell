/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_struct3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:20:58 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 16:47:11 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_update_arg4(char **arg, char **new_str)
{
	int		j;
	char	*tmp;

	j = 0;
	while (arg[j])
	{
		if (arg[j][0] != '\0')
		{
			if (!new_str)
				*new_str = ft_strjoin(arg[j], " ");
			else
			{
				tmp = *new_str;
				*new_str = ft_strjoin(*new_str, arg[j]);
				free (tmp);
				tmp = *new_str;
				*new_str = ft_strjoin(*new_str, " ");
				free (tmp);
			}
		}
		j++;
	}
}

static	int	ft_new_size(char **arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	while (arg[i])
		i++;
	return (i);
}

static	void	ft_fill_arg4(char **new_str, char **new_arg)
{
	char	*tmp;

	if (!(*new_str))
	{
		tmp = *new_str ;
		*new_str = ft_strjoin(*new_arg, " ");
		free (tmp);
	}
	else
	{
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, *new_arg);
		free (tmp);
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, " ");
		free (tmp);
	}
}

static	char	**ft_fill_arg2(t_data *s_dt, char **new_arg, int *i, int index)
{
	int		j;
	char	*new_str;
	int		x;

	new_str = NULL;
	j = 1;
	x = 0;
	while (s_dt->s_cmd[index].args[j])
		new_arg[(*i)++] = ft_strdup(s_dt->s_cmd[index].args[j++]);
	ft_free_split (s_dt->s_cmd[index].args);
	new_arg[*i] = NULL;
	while (new_arg[x])
		ft_fill_arg4(&new_str, &new_arg[x++]);
	ft_free_split(new_arg);
	new_arg = ft_split(new_str, ' ', '\t');
	free (new_str);
	return (new_arg);
}

char	**ft_fill_arg(char **arg, t_data *s_dt, int index, char **cmd)
{
	int		size;
	int		i;
	int		j;
	char	**new_arg;

	i = 0;
	size = ft_new_size(arg) + s_dt->s_cmd[index].count_arg + 1;
	s_dt->s_cmd[index].count_arg += ft_new_size(arg);
	new_arg = malloc(sizeof(char *) * size);
	new_arg[i++] = ft_strdup(*cmd);
	if (!arg && s_dt->s_cmd[index].count_arg == 1)
	{
		new_arg[i] = NULL;
		return (new_arg);
	}
	j = 0;
	if (arg)
	{
		while (arg[j])
			new_arg[i++] = ft_strdup(arg[j++]);
		ft_free_split (arg);
	}
	return (ft_fill_arg2(s_dt, new_arg, &i, index));
}
