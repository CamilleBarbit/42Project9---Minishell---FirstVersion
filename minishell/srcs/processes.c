/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:28:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 20:14:44 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

int create_proc_str(int i)
{
	int	j;
	int	k;
	int	l;
	
	j = g_shell.tab_proc[i].start;
	k = g_shell.tab_proc[i].end;
	l = 0;
	g_shell.tab_proc[i].strlen = k - j;
	g_shell.tab_proc[i].index = 0;
	g_shell.tab_proc[i].str = ft_malloc("str", g_shell.tab_proc[i].strlen, "malloc processor str failed", g_shell.gc2);
	// malloc(sizeof(char *) * (g_shell.tab_proc[i].strlen + 1)); //securiser gc_2;
	// if (!g_shell.tab_proc[i].str)
	// 	return (1); //erreur malloc -> bosser un code d'erreurs plus rode
	while (l < g_shell.tab_proc[i].strlen)
	{
		g_shell.tab_proc[i].str[l] = g_shell.line[j];
		l++;
		j++;
	}
	g_shell.tab_proc[i].str[l] = '\0';
	return (0);
}

int	init_processes(void)
{
	int	i;
	int	j;
	int index;
	//int	l;

	index = 0;
	i = 0;
	j = ft_strlen(g_shell.line);
	while (i < g_shell.nb_proc)
	{
		if (i == 0)
			g_shell.tab_proc[i].start = 0;
		else
			g_shell.tab_proc[i].start = g_shell.tab_index_pipes[i - 1] + 1;
		if (i == (g_shell.nb_proc - 1))
			g_shell.tab_proc[i].end = j;
		else
			g_shell.tab_proc[i].end = g_shell.tab_index_pipes[i];
		if (create_proc_str(i) == 1)
			return (1);
		find_nb_tokens(i);
		g_shell.tab_proc[i].tab_token = malloc(sizeof(t_token) * (g_shell.tab_proc[i].nb_tokens + 1));
		if (!g_shell.tab_proc[i].tab_token)
			mallocreturn_failed(g_shell.gc2, "t_token malloc failed");
		else
			ft_gcadd_back(g_shell.gc2, ft_gcnew(g_shell.tab_proc[i].tab_token, g_shell.gc2));
		i++;
	}
	return (0);
}
