/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/04 15:46:58 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(void)
{
	char	*line;
	
	while (1)
	{
		line = readline(MINISHELL);
		add_history(line);
		// printf("%s\n", line);
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