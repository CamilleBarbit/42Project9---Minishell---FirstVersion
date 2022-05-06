/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:31:52 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/06 18:53:04 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

void	add_env(t_env *env, t_env *to_add)
{
	t_env *temp;

	temp = env;
	while(temp->next)
		temp = temp->next;
	temp->next = to_add;
}
char	*env_dup(char *src, int size, t_gc *gc)
{
	char	*dest;
	int		returnvalue;

	
	// printf("%d", size);
	// printf("%s", src);
	dest = ft_malloc("str", size, "erreur malloc var/val lst_env", gc);
	returnvalue = ft_strlcpy(dest, src, size);
	// printf("%s", dest);
	// puts("lol");
	if (returnvalue == 0)
		puts("return value de ft_strlcpy = 0"); //a gerer?
	return (dest);
}

t_env   *get_envlst(char *var, t_gc *gc)
{
    t_env   *env_lst;
    int	i;

	i = 0;
	env_lst = ft_malloc("env", 0, "erreur malloc lst_env", gc);
	while (var[i] != '=')
		i++;
	env_lst->val = env_dup(var + i + 1, ft_strlen(var + i), gc);
	env_lst->var = env_dup(var, i + 1, gc);
	env_lst->next = NULL;
	return (env_lst);
}

 t_env	*get_env(char **env, t_gc *gc)
 {
	t_env	*env_lst;
	int		i;

	i = 0;
	env_lst = get_envlst(env[i], gc);
	i++;
	while (env[i])
	{
		add_env(env_lst, get_envlst(env[i], gc));
		i++;
	}
	return (env_lst);
 }

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while(temp)
	{
		printf("%s", temp->var);
		printf("=");
		printf("%s\n", temp->val);
		if (!temp->next)
			break;
		temp = temp->next;
	}
}
