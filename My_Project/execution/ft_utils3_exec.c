/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:52:34 by yaghrous          #+#    #+#             */
/*   Updated: 2023/09/19 05:51:40 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_print_cmd_err(char *command, char *err)
{
	char	*command_error;

	command_error = ft_strjoin(command, err);
	ft_print_err(command_error);
	free(command_error);
}

char	*ft_env_value(char *variable, t_env *s_env)
{
	char	*str;

	while (s_env)
	{
		if (ft_strcmp(variable, s_env->variable) == 0)
		{
			str = ft_strdup(s_env->value);
			return (str);
		}
		s_env = s_env->next;
	}
	return (NULL);
}

void	ft_free_path(char	**env_path_2d, char	*slash_command)
{
	ft_free_split(env_path_2d);
	free(slash_command);
}
