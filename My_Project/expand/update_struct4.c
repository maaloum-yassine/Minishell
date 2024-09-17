/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_struct4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 02:08:29 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:12:50 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_skip_quotee(char *tmp, int *i)
{
	char	quote;

	if (tmp[*i] == '\'' || tmp[*i] == '\"')
	{
		quote = tmp[(*i)++];
		while (tmp[*i])
		{
			if (tmp[(*i)++] == quote)
				break ;
		}
	}
}
