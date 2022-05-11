/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 20:51:47 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	g_shell;

int lexer(void)
{
	if (lexer_prompt() != 0)
		return (1);
	if (malloc_processes() == 1)
		return (1);
	if (init_processes() == 1)
		return (1);
	if (init_tokens() == 1)
		return (1);
	// printf("NB PROCESSUS: %d\n", g_shell.nb_proc);
	return (0); //le prompt peut etre parse
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
		g_shell.gc2 = ft_gcnew(NULL, NULL);
		if (lexer() == 0)
			puts("a parser");
		add_history(g_shell.line);
		free(g_shell.line);
		ft_free(g_shell.gc2);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	g_shell.gc = ft_gcnew(NULL, NULL);
	g_shell.lst_env = get_env(env, g_shell.gc);
	print_env(g_shell.lst_env);
	minishell();
}


// void	minishell(void) POUR TESTER LES LEAKS ET NE PAS UTILISER LE READLINE QUI LEAK MAIS UN GETNEXTLINE A LA PLACE 
// {
// 	int fd = open("gnl.txt",  O_RDWR);
// 		if (fd < 1)
// 		{
// 			puts("no fd");
// 			exit(1);
// 		}
// 	g_shell.line = get_next_line(fd);
// 	while (g_shell.line)
// 	{
// 		signal(SIGINT, sighandler_int);
// 		signal(SIGQUIT, sighandler_quit);
// 		// g_shell.line = readline(MINISHELL);
		
// 		puts("AAAAAAAAAAAAAAAAAAAAAAA");
// 		if (ft_strcmp(g_shell.line, "exit"))
// 		{
// 			free(g_shell.line);
// 			ft_free(g_shell.gc);
// 			puts("qqqqqqqqqqqqqqqq");
// 			exit (0);
// 		}
// 		g_shell.gc2 = ft_gcnew(NULL, NULL);
// 		if (lexer() == 0)
// 			puts("a parser");
// 		// add_history(g_shell.line);
// 		free(g_shell.line);
// 		ft_free(g_shell.gc2);
// 		puts("finzer");
// 		g_shell.line = get_next_line(fd);
// 	}
// 	puts("SSSSSSSSSSSSSSSSSSS");
// 	free(g_shell.line);
// }