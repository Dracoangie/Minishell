/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/03 15:33:45 by tu_nombre_d      ###   ########.fr       */
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

//structs
typedef struct s_command {
	char	**args;
	char	*path;
	int		input_fd;
	int		output_fd;
}	t_cmd;


typedef struct s_pipex
{
	pid_t	*childs;
	int		file[2];
	int		**pipes;
	int		cmd_len;
	int		here_doc_mode;
}			t_pipex;

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
	int			cmds_len;
	int			last_exit_code;
	char		**envp;
	t_pipex		*pipex;
}	t_shell;

//Errors
void	print_error(t_shell *shell, char *msg, int err_code);
void	print_error_and_exit(t_shell *shell, char *msg);

//Free
int free_input(char *input);
int free_args(char **args);
void free_shell(t_shell *shell);
void free_all(char *input, char **args, t_shell *shell);

//Parse
char **Parse_input(char *input);
int check_exit_cmd(char *input);
//t_cmd *parse_input(char *input);

//Utils
int			ft_strcmp(const char *s1, const char *s2);
int			ft_getline(char **line, size_t *len, int fd);

//Pipex

void		execute_command(char *cmd, char **envp, t_shell *mn_shell);
int			here_doc_open_files(t_shell *mn_shell, char **argv);
int			open_files(t_shell *mn_shell, char **argv);
void		close_pipes(t_shell *mn_shell);

void		pipex(char **argv, char **envp, t_shell *mn_shell, int here_doc_mode);

//Minishell
void Minishell(char **envp);

#endif