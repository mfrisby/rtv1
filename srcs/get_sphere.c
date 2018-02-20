#include "../inc/rtv1.h"

static int get_pos(char *s, t_sphere *sphere)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
    {
        ft_putendl(s);
        return (-1);
    }
    sphere->x = ft_getnbr(tab[0]);
    sphere->y = ft_getnbr(tab[1]);
    sphere->z = ft_getnbr(tab[2]);
    sphere->x /= 10.0f;
    sphere->y /= 10.0f;
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_color(char *s, t_sphere *sphere)
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
    sphere->color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

t_sphere *get_sphere(char *s)
{
    int i;
    char **tab;
    char **tab2;
    t_sphere *sphere;

    i = 0;
    tab = ft_strsplit(s, ';');
    if (!tab)
        return (NULL);
    sphere = malloc(sizeof(t_sphere));
    while (tab[i])
    {
        tab2 = ft_strsplit(tab[i], ':');
        if (ft_strcmp(tab2[0], "pos") == 0)
        {
            if (get_pos(tab2[1], sphere) == -1)
                return (NULL);
        }
        else if (ft_strcmp(tab2[0], "color") == 0)
        {
            if (get_color(tab2[1], sphere) == -1)
                return (NULL);
        }
        else if (ft_strcmp(tab2[0], "rad") == 0)
            sphere->r = ft_getnbr(tab2[1]);
        i++;
        free(tab2[0]);
        free(tab2[1]);
        free(tab2);
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