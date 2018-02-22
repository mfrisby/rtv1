#include "../inc/rtv1.h"

static float    get_dot(char *str, int nbr, int i)
{
    float   result;
    float     mult;

    mult = 1.0f;
    result = (float)nbr;
    while (i != 0)
    {
        if (str[i] == '.')
            break;
        i--;
    }
    if (str[0] == '-' || str[0] == '+')
        i--;
    while (i > 0 && (str[i] != '-' && str[i] != '+'))
    {
        mult *= 10;
        i--;
    }
    if (mult < 10)
        return (result);
    return (result/mult);
}

float		ft_getfloat(char *str)
{
	int		nbr;
	int		i;
    int		neg;

	nbr = 0;
    i = 0;
    neg = 0;
    if (str[0] == '-')
    {
        neg = 1;
        i = 1;
    }
    else if (str[0] == '+')
        i = 1;
    while (str[i] != '\0')
	{
        if (str[i] == '.')
        {
            i++;
            continue;
        }
        else if (str[i] < '0' || str[i] > '9')
            return (-1);
        nbr = nbr * 10 + (str[i] - '0');
		i++;
    }
	if (neg == 1)
        nbr = -nbr;
	return (get_dot(str, nbr, i));
}
