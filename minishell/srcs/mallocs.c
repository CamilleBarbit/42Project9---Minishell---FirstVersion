/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:44:28 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 15:00:03 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

int malloc_processes(void)
{
	g_shell.tab_proc = malloc(sizeof(t_process) * (g_shell.nb_proc + 1)); //necessary the +1?
	if (!g_shell.tab_proc)
		return (1);
	return (0);
}

int	malloc_tokens(int i, int j)
{
	g_shell.tab_proc[i].tab_token[j].word = malloc(sizeof(char *) * (g_shell.tab_proc[i].tab_token[j].word_malloc_count + 1));
	if (!g_shell.tab_proc[i].tab_token[j].word)
		return (1);
	return (0);	
}

static void	on_simple_quote(int	i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '\'')
	{
		g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
		g_shell.tab_proc[i].index++;
	}
	g_shell.tab_proc[i].index++;
}

static void	on_double_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '"')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
				g_shell.tab_proc[i].tab_token[j].word_malloc_count += gestion_var_size(i, str);
		else
		{
			g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
			g_shell.tab_proc[i].index++;
		}
	}
	g_shell.tab_proc[i].index++;
}

void	size_malloc_tokens(int i, int j, char *str)
{
	g_shell.tab_proc[i].tab_token[j].word_malloc_count = 0;
	while (str[g_shell.tab_proc[i].index] == ' ')
		g_shell.tab_proc[i].index++;
	while(str[g_shell.tab_proc[i].index] && str[g_shell.tab_proc[i].index] != ' ')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
			g_shell.tab_proc[i].tab_token[j].word_malloc_count += gestion_var_size(i, str);
		else if (str[g_shell.tab_proc[i].index] == '"')
			on_double_quote(i, j, str);
		else if (str[g_shell.tab_proc[i].index] == '\'')
			on_simple_quote(i, j, str);
		else
		{
			g_shell.tab_proc[i].index++;
			g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
		}
	}
}