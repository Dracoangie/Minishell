/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:57 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/04 19:50:37 by kpineda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "libft.h"

//Parse
char **Parse_input(char *input);
int check_exit_command(char *input);

//Free
int free_input(char *input);
int free_args(char **args);
void free_all(char *input, char **args);
//Minishell
void Minishell();

//signals
void	handle_sigint(int sig);
void	handle_signals(void);

#endif