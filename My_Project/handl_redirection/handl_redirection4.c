/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_redirection4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:56:04 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 01:37:46 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static	char	ft_check_col(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] >= 1 && tmp[i][0] <= 4)
			i += 2;
		else
			return (0);
	}
	return (1);
}

static	void	ft_update_cmd__3(t_red *s_rd, int *j, int *x)
{
	while (s_rd->tmp[*j])
		(*j)++;
	if (ft_check_col(s_rd->tmp) == 1)
		s_rd->new_cmd[(*x)++] = ft_strdup("");
	else
	{
		*j = 0;
		while (s_rd->tmp[*j])
		{
			if (s_rd->tmp[*j][0] >= 1 && s_rd->tmp[*j][0] <= 4)
				(*j)++;
			else
			{
				s_rd->tmp1 = s_rd->new_cmd[*x];
				s_rd->new_cmd[*x]
					= ft_strjoin(s_rd->new_cmd[*x], s_rd->tmp[*j]);
				free (s_rd->tmp1);
				s_rd->tmp1 = s_rd->new_cmd[*x];
				s_rd->new_cmd[*x] = ft_strjoin(s_rd->new_cmd[*x], " ");
				free (s_rd->tmp1);
				s_rd->check = 1;
			}
			(*j)++;
		}
	}
}

static	int	ft_len_new_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static	void	ft_initialize_rd(char **cmd, t_red *s_rd)
{
	s_rd->tmp = NULL;
	s_rd->new_cmd = NULL;
	s_rd->tmp1 = NULL;
	s_rd->check = 0;
	s_rd->len = ft_len_new_cmd(cmd);
	s_rd->new_cmd = malloc(sizeof(char *) * (s_rd->len + 1));
}

char	**ft_update_cmd2(char **cmd, t_red *s_rd)
{
	int	i;
	int	j;
	int	x;

	ft_initialize_rd(cmd, s_rd);
	i = 0;
	j = 0;
	x = 0;
	while (i <= s_rd->len)
		s_rd->new_cmd[i++] = NULL;
	i = 0;
	while (cmd[i])
	{
		s_rd->tmp = ft_split(cmd[i], ' ', '\t');
		j = 0;
		ft_update_cmd__3(s_rd, &j, &x);
		ft_free_split(s_rd->tmp);
		i++;
		if (s_rd->check == 1)
		{
			x++;
			s_rd->check = 0;
		}
	}
	return (s_rd->new_cmd);
}
