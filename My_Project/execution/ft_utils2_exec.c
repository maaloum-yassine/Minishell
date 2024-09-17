/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:40:11 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 05:22:43 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_execute(t_data *data, int i, char **env)
{
	char	*path_command;

	if (data->x == 0)
	{
		if (ft_check_builtins(data, i) == 0)
		{
			path_command = ft_path_command(data->s_cmd[i].command,
					"PATH", data->s_env);
			if (execve(path_command, data->s_cmd[i].args, env) < 0)
			{
				free(path_command);
				ft_print_err(path_command);
				ft_print_err(": is a directory\n");
				exit(126);
			}
			free(path_command);
			path_command = NULL;
		}
	}
}

void	ft_exec_first_cmd_pipe(t_data *data, int i, int **fd, char **env)
{
	if (data->s_cmd[i].fd_out == -1)
	{
		if (dup2(fd[i][1], 1) < 0)
		{
			ft_print_err("ERROR dup2\n");
			exit(1);
		}
	}
	ft_close_fd_shild(data, fd);
	ft_execute(data, i, env);
}

void	ft_exec_middle_cmd_pipe(t_data *data, int i, int **fd, char **env)
{
	if (data->s_cmd[i].fd_in == -1 && data->s_cmd[i].fd_herdoc == -1)
	{
		if (dup2(fd[i - 1][0], 0) < 0)
		{
			ft_print_err("ERROR dup2");
			exit(1);
		}
	}
	if (data->s_cmd[i].fd_out == -1)
	{
		if (dup2(fd[i][1], 1) < 0)
		{
			ft_print_err("ERROR dup2");
			exit(1);
		}
	}
	ft_close_fd_shild(data, fd);
	ft_execute(data, i, env);
}

void	ft_exec_last_cmd_pipe(t_data *data, int i, int **fd, char **env)
{
	if (data->s_cmd[i].fd_in == -1 && data->s_cmd[i].fd_herdoc == -1)
	{
		if (dup2(fd[i - 1][0], 0) < 0)
		{
			ft_print_err("ERROR dup2");
			exit(1);
		}
	}
	ft_close_fd_shild(data, fd);
	ft_execute(data, i, env);
}

void	ft_check_redirection(t_data *data, int i)
{
	if (data->s_cmd[i].s_files[0] != NULL)
		ft_check_o_a_i_and_dup(&data->s_cmd[i]);
}
