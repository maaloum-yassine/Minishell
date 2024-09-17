/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1_redirecrtion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:40:09 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 05:24:08 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_putchar(char *s, int fd)
{
	write(fd, s, ft_lenght(s));
}

int	ft_check_o(t_commands *cmd, int i)
{
	int	fd;

	if (access(cmd->s_files[i]->file, F_OK) == 0)
	{
		if (access(cmd->s_files[i]->file, W_OK) < 0)
		{
			write(2, cmd->s_files[i]->file, ft_lenght(cmd->s_files[i]->file));
			write(2, ": Permission denied\n", 20);
			exit(1);
		}
		else
			fd = open((cmd->s_files[i]->file), 
					O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else
		fd = open((cmd->s_files[i]->file), O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	ft_check_a(t_commands *cmd, int i)
{
	int	fd;

	if (access(cmd->s_files[i]->file, F_OK) == 0)
	{
		if (access(cmd->s_files[i]->file, W_OK) < 0)
		{
			write(2, cmd->s_files[i]->file, ft_lenght(cmd->s_files[i]->file));
			write(2, ": Permission denied\n", 20);
			exit(1);
		}
		else
			fd = open((cmd->s_files[i]->file), 
					O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else
		fd = open((cmd->s_files[i]->file), O_RDWR | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	ft_check_i(t_commands *cmd, int i)
{
	int	fd;

	if (access(cmd->s_files[i]->file, F_OK) == 0)
	{
		if (access(cmd->s_files[i]->file, R_OK) < 0)
		{
			write(2, cmd->s_files[i]->file, ft_lenght(cmd->s_files[i]->file));
			write(2, ": Permission denied\n", 20);
			exit(1);
		}
		else
			fd = open((cmd->s_files[i]->file), O_RDONLY);
	}
	else
	{
		write(2, cmd->s_files[i]->file, ft_lenght(cmd->s_files[i]->file));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	return (fd);
}

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		write(2, "error dup2\n", 11);
		exit(1);
	}
	close(oldfd);
}
