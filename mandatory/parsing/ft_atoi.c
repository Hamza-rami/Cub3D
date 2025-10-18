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
			ft_malloc(0,0);
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
			ft_malloc(0,0);
			exit(1);
		}
		r = r * 10 + (str[i] - '0');
		if (r > 2147483647)
		{
			printf("Error: color value Not Exact");
			ft_malloc(0,0);
			exit(1);
		}
		i++;
	}
	if (r > 255)
	{
		printf("Error: color value out of range");
		ft_malloc(0,0);
		exit(1);
	}
	return (r);
}
