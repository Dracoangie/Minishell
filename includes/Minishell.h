/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/21 04:03:47 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd	t_cmd;

//structs
typedef struct s_cmd
{
	t_cmd	*next;
	char	**args;
	char	*path;
	int		is_builtin;
	int		has_cmd;
	int		input_fd;
	int		output_fd;
}	t_cmd;

typedef struct s_cmd_state
{
	t_cmd	*head;
	t_cmd	*curr;
	int		i;
}	t_cmd_state;

typedef struct s_heredoc
{
	int		pipe_fd[2];
	char	*line;
	size_t	len;
	size_t	size;
}			t_heredoc;

typedef struct s_shell
{
	t_cmd	*cmds;
	int		n_cmds;
	int		last_exit_code;
	int		lvl;
	char	**envp;
	pid_t	*childs;
}	t_shell;

//Init
t_shell	*init_shell(char **envp);
t_cmd	*init_cmd(char **args);
int		count_cmds(t_cmd *cmds);

//Errors
void	perr_shll(t_shell *shell, char *msg, int err_code);
void	perr_exit(t_shell *shell, char *msg);
void	perr_export(t_shell *mn_shell, char *msg);
void	perr_cd(t_shell *mn_shell, char *msg);
void	perr_name(t_shell *shell, char *name, char *msg, int err_code);
void	perr_mem(t_shell *mn_shell);
void	perr_redir(t_shell *mn_shell, char *msg);

//Free
int		free_input(char *input);
int		free_args(char **args);
int		free_strn(char **str, int j);
void	free_cmds(t_cmd *cmds);
void	free_shell(t_shell *shell);
void	free_all(char *input, t_shell *shell);
void	free_env(char **env_copy);

//Parse
t_cmd	*parse_input(char *input, t_shell *mn_shell);
t_cmd	*parse_to_cmds(char const *s, char c, t_shell *mn_shell);
int		parse_files(t_shell *mn_shell, t_cmd *current, t_cmd *cmds);
void	parse_env(t_cmd *cmd, t_shell *mn_shell);
void	parse_quotes(t_cmd *cmd);
int		parse_redirect(t_cmd *cmd, t_shell *mn_shell);
int		parse_builtins(t_cmd *cmds);
int		parse_redirs(t_cmd *cmd);
int		check_exit_cmd(char *input);
int		here_doc(char *delimiter, t_shell *mn_shell);
char	**ft_split_with_quotes(const char *s, char c);
int		handle_quotes(const char *str, int i, char *quote, char **result);
int		handle_expnd(const char *str, int i, t_shell *mn_shell, char **result);
char	*expand_args(const char *arg, t_shell *mn_shell);

//Utils
int		ft_strcmp(const char *s1, const char *s2);
int		ft_getline(char **line, size_t *len, int fd);
void	ft_remove_arg(char **args, int index);
void	ft_print_cmds(t_cmd *cmd_list);
int		ft_argstr(const char **args, const char *str);
int		ft_count_args(char **args);
char	*ft_remove_quotes(const char *str);
int		ft_fd_null(t_shell *mn_shell);

//Commands
char	*check_cmd(t_shell *mn_shell, char	**args);
void	execute_command(t_cmd *cmd, t_shell *mn_shell);
char	*get_cmd_path(char *cmd, char **envp);
int		exec_builtin_cmds(t_cmd *cmds, t_shell *mn_shell);

//Execution
void	close_pipes(t_shell *mn_shell);
void	exec_cmds(t_shell *mn_shell);

//Minishell
int		minishell(char **envp);

//signals
void	handle_sigint(int sig);
void	handle_signals(void);

//Builtins
int		execute_echo(t_cmd *cmds, t_shell *mn_shell);
void	execute_unset(t_shell *mn_shell, t_cmd *command);
int		execute_cd(t_shell *mn_shell, char **args);
char	*get_env_value(const char *name, char **envp);
int		execute_export(t_shell *mn_shell, char **args);
int		execute_exit(t_cmd *cmds, t_shell *mn_shell);

//Builtins utils
void	update_env_var(char ***envp, const char *key, const char *value);
char	**ft_realloc_env(char **envp, char *new_var);
int		find_env_line(char **envp, char *key);
char	*get_env_value(const char *name, char **envp);
char	**delete_env_var(char **envp, char *key);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
int		is_valid_identifier(const char *str);
int		cd_to_home(t_shell *mn_shell, char *oldpwd);
int		cd_to_oldpwd(t_shell *mn_shell, char *oldpwd);
int		cd_to_path(t_shell *mn_shell, char *path, char *oldpwd);
void	print_sorted_env(char **envp);
void	handle_export_arg(t_shell *mn_shell, char *arg);

#endif