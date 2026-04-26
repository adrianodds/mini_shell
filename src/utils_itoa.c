#include "../minishell.h"

static int	number_len(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nb;
	int		len;
	int		sign;

	nb = n;
	len = number_len(nb);
	sign = 0;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nb < 0)
	{
		sign = 1;
		result[0] = '-';
		nb = -nb;
	}
	while (len > sign)
	{
		len--;
		result[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (result);
}
