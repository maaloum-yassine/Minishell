/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 03:56:13 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 00:14:43 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_print_err_env(t_data *s_data)
{
	ft_print_err("bash: env: No such file or directory\n");
	s_data->check_status++;
	g_exit_status = 127;
}

static	void	ft_print_env(t_env *s_env)
{
	while (s_env)
	{
		if (s_env->status == 1)
			printf("%s=%s\n", s_env->variable, s_env->value);
		s_env = s_env->next;
	}
}

void	ft_env(t_data *s_data, t_env *s_env)
{
	t_env	*s_check;
	char	check;

	check = 1;
	if (!s_env)
		return ;
	s_check = s_env;
	while (s_check)
	{
		if (ft_strcmp(s_check->variable, "PATH") == 0)
		{
			check = 0;
			break ;
		}
		s_check = s_check->next;
	}
	if (check == 0)
		ft_print_env(s_env);
	else
		ft_print_err_env(s_data);
}
