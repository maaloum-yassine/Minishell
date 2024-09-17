/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:39:08 by yaghrous          #+#    #+#             */
/*   Updated: 2023/09/19 05:32:03 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		exit(1);
}

int	ft_last_idx_o(t_commands *cmd)
{
	int	i;
	int	idx;

	i = 0;
	idx = -1;
	while (cmd->s_files[i])
	{
		if (cmd->s_files[i]->type == 'O')
			idx = i;
		i++;
	}
	return (idx);
}

int	ft_last_idx_a(t_commands *cmd)
{
	int	i;
	int	idx;

	i = 0;
	idx = -1;
	while (cmd->s_files[i])
	{
		if (cmd->s_files[i]->type == 'A')
			idx = i;
		i++;
	}
	return (idx);
}

int	ft_last_idx_i(t_commands *cmd)
{
	int	i;
	int	idx;

	i = 0;
	idx = -1;
	while (cmd->s_files[i])
	{
		if (cmd->s_files[i]->type == 'I')
			idx = i;
		i++;
	}
	return (idx);
}

int	ft_last_idx_h(t_commands *cmd)
{
	int	i;
	int	idx;

	i = 0;
	idx = -1;
	while (cmd->s_files[i])
	{
		if (cmd->s_files[i]->type == 'H')
			idx = i;
		i++;
	}
	return (idx);
}
