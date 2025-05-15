/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/15 11:20:41 by angnavar         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd	t_cmd;

//structs
typedef struct s_cmd
{
	t_cmd	*next;
	char	**args;
	char	*path;
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
int		check_exit_cmd(char *input);
int		here_doc(char *delimiter, t_shell *mn_shell);
char	**ft_split_with_quotes(const char *s, char c);

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

//Execution
void	close_pipes(t_shell *mn_shell);
void	exec_cmds(t_shell *mn_shell);

//Minishell
void	minishell();

//signals
void	handle_sigint(int sig);
void	handle_signals(void);

//Builtins
int		execute_echo(t_cmd *cmds, t_shell *mn_shell);
char	**execute_unset(char **envp, char *command);
int		find_env_line(char **envp, char *key);
char	*get_env_value(const char *name, char **envp);
char	**delete_env_var(char **envp, char *key);

#endif