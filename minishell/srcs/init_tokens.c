/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:07:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 14:54:40 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

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
		g_shell.tab_proc[j].nb_tokens++; //recupere le nb de tokens pour chaque processus -> pour malloc la bonne taille de tab_token
	}
}

int init_tokens(void)
{
	int i;
	int j;
    
	i = 0;
	while (i < g_shell.nb_proc)
	{
		j = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			//g_shell.tab_proc[i].tab_token[j].word_malloc_count = malloc_tokens(i, g_shell.tab_proc[i].str);
			//printf("Taille malloc token[index_du_process: %d][index_du_token: %d] : %d\n", i, j, malloc_tokens(i, g_shell.tab_proc[i].str));
			//g_shell.tab_proc[i].tab_token[j].word = malloc(sizeof(char *) * (malloc_tokens(i, g_shell.tab_proc[i].str) + 1));
			size_malloc_tokens(i, j, g_shell.tab_proc[i].str);
			printf("Taille malloc token[index_du_process: %d][index_du_token: %d] : %d\n", i, j, g_shell.tab_proc[i].tab_token[j].word_malloc_count);
			if (malloc_tokens(i, j) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
