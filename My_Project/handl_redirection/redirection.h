/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:36:23 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/18 22:38:09 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../minishell.h"

char	**ft_update_cmd2(char **cmd, t_red *s_rd);
void	ft_distinct_red_and_fill2(char *new_cmd, char *cmd, int *i, int *j);
void	ft_distinct_red_and_fill(char *new_cmd, char *cmd, int *i, int *j);
void	ft_skip_and_fill_new_cmd(char *new_cmd, char *cmd, int *i, int *j);
t_files	**ft_fill_s_file(char *cmd, int *len_red);
#endif
