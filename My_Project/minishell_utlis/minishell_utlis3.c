/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utlis3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:02:39 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/17 05:22:20 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;
	int		length;

	if (!s1)
		return (NULL);
	length = ft_lenght(s1);
	i = 0;
	str = malloc(sizeof(char) * length + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_search_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_free_list(t_env	*s_env)
{
	t_env	*tmp;

	while (s_env)
	{
		tmp = s_env;
		free (s_env->variable);
		free (s_env->value);
		s_env = tmp->next;
		free(tmp);
	}
}
