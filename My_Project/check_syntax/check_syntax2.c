/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:29:28 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 20:32:12 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_check_pipe(t_data *s_var, int i)
{
	if (i == 0 || i == ft_lenght(s_var->l_cmd) - 1)
	{
		s_var->check = 2;
		return ;
	}
	i++;
	while ((s_var->l_cmd[i] == 32 || s_var->l_cmd[i] == '\t' )
		&& s_var->l_cmd[i])
		i++;
	if (s_var->l_cmd[i] == '|' || s_var->l_cmd[i] == '&')
		s_var->check = 2;
}

static	void	ft_check_redirection_input(t_data *s_var, int i)
{
	if (i == ft_lenght(s_var->l_cmd) - 1)
	{
		s_var->check = 3;
		return ;
	}
	i++;
	if (s_var->l_cmd[i] == '<')
		i++;
	while ((s_var->l_cmd[i] == 32 || s_var->l_cmd[i] == '\t')
		&& s_var->l_cmd[i])
		i++;
	if (s_var->l_cmd[i] == '>' || s_var->l_cmd[i] == '|'
		|| s_var->l_cmd[i] == '<')
		s_var->check = 3;
}

static	void	ft_check_redirection_output(t_data *s_var, int i)
{
	if (i == ft_lenght(s_var->l_cmd) - 1)
	{
		s_var->check = 3;
		return ;
	}
	i++;
	if (s_var->l_cmd[i] == '>')
		i++;
	while ((s_var->l_cmd[i] == 32 || s_var->l_cmd[i] == '\t')
		&& s_var->l_cmd[i])
		i++;
	if (s_var->l_cmd[i] == '>' || s_var->l_cmd[i] == '|'
		|| s_var->l_cmd[i] == '<')
		s_var->check = 3;
	return ;
}

void	ft_check_redirection_pipe(t_data *s_var, int i)
{
	if (s_var->l_cmd[i] == '|')
		ft_check_pipe(s_var, i);
	else if (s_var->l_cmd[i] == '<')
		ft_check_redirection_input(s_var, i);
	else if (s_var->l_cmd[i] == '>')
		ft_check_redirection_output(s_var, i);
}
