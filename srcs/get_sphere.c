#include "../inc/rtv1.h"

static int get_pos(char *s, t_sphere *sphere)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (-1);
    sphere->x = ft_getfloat(tab[0]);
    sphere->y = ft_getfloat(tab[1]);
    sphere->z = ft_getfloat(tab[2]);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_col(char *s, t_sphere *sphere)
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
    sphere->color[0] = r;
    sphere->color[1] = g;
    sphere->color[2] = b;
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_attribu(char **tab, int i, t_sphere *sphere)
{
    char **tab2;

    tab2 = ft_strsplit(tab[i], ':');
    if (!tab2 || !tab2[0] || !tab2[1])
        return (-1);
    if (ft_strcmp(tab2[0], "pos") == 0)
    {
        if (get_pos(tab2[1], sphere) == -1)
            return (-1);
    }
    else if (ft_strcmp(tab2[0], "color") == 0)
    {
        if (get_col(tab2[1], sphere) == -1)
            return (-1);
    }
    else if (ft_strcmp(tab2[0], "rad") == 0)
        sphere->r = ft_getfloat(tab2[1]);
    else
        return (-1);
    free(tab2[0]);
    free(tab2[1]);
    free(tab2);
    return (0);
}

t_sphere *get_sphere(char *s)
{
    int i;
    char **tab;
    t_sphere *sphere;

    i = 0;
    tab = ft_strsplit(s, ';');
    if (!tab)
        return (NULL);
    if ((sphere = malloc(sizeof(t_sphere))) == NULL)
        return (NULL);
    sphere->next = NULL;
    while (tab[i])
    {
        if (get_attribu(tab, i, sphere) == -1)
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
    return (sphere);
}