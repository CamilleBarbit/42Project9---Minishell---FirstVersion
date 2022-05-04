/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:31:52 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/04 15:40:51 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env   get_env(char **env, t_gc *gc)
{
    t_env   *env_lst;
    int     i;

    i = 0;
    while(env[i])
    {
        
    }
}

char	*ft_envdup(char *src, int size, t_gc *gc)
{
	char	*dest;
    
	dest = ft_malloc((ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	return (ft_strcpy(src, dest));
}