#include "../inc/rtv1.h"

t_data        *init_data()
{
    t_data      *data;

    ft_putendl("Init data struct.");
    if ((data = malloc(sizeof(t_data))) == NULL)
    {
        ft_printf("\033[0;31mError: %s\033[0m",strerror(errno));
        exit (0);
    }
    data->sphere_head = NULL;
    data->plan_head = NULL;
    data->cone_head = NULL;
    data->cylindre_head = NULL;
    data->object_vect = malloc(sizeof(t_ray));
    data->light_head = NULL;
    data->cam = NULL;
    data->mlx = NULL;
    data->win = NULL;
    data->current = NULL;
    return (data);
}

void        init_mlx(t_data **data)
{
    ft_putendl("Init mlx.");
    (*data)->mlx = mlx_init();
    (*data)->win = mlx_new_window((*data)->mlx, WIDTH, HEIGHT, "RTV1");
    if (!(*data)->mlx || !(*data)->win)
    {
        ft_putendl("\033[0;33mMLX init error.\033[0m");
        exit (0);
    }
}

void        init_space(t_cam *cam, t_pix **pix, t_upleft **upleft)
{
    ft_putendl("Init camera.");
    if (((*upleft) = malloc(sizeof(t_upleft))) == NULL || ((*pix) = malloc(sizeof(t_pix))) == NULL)
    {
        ft_printf("\033[0;31mError: %s\033[0m",strerror(errno));
        exit (0);
    }
    (*upleft)->x = cam->camx + ((cam->vdirx * cam->fovd) + (cam->vupx * (cam->fovh / 2.0f))) - (cam->vrightx * (cam->fovw / 2.0f));
    (*upleft)->y = cam->camy + ((cam->vdiry * cam->fovd) + (cam->vupy * (cam->fovh / 2.0f))) - (cam->vrighty * (cam->fovw / 2.0f));
    (*upleft)->z = cam->camz + ((cam->vdirz * cam->fovd) + (cam->vupz * (cam->fovh / 2.0f))) - (cam->vrightz * (cam->fovw / 2.0f));
    (*pix)->xindent = (float)cam->fovw / (float)WIDTH;
    (*pix)->yindent = (float)cam->fovh / (float)HEIGHT;
}

int     main(int ac, char **av)
{
    t_data          *data;
    t_upleft        *upleft;
    t_pix           *pix;
    
    if (ac < 2)
    {
        ft_putendl("File needed.");
        return (0);
    }
    pix = NULL;
    upleft = NULL;
    data = init_data();
    if  (parse_file(av[1], &data) == -1)
    {
        ft_putendl("Error while parsing file.");
        return (-1);
    }
    init_mlx(&data);
    init_space(data->cam, &pix, &upleft);
    ft_putendl("\033[0;32mInit OK; Please use escape key to quit.\033[0m");
    rayloop(data, upleft, pix);
    mlx_loop(data->mlx);
    free_heads(data);
    return (0);
}