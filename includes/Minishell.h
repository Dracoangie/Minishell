/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/07 22:51:53 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "libft.h"

typedef struct s_cmd t_cmd;

//structs
typedef struct s_cmd
{
	t_cmd	*next;
	char	**args;
	char	*path;
	int		input_fd;
	int		output_fd;
}	t_cmd;

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
t_shell	*Init_shell(char **envp);
t_cmd	*Init_cmd(char **args);
int		Count_cmds(t_cmd *cmds);

//Errors
void	Perr_shll(t_shell *shell, char *msg, int err_code);
void	Perr_exit(t_shell *shell, char *msg);
void	Perr_name(t_shell *shell, char* name, char *msg, int err_code);
void	Perr_mem(t_shell *mn_shell);
void	Perr_redir(t_shell *mn_shell, char *msg);

//Free
int		Free_input(char *input);
int		Free_args(char **args);
int		Free_strn(char **str, int j);
void	Free_cmds(t_cmd *cmds);
void	Free_shell(t_shell *shell);
void	Free_all(char *input, t_shell *shell);

//Parse
t_cmd	*Parse_input(char *input, t_shell *mn_shell);
int		Check_exit_cmd(char *input);
int		Parse_files(t_shell *mn_shell, t_cmd *current, t_cmd *cmds);

//Utils
int		ft_strcmp(const char *s1, const char *s2);
int		ft_getline(char **line, size_t *len, int fd);
void	ft_remove_arg(char **args, int index);
void	print_cmds(t_cmd *cmd_list);
int		ft_argstr(const char **args, const char *str);
int		ft_count_args(char **args);

//Commands
char	*Check_cmd(t_shell *mn_shell, char	**args);
void	Execute_command(t_cmd *cmd, t_shell *mn_shell);
char	*Get_cmd_path(char *cmd, char **envp);

//Execution
void	Close_pipes(t_shell *mn_shell);
void	Exec_cmds(t_shell *mn_shell);

//Minishell
void	Minishell(char **envp);

#endif