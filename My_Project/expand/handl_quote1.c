/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quote1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:36:18 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/18 04:51:54 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_filter_str1(char *str, char **new_str, int *i, char *quote)
{
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		*quote = str[(*i)++];
		while (str[*i])
		{
			if (str[*i] == *quote)
			{
				(*i)++;
				break ;
			}
			else
				ft_copie_and_free(new_str, str[(*i)++]);
		}
	}
}

static	char	*ft_filter_str(char *str)
{
	int		i;
	char	quote;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[i])
	{
		ft_filter_str1(str, &new_str, &i, &quote);
		if (str[i] && str[i] != '\'' && str[i] != '\"')
			ft_copie_and_free(&new_str, str[i++]);
	}
	if (!new_str)
	{
		if (quote == '\'')
			new_str = ft_strdup("''");
		else
			new_str = ft_strdup("\"\"");
	}
	return (new_str);
}

void	ft_filter(t_data *s_dt)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			tmp = s_dt->s_cmd[i].command;
			s_dt->s_cmd[i].command = ft_filter_str(s_dt->s_cmd[i].command);
			free (tmp);
			j = 0;
			while (s_dt->s_cmd[i].args[j])
			{
				tmp = s_dt->s_cmd[i].args[j];
				s_dt->s_cmd[i].args[j] = ft_filter_str(s_dt->s_cmd[i].args[j]);
				free (tmp);
				j++;
			}
		}
		ft_filter_s_file(s_dt, &i);
	}
}
