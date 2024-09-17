/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 06:20:37 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 16:27:00 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static	void	ft_skip_quote(char *args, int *i, int *lenght)
{
	char	quote;

	if (args[*i] == '\'' || args[*i] == '\"')
	{
		quote = args[(*i)++];
		(*lenght)++;
		while (args[*i])
		{
			if (args[*i] == quote)
				break ;
			if (quote == '\"' && args[*i] == '$' && args[*i + 1] == '$')
				(*i) += 2;
			else
			{
				(*i)++;
				(*lenght)++;
			}
		}
	}
}

static	int	ft_lenght_arg(char *args)
{
	int		lenght;
	int		i;

	i = 0;
	lenght = 0;
	while (args[i])
	{
		ft_skip_quote(args, &i, &lenght);
		if (args[i] == '$' && args[i + 1]
			&& (args[i + 1] == '\'' || args[i + 1] == '\"'))
			i++;
		else if (args[i] == '$' && args[i + 1] == '$')
			i += 2;
		else
		{
			i++;
			lenght++;
		}
	}
	return (lenght);
}

static	void	ft_skip_and_fill(char **tmp, char *args, int *i, int *j)
{
	char	quote;

	if (args[*i] == '\'' || args[*i] == '\"')
	{
		quote = args[(*i)++];
		(*tmp)[(*j)++] = quote;
		while (args[(*i)])
		{
			if (args[*i] == quote)
				break ;
			if (quote == '\"' && args[*i] == '$' && args[*i + 1] == '$')
				(*i) += 2;
			else
				(*tmp)[(*j)++] = args[(*i)++];
		}
	}
}

char	*ft_removed(char *args)
{
	int		lenght;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lenght = ft_lenght_arg(args);
	tmp = malloc(lenght + 1);
	while (args[i])
	{
		ft_skip_and_fill(&tmp, args, &i, &j);
		if ((args[i] == '$' && args[i + 1])
			&& (args[i + 1] == '\'' || args[i + 1] == '\"'))
			i++;
		else if (args[i] == '$' && args[i + 1] == '$')
			i += 2;
		else
			tmp[j++] = args[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}
