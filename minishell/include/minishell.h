/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:09:51 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/05 15:20:52 by cbarbit          ###   ########.fr       */
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
	int		type;
}	t_token;

/* PROCESS DATA STRUCTURE */

typedef struct	s_process
{
	char	*str;
	char	*path; //path de la commande?
	int		in_fd;
	int		out_fd;
	int		nb_tokens;
	t_token	*tab_token;
}	t_process;


/* MAIN STRUCTURE */

typedef struct	s_minishell
{
	int			exit;
	int			nb_process; //défini par le nombre de pipes dans la ligne d'entrée
	char		*line;
	t_process	*tab_process; //de taille de nb_process
}	t_minishell;


/* LEXER */

int ft_find_nb_proc(void);
void	ft_lexer(void);

/* FUNCTIONS */
void	minishell(void);

#endif