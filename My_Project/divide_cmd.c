/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:33:44 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:05:46 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_fill_struct(char **str, char **cmd)
{
	*cmd = ft_strdup(str[0]);
}

void	ft_trim_cmd(char **cmd)
{
	char	*str;
	int		i;

	i = 0;
	while (cmd[i])
	{
		str = cmd[i];
		cmd[i] = ft_strtrim(cmd[i], " \t");
		free(str);
		i++;
	}
}

static	void	ft_cont_arg(t_data *s_dt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			j = 0;
			s_dt->s_cmd[i].count_arg = 0;
			while (s_dt->s_cmd[i].args[j])
			{
				s_dt->s_cmd[i].count_arg++;
				j++;
			}
		}
	}
}

static	void	ft_fill_s_cmd(t_data *s_data, char **cmd)
{
	char	**new_cmd;
	int		i;

	new_cmd = NULL;
	i = 0;
	while (cmd[i])
	{
		new_cmd = ft_split(cmd[i], ' ', '\t');
		if (new_cmd != NULL)
		{
			s_data->s_cmd[i].args = new_cmd;
			ft_fill_struct(s_data->s_cmd[i].args, &(s_data->s_cmd[i].command));
		}
		else
			s_data->s_cmd[i].command = NULL;
		i++;
	}
}

void	ft_divide_cmd(t_data *s_data, char **env)
{
	char	**cmd;

	s_data->count_cmd = ft_count_w(s_data->l_cmd, '|', 0);
	s_data->s_cmd = malloc(sizeof(t_commands) * (s_data->count_cmd));
	cmd = ft_split(s_data->l_cmd, '|', 0);
	ft_trim_cmd(cmd);
	cmd = ft_handl_red(s_data, cmd);
	ft_fill_s_cmd(s_data, cmd);
	ft_free_split(cmd);
	ft_cont_arg(s_data);
	ft_handl_expand(s_data);
	ft_exec_cmd(s_data, env);
}
