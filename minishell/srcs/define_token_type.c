/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:46:04 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/16 18:28:30 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

/* Function to check if the token is a redirection */
//send 0 if it is a redir and 1 if it is not a redir //

int	is_redir(char *str) //It will receive and check each token
{
	int	i;

	i = 0;
	if (str[0] != '>' && str[0] != '<')
		return (1);
	
	i++;
	if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '\0')
		return (1);
	return (0); //c'est une redir
}

int	is_builtin(char *str)
{
	if 
}