/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:09:51 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 14:15:40 by aboudjel         ###   ########.fr       */
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
	int		strlen;
	int		start;
	int		end;
	int		index;
	int		index2;
	char	*path; //path de la commande?
	int		in_fd;
	int		out_fd;
	int		nb_tokens;
	t_token	*tab_token;
}	t_process;

/* ENV LISTE CHAINEE */

// typedef struct s_env
// {
// 	char			*var;
// 	char			*val;
// 	struct s_env	*next;
// }	t_env;

/* MAIN STRUCTURE */

typedef struct	s_minishell
{
	//int			exit;
	int			nb_proc; //défini par le nombre de pipes dans la ligne d'entrée
	char		*line;
	int			length_line;
	int			tab_index_pipes[512];
	t_gc	*gc; //garbage_collector pour collecter tout les adresses de mallocs afin de tous les free a la fin
	t_env	*lst_env; // liste chainee dans laquelle est stockee l'env
	t_process	*tab_proc; //de taille de nb_process
}	t_minishell;


/* LEXER */

int ft_find_nb_proc(void);
int	ft_lexer_prompt(void);
int ft_malloc_processes(void);
int ft_lexer(void);

/* ENV */

void	add_env(t_env *env, t_env *to_add);
char	*env_dup(char *src, int size, t_gc *gc);
t_env	*get_envlst(char *var, t_gc *gc);
t_env	*get_env(char **env, t_gc *gc);
void	print_env(t_env *env);

/* FUNCTIONS */

void	minishell(void);

#endif