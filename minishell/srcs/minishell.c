/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/04 14:22:48 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(void)
{
	char	*line;
	
	while (1)
	{
		line = readline(MINISHELL);
		printf("%s\n", line);
		free(line);
	}
}

int main(int argc, char **argv, char **env)
{
    //securite env
    //struct
    (void)argc;
    (void)argv;
	(void)env;
    minishell();   
}