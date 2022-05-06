
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <errno.h>

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}t_gc;

void	*malloc_int(int size, char *errormsg, t_gc *mallocs);
void	*malloc_str(int size, char *errormsg, t_gc *mallocs);
void	*malloc_env(char *errormsg, t_gc *mallocs);
void	ft_free(t_gc	*lst);
void	*ft_malloc(char *type, int size, char *msg, t_gc *lst);
void	ft_gcadd_back(t_gc *lst, t_gc *new);
void	ft_gcclear(t_gc *lst);
t_gc	*ft_gcnew(void *data, t_gc *lst);

// -----------------------------------------------------------------------------------
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (1);
	else
		return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

t_gc	*ft_gcnew(void *data, t_gc *lst)
{
	t_gc	*n;

	n = malloc(sizeof(t_gc));
	if (!n)
	{
		ft_putstr_fd("Error: Malloc failed", 2);
		ft_free(lst);
		exit(EXIT_FAILURE);
	}
	n->data = data;
	n->next = NULL;
	return (n);
}

void	ft_gcadd_back(t_gc *lst, t_gc *new)
{
	if (!lst || !new)
		return ;
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	lst->next = new;
}

void	ft_gcclear(t_gc *lst)
{
	t_gc	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	lst = NULL;
}

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


void	*malloc_env(char *errormsg, t_gc *mallocs)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		ft_putstr_fd(errormsg, 2);
		ft_free(mallocs);
		exit(EXIT_FAILURE);
	}
	if (mallocs->data == NULL)
		mallocs->data = env;
	else
		ft_gcadd_back(mallocs, ft_gcnew(env, mallocs));
	return (env);
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

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (--size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// -------------------------------------------------------------------

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
int	main(int argc, char **argv, char **env)
{
	t_gc	*gc;
	t_env	*envii;

	(void)argc;
	(void)argv;
	gc = ft_gcnew(NULL, NULL);
	envii = get_env(env, gc);
	(void)envii;
	print_env(envii);
	ft_free(gc);
	return (0);
}