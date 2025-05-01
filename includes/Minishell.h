/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/01 15:36:53 by angnavar         ###   ########.fr       */
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

//Parse
char **Parse_input(char *input);
int check_exit_command(char *input);

typedef struct s_command {
	char	**args;
	char	*path;
	int		input_fd;
	int		output_fd;
}	t_command;

//Free
int free_input(char *input);
int free_args(char **args);
void free_all(char *input, char **args);

//Minishell
void Minishell(char **envp);

typedef struct s_minishell
{
	t_command	*cmds;
	int			cmds_len;
	int			last_exit_code;
}	t_minishell;

//Pipex
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

void		execute_command_np(char *cmd, char **envp);
void		execute_command(char *cmd, char **envp, t_pipex *pipex);
void		pipex(char **argv, char **envp, t_minishell *mn_shell, int here_doc_mode);
int			ft_strcmp(const char *s1, const char *s2);
void		here_doc(char *delimiter);
int			ft_getline(char **line, size_t *len, int fd);
void		do_here_doc(int argc, char **argv, char **envp);
void		here_doc_open_files(t_pipex *pipex, char **argv);
void		open_files(t_pipex *pipex, char **argv);
void		close_pipes(t_pipex *pipex);

#endif