/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaghrous <yaghrous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:27:18 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/09/19 06:30:19 by yaghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H
# include "../minishell.h"

char	*ft_path_command(char *command, char *variable, t_env *s_env);
void	ft_exec_cmd(t_data *data, char **env);
void	ft_wait(t_data *s_data, pid_t *shild_pid);
void	ft_close_fd_shild(t_data *data, int **fd);
void	ft_close_fd_parent(int **fd, int count_cmd, int i);
void	ft_initial_pipe(int count_cmd, int **fd);
void	sig_handler(int signum);
int		ft_creat_herdoc(t_data *data);
void	ft_execute(t_data *data, int i, char **env);
void	ft_exec_first_cmd_pipe(t_data *data, int i, int **fd, char **env);
void	ft_exec_middle_cmd_pipe(t_data *data, int i, int **fd, char **env);
void	ft_exec_last_cmd_pipe(t_data *data, int i, int **fd, char **env);
void	ft_check_redirection(t_data *data, int i);
void	ft_putchar(char *s, int fd);
int		ft_check_o(t_commands *cmd, int i);
int		ft_check_a(t_commands *cmd, int i);
int		ft_check_i(t_commands *cmd, int i);
void	ft_dup2(int oldfd, int newfd);
int		ft_herdoc(t_commands *cmd, int i, t_data *data);
int		ft_last_idx_o(t_commands *cmd);
int		ft_last_idx_a(t_commands *cmd);
int		ft_last_idx_i(t_commands *cmd);
int		ft_last_idx_h(t_commands *cmd);
int		ft_last_idx_output(t_commands *cmd);
int		ft_last_idx_input(t_commands *cmd);
int		ft_check_h(t_commands *cmd, t_data *data);
void	ft_dup_last_in_and_out(t_commands *cmd);
void	ft_check_o_a_i_and_dup(t_commands *cmd);
int		ft_check_herdoc(t_commands *cmd, t_data *data);
void	ft_print_cmd_err(char *command, char *err);
char	*ft_env_value(char *variable, t_env *s_env);
void	ft_free_path(char	**env_path_2d, char	*slash_command);
#endif
