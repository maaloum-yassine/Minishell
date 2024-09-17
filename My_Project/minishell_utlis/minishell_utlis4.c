/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utlis4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 04:17:43 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/17 05:22:35 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9' ) || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalpha(int n)
{
	if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z'))
		return (1);
	return (0);
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == ((char)c))
			return ((char *)s);
		s++;
	}
	if (((char)c) == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	char	*tmp;
	int		i;
	int		len;

	if (!s1 || !set || s1[0] == '\0')
		return (NULL);
	len = ft_lenght(s1);
	i = 0;
	tmp = (char *)set;
	while (s1[i] && ft_strchr(tmp, s1[i]) != NULL )
	{
		tmp = set;
		i++;
	}
	tmp = set;
	while (len > 0 && ft_strchr(tmp, s1[len -1]) != NULL)
	{
		tmp = set;
		len --;
	}
	str = ft_substr(s1, i, len - i);
	return (str);
}
