#include "lem_in.h"

int		ft_atoli(const char *str)
{
	int			i;
	long long	nbr;

	i = 0;
	nbr = 0;
	while (*str == '\t' || *str == '\n'
			|| *str == ' ' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str++;
	if (str[0] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
    if (!ft_isdigit(str[i]) && str[i] != '\0')
        ft_outerror();
	if (str[0] == '-')
		nbr = nbr * -1;
    if (nbr > INT_MAX)
        return (INT_MAX);
	return ((int)nbr);
}