/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:28:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/11 14:59:13 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

static void	strlentoken(int j);
int	val_strncmp(char *stra, char *val, int length);

int ft_malloc_processes(void)
{
	g_shell.tab_proc = malloc(sizeof(t_process) * g_shell.nb_proc);
	if (!g_shell.tab_proc)
		return (1);
	return (0);
}

int	malloctoken(int i, char	*str);

void	val_strlcpy(char *dst, char *src, int size)
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

int copy_var(char *copy, int i, char *str)
{
	int		j;
	int		k;
	t_env	*temp;
	
	g_shell.tab_proc[i].index2++;
	printf(" copy_var index2 = %c %d\n", str[g_shell.tab_proc[i].index2], g_shell.tab_proc[i].index2);
	j = g_shell.tab_proc[i].index2;
	if (ft_isalpha(str[g_shell.tab_proc[i].index2]) == 1 && str[g_shell.tab_proc[i].index2] != '_')
	{
		copy[0] = '$';
		return (1);
	}
	g_shell.tab_proc[i].index2++;
	printf(" ft_gestion_var index2 = %c %d\n", str[g_shell.tab_proc[i].index2], g_shell.tab_proc[i].index2);
	while (ft_isalnum(str[g_shell.tab_proc[i].index2]) == 0 || str[g_shell.tab_proc[i].index2] == '_')
		g_shell.tab_proc[i].index2++;
	// printf(" ft_gestion_var index2 = %d\n", g_shell.tab_proc[i].index2);
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.tab_proc[i].index2 - j));

		if (k == 0)
		{
			k = ft_strlen(temp->val);
			val_strlcpy(copy, temp->val, k);
			printf(" ft_gestion_var = %d\n", k);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

void	copy_token(int l, int i, char *str)
{
	int	count;

	count = 0;
	while (str[g_shell.tab_proc[i].index2] == ' ')
		g_shell.tab_proc[i].index2++;
	while(str[g_shell.tab_proc[i].index2] && str[g_shell.tab_proc[i].index2] != ' ')
	{
		if (str[g_shell.tab_proc[i].index2] == '$')
			count += copy_var(g_shell.tab_proc[i].tab_token[l].word + count, i, str);
		else if (str[g_shell.tab_proc[i].index2] == '"')
			{
				// puts("lol");
				g_shell.tab_proc[i].index2++;
				// printf("index2 = %d\n", g_shell.tab_proc[i].index2);
				while (str[g_shell.tab_proc[i].index2] != '"')
				{
					// printf("indexxxxxxxxxxxxxxxxxxxxx = %d\n", g_shell.tab_proc[i].index2);
					if (str[g_shell.tab_proc[i].index2] == '$')
						count += copy_var(g_shell.tab_proc[i].tab_token[l].word + count, i, str);
					else
					{
						g_shell.tab_proc[i].tab_token[l].word[count++] = str[g_shell.tab_proc[i].index2++];
						// g_shell.tab_proc[i].index2++;
					}
				}
				g_shell.tab_proc[i].index2++;
			}
		else if (str[g_shell.tab_proc[i].index2] == '\'')
			{
				g_shell.tab_proc[i].index2++;
				while (str[g_shell.tab_proc[i].index2] != '\'')
				{
					g_shell.tab_proc[i].tab_token[l].word[count++] = str[g_shell.tab_proc[i].index2++];
					// count++;
					// g_shell.tab_proc[i].index2++;
				}
				g_shell.tab_proc[i].index2++;
			}
		else
		{
			g_shell.tab_proc[i].tab_token[l].word[count++] = str[g_shell.tab_proc[i].index2++];
			// g_shell.tab_proc[i].index2++;
			// count++;
		}
	}
	g_shell.tab_proc[i].tab_token[l].word[count] = '\0';
	printf(" count%d\n", count);
	return ;
}

int	ft_create_proc_str(int i)
{
	int	j;
	int	k;
	int	l;
	
	j = g_shell.tab_proc[i].start;
	k = g_shell.tab_proc[i].end;
	l = 0;
	g_shell.tab_proc[i].strlen = k - j;
	g_shell.tab_proc[i].index = 0;
	g_shell.tab_proc[i].index2 = 0;
	g_shell.tab_proc[i].str = malloc(sizeof(char *) * (g_shell.tab_proc[i].strlen + 1)); //securiser gc_2;
	if (!g_shell.tab_proc[i].str)
		return (1); //erreur malloc -> bosser un code d'erreurs plus rode
	while (l < g_shell.tab_proc[i].strlen)
	{
		g_shell.tab_proc[i].str[l] = g_shell.line[j];
		l++;
		j++;
	}
	g_shell.tab_proc[i].str[l] = '\0';
	strlentoken(i);
	g_shell.tab_proc[i].tab_token = malloc(sizeof(t_token) * g_shell.tab_proc[i].nb_tokens); //securiser gc_2;
	l = 0;
	while (l < g_shell.tab_proc[i].nb_tokens)
	{
		// printf("taille malloc process[%d][%d] : %d \n", i, l, malloctoken(i, g_shell.tab_proc[i].str));
		g_shell.tab_proc[i].tab_token[l].word = malloc(sizeof(char *) * (malloctoken(i, g_shell.tab_proc[i].str) + 1));
		copy_token(l, i, g_shell.tab_proc[i].str);
		printf("mot %d du process %d : %s\n", l, i, g_shell.tab_proc[i].tab_token[l].word);
		l++;
	}
	return (0);
}

static void	strlentoken(int j)
{
	int i;
	
	i = 0;
	g_shell.tab_proc[j].nb_tokens = 0;
	while(g_shell.tab_proc[j].str[i])
	{
		while (g_shell.tab_proc[j].str[i] == ' ')
		{
			i++;
			if (!g_shell.tab_proc[j].str[i])
				return ;
		}
		while (g_shell.tab_proc[j].str[i] != ' ' && g_shell.tab_proc[j].str[i] != '\0')
		{
			if (g_shell.tab_proc[j].str[i] == '"')
			{
				i++;
				while (g_shell.tab_proc[j].str[i] != '"')
				{
					i++;
					if (g_shell.tab_proc[j].str[i] == '"')
						break;
				}
			}
			if (g_shell.tab_proc[j].str[i] == '\'')
			{
				i++;
				while (g_shell.tab_proc[j].str[i] != '\'')
				{
					i++;
					if (g_shell.tab_proc[j].str[i] == '\'')
						break;
				}
			}
			i++;
		}
		g_shell.tab_proc[j].nb_tokens++;
	}
}

int	init_processes(void)
{
	int	i;
	int	j;
	int index;

	index = 0;
	i = 0;
	j = ft_strlen(g_shell.line);
	while (i < g_shell.nb_proc)
	{
		if (i == 0)
			g_shell.tab_proc[i].start = 0;
		else
			g_shell.tab_proc[i].start = g_shell.tab_index_pipes[i - 1] + 1;
		if (i == (g_shell.nb_proc - 1))
			g_shell.tab_proc[i].end = j;
		else
			g_shell.tab_proc[i].end = g_shell.tab_index_pipes[i];
		if (ft_create_proc_str(i) == 1)
			return (1);
		printf("NB TOKEN: %d\n", g_shell.tab_proc[i].nb_tokens);
		i++;
	}
	return (0);
}

int	val_strncmp(char *stra, char *val, int length)
{
	int		i;
	char	*str1;
	char	*str2;

	str1 = stra;
	str2 = val;
	i = 0;
	while (length > i && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (!str2[i])
		return (0);
	else
		return (1);
}

int ft_gestion_var(int i, char *str)
{
	int		j;
	int		k;
	t_env	*temp;
	
	g_shell.tab_proc[i].index++;
	printf(" ft_gestion_var index = %c %d\n", str[g_shell.tab_proc[i].index], g_shell.tab_proc[i].index);
	j = g_shell.tab_proc[i].index;
	if (ft_isalpha(str[g_shell.tab_proc[i].index]) == 1 && str[g_shell.tab_proc[i].index] != '_')
		return (1);
	g_shell.tab_proc[i].index++;
	printf(" ft_gestion_var index = %c %d\n", str[g_shell.tab_proc[i].index], g_shell.tab_proc[i].index);
	while (ft_isalnum(str[g_shell.tab_proc[i].index]) == 0 || str[g_shell.tab_proc[i].index] == '_')
		g_shell.tab_proc[i].index++;
	// printf(" ft_gestion_var index = %d\n", g_shell.tab_proc[i].index);
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.tab_proc[i].index - j));

		if (k == 0)
		{
			k = ft_strlen(temp->val);
			// printf(" ft_gestion_var = %d\n", k);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

int	malloctoken(int i, char	*str)
{
	int	count;

	count = 0;
	while (str[g_shell.tab_proc[i].index] == ' ')
		g_shell.tab_proc[i].index++;
	while(str[g_shell.tab_proc[i].index] && str[g_shell.tab_proc[i].index] != ' ')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
			count += ft_gestion_var(i, str);
		else if (str[g_shell.tab_proc[i].index] == '"')
			{
				// puts("lol");
				g_shell.tab_proc[i].index++;
				// printf("index = %d\n", g_shell.tab_proc[i].index);
				while (str[g_shell.tab_proc[i].index] != '"')
				{
					// printf("indexxxxxxxxxxxxxxxxxxxxx = %d\n", g_shell.tab_proc[i].index);
					if (str[g_shell.tab_proc[i].index] == '$')
						count += ft_gestion_var(i, str);
					else
					{
						count++;
						g_shell.tab_proc[i].index++;
					}
				}
				g_shell.tab_proc[i].index++;
			}
		else if (str[g_shell.tab_proc[i].index] == '\'')
			{
				g_shell.tab_proc[i].index++;
				while (str[g_shell.tab_proc[i].index] != '\'')
				{
					count++;
					g_shell.tab_proc[i].index++;
				}
				g_shell.tab_proc[i].index++;
			}
		else
		{
			g_shell.tab_proc[i].index++;
			count++;
		}
	}
	printf(" count%d\n", count);
	return(count);
}

int ft_lexer(void)
{
	if (ft_lexer_prompt() != 0)
		return (1);
	if (ft_malloc_processes() == 1)
		return (1);
	if (init_processes() == 1)
		return (1);
	(void)strlentoken(0);
	printf("INDEX PIPE: %d\n", g_shell.tab_index_pipes[0]);
	printf("INDEX PIPE: %d\n", g_shell.tab_index_pipes[1]);
	
	return (0); //le prompt peut etre parse
}
