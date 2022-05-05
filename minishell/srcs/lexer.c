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

extern t_minishell	struct_shell;

static int ft_lexer_quote(int i);
static int ft_lexer_pipe(int i);

static int	ft_quote_and_pipe(void)
{
	int	i;

	i = 0;
	while (struct_shell.line[i])
	{
		if (struct_shell.line[i] == '"' || struct_shell.line[i] == '\'')
		{
			i = t_lexer_quote(i);
			if (i = -1)
				return (printf("ERROR\n"), 1);
		if (struct_shell.line[i] == '|')
		{
			i = ft_lexer_pipe(i);
			if (i = -1)
				return (printf("ERROR\n"), 1);
		}
		i++;
	}
}

static int ft_lexer_quote(int i)
{
	char	c;

	c = struct_shell.line[i];
	i++;
	while (struct_shell.line[i] != c)
	{
		if (!struct_shell.line[i])
			return (printf("ERROR\n"), -1);
		i++;
	}
	return(i);
}


static int ft_lexer_pipe(int i)
{
	int	j;

	j = i;
	while (j > 0)
	{
		if (struct_shell.line[j] != ' ')
			break;
		j--:
	}
	if (struct_shell.line[j] == ' ' || struct_shell.line[j] == '|')
		return (printf("ERROR\n"), 1);
	i++;
	while (struct_shell.line[i])
	{
		if (struct_shell.line[i] != ' ')
			break;
		i++;
	}
	if (!struct_shell.line[i] || struct_shell.line[i] == '|')
		return (printf("ERROR\n"), 1);
	struct_shell.nb_process++;








// -------------------------------------------------------------------------------------


/*

static int ft_find_nb_proc(void)
{
	int i;

	i = 0;
	while (struct_shell.line[i] == '|' || struct_shell.line[i] == ' ')
	{
		if (struct_shell.line[i] == '|')
			return (printf("ERROR\n"), 1);
		i++;
	}
	if (!struct_shell.line[i])
		return (2);
	while (struct_shell.line[i] != '\0')
	{
        if (struct_shell.line[i] == '|')
		{
			while (struct_shell.line[i] == ' ' || struct_shell.line[i] == '|')
			{
				i++;
				if (struct_shell.line[i] == '|' || !struct_shell.line[i])
					return (printf("ERROR\n"), 1);
			}
		}
		i++;
	}
	return (0);
	
int ft_find_nb_proc(void)
{
	int i;

	i = 0;
	while (struct_shell.line[i] == '|' || struct_shell.line[i] == ' ')
	{
		if (struct_shell.line[i] == '|')
			return (printf("ERROR\n"), 1);
		i++;
	}
	if (!struct_shell.line[i])
		return (2);
	while (struct_shell.line[i] != '\0')
	{
        if (struct_shell.line[i] == '|')
		{
			// struct_shell.nb_process += 1;
			// printf("NB PROCESS: %d\n", struct_shell.nb_process);
			while (struct_shell.line[i] == ' ' || struct_shell.line[i] == '|')
			{
				i++;
				if (struct_shell.line[i] == '|' || !struct_shell.line[i])
					return (printf("ERROR\n"), 1);
			}
		}
		i++;
	}
	return (0);
}

int ft_check_quote(void)
{
	int	i;

	i = 0;
	while (struct_shell.line[i])
	{
		if (struct_shell.line[i] == '"')
		{
			i++;
			while (struct_shell.line[i] != '"')
			{
				i++;
				if (!struct_shell.line[i])
					return (printf("ERROR\n"), 1);
			}
		}
		if (struct_shell.line[i] == '\'')
		{
			i++;
			while (struct_shell.line[i] != '\'')
			{
				i++;
				if (!struct_shell.line[i])
					return (printf("ERROR\n"), 1);
			}

		}
		i++;
	}
	return (0);
}
*/

int	ft_lexer(void)
{
	int return_lexer;
	struct_shell.nb_process = 1;

	if (struct_shell.line == NULL)
	{
		printf("exit");
		free(struct_shell.line);
		exit(2);
	}
	return_lexer = ft_find_nb_proc();
	if (ft_check_quote() == 1)
	{
		printf("error with the quotes\n");
		free(struct_shell.line);
		exit(EXIT_FAILURE);
	}	
	if (return_lexer == 1)
	{
		printf("error with the pipes\n");
		free(struct_shell.line);
		exit(EXIT_FAILURE);
	}
	if (return_lexer == 2)
		return (1);
	return (0);
}
