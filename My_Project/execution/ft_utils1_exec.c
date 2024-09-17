/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:40:06 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 06:30:41 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_wait(t_data *s_data, pid_t *shild_pid)
{
	int	i;
	int	status;

	i = -1;
	while (++i < s_data->count_cmd)
	{
		waitpid(shild_pid[i], &status, 0);
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		else if (WIFEXITED(status) && status != 0)
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 0;
	}
}

void	ft_close_fd_shild(t_data *data, int **fd)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	ft_close_fd_parent(int **fd, int count_cmd, int i)
{
	if (count_cmd > 1 && i > 0)
	{
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
}

void	ft_initial_pipe(int count_cmd, int **fd)
{
	int	i;

	i = 0;
	while (i < count_cmd - 1)
	{
		fd[i] = malloc(2 * sizeof(int));
		if (pipe(fd[i]) < 0)
		{
			ft_print_err("error pipe");
			exit(1);
		}
		i++;
	}
}

int	ft_creat_herdoc(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count_cmd)
	{
		if (ft_check_herdoc(&data->s_cmd[i], data) == -2)
		{
			g_exit_status = 1;
			return (1);
		}
	}
	return (0);
}
