/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 05:52:04 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 00:14:21 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_err_exp(t_data *s_data, char *str)
{
	ft_print_err("bash: export: `");
	ft_print_err(str);
	ft_print_err("': not a valid identifier\n");
	s_data->check_status++;
	g_exit_status = 1;
}

static	char	*ft_update_env(char *env_value, char *new_value)
{
	char	*tmp;

	tmp = env_value;
	env_value = ft_strdup(new_value);
	free (tmp);
	return (env_value);
}

static	int	ft_check_list(t_env *s_env, char *var, char *value, char status)
{
	while (s_env)
	{
		if (ft_strcmp(s_env->variable, var) == 0)
		{
			if (status == -1 || ((status == 1 && s_env->status == 1)
					&& (ft_strcmp(s_env->value, value) == 0)))
				return (0);
			else if ((status == 0
					&& (s_env->status == -1 || s_env->status == 1))
				|| (status == 1 && (s_env->status == 0 || s_env->status == -1)))
			{
				s_env->value = ft_update_env(s_env->value, value);
				s_env->status = status;
				return (0);
			}
			else if ((status == 1 && s_env->status == 1)
				&& (ft_strcmp(s_env->value, value) != 0))
			{
				s_env->value = ft_update_env(s_env->value, value);
				return (0);
			}
		}
		s_env = s_env->next;
	}
	return (1);
}

void	ft_add_to_env(t_export s_ex, t_data *s_data, char status)
{
	char	*tmp;

	tmp = NULL;
	if (ft_check_list(s_data->s_env, s_ex.var, s_ex.value, status) == 1)
	{
		if (status == 0 || status == -1)
		{
			tmp = ft_strjoin(s_ex.var, s_ex.value);
			s_data->s_env = ft_append_to_list(s_data->s_env, tmp, status);
		}
		else if (status == 1)
		{
			s_ex.var = ft_strjoin(s_ex.var, "=");
			tmp = ft_strjoin(s_ex.var, s_ex.value);
			s_data->s_env = ft_append_to_list(s_data->s_env, tmp, status);
			free (s_ex.var);
		}
		free (tmp);
	}
}
