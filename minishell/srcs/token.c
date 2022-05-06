/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:28:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/06 11:42:30 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

int ft_malloc_processes(void)
{
	g_shell.tab_proc = malloc(sizeof(t_process) * g_shell.nb_proc);
	if (!g_shell.tab_proc)
		return (1);
	return (0);
}

int ft_lexer(void)
{
	if (ft_lexer_prompt() != 0)
		return (1);
	if (ft_malloc_processes() == 1)
		return (1);
	return (0); //le prompt peut etre parse
}


