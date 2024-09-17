/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_redirection1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:14:45 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 01:37:40 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static	void	ft_new_len2(char *cmd, int *i, int *lenght)
{
	if (cmd[*i] == '<' || cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '<' || cmd[*i + 1] == '>')
		{
			(*i)++;
			(*lenght)++;
		}
		(*i)++;
		(*lenght) = (*lenght) + 4;
	}
	else if (cmd[*i])
	{
		(*i)++;
		(*lenght)++;
	}
}

static	int	ft_new_len(char *cmd)
{
	int		i;
	int		lenght;
	char	quote;

	lenght = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i++];
			lenght++;
			while (cmd[i])
			{
				if (cmd[i++] == quote)
				{
					lenght++;
					break ;
				}
				lenght++;
			}
		}
		ft_new_len2(cmd, &i, &lenght);
	}
	return (lenght);
}

static	char	*ft_add_space(char *cmd, int *len_red)
{
	char	*new_cmd;
	int		n_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	n_len = ft_new_len(cmd);
	new_cmd = malloc(n_len + 1);
	while (cmd[i])
	{
		ft_skip_and_fill_new_cmd(new_cmd, cmd, &i, &j);
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			ft_distinct_red_and_fill(new_cmd, cmd, &i, &j);
			(*len_red)++;
		}
		else if (cmd[i])
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

static	char	**ft_divide_cmd2(t_data *s_dt, char **cmd)
{
	int		i;
	char	*tmp;
	int		len_red;

	s_dt->s_red = NULL;
	i = 0;
	s_dt->s_red = malloc(sizeof(t_red));
	while (cmd[i])
	{
		len_red = 0;
		tmp = cmd[i];
		cmd[i] = ft_add_space(cmd[i], &len_red);
		free (tmp);
		s_dt->s_cmd[i].s_files = NULL;
		s_dt->s_cmd[i].s_files = ft_fill_s_file(cmd[i], &len_red);
		i++;
	}
	cmd = ft_update_cmd2(cmd, s_dt->s_red);
	free (s_dt->s_red);
	return (cmd);
}

char	**ft_handl_red(t_data *s_dt, char **cmd)
{
	char	**tmp;

	tmp = cmd;
	cmd = ft_divide_cmd2(s_dt, cmd);
	ft_free_split (tmp);
	return (cmd);
}
