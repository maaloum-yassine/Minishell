/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:27:33 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 01:37:52 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	ft_distinct_red_and_fill2(char *new_cmd, char *cmd, int *i, int *j)
{
	new_cmd[(*j)++] = ' ';
	new_cmd[(*j)++] = 4;
	new_cmd[(*j)++] = cmd[(*i)++];
	new_cmd[(*j)++] = cmd[(*i)++];
	new_cmd[(*j)++] = ' ';
}

void	ft_distinct_red_and_fill(char *new_cmd, char *cmd, int *i, int *j)
{
	if (cmd[*i] == '<' && cmd[(*i) + 1] != '<')
	{
		new_cmd[(*j)++] = ' ';
		new_cmd[(*j)++] = 1;
		new_cmd[(*j)++] = cmd[(*i)++];
		new_cmd[(*j)++] = ' ';
	}
	else if (cmd[*i] == '>' && cmd[(*i) + 1] != '>')
	{
		new_cmd[(*j)++] = ' ';
		new_cmd[(*j)++] = 3;
		new_cmd[(*j)++] = cmd[(*i)++];
		new_cmd[(*j)++] = ' ';
	}
	else if (cmd[*i] == '>' && cmd[(*i) + 1] == '>')
	{
		new_cmd[(*j)++] = ' ';
		new_cmd[(*j)++] = 2;
		new_cmd[(*j)++] = cmd[(*i)++];
		new_cmd[(*j)++] = cmd[(*i)++];
		new_cmd[(*j)++] = ' ';
	}
	else if (cmd[*i] == '<' && cmd[(*i) + 1] == '<')
		ft_distinct_red_and_fill2(new_cmd, cmd, i, j);
}

void	ft_skip_and_fill_new_cmd(char *new_cmd, char *cmd, int *i, int *j)
{
	char	quote;

	if (cmd[*i] == '\'' || cmd[*i] == '\"')
	{
		quote = cmd[(*i)++];
		new_cmd[(*j)++] = quote;
		while (cmd[*i])
		{
			if (cmd[*i] == quote)
			{
				new_cmd[(*j)++] = cmd[(*i)++];
				break ;
			}
			new_cmd[(*j)++] = cmd[(*i)++];
		}
	}
}
