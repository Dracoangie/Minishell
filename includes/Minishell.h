/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/05 14:20:42 by angnavar         ###   ########.fr       */
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

typedef struct s_pipex
{
	pid_t	*childs;
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
	int			n_cmds;
	int			last_exit_code;
	char		**envp;
	t_pipex		*pipex;
}	t_shell;

//Init
t_shell	*init_shell(char **envp);
t_cmd	*init_cmd(char **args);
int		count_cmds(t_cmd *cmds);

//Errors
void	print_error(t_shell *shell, char *msg, int err_code);
void	print_error_and_exit(t_shell *shell, char *msg);

//Free
int free_input(char *input);
int	free_args(char **args);
int	free_strn(char **str, int j);
void free_shell(t_shell *shell);
void free_all(char *input, t_shell *shell);

//Parse
t_cmd	*Parse_input(char *input, t_shell *mn_shell);
int		check_exit_cmd(char *input);

//Utils
int			ft_strcmp(const char *s1, const char *s2);
int			ft_getline(char **line, size_t *len, int fd);

//Pipex

void	execute_command(t_cmd *cmd, t_shell *mn_shell);
int			open_files(t_shell *mn_shell);
void		close_pipes(t_shell *mn_shell);

char	*get_cmd_path(char *cmd, char **envp);
void	pipex(t_shell *mn_shell);

//Minishell
void Minishell(char **envp);

#endif