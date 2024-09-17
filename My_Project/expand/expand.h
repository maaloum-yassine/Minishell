/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:14:13 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 02:11:43 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../minishell.h"

void	ft_copie_and_free(char **str, char c);
void	ft_initialize_s_expand(t_data *s_dt);
char	*ft_removed(char *args);
char	*ft_replace_value(t_env *s_env, char *old_val);
char	*ft_expand_dblquote(t_data *s_dt, char *str);
char	*ft_expand(t_data *s_dt, char *str);
void	ft_expand_status(t_data *s_dt);
void	ft_check_element(t_data *s_dt);
char	**ft_fill_arg(char **arg, t_data *s_dt, int index, char **cmd);
void	ft_update2(t_data *s_dt);
void	ft_skip_quotee(char *tmp, int *i);
void	ft_update_arg4(char **arg, char **new_str);
void	ft_filter(t_data *s_dt);
void	ft_filter_str1(char *str, char **new_str, int *i, char *quote);
void	ft_filter_s_file(t_data *s_dt, int *i);

#endif
