/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:55:12 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/02 20:15:56 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_exp(t_export s_ex)
{
	if (s_ex.var)
		free (s_ex.var);
	if (s_ex.value)
		free (s_ex.value);
	if (s_ex.tmp)
		free (s_ex.tmp);
}

static	char	ft_check_middle_var(char *var)
{
	char	*tmp;

	tmp = var;
	while (*tmp)
	{
		if (ft_isalnum(*tmp) == 0 && *tmp != '_')
			return (0);
		tmp++;
	}
	return (1);
}

static	char	ft_check_id(char *var)
{
	while (*var && *var == '_')
		var++;
	return (ft_check_middle_var(var));
}

char	ft_identifier(char *var)
{
	if ((ft_isdigit(*var) == 1) || (ft_isalpha(*var) == 0 && *var != '_'))
		return (0);
	else if (*var == '_')
	{
		if (ft_check_id(var) == 0)
			return (0);
	}
	else if (ft_check_middle_var(var) == 0)
		return (0);
	return (1);
}
