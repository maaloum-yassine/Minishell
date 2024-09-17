/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utlis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 01:07:10 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/18 06:58:58 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free (str);
}

static	void	ft_skip_quote(char *str, int *i)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[*i];
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == quote)
				break ;
			(*i)++;
		}
	}
}

int	ft_count_w(char *str, char sep1, char sep2)
{
	int	lenght_word;
	int	check;
	int	i;

	i = 0;
	lenght_word = 0;
	check = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == sep1 || str[i] == sep2))
			i++;
		while (str[i] && (str[i] != sep1 && str[i] != sep2))
		{
			ft_skip_quote(str, &i);
			i++;
			check = 1;
		}
		if (check == 1)
		{
			check = 0;
			lenght_word++;
		}
	}
	return (lenght_word);
}

static	void	ft_skipp_quote(char *str, int *j, char sep1, char sep2)
{
	while (str[*j] != sep1 && str[*j] != sep2 && str[*j])
	{
		ft_skip_quote(str, j);
		(*j)++;
	}
}

char	**ft_split(char *str, char sep1, char sep2)
{
	char	**s;
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	if ((ft_count_w(str, sep1, sep2) + 1) == 1)
		return (NULL);
	s = malloc (sizeof(char *) * (ft_count_w(str, sep1, sep2) + 1));
	while (str[i])
	{
		while ((str[j] == sep1 || str[j] == sep2) && str[j])
			j++;
		i = j;
		ft_skipp_quote(str, &j, sep1, sep2);
		if (i != j)
			s[index++] = ft_substr(str, i, j - i);
	}
	s[index] = NULL;
	return (s);
}
