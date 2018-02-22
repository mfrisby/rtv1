#include "../inc/rtv1.h"

static int get_pos(char *s, t_plan *plan)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (-1);
    plan->x = ft_getfloat(tab[0]);
    plan->y = ft_getfloat(tab[1]);
    plan->z = ft_getfloat(tab[2]);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_dir(char *s, t_plan *plan)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (-1);
    plan->dirx = ft_getfloat(tab[0]);
    plan->diry = ft_getfloat(tab[1]);
    plan->dirz = ft_getfloat(tab[2]);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_col(char *s, t_plan *plan)
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
    plan->color[0] = r;
    plan->color[1] = g;
    plan->color[2] = b;
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}
static int get_attribu(char **tab, int i, t_plan *plan)
{
    char **tab2;
    
    tab2 = ft_strsplit(tab[i], ':');
    if (!tab2 || !tab2[0] || !tab2[1])
        return (-1);
    if (ft_strcmp(tab2[0], "pos") == 0)
    {
        if (get_pos(tab2[1], plan) == -1)
            return (-1);
    }
    else if (ft_strcmp(tab2[0], "dir") == 0)
    {
        if (get_dir(tab2[1], plan) == -1)
            return (-1);
    }
    else if (ft_strcmp(tab2[0], "color") == 0)
    {
        if (get_col(tab2[1], plan) == -1)
            return (-1);
    }
    else
        return (-1);
    free(tab2[0]);
    free(tab2[1]);
    free(tab2);
    return (0);
}

t_plan      *get_plan(char *s)
{
    int i;
    char **tab;
    t_plan *plan;

    i = 0;
    tab = ft_strsplit(s, ';');
    if (!tab || (plan = malloc(sizeof(t_plan))) == NULL)
        return (NULL);
    plan->next = NULL;
    while (tab[i])
    {
        if (get_attribu(tab, i, plan) == -1)
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
    return (plan);
}