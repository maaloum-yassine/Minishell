/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:37:50 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 06:30:24 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_exec_shild(t_data *data, int **fd, int i, char **env)
{
	if (data->count_cmd == 1)
	{
		ft_check_redirection(data, i);
		if (data->s_cmd[i].command != NULL)
			ft_execute(data, i, env);
	}
	else if (i == 0 && data->count_cmd > 1)
	{
		ft_check_redirection(data, i);
		if (data->s_cmd[i].command != NULL)
			ft_exec_first_cmd_pipe(data, i, fd, env);
	}
	else if (i > 0 && i < (data->count_cmd - 1))
	{
		ft_check_redirection(data, i);
		if (data->s_cmd[i].command != NULL)
			ft_exec_middle_cmd_pipe(data, i, fd, env);
	}
	else if (i == (data->count_cmd - 1) && i != 0)
	{
		ft_check_redirection(data, i);
		if (data->s_cmd[i].command != NULL)
			ft_exec_last_cmd_pipe(data, i, fd, env);
	}
}

static void	ft_fork_and_exec(t_data *data, char **env,
	int **fd, pid_t *shild_pid)
{
	int	i;

	i = 0;
	while (i < data->count_cmd)
	{
		shild_pid[i] = fork();
		if (shild_pid[i] < 0)
		{
			ft_print_err("ERROR shild(fork)\n");
			exit(1);
		}
		else if (shild_pid[i] == 0)
		{
			ft_exec_shild(data, fd, i, env);
			exit(0);
		}
		else
		{
			ft_close_fd_parent(fd, data->count_cmd, i);
			close(data->s_cmd[i].fd_herdoc);
		}
		i++;
	}
}

static	void	ft_free_3(t_data *data, int **fd, pid_t	*shild_pid)
{
	int	i;

	i = -1;
	while (++i < data->count_cmd - 1)
		free (fd[i]);
	free (fd);
	free (shild_pid);
}

void	ft_exec_cmd(t_data *data, char **env)
{
	int		**fd;
	pid_t	*shild_pid;

	fd = NULL;
	shild_pid = NULL;
	data->x = 0;
	if (data->count_cmd > 1)
		fd = malloc((data->count_cmd - 1) * sizeof(int *));
	shild_pid = malloc(data->count_cmd * sizeof(pid_t));
	ft_initial_pipe(data->count_cmd, fd);
	if (ft_creat_herdoc(data) == 0)
	{
		if (data->count_cmd == 1 && data->s_cmd->s_files[0] == NULL)
			data->x = ft_check_builtins(data, 0);
		if (data->check_status == 0)
		{
			ft_fork_and_exec(data, env, fd, shild_pid);
			ft_wait(data, shild_pid);
		}
	}
	ft_free_3(data, fd, shild_pid);
}
