/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/04 16:50:59 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*line = NULL;

void	sighandler(int signum)
{
	//char *line;
	
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		// signal(SIGINT, sighandler);
		// line = readline(MINISHELL);
		// //free(line);
	}
}

void	minishell(void)
{
	//char	*line;
	
	while (1)
	{
		signal(SIGINT, sighandler);
		line = readline(MINISHELL);
		add_history(line);
		//printf("%s\n", line);
		if (line == NULL)
		{
			printf(" exit");
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
//  SIGINT ctrl + c (reset le prompt)
// SIGQUIT ctrl + \ (ne rien faire)
}

int main(int argc, char **argv, char **env)
{
	// t_env *env;
	
	// env =
    //securite env
    //struct
    (void)argc;
    (void)argv;
	(void)env;
    minishell();   
}