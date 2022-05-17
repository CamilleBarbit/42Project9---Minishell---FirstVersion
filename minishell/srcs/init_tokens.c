/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:07:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/17 12:02:46 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;


static int	is_a_separator(int i, int j)
{
	if ((g_shell.tab_proc[j].str[i] == '>') || (g_shell.tab_proc[j].str[i] == '<'))
		return (0);
	return (1);
}

void	find_nb_tokens(int j)
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
		while ((g_shell.tab_proc[j].str[i] != ' ') && (g_shell.tab_proc[j].str[i] != '\0'))
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
			if (is_a_separator(i, j) == 0)
			{
				if ((g_shell.tab_proc[j].str[i - 1] != ' ' || i != 0) && (is_a_separator(i - 1, j) == 1))
					g_shell.tab_proc[j].nb_tokens++;
				i++;
				if (g_shell.tab_proc[j].str[i] != '<' && g_shell.tab_proc[j].str[i] != '>')
				{
					//g_shell.tab_proc[j].nb_tokens++;
					break;	
				}
			}
			i++;
		}
		printf("%c\n", g_shell.tab_proc[j].str[i]);
		puts("lol");
		g_shell.tab_proc[j].nb_tokens++;
	}
	printf("NB TOKENS: %d\n", g_shell.tab_proc[j].nb_tokens);
}

int init_tokens(void)
{
	int i;
	int j;
    
	i = 0;
	while (i < g_shell.nb_proc)
	{
		j = 0;
		g_shell.tab_proc[i].index = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
		
			size_malloc_tokens(i, j, g_shell.tab_proc[i].str);
			if (malloc_tokens(i, j) == 1)
				return (1);
			j++;
		}
		j = 0;
		g_shell.tab_proc[i].index = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			copy_token(i, j, g_shell.tab_proc[i].str);
			//printf("INDEX PROC : %d\n", i);
			//printf("INDEX TOKEN : %d\n", j);
			//printf("STRING %s\n", g_shell.tab_proc[i].tab_token[j].word);
			j++;
		}
		i++;
	}
	return (0);
}
