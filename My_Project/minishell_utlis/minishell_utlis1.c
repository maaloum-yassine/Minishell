/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utlis1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:39:05 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/17 05:21:54 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lenght(char *str)
{
	int	lenght;

	lenght = 0;
	while (str[lenght])
		lenght++;
	return (lenght);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	if (start >= ft_lenght(s))
		return (ft_strdup(""));
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		s2 = "";
	else if (!s1)
		s1 = "";
	str = malloc(sizeof(char) * ft_lenght(s1) + ft_lenght(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

static int	ft_size_arr(long long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n *= (-1);
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long long	nombre;
	int			lenght;
	char		*p;
	int			sizealloce;

	nombre = (long long)n;
	lenght = ft_size_arr(nombre);
	sizealloce = lenght + 1;
	p = malloc(sizealloce);
	if (!p)
		return (0);
	if (nombre < 0)
	{
		p[0] = '-';
		nombre *= -1;
	}
	while (nombre > 9)
	{
		p[--lenght] = nombre % 10 + '0';
		nombre = nombre / 10;
	}
	p[--lenght] = nombre + 48;
	p[sizealloce - 1] = '\0';
	return (p);
}
