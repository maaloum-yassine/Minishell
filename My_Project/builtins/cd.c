/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:30:44 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 00:15:45 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_print_err_cd(t_data *s_data, char *path, char x)
{
	if (x == 1)
	{
		ft_print_err("bash: cd: ");
		ft_print_err(path);
		ft_print_err(": No such file or directory\n");
	}
	else
		ft_print_err(path);
	s_data->check_status++;
	g_exit_status = 1;
}

static	void	ft_change_env(t_env *s_env, char *old_path)
{
	char	check;

	check = 0;
	while (s_env)
	{
		if (ft_strcmp(s_env->variable, "PWD") == 0)
		{
			free (s_env->value);
			s_env->value = getcwd(NULL, 0);
			check++;
		}
		if (ft_strcmp(s_env->variable, "OLDPWD") == 0)
		{
			free (s_env->value);
			s_env->value = ft_strdup(old_path);
			check++;
		}
		if (check == 2)
			break ;
		s_env = s_env->next;
	}
}

static	char	ft_home_env(t_env *s_env)
{
	while (s_env)
	{
		if (ft_strcmp(s_env->variable, "HOME") == 0)
		{
			if (chdir(s_env->value) == -1)
				return (0);
			return (1);
		}
		s_env = s_env->next;
	}
	return (0);
}

void	ft_cd(t_data *s_data)
{
	char	*path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	path = s_data->s_cmd->args[1];
	if (!path)
	{
		if (ft_home_env(s_data->s_env) == 0)
		{
			ft_print_err_cd(s_data, "bash: cd: HOME not set\n", 2);
			free (old_path);
			return ;
		}
		s_data->check = 1;
	}
	else if (ft_strcmp(path, "~") == 0)
		path = getenv("HOME");
	if (s_data->check == 0)
	{
		if (chdir(path) == -1)
			ft_print_err_cd(s_data, path, 1);
		s_data->check = 0;
	}
	ft_change_env(s_data->s_env, old_path);
	free (old_path);
}
