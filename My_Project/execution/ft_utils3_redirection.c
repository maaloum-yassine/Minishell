/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:39:33 by yaghrous          #+#    #+#             */
/*   Updated: 2023/09/19 05:17:52 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_last_idx_output(t_commands *cmd)
{
	int	idx_o;
	int	idx_a;

	idx_o = ft_last_idx_o(cmd);
	idx_a = ft_last_idx_a(cmd);
	if (idx_o > idx_a)
		return (idx_o);
	return (idx_a);
}

int	ft_last_idx_input(t_commands *cmd)
{
	int	idx_i;
	int	idx_h;

	idx_i = ft_last_idx_i(cmd);
	idx_h = ft_last_idx_h(cmd);
	if (idx_i > idx_h)
		return (idx_i);
	return (idx_h);
}

void	ft_dup_last_in_and_out(t_commands *cmd)
{
	if (cmd->fd_out != -1)
		ft_dup2(cmd->fd_out, 1);
	if (cmd->fd_in != -1 && ft_last_idx_i(cmd) > ft_last_idx_h(cmd))
		ft_dup2(cmd->fd_in, 0);
	if (cmd->fd_herdoc != -1 && ft_last_idx_h(cmd) > ft_last_idx_i(cmd))
		ft_dup2(cmd->fd_herdoc, 0);
}

static	void	ft_check_red(t_commands *cmd, int i)
{
	if (cmd->s_files[i]->type == 'E')
	{
		ft_print_err(cmd->s_files[i]->file);
		ft_print_err(": ambiguous redirect\n");
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		exit (1);
	}
	else if (cmd->s_files[i]->type == 'O')
		cmd->fd_out = ft_check_o(cmd, i);
	else if (cmd->s_files[i]->type == 'A')
		cmd->fd_out = ft_check_a(cmd, i);
	else if (cmd->s_files[i]->type == 'I')
		cmd->fd_in = ft_check_i(cmd, i);
}

void	ft_check_o_a_i_and_dup(t_commands *cmd)
{
	int	i;

	i = 0;
	while (cmd->s_files[i])
	{
		ft_check_red(cmd, i);
		if (i < cmd->last_idx_out && cmd->fd_out != -1)
		{
			close(cmd->fd_out);
			cmd->fd_out = -1;
		}
		if (i < cmd->last_idx_in && cmd->fd_in != -1)
		{
			close(cmd->fd_in);
			cmd->fd_in = -1;
		}
		i++;
	}
	ft_dup_last_in_and_out(cmd);
}
