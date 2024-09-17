/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 05:25:17 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 06:31:16 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_err_exit(char *str)
{
	write(2, "exit\n", 5);
	write(2, "bash: exit: ", 12);
	ft_print_err(str);
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

static int	ft_check_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i])
	{
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

unsigned long long int	ft_atoi(char *str)
{
	int						i;
	int						s;
	unsigned long long int	nb;

	i = 0;
	nb = 0;
	s = 1;
	if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - 48;
		i++;
	}
	return (s * nb);
}

static void	ft_check_max_and_min(char *str)
{
	int						i;
	int						s;
	unsigned long long int	nb;
	unsigned long long int	long_max;

	i = 0;
	nb = 0;
	s = 1;
	long_max = LONG_MAX;
	if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		nb *= 10;
		nb += str[i] - 48;
		if ((nb > LONG_MAX && s > 0) || ((nb > (long_max + 1)) && s < 0))
			ft_print_err_exit(str);
		i++;
	}
}

void	ft_exit(t_data *s_data, t_commands *s_cmd)
{
	int		i;
	char	check;

	check = 0;
	i = 1;
	while (s_cmd->args[i] != NULL)
	{
		if (i >= 2)
		{
			ft_print_err("exit: too many arguments\n");
			s_data->check_status++;
			g_exit_status = 1;
			return ;
		}
		if (ft_check_is_digit(s_cmd->args[i]) != 0)
			ft_print_err_exit(s_cmd->args[i]);
		ft_check_max_and_min(s_cmd->args[i]);
		i++;
		check++;
	}
	if (check != 0)
		exit ((unsigned char)ft_atoi(s_cmd->args[1]));
	exit(0);
}
