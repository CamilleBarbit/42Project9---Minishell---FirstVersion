/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:41:48 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/05 15:30:42 by cbarbit          ###   ########.fr       */
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

	j = i;
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
	g_shell.nb_process++;
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

static int	lexer_empty_line(void)
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

int	ft_lexer(void)
{
	int return_lexer;

	g_shell.nb_process = 1;
	if (g_shell.line == NULL)
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
		exit(EXIT_FAILURE);
	}	
	if (return_lexer == 2)
	{
		printf("error with the pipes syntax\n");
		free(g_shell.line);
		exit(EXIT_FAILURE);
	}
	//printf("NB process: %d\n", g_shell.nb_process);
	return (0);
}