/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:09:11 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/03 14:09:11 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	print_error(t_shell *shell, char *msg, int err_code)
{
	write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
	shell->last_exit_code = err_code;
}
void print_error_and_exit(t_shell *shell, char *msg)
{
	write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    exit(shell->last_exit_code);
}
	