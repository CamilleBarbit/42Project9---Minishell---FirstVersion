/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes..c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:28:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/06 15:03:59 by cbarbit          ###   ########.fr       */
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

int	ft_create_proc_str(int i)
{
	int	size;
	int	j;
	int	k;
	int	l;
	
	j = g_shell.tab_proc[i].start;
	k = g_shell.tab_proc[i].end;
	l = 0;
	size = k - j;
	g_shell.tab_proc[i].str = malloc(sizeof(char *) * (size + 1));
	if (!g_shell.tab_proc[i].str)
		return (1); //erreur malloc
	while (l < size)
	{
		g_shell.tab_proc[i].str[l] = g_shell.line[j];
		l++;
		j++;
	}
}

int	init_processes(void)
{
	int	i;

	i = 0;
	while (i < g_shell.nb_proc)
	{
		if (i = 0)
			g_shell.tab_proc[i].start = 0;
		else
			g_shell.tab_proc[i].start = g_shell.tab_index_pipes[i - 1] + 1;
		g_shell.tab_proc[i].end = g_shell.tab_index_pipes[i];
		ft_create_proc_str(i);
	}
}

int ft_lexer(void)
{
	if (ft_lexer_prompt() != 0)
		return (1);
	if (ft_malloc_processes() == 1)
		return (1);
	// printf("INDEX: %d\n", g_shell.tab_index_pipes[0]);
	// printf("INDEX: %d\n", g_shell.tab_index_pipes[1]);
	// printf("INDEX: %d\n", g_shell.tab_index_pipes[2]);
	return (0); //le prompt peut etre parse
}


