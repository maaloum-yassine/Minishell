/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:34:13 by ymaaloum          #+#    #+#             */
/*   Updated: 2024/09/17 07:09:50 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_free1(t_data *s_data, int *i, int *x)
{
	*x = 0;
	if (s_data->s_cmd[*i].command)
	{
		free (s_data->s_cmd[*i].command);
		s_data->s_cmd[*i].command = NULL;
		ft_free_split (s_data->s_cmd[*i].args);
		s_data->s_cmd[*i].count_arg = 0;
		s_data->s_cmd[*i].args = NULL;
	}
	if (s_data->s_cmd[*i].s_files)
	{
		while (s_data->s_cmd[*i].s_files[*x])
		{
			free (s_data->s_cmd[*i].s_files[*x]->file);
			free (s_data->s_cmd[*i].s_files[(*x)++]);
		}
		free (s_data->s_cmd[*i].s_files);
	}
	else
	{
		free (s_data->s_cmd[*i].s_files[0]);
		free (s_data->s_cmd[*i].s_files);
	}
	s_data->s_cmd[*i].s_files = NULL;
}

void	ft_free(t_data *s_data)
{
	int	i;
	int	x;

	i = -1;
	free (s_data->l_cmd);
	s_data->l_cmd = "";
	if (s_data->s_cmd)
	{
		while (++i < s_data->count_cmd)
			ft_free1(s_data, &i, &x);
		free (s_data->s_cmd);
		s_data->s_cmd = NULL;
	}
	s_data->count_cmd = 0;
}

void	ft_scren_prog(t_data *s_data, char **env)
{
	ft_fill_env(&(s_data->s_env), env);
	s_data->l_cmd = "";
	ft_signal();
	g_exit_status = 0;
	while (s_data->l_cmd)
	{
		s_data->check_status = 0;
		s_data->l_cmd = readline("Minishell~$ ");
		ft_ctr_d(s_data);
		ft_check_syntax(s_data, env);
		if (s_data->l_cmd[0])
			add_history(s_data->l_cmd);
		ft_free(s_data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	s_data;

	s_data.s_xpd = NULL;
	s_data.s_cmd = NULL;
	s_data.s_env = NULL;
	s_data.s_red = NULL;
	(void)ac;
	(void)av;
	ft_scren_prog(&s_data, env);
	return (0);
}
