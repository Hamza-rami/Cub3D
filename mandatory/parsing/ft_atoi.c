/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:13:28 by hrami             #+#    #+#             */
/*   Updated: 2025/10/26 11:10:01 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_skip(char const *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if ((str[*i] == '+' || str[*i] == '-'))
	{
		if (str[*i] == '-')
		{
			printf("Error: color value Not Exact");
			ft_malloc(0, 0);
			exit(1);
		}
		(*i)++;
	}
}

int	ft_atoi(char *str)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	ft_skip(str, &i);
	while (str[i] && str[i] != '\n')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Error: color value Not Exact");
			ft_malloc(0, 0);
			exit(1);
		}
		r = r * 10 + (str[i] - '0');
		if (r > 2147483647)
			return (printf("Error: color value Not Exact"),
				ft_malloc(0, 0), exit(1), 0);
		i++;
	}
	if (r > 255)
		return (printf("Error: color value out of range"),
			ft_malloc(0, 0), exit(1), 0);
	return (r);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
