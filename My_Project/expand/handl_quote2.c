/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:36:39 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 00:23:24 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static	char	*ft_filter_file_her(char *str, char *check_h, char *check)
{
	int		i;
	char	quote;
	char	*new_str;

	new_str = NULL;
	i = 0;
	if (str[0] == '\'' || str[0] == '\"')
		*check_h = 'N';
	else
		*check_h = 'E';
	while (str[i])
	{
		ft_filter_str1(str, &new_str, &i, &quote);
		if (str[i] && str[i] != '\'' && str[i] != '\"')
			ft_copie_and_free(&new_str, str[i++]);
	}
	if (!new_str)
	{
		new_str = ft_strdup("");
		*check = 'N';
	}
	else
		*check = 'Y';
	return (new_str);
}

static	char	*ft_filter_file(char *str, char *check)
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
		new_str = ft_strdup("");
		*check = 'N';
	}
	else
		*check = 'Y';
	return (new_str);
}

void	ft_filter_s_file(t_data *s_dt, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (s_dt->s_cmd[*i].s_files[j])
	{
		tmp = s_dt->s_cmd[*i].s_files[j]->file;
		if (s_dt->s_cmd[*i].s_files[j]->type == 'H')
			s_dt->s_cmd[*i].s_files[j]->file
				= ft_filter_file_her(s_dt->s_cmd[*i].s_files[j]->file,
					&(s_dt->s_cmd[*i].s_files[j]->check_ex),
					&(s_dt->s_cmd[*i].s_files[j]->exist));
		else
		{
			s_dt->s_cmd[*i].s_files[j]->file
				= ft_filter_file(s_dt->s_cmd[*i].s_files[j]->file,
					&(s_dt->s_cmd[*i].s_files[j]->exist));
			s_dt->s_cmd[*i].s_files[j]->check_ex = ' ';
		}
		free (tmp);
		j++;
	}
}
