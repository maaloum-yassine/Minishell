/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 05:15:07 by yaghrous          #+#    #+#             */
/*   Updated: 2023/09/19 05:15:07 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_pipe1(t_commands *cmd, int i, t_data *data, int fd)
{
	char	*ptr;

	ptr = NULL;
	ptr = ft_strdup(data->input);
	if (cmd->s_files[i]->check_ex == 'E')
	{
		ptr = ft_check_expand(data, ptr);
		if (ptr == NULL)
			ptr = ft_strdup("");
		ft_putchar(ptr, fd);
		free (ptr);
		ptr = NULL;
	}
	else
	{
		ft_putchar(data->input, fd);
		free(ptr);
		ptr = NULL;
	}
	write(fd, "\n", 1);
}

static	void	ft_herdoc_pipe(t_commands *cmd, int i, t_data *data, int *fd)
{
	data->check = 1;
	data->s_xpd = malloc(sizeof(t_xpand));
	signal (SIGINT, sig_handler);
	while (1)
	{
		data->input = readline(">");
		if ((data->input == NULL)
			|| (ft_strcmp(data->input, cmd->s_files[i]->file) == 0))
		{
			free (data->input);
			close(fd[1]);
			close(fd[0]);
			break ;
		}
		ft_pipe1(cmd, i, data, fd[1]);
		free(data->input);
	}
	free (data->s_xpd);
}

int	ft_herdoc(t_commands *cmd, int i, t_data *data)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_herdoc_pipe(cmd, i, data, fd);
		exit(0);
	}
	else
		close(fd[1]);
	waitpid(pid, &status, 0);
	if (status != 0)
		return (-2);
	return (fd[0]);
}

int	ft_check_h(t_commands *cmd, t_data *data)
{
	int	i;
	int	last_idx_h;

	i = 0;
	last_idx_h = ft_last_idx_h(cmd);
	while (cmd->s_files[i])
	{
		if (cmd->s_files[i]->type == 'H')
		{
			cmd->fd_herdoc = ft_herdoc(cmd, i, data);
			if (cmd->fd_herdoc == -2)
				return (-2);
			if (i < cmd->last_idx_in && cmd->fd_herdoc != -1)
			{
				close(cmd->fd_herdoc);
				cmd->fd_herdoc = -1;
			}
		}
		if (last_idx_h == i)
			break ;
		i++;
	}
	return (cmd->fd_herdoc);
}

int	ft_check_herdoc(t_commands *cmd, t_data *data)
{
	cmd->fd_herdoc = -1;
	cmd->fd_out = -1;
	cmd->fd_in = -1;
	cmd->last_idx_out = ft_last_idx_output(cmd);
	cmd->last_idx_in = ft_last_idx_input(cmd);
	cmd->fd_herdoc = ft_check_h(cmd, data);
	if (cmd->fd_herdoc == -2)
		return (-2);
	return (0);
}
