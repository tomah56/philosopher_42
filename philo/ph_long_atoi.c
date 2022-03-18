/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_long_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:33:51 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/18 13:54:52 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	char	*line;

	line = "\t\n\v\f\r ";
	while (*line != '\0')
	{
		if (*line == c)
			return (1);
		line++;
	}
	return (0);
}

static long	overflow(long long int num, long long int sign)
{
	if ((sign * num) > LONG_MAX / 10)
		return (-1);
	else if ((sign * num) < LONG_MIN / 10)
		return (0);
	else
		return (2);
}

static long	create(const char *str, int n, long long int sign)
{
	int				i;
	int				j;
	int				k;
	long long int	temp;

	i = n;
	k = n;
	while (str[i] != '\0' && str[i] < 58 && str[i] > 47)
		i++;
	if (!(str[i] < 58 && str[i] > 47) && str[i] != '\0')
		return (0);
	temp = 0;
	while (i > n)
	{
		j = 48;
		while (j < 58 && str[k] != j)
			j++;
		temp += (j - 48);
		if (overflow(temp, sign) == 0 || overflow(temp, sign) == -1)
			return (overflow(temp, sign));
		if (--i != n)
			temp *= 10;
		k++;
	}
	return ((sign * temp));
}

long	ft_long_atoi(const char *str)
{
	int				i;
	long long int	sign;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 43)
	{
		sign = 1;
		i++;
	}
	else if (str[i] == 45)
	{
		sign = -1;
		i++;
	}
	if (!(str[i] < 58 && str[i] > 47))
		return (0);
	return (create(str, i, sign));
}
