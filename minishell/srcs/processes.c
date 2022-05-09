/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:28:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/09 17:00:01 by aboudjel         ###   ########.fr       */
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
		return (1); //erreur malloc -> bosser un code d'erreurs plus rode
	while (l < size)
	{
		g_shell.tab_proc[i].str[l] = g_shell.line[j];
		l++;
		j++;
	}
	g_shell.tab_proc[i].str[l] = '\0';
	return (0);
}

static void	strlentoken(int j)
{
	int i;
	
	i = 0;
	g_shell.tab_proc[j].nb_tokens = 0;
	while(g_shell.tab_proc[j].str[i])
	{
		while (g_shell.tab_proc[j].str[i] == ' ')
		{
			i++;
			if (!g_shell.tab_proc[j].str[i])
				return ;
		}
		while (g_shell.tab_proc[j].str[i] != ' ' && g_shell.tab_proc[j].str[i] != '\0')
		{
			if (g_shell.tab_proc[j].str[i] == '"')
			{
				i++;
				while (g_shell.tab_proc[j].str[i] != '"')
				{
					i++;
					if (g_shell.tab_proc[j].str[i] == '"')
						break;
				}
			}
			if (g_shell.tab_proc[j].str[i] == '\'')
			{
				i++;
				while (g_shell.tab_proc[j].str[i] != '\'')
				{
					i++;
					if (g_shell.tab_proc[j].str[i] == '\'')
						break;
				}
			}
			i++;
		}
		g_shell.tab_proc[j].nb_tokens++;
	}
}

int	init_processes(void)
{
	int	i;
	int	j;

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
		if (ft_create_proc_str(i) == 1)
			return (1);
		strlentoken(i);	
		printf("NB TOKEN: %d\n", g_shell.tab_proc[i].nb_tokens);
		i++;
	}
	return (0);
}

int ft_lexer(void)
{
	if (ft_lexer_prompt() != 0)
		return (1);
	if (ft_malloc_processes() == 1)
		return (1);
	if (init_processes() == 1)
		return (1);
	printf("INDEX PIPE: %d\n", g_shell.tab_index_pipes[0]);
	printf("INDEX PIPE: %d\n", g_shell.tab_index_pipes[1]);
	return (0); //le prompt peut etre parse
}
