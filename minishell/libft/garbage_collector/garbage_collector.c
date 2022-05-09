/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:19 by aboudjel          #+#    #+#             */
/*   Updated: 2022/05/06 19:06:23 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free(t_gc	*lst)
{
	t_gc	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		if (!tmp->data && !tmp->next)
			break ;
		free(tmp->data);
		tmp = tmp->next;
	}
	ft_gcclear(lst);
}

void	*ft_malloc(char *type, int size, char *msg, t_gc *lst)
{
	t_gc	*mallocs;

	mallocs = lst;
	if (ft_strcmp(type, "str"))
		return (malloc_str(size, msg, mallocs));
	if (ft_strcmp(type, "int"))
		return (malloc_int(size, msg, mallocs));
	if (ft_strcmp(type, "tabstr"))
		return (malloc_int(size, msg, mallocs));
	if (ft_strcmp(type, "env"))
		return (malloc_env(msg, mallocs));
	else
		return (NULL);
}

void	*malloc_str(int size, char *errormsg, t_gc *mallocs)
{
	char	*str;

	str = malloc(sizeof(char) * size + 1);
	if (!str)
	{
		ft_putstr_fd(errormsg, 2);
		ft_free(mallocs);
		exit(EXIT_FAILURE);
	}
	if (mallocs->data == NULL)
		mallocs->data = str;
	else
		ft_gcadd_back(mallocs, ft_gcnew(str, mallocs));
	return (str);
}

void	*malloc_tabstr(int size, char *errormsg, t_gc *mallocs)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
	{
		ft_putstr_fd(errormsg, 2);
		ft_free(mallocs);
		exit(EXIT_FAILURE);
	}
	if (mallocs->data == NULL)
		mallocs->data = tab;
	else
		ft_gcadd_back(mallocs, ft_gcnew(tab, mallocs));
	return (tab);
}

void	*malloc_int(int size, char *errormsg, t_gc *mallocs)
{
	char	*nbr;

	nbr = malloc(sizeof(char) * size);
	if (!nbr)
	{
		ft_putstr_fd(errormsg, 2);
		ft_free(mallocs);
		exit(EXIT_FAILURE);
	}
	if (mallocs->data == NULL)
		mallocs->data = nbr;
	else
		ft_gcadd_back(mallocs, ft_gcnew(nbr, mallocs));
	return (nbr);
}
