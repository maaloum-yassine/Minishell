/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:18:47 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 00:26:02 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_append_to_list(t_env *head, char *env, char status)
{
	int		i;
	t_env	*current;

	i = ft_index_equal(env);
	current = head;
	if (!current)
	{
		current = (t_env *) malloc(sizeof(t_env));
		current->variable = ft_substr(env, 0, i);
		current->value = ft_substr(env, i + 1, ft_lenght(env));
		current->status = status;
		current->next = NULL;
		return (current);
	}
	while (current->next != NULL)
		current = current->next;
	current->next = (t_env *) malloc(sizeof(t_env));
	current->next->variable = ft_substr(env, 0, i);
	current->next->value = ft_substr(env, i + 1, ft_lenght(env) - (i + 1));
	current->next->status = status;
	current->next->next = NULL;
	return (head);
}

void	ft_fill_env(t_env **head, char **env)
{
	int		i;

	i = 0;
	while (env[i])
		*head = ft_append_to_list(*head, env[i++], 1);
}
