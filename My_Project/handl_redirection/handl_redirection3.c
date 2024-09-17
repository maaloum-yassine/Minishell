/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_redirection3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:20 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/15 01:37:30 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static	void	ft_fill_s_file_null(t_files **s_files)
{
	s_files = malloc(sizeof(t_files *));
	s_files[0] = malloc(sizeof(t_files));
	s_files[0] = NULL;
}

static	void	ft_fill_s_file2(t_files **s_files, char **new_cmd,
								int *i, int *x)
{
	while (new_cmd[*i])
	{
		if (new_cmd[*i][0] == 1)
		{
			s_files[*x]->type = 'I';
			s_files[(*x)++]->file = ft_strdup(new_cmd[*i + 1]);
		}
		else if (new_cmd[*i][0] == 2)
		{
			s_files[*x]->type = 'A';
			s_files[(*x)++]->file = ft_strdup(new_cmd[*i + 1]);
		}
		else if (new_cmd[*i][0] == 3)
		{
			s_files[*x]->type = 'O';
			s_files[(*x)++]->file = ft_strdup(new_cmd[*i + 1]);
		}
		else if (new_cmd[*i][0] == 4)
		{
			s_files[*x]->type = 'H';
			s_files[(*x)++]->file = ft_strdup(new_cmd[*i + 1]);
		}
		(*i)++;
	}
}

t_files	**ft_fill_s_file(char *cmd, int *len_red)
{
	char	**new_cmd;
	t_files	**s_files;
	int		i;
	int		x;

	new_cmd = NULL;
	s_files = NULL;
	if (len_red != 0)
	{
		s_files = malloc(sizeof(t_files *) * (*len_red + 1));
		new_cmd = ft_split(cmd, ' ', '\t');
		i = 0;
		while (i < *len_red)
			s_files[i++] = malloc(sizeof(t_files) * *len_red);
		s_files[i] = NULL;
		i = 0;
		x = 0;
		ft_fill_s_file2(s_files, new_cmd, &i, &x);
		ft_free_split(new_cmd);
	}
	else
		ft_fill_s_file_null(s_files);
	return (s_files);
}
