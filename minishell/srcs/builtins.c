/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:30:57 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/16 17:50:06 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

/* CODE ECHO :

Echo will not have the same behavior depending on the kind of token that is following
In order to make the command works -> My function needs to take the table of tokens as a parameter
I need to check whether there is an option - and whether this option is "-n" - or else omit the \n
The command echo automatically writes a new line unless there is the -n option
The function will only execute if there is a token following - if no token, then it will have to print a \n
What kind of token can it be? If (while) it is a word, it litterally prints the word -> I say while because there can be more than one token
If there is more than one word, echo needs to print them

*/

char	*ft_echo(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, '\n', 1);
}

