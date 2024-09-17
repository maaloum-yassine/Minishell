/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:34:24 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:33:06 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_expand_status(t_data *s_dt)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(g_exit_status);
	while (str[i])
		ft_copie_and_free(&(s_dt->s_xpd->var), str[i++]);
	free (str);
}

static	void	ft_expand_value2(t_data *s_dt, char *s)
{
	char	*tmp;

	tmp = NULL;
	if ((ft_isalpha(s[s_dt->s_xpd->i]) == 1 || s[s_dt->s_xpd->i] == '_'))
	{
		while (ft_isalnum(s[s_dt->s_xpd->i]) == 1 || s[s_dt->s_xpd->i] == '_')
			ft_copie_and_free(&(s_dt->s_xpd->var), s[s_dt->s_xpd->i++]);
		tmp = s_dt->s_xpd->var;
		s_dt->s_xpd->var = ft_replace_value(s_dt->s_env, s_dt->s_xpd->var);
		free (tmp);
	}
	else if (s[s_dt->s_xpd->i] == '?')
	{
		s_dt->s_xpd->i++;
		ft_expand_status(s_dt);
	}
	else if (ft_isalpha(s[s_dt->s_xpd->i]) == 0)
	{
		s_dt->s_xpd->i++;
		while ((ft_isalnum(s[s_dt->s_xpd->i]) == 1 || s[s_dt->s_xpd->i] == '_'))
			ft_copie_and_free(&(s_dt->s_xpd->var), s[s_dt->s_xpd->i++]);
	}
}

static	void	ft_expand_value(t_data *s_dt, char *s)
{
	char	*tmp;

	tmp = NULL;
	s_dt->s_xpd->i++;
	ft_expand_value2(s_dt, s);
	tmp = s_dt->s_xpd->new_str;
	s_dt->s_xpd->new_str
		= ft_strjoin(s_dt->s_xpd->new_str, s_dt->s_xpd->var);
	free (tmp);
	free (s_dt->s_xpd->var);
	s_dt->s_xpd->var = NULL;
	tmp = NULL;
}

static	void	ft_skip_skip_quote(t_data *s_dt, char *str)
{
	char	quote;

	quote = str[s_dt->s_xpd->i];
	ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i]);
	s_dt->s_xpd->i++;
	while (str[s_dt->s_xpd->i])
	{
		if (str[s_dt->s_xpd->i] == quote)
			break ;
		ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i]);
		s_dt->s_xpd->i++;
	}
	ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i++]);
}

char	*ft_expand(t_data *s_dt, char *str)
{
	ft_initialize_s_expand(s_dt);
	while (str[s_dt->s_xpd->i])
	{
		if (str[s_dt->s_xpd->i] == '\'' || str[s_dt->s_xpd->i] == '\"')
			ft_skip_skip_quote(s_dt, str);
		else if (str[s_dt->s_xpd->i] == '$' && str[s_dt->s_xpd->i + 1])
			ft_expand_value(s_dt, str);
		else
			ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i++]);
	}
	return (s_dt->s_xpd->new_str);
}
