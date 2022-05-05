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

int ft_find_nb_proc(void)
{
	int i;

	i = 0;
	if (struct_shell.line[i] == '|')
		return (printf("ERROR\n"), -1);
	while (struct_shell.line[i] == '|' || struct_shell.line[i] == ' ')
	{
		if (struct_shell.line[i] == '|')
			return (printf("ERROR\n"), -1);
		i++;
	}
	i = 0;
	while (struct_shell.line[i] != '\0')
	{
        if (struct_shell.line[i] == '|')
		{
			struct_shell.nb_process += 1;
			while ()
		}
		i++;
	}
	if (struct_shell.line[i - 1] == '|')
		return (printf("ERROR\n"), -1);
	printf("NN PROCESS: %d\n", struct_shell.nb_process);
	return (struct_shell.nb_process);
}


void	ft_lexer(void)
{
	if (struct_shell.line == NULL)
	{
		printf("exit");
		free(struct_shell.line);
		exit(2);
	}
	if (ft_find_nb_proc() == -1)
	{
		printf("error with the pipes\n");
		free(struct_shell.line);
		exit(EXIT_FAILURE);
	}
}