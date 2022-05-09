/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:30:17 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/09 14:15:29 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

static void	sighandler_int(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sighandler_quit(int signum)
{
	(void)signum;
	return ;
}

void	minishell(void)
{
	while (1)
	{
		signal(SIGINT, sighandler_int);
		signal(SIGQUIT, sighandler_quit);
		g_shell.line = readline(MINISHELL);
		if (ft_strcmp(g_shell.line, "exit"))
		{
			free(g_shell.line);
			ft_free(g_shell.gc);
			exit (0);
		}	
		if (ft_lexer() == 0)
			puts("a parser");
		add_history(g_shell.line);
		free(g_shell.line);
	}
}
