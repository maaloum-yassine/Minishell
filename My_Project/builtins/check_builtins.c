/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:35:39 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:14:33 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

static	char	*ft_cmdto_lower(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (cmd);
}

static	int	ft_builtins_upper(t_data *s_data, int i)
{
	int	x;

	x = 0;
	if (ft_strcmp(s_data->s_cmd[i].command, "unset") == 0)
	{
		ft_unset(s_data);
		x++;
	}
	else if (ft_strcmp(s_data->s_cmd[i].command, "cd") == 0)
	{
		ft_cd(s_data);
		x++;
	}
	else if (ft_strcmp(s_data->s_cmd[i].command, "export") == 0)
	{
		ft_export(s_data, i);
		x++;
	}
	else if (ft_strcmp(s_data->s_cmd[i].command, "exit") == 0)
	{
		ft_exit(s_data, &s_data->s_cmd[i]);
		x++;
	}
	return (x);
}

static	void	ft_execute_bull(t_data *s_data, int *i, char *cmd, int *x)
{
	if (ft_strcmp(cmd, "echo") == 0)
	{
		ft_echo(s_data->s_cmd[*i].args);
		(*x)++;
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		ft_env(s_data, s_data->s_env);
		(*x)++;
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		ft_pwd();
		(*x)++;
	}
}

int	ft_check_builtins(t_data *s_data, int i)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	x = 0;
	if (s_data->s_cmd[i].command != NULL)
	{
		tmp = ft_strdup(s_data->s_cmd[i].command);
		tmp = ft_cmdto_lower(tmp);
		x = ft_builtins_upper(s_data, i);
		if (x != 0)
		{
			free (tmp);
			return (x);
		}
		ft_execute_bull(s_data, &i, tmp, &x);
		free (tmp);
	}
	return (x);
}
