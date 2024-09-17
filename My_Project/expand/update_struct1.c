/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_struct1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:33:05 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:12:33 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static	char	ft_check2(t_data *s_dt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			if (s_dt->s_cmd[i].command[0] == '\0')
				return (1);
			j = 0;
			while (s_dt->s_cmd[i].args[j])
			{
				if (s_dt->s_cmd[i].args[j][0] == '\0')
					return (1);
				j++;
			}
		}
	}
	return (0);
}

static	int	ft_check_len_space(char *tmp)
{
	char	*tmp2;
	int		i;

	i = 0;
	tmp2 = ft_strtrim(tmp, " \t");
	if (tmp2)
	{
		while (tmp2[i])
		{
			ft_skip_quotee(tmp, &i);
			if (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
			{
				free (tmp2);
				return (i);
			}
			i++;
		}
	}
	free (tmp2);
	return (-1);
}

static	char	**ft_update_cmd(char **cmd, t_data *s_dt, int index)
{
	char	*tmp;
	char	**str2;
	int		i;

	str2 = NULL;
	i = ft_check_len_space(*cmd);
	if (i != -1)
	{
		tmp = *cmd;
		*cmd = ft_substr(*cmd, 0, ft_check_len_space(*cmd));
		tmp += i;
		str2 = ft_split(tmp, ' ', '\t');
		free (tmp -= i);
	}
	return (ft_fill_arg(str2, s_dt, index, cmd));
}

static	int	ft_check1(t_data *s_dt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < s_dt->count_cmd)
	{
		if (s_dt->s_cmd[i].command)
		{
			if (ft_check_len_space(s_dt->s_cmd[i].command) != -1)
				return (1);
			j = 0;
			while (s_dt->s_cmd[i].args[j])
			{
				if (ft_check_len_space(s_dt->s_cmd[i].args[j++]) != -1)
					return (1);
			}
		}
	}
	return (0);
}

void	ft_check_element(t_data *s_dt)
{
	int		i;

	i = -1;
	if (ft_check1(s_dt) == 1)
	{
		while (++i < s_dt->count_cmd)
			s_dt->s_cmd[i].args
				= ft_update_cmd(&(s_dt->s_cmd[i].command), s_dt, i);
	}
	if (ft_check2(s_dt) == 1)
		ft_update2(s_dt);
}
