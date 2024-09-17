/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 08:35:16 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/18 23:25:10 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_initialize_s_ex(t_export *s_ex, char **args)
{
	s_ex->var = NULL;
	s_ex->value = NULL;
	s_ex->tmp = NULL;
	s_ex->args = args;
}

static	void	ft_print_export(t_env *s_env)
{
	t_env	*head;

	head = s_env;
	while (head)
	{
		if (head->status == 1)
			printf("declare -x %s=\"%s\"\n", head->variable, head->value);
		head = head->next;
	}
	head = s_env;
	while (head)
	{
		if (head->status == 0)
			printf("declare -x %s=\"\"\n", head->variable);
		head = head->next;
	}
	head = s_env;
	while (head)
	{
		if (head->status == -1)
			printf("declare -x %s\n", head->variable);
		head = head->next;
	}
}

int	ft_index_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static	void	ft_handl_export(t_export s_ex, t_data *s_data, int *i)
{
	if (ft_identifier(s_ex.tmp) == 0)
		ft_print_err_exp(s_data, s_ex.args[*i]);
	else if (s_ex.check_equal == 0)
	{
		s_ex.var = ft_substr(s_ex.args[*i], 0, s_ex.len_arg);
		ft_add_to_env(s_ex, s_data, -1);
	}
	else if (s_ex.len_arg - 1 == s_ex.index_equal)
	{
		s_ex.var = ft_substr(s_ex.args[*i], 0, s_ex.check_equal);
		s_ex.value = ft_strdup("");
		ft_add_to_env(s_ex, s_data, 0);
	}
	else if (s_ex.check_equal)
	{
		s_ex.var = ft_substr(s_ex.args[*i], 0, s_ex.check_equal);
		s_ex.value = ft_substr(s_ex.args[*i],
				s_ex.check_equal + 1, s_ex.len_arg - (s_ex.check_equal + 1));
		ft_add_to_env(s_ex, s_data, 1);
	}
	ft_free_exp(s_ex);
}

void	ft_export(t_data *s_data, int index)
{
	t_export	s_ex;
	int			i;

	i = 1;
	ft_initialize_s_ex(&(s_ex), s_data->s_cmd[index].args);
	if (!s_ex.args[i])
		ft_print_export(s_data->s_env);
	else if (s_ex.args[i])
	{
		while (s_ex.args[i])
		{
			s_ex.len_arg = ft_lenght(s_ex.args[i]);
			s_ex.index_equal = ft_index_equal(s_ex.args[i]);
			s_ex.tmp = ft_substr(s_ex.args[i], 0, s_ex.index_equal);
			s_ex.check_equal = ft_search_equal(s_ex.args[i]);
			ft_handl_export(s_ex, s_data, &i);
			i++;
		}
	}
}
