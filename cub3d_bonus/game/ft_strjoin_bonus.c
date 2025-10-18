/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:15:52 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/10 21:17:26 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../parsing/cub.h"

static void	my_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	string = (char *) ft_malloc(((len_s1 + len_s2) + 1) * sizeof(char), 1);
	if (!string)
		return (NULL);
	my_strlcpy(string, s1, len_s1 + 1);
	my_strlcpy(string + len_s1, s2, len_s2 + 1);
	return (string);
}