/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:20:19 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:47:55 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static	void	ft_expand_dbl_quote2(t_data *s_dt, char *s)
{
	char	*tmp;

	tmp = NULL;
	s_dt->s_xpd->i++;
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
	else if (ft_isalpha(s[s_dt->s_xpd->i]) == 0
		&& s[s_dt->s_xpd->i] != '\"' && s[s_dt->s_xpd->i] != '\'')
	{
		ft_copie_and_free(&(s_dt->s_xpd->var), s[s_dt->s_xpd->i - 1]);
		while ((ft_isalnum(s[s_dt->s_xpd->i]) == 1 || s[s_dt->s_xpd->i] == '_'))
			ft_copie_and_free(&(s_dt->s_xpd->var), s[s_dt->s_xpd->i++]);
	}
}

static void	ft_expand_dbl_quote(t_data *s_dt, char *s)
{
	char	*tmp;

	tmp = NULL;
	ft_copie_and_free(&(s_dt->s_xpd->new_str), s[s_dt->s_xpd->i++]);
	while (s[s_dt->s_xpd->i])
	{
		if (s[s_dt->s_xpd->i] == '$' && s[s_dt->s_xpd->i + 1] != '\"')
		{
			ft_expand_dbl_quote2(s_dt, s);
			tmp = s_dt->s_xpd->new_str;
			s_dt->s_xpd->new_str
				= ft_strjoin(s_dt->s_xpd->new_str, s_dt->s_xpd->var);
			free (tmp);
			free (s_dt->s_xpd->var);
			s_dt->s_xpd->var = NULL;
			tmp = NULL;
		}
		else if (s[s_dt->s_xpd->i] == '\"')
		{
			ft_copie_and_free(&(s_dt->s_xpd->new_str), s[s_dt->s_xpd->i++]);
			break ;
		}
		else
			ft_copie_and_free(&(s_dt->s_xpd->new_str), s[s_dt->s_xpd->i++]);
	}
}

static	void	ft_skip_single_quote(t_data *s_dt, char *str)
{
	if (str[s_dt->s_xpd->i] == '\'')
	{
		ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i]);
		s_dt->s_xpd->i++;
		while (str[s_dt->s_xpd->i])
		{
			if (str[s_dt->s_xpd->i] == '\'')
				break ;
			ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i]);
			s_dt->s_xpd->i++;
		}
		ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i++]);
	}
}

char	*ft_expand_dblquote(t_data *s_dt, char *str)
{
	ft_initialize_s_expand(s_dt);
	while (str[s_dt->s_xpd->i])
	{
		if (str[s_dt->s_xpd->i] == '\'')
			ft_skip_single_quote(s_dt, str);
		else if (str[s_dt->s_xpd->i] == '\"')
			ft_expand_dbl_quote(s_dt, str);
		else
			ft_copie_and_free(&(s_dt->s_xpd->new_str), str[s_dt->s_xpd->i++]);
	}
	return (s_dt->s_xpd->new_str);
}
