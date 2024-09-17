/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:26:54 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 22:37:39 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i])
	{
		if (str[i++] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(char **str)
{
	int		i;
	char	check;

	i = 1;
	check = 0;
	while (str[i])
	{
		if (ft_check_arg(str[i]) == 1)
		{
			check = 1;
			i++;
		}
		else
			break ;
	}
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (check == 0)
		printf("\n");
}
