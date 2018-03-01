#include "../inc/rtv1.h"

static int get_pos(char *s, t_cam *cam)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (-1);
    cam->camx = ft_getnbr(tab[0]);
    cam->camy = ft_getnbr(tab[1]);
    cam->camz = ft_getnbr(tab[2]);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static int get_dir(char *s, t_cam *cam)
{
    char **tab;

    tab = ft_strsplit(s, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
    {
        ft_putendl(s);
        return (-1);
    }
    cam->vdirx = ft_getnbr(tab[0]);
    cam->vdiry = ft_getnbr(tab[1]);
    cam->vdirz = ft_getnbr(tab[2]);
    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);
    return (0);
}

static void sup_var(t_cam *cam)
{
    cam->vrightx = 1.0f;
    cam->vrighty = 0.0f;
    cam->vrightz = 0.0f;
    cam->vupx = 0.0f;
    cam->vupy = 1.0f;
    cam->vupz = 0.0f;
    cam->fovh = (float)(HEIGHT / 1000.0f);
    cam->fovw = (float)(WIDTH / 1000.0f);
    cam->fovd = 1.0f;
    cam->is_init = INIT;
}

t_cam *get_cam(char *s)
{
    int i;
    char **tab;
    char **tab2;
    t_cam *cam;

    i = 0;
    cam = malloc(sizeof(t_cam));
    cam->is_init = NOTINIT;
    tab = ft_strsplit(s, ';');
    while (tab[i])
    {
        tab2 = ft_strsplit(tab[i], ':');
        if (ft_strcmp(tab2[0], "pos") == 0)
            get_pos(tab2[1], cam);
        if (ft_strcmp(tab2[0], "dir") == 0)
            get_dir(tab2[1], cam);
        free(tab2[0]);
        free(tab2[1]);
        free(tab2);
        i++;
    }
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    sup_var(cam);
    return (cam);
}