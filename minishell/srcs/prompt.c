/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:30:17 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/05 15:16:57 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	struct_shell;

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
	return;
}

void	minishell(void)
{
	while (1)
	{
		signal(SIGINT, sighandler_int);
		signal(SIGQUIT, sighandler_quit);
		struct_shell.line = readline(MINISHELL);
		ft_lexer();
		add_history(struct_shell.line);
		free(struct_shell.line);
	}
}
