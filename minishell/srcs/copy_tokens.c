/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:04:32 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 17:36:01 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

static void	val_strlcpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return ;
}

static int copy_var(char *copy, int i, char *str)
{
	int		j;
	int		k;
	t_env	*temp;
	
	g_shell.tab_proc[i].index++;
	//printf(" copy_var index = %c %d\n", str[g_shell.tab_proc[i].index], g_shell.tab_proc[i].index);
	j = g_shell.tab_proc[i].index;
	if (ft_isalpha(str[g_shell.tab_proc[i].index]) == 1 && str[g_shell.tab_proc[i].index] != '_')
	{
		copy[0] = '$';
		return (1);
	}
	g_shell.tab_proc[i].index++;
	//printf(" ft_gestion_var index = %c %d\n", str[g_shell.tab_proc[i].index], g_shell.tab_proc[i].index);
	while (ft_isalnum(str[g_shell.tab_proc[i].index]) == 0 || str[g_shell.tab_proc[i].index] == '_')
		g_shell.tab_proc[i].index++;
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.tab_proc[i].index - j));

		if (k == 0)
		{
			k = ft_strlen(temp->val);
			val_strlcpy(copy, temp->val, k);
			//printf(" ft_gestion_var = %d\n", k);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

static void copy_on_simple_quote(int	i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '\'')
	{
		g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];
	}
	g_shell.tab_proc[i].index++;
}

static void	copy_on_double_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '"')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
			g_shell.tab_proc[i].tab_token[j].word_malloc_count += copy_var(g_shell.tab_proc[i].tab_token[j].word + g_shell.tab_proc[i].tab_token[j].word_malloc_count, i, str);
		else
		{
			g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];
		}
	}
	g_shell.tab_proc[i].index++;
}

void	copy_token(int i, int j, char *str)
{
	g_shell.tab_proc[i].tab_token[j].word_malloc_count = 0;
	while (str[g_shell.tab_proc[i].index] == ' ')
		g_shell.tab_proc[i].index++;
	while(str[g_shell.tab_proc[i].index] && str[g_shell.tab_proc[i].index] != ' ')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
			g_shell.tab_proc[i].tab_token[j].word_malloc_count += copy_var(g_shell.tab_proc[i].tab_token[j].word + g_shell.tab_proc[i].tab_token[j].word_malloc_count, i, str);
		else if (str[g_shell.tab_proc[i].index] == '"')
            copy_on_double_quote(i, j, str);
		else if (str[g_shell.tab_proc[i].index] == '\'')
            copy_on_simple_quote(i, j, str);
		else
            g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];		
	}
	g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count] = '\0';
//	printf(" count %d\n", g_shell.tab_proc[i].tab_token[j].word_malloc_count);
//	printf("STRING3 %s\n", g_shell.tab_proc[i].tab_token[j].word);
	return ;
}