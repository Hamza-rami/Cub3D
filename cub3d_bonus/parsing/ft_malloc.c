#include "cub.h"

t_gc	*new_node(void *ptr)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}


void	add_back(t_gc **list, t_gc *new)
{
	t_gc	*tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_free_all(t_gc **mlc)
{
	t_gc	*tmp;

	while (*mlc)
	{
		tmp = (*mlc)->next;
		free((*mlc)->ptr);
		free(*mlc);
		*mlc = tmp;
	}
}

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	size_t			i;
// 	unsigned char	*p;
// 	unsigned char	value;

// 	i = 0;
// 	p = (unsigned char *)b;
// 	value = (unsigned char)c;
// 	while (i < len)
// 	{
// 		p[i] = value;
// 		i++;
// 	}
// 	return (b);
// }

void	*ft_malloc(size_t size, int flag)
{
	static t_gc	*mlc;
	t_gc		*new;
	void		*ptr;

	if (flag == 1)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_free_all(&mlc), printf("ft_malloc failed\n"), exit(1),
				NULL);
		// ft_memset(ptr, 0, size);
		new = new_node(ptr);
		if (!new)
			return (ft_free_all(&mlc), free(ptr), printf("ft_malloc failed\n"),
				exit(1), NULL);
		add_back(&mlc, new);
		return (ptr);
	}
	else if (flag == 0)
		ft_free_all(&mlc);
	return (NULL);
}
