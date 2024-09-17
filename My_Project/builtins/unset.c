/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 05:25:04 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:14:14 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_print_err_unset(t_data *s_data, char *str)
{
	ft_print_err("bash: unset: `");
	ft_print_err(str);
	ft_print_err("': not a valid identifier\n");
	s_data->check_status ++;
	g_exit_status = 1;
}

static	void	ft_remove_list(t_env **s_env, int pos)
{
	int		i;
	t_env	*current;
	t_env	*tmp;

	tmp = *s_env;
	current = *s_env;
	i = 1;
	while (current->next)
	{
		if (pos == i)
		{
			tmp = current->next;
			current->next = current->next->next;
			free (tmp->variable);
			free (tmp->value);
			free (tmp);
			break ;
		}
		else
		{
			i++;
			current = current->next;
		}
	}
}

static	void	ft_remove(t_env **s_env, int pos)
{
	t_env	*tmp;

	tmp = *s_env;
	if (pos == 0)
	{
		*s_env = (*s_env)->next;
		free (tmp);
	}
	else
		ft_remove_list(s_env, pos);
}

static	int	ft_find_pos(t_env *s_env, char *arg)
{
	int	pos;

	pos = 0;
	while (s_env)
	{
		if (ft_strcmp(s_env->variable, arg) == 0)
			return (pos);
		s_env = s_env->next;
		pos++;
	}
	return (-1);
}

void	ft_unset(t_data *s_data)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	if (s_data->s_cmd->args[i] && ft_identifier(s_data->s_cmd->args[i]) == 0)
		ft_print_err_unset(s_data, s_data->s_cmd->args[i]);
	else
	{
		while (s_data->s_cmd->args[i])
		{
			pos = ft_find_pos(s_data->s_env, s_data->s_cmd->args[i++]);
			if (pos != -1)
				ft_remove(&(s_data->s_env), pos);
		}
	}
}
