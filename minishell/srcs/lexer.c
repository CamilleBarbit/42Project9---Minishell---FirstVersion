/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:41:48 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/06 12:00:56 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

static int	lexer_quote(int i)
{
	char	c;

	c = g_shell.line[i];
	i++;
	while (g_shell.line[i] != c)
	{
		if (!g_shell.line[i])
			return (-1);
		i++;
	}
	return (i);
}

static int	lexer_pipe(int i)
{
	int	j;
	int	k;

	j = i;
	k = 0;
	g_shell.tab_index_pipes = malloc(sizeof(int) * g_shell.nb_proc);
	if (!g_shell.tab_index_pipes)
		return (-2); //malloc error
	while (j > 0)
	{
		j--;
		if (g_shell.line[j] != ' ')
			break ;
	}
	if (g_shell.line[j] == ' ' || g_shell.line[j] == '|')
		return (-1);
	i++;
	while (g_shell.line[i])
	{
		if (g_shell.line[i] != ' ')
			break ;
		i++;
	}
	g_shell.nb_proc++;
	g_shell.tab_index_pipes[k] = i - 2;
	printf("INDEX: %d\n", g_shell.tab_index_pipes[k]);
	k++;
	if (!g_shell.line[i] || g_shell.line[i] == '|')
		return (-1);
	return (i);
}

static int	lexer_quote_and_pipe(void)
{
	int	i;

	i = 0;
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '"' || g_shell.line[i] == '\'')
		{
			i = lexer_quote(i);
			if (i == -1)
				return (1);
		}
		if (g_shell.line[i] == '|')
		{
			i = lexer_pipe(i);
			if (i == -1)
				return (2);
			i--;
		}
		i++;
	}
	return (0);
}

static int	lexer_empty_line(void) //line with empty space or empty line (with \0)
{
	int	i;

	i = 0;
	while (g_shell.line[i] && g_shell.line[i] == ' ')
		i++;
	if (!g_shell.line[i])
		return (1);
	else
		return (0);
}

int	ft_lexer_prompt(void)
{
	int return_lexer;

	g_shell.nb_proc = 1;
	if (g_shell.line == NULL) //le pointeur est NULL
	{
		printf("exit");
		free(g_shell.line);
		exit(2);
	}
	if (lexer_empty_line() == 1)
		return (1);
	return_lexer = lexer_quote_and_pipe();
	if (return_lexer == 1)
	{
		printf("error with the pipes quotes\n");
		free(g_shell.line);
		exit(1);
	}	
	if (return_lexer == 2)
	{
		printf("error with the pipes syntax\n");
		free(g_shell.line);
		exit(1);
	}
	//si ca retourne -2, c'est une erreur de malloc -> a rajouter!
	//printf("NB process: %d\n", g_shell.nb_process);
	return (0);
}