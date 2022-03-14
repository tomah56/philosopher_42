#include "philo.h"

static int	pbe(long num, int count)
{
	char *base;

	base = "0123456789";
	if (num >= 10)
	{
		count = pbe(num / 10, count + 1);
		num = num % 10;
	}
	if (num < 10)
		write(1, &base[num], 1);
	return (count);
}

static int	stringpritn(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!(str))
		return (0);
	while (str[i] != '\0')
	{
		count += write(1, &str[i], 1);
		i++;
	}
	return (count);
}

int	crossroad(char *args, int number)
{
	int	count;

	count = 0;
	if (args != NULL)
		count += stringpritn(args);
	if (number > -1)
		count += pbe(number, 1);
	return (count);
}
