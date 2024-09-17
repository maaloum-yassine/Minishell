/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 04:34:28 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/18 22:40:51 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_err(char *err)
{
	write(2, err, ft_lenght(err));
}

void	ft_check_err(char quote)
{
	if (quote == 1)
	{
		ft_print_err("ERREUR\nsyntax quote\n");
		g_exit_status = 258;
	}
	else if (quote == 2)
	{
		ft_print_err("ERREUR\nsyntax pipe\n");
		g_exit_status = 258;
	}
	else if (quote == 3)
	{
		ft_print_err("ERREUR\nsyntax redirection\n");
		g_exit_status = 258;
	}
}

void	ft_check_quote(t_data *s_var, int *i)
{
	char	quote;

	if (s_var->l_cmd[*i] == '\'' || s_var->l_cmd[*i] == '\"')
	{
		s_var->check = 1;
		quote = s_var->l_cmd[(*i)++];
		while (s_var->l_cmd[*i])
		{
			if (s_var->l_cmd[*i] == quote)
			{
				s_var->check = 0;
				break ;
			}
			(*i)++;
		}
	}
}

void	ft_syntax(t_data *s_var)
{
	int	i;

	s_var->check = 0;
	i = 0;
	while (s_var->l_cmd[i])
	{
		ft_check_quote(s_var, &i);
		if (s_var->check != 0)
			break ;
		ft_check_redirection_pipe(s_var, i);
		i++;
		if (s_var->check != 0)
			break ;
	}
	ft_check_err(s_var->check);
}

void	ft_check_syntax(t_data *s_var, char **env)
{
	char	*str;

	str = ft_strtrim(s_var->l_cmd, " \t");
	if (str == NULL || str[0] == '\0')
	{
		free (str);
		return ;
	}
	else
	{
		free (s_var->l_cmd);
		s_var->l_cmd = str;
	}
	ft_syntax(s_var);
	if (s_var->check == 0)
		ft_divide_cmd(s_var, env);
	s_var->check = 0;
}
