/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:38:58 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 06:30:29 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	char	**ft_env_path_2d(char *variable, t_env *s_env)
{
	char	*env_value;
	char	**env_path;

	env_value = ft_env_value(variable, s_env);
	env_path = ft_split(env_value, ':', ':');
	free(env_value);
	return (env_path);
}

int	ft_check_path(char *command)
{
	if (command[0] == '.' || command[0] == '/')
	{
		if (access(command, F_OK) == 0)
			return (1);
		else
		{
			ft_print_cmd_err(command, ": No such file or directory\n");
			exit(127);
		}
	}
	return (0);
}

static char	*ft_command(char *command, char *variable, t_env *s_env)
{
	char	*path_command;
	char	*slash_command;
	char	*str;
	char	*tmp;

	str = ft_env_value(variable, s_env);
	if (str == NULL)
	{
		tmp = getcwd(NULL, 0);
		slash_command = ft_strjoin("/", command);
		path_command = ft_strjoin(tmp, slash_command);
		if (access(path_command, F_OK) == 0)
		{
			free(tmp);
			free(slash_command);
			return (path_command);
		}
		free(tmp);
		free(slash_command);
		free(path_command);
		ft_print_cmd_err(command, ": No such file or directory\n");
		exit(127);
	}
	return (NULL);
}

static	void	ft_free_print(char **env_path_2d,
				char *slash_command, char *command)
{
	ft_free_split(env_path_2d);
	free(slash_command);
	ft_print_cmd_err(command, ": command not found\n");
	exit(127);
}

char	*ft_path_command(char *command, char *variable, t_env *s_env)
{
	char	**env_path_2d;
	char	*path_command;
	char	*slash_command;
	int		i;

	i = 0;
	if (ft_check_path(command) != 0)
		return (command);
	path_command = ft_command(command, variable, s_env);
	if (path_command != NULL)
		return (path_command);
	env_path_2d = ft_env_path_2d(variable, s_env);
	slash_command = ft_strjoin("/", command);
	while (env_path_2d[i])
	{
		path_command = ft_strjoin(env_path_2d[i++], slash_command);
		if (access(path_command, F_OK) == 0)
		{
			ft_free_path(env_path_2d, slash_command);
			return (path_command);
		}
		free(path_command);
	}
	ft_free_print(env_path_2d, slash_command, command);
	return (NULL);
}
