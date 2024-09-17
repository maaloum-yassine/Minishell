/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_struct2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 07:28:23 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 01:11:23 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static	void	ft_update_arg3(t_data *s_dt)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = -1;
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			ft_update_arg4(s_dt->s_cmd[i].args, &new_str);
			ft_free_split(s_dt->s_cmd[i].args);
			s_dt->s_cmd[i].args = ft_split(new_str, ' ', '\t');
			free (new_str);
			new_str = NULL;
		}
	}
}

static	void	ft_update_cmd4(char **cmd, char **arg)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	tmp = *cmd;
	j = 0;
	while (arg[j])
	{
		if (arg[j][0] != '\0')
		{
			*cmd = ft_strdup(arg[j]);
			free (tmp);
			break ;
		}
		j++;
	}
}

static	char	ft_check_arg2(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static	void	ft_update_cmd3(t_data *s_dt)
{
	int	i;

	i = -1;
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			if (s_dt->s_cmd[i].command[0] == '\0')
			{
				if (ft_check_arg2(s_dt->s_cmd[i].args) == 1)
					ft_update_cmd4(&s_dt->s_cmd[i].command,
						s_dt->s_cmd[i].args);
				else
				{
					free (s_dt->s_cmd[i].command);
					s_dt->s_cmd[i].command = NULL;
					ft_free_split(s_dt->s_cmd[i].args);
					s_dt->s_cmd[i].args = NULL;
				}
			}
		}
	}
}

void	ft_update2(t_data *s_dt)
{
	ft_update_cmd3(s_dt);
	ft_update_arg3(s_dt);
}
