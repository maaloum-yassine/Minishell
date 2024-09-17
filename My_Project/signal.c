/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:21:54 by ymaaloum          #+#    #+#             */
/*   Updated: 2024/09/17 07:06:11 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
	if (signum == SIGQUIT)
		rl_redisplay();
}

void	ft_ctr_d(t_data *s_var)
{
	if (s_var->l_cmd == NULL)
	{
		ft_free_list(s_var->s_env);
		ft_free(s_var);
		printf("exit");
		exit(g_exit_status);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}
