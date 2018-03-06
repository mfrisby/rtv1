#include "../inc/rtv1.h"

static int get_pos(char *s, t_cone *cone)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (-1);
    cone->x = ft_getfloat(tab[0]);
    cone->y = ft_getfloat(tab[1]);
    cone->z = ft_getfloat(tab[2]);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_col(char *s, t_cone *cone)
{
    int     r;
    int     g;
    int     b;
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (-1);
    r = ft_getnbr(tab[0]);
    g = ft_getnbr(tab[1]);
    b = ft_getnbr(tab[2]);
    cone->color[0] = r;
    cone->color[1] = g;
    cone->color[2] = b;
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}
static int get_attribu(char **tab, int i, t_cone *cone)
{
    char **tab2;
    
    tab2 = ft_strsplit(tab[i], ':');
    if (!tab2 || !tab2[0] || !tab2[1])
        return (-1);
    if (ft_strcmp(tab2[0], "pos") == 0)
    {
        if (get_pos(tab2[1], cone) == -1)
            return (-1);
    }
    else if (ft_strcmp(tab2[0], "ang") == 0)
        cone->r = pow(tan(ft_getnbr(tab2[1]) * 0.0174533f), 2);
    else if (ft_strcmp(tab2[0], "color") == 0)
    {
        if (get_col(tab2[1], cone) == -1)
            return (-1);
    }
    else
        return (-1);
    free(tab2[0]);
    free(tab2[1]);
    free(tab2);
    return (0);
}

t_cone      *get_cone(char *s)
{
    int i;
    char **tab;
    t_cone *cone;

    i = 0;
    tab = ft_strsplit(s, ';');
    if (!tab)
        return (NULL);
    if ((cone = malloc(sizeof(t_cone))) == NULL)
        return (NULL);
    cone->next = NULL;
    while (tab[i])
    {
        if (get_attribu(tab, i, cone) == -1)
            return (NULL);
        i++;
    }
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);    
    return (cone);
}