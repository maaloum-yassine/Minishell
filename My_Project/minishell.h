/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:24:29 by ymaaloum          #+#    #+#             */
/*   Updated: 2024/09/17 06:07:36 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

int	g_exit_status;

typedef struct s_files
{
	char	*file;
	char	type;
	char	check_ex;
	char	exist;
}t_files;

typedef struct s_command
{
	t_files		**s_files;
	char		*command;
	char		**args;
	int			count_arg;
	int			fd_herdoc;
	int			fd_out;
	int			fd_in;
	int			last_idx_out;
	int			last_idx_in;
}t_commands;

typedef struct s_env
{
	struct s_env	*next;
	char			*variable;
	char			*value;
	char			status;
}	t_env;

typedef struct s_export
{
	char	**args;
	char	*var;
	char	*value;
	char	*tmp;
	int		len_arg;
	int		index_equal;
	int		check_equal;
}t_export;

typedef struct s_xpand
{
	char	*new_str;
	char	*var;
	char	*tmp;
	int		i;
}t_xpand;

typedef struct s_red
{
	char	**new_cmd;
	char	**tmp;
	char	*tmp1;
	int		len;
	char	check;
}t_red;

typedef struct s_data
{
	t_commands	*s_cmd;
	t_xpand		*s_xpd;
	t_env		*s_env;
	t_red		*s_red;
	char		*l_cmd;
	char		*input;
	char		*quote;
	int			x;
	int			count_cmd;
	int			check_status;
	char		check;
}t_data;

void	ft_free(t_data *s_data);
int		ft_lenght(char *str);
char	*ft_strtrim(char *s1, char *set);
void	ft_ctr_d(t_data *s_var);
void	ft_signal(void);
void	ft_print_err(char *err);
void	ft_check_syntax(t_data *s_var, char **env);
void	ft_check_redirection_pipe(t_data *s_var, int i);
char	*ft_substr(char *s, int start, int len);
int		ft_count_w(char *str, char sep1, char sep2);
char	**ft_split(char *str, char sep1, char sep2);
char	*ft_itoa(int n);
void	ft_free_split(char **str);
char	*ft_strdup(char *s1);
int		ft_search_equal(char *str);
void	ft_divide_cmd(t_data *s_var, char **env);
void	ft_fill_env(t_env **head, char **env);
int		ft_strcmp(char *s1, char *s2);
int		ft_check_builtins(t_data *s_data, int i);
void	ft_echo(char **str);
t_env	*ft_append_to_list(t_env *head, char *env, char status);
void	ft_env(t_data *s_data, t_env *s_env);
void	ft_pwd(void);
void	ft_unset(t_data *s_data);
void	ft_cd(t_data *s_data);
int		ft_isdigit(char c);
int		ft_isalnum(int c);
int		ft_isalpha(int n);
void	ft_free_exp(t_export s_ex);
void	ft_export(t_data *s_var, int index);
void	ft_exit(t_data *s_data, t_commands *s_cmd);
char	ft_identifier(char *var);
int		ft_index_equal(char *str);
void	ft_print_err_exp(t_data *s_data, char *str);
char	*ft_strjoin(char *s1, char *s2);
void	ft_add_to_env(t_export s_ex, t_data *s_data, char status);
void	ft_free_list(t_env	*s_env);
void	ft_handl_expand(t_data *s_data);
void	ft_check_element(t_data *s_dt);
char	**ft_handl_red(t_data *s_dt, char **cmd);
char	*ft_check_expand(t_data *s_data, char *arg);
void	ft_exec_cmd(t_data *data, char **env);

#endif
