/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/06 19:15:01 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	g_shell;

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	g_shell.gc = ft_gcnew(NULL, NULL);
	g_shell.lst_env = get_env(env, g_shell.gc);
	// print_env(g_shell.lst_env);
	minishell();
}