/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 07:56:44 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 03:28:27 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static	char	*ft_copie_car(char *str, char c)
{
	int		lenght;
	char	*new_str;
	int		i;

	i = 0;
	if (!str)
		str = "";
	lenght = ft_lenght(str) +1;
	new_str = malloc(lenght + 1);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}

void	ft_copie_and_free(char **str, char c)
{
	char	*tmp;

	tmp = NULL;
	tmp = *str;
	*str = ft_copie_car(*str, c);
	free (tmp);
}

void	ft_initialize_s_expand(t_data *s_dt)
{
	s_dt->s_xpd->i = 0;
	s_dt->s_xpd->new_str = NULL;
	s_dt->s_xpd->tmp = NULL;
	s_dt->s_xpd->var = NULL;
}

char	*ft_replace_value(t_env *s_env, char *old_val)
{
	char	*new_value;

	new_value = NULL;
	while (s_env)
	{
		if (s_env->status == 1 && ft_strcmp(s_env->variable, old_val) == 0)
		{
			new_value = ft_strdup(s_env->value);
			return (new_value);
		}
		s_env = s_env->next;
	}
	return (new_value);
}

char	*ft_exist_value(t_env *s_env, char *old_val)
{
	char	*new_value;

	new_value = NULL;
	while (s_env)
	{
		if (s_env->status == 1 && ft_strcmp(s_env->variable, old_val) == 0)
		{
			new_value = ft_strdup(s_env->value);
			return (new_value);
		}
		s_env = s_env->next;
	}
	return (new_value);
}
