/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:09:51 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/06 14:48:03 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBRARIES */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"

/* DEFINED VARIABLES */

#define MINISHELL "minishell>"

/* TOKEN STRUCTURE */

typedef struct s_token
{
	char	*word;
	int		type; //faire un enum pour le type de chaque mot
}	t_token;

/* PROCESS DATA STRUCTURE */

typedef struct	s_process
{
	char	*str;
	int		i_start;
	int		i_end;
	char	*path; //path de la commande?
	int		in_fd;
	int		out_fd;
	int		nb_tokens;
	t_token	*tab_token;
}	t_process;


/* MAIN STRUCTURE */

typedef struct	s_minishell
{
	//int			exit;
	int			nb_proc; //défini par le nombre de pipes dans la ligne d'entrée
	char		*line;
	int			tab_index_pipes[512];
	t_process	*tab_proc; //de taille de nb_process
}	t_minishell;


/* LEXER */

int ft_find_nb_proc(void);
int	ft_lexer_prompt(void);
int ft_malloc_processes(void);
int ft_lexer(void);

/* FUNCTIONS */
void	minishell(void);

#endif