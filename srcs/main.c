#include "../inc/rtv1.h"

t_data        *init_data()
{
    t_data      *data;

    data = malloc(sizeof(t_data));
    data->sphere_head = NULL;
    data->plan_head = NULL;
    data->cone_head = NULL;
    data->cylindre_head = NULL;
    data->light_head = NULL;
    data->cam = NULL;
    data->mlx = NULL;
    data->win = NULL;
    return (data);
}

void        init_mlx(t_data **data)
{
    (*data)->mlx = mlx_init();
    (*data)->win = mlx_new_window((*data)->mlx, WIDTH, HEIGHT, "RTV1");
}

void        init_space(t_cam *cam, t_pix **pix, t_upleft **upleft)
{
    (*upleft) = malloc(sizeof(t_upleft));
    (*pix) = malloc(sizeof(t_pix));
    //screen up-left
    (*upleft)->x = cam->camx + ((cam->vdirx * cam->fovd) + (cam->vupx * (cam->fovh / 2.0f))) - (cam->vrightx * (cam->fovw / 2.0f));
    (*upleft)->y = cam->camy + ((cam->vdiry * cam->fovd) + (cam->vupy * (cam->fovh / 2.0f))) - (cam->vrighty * (cam->fovw / 2.0f));
    (*upleft)->z = cam->camz + ((cam->vdirz * cam->fovd) + (cam->vupz * (cam->fovh / 2.0f))) - (cam->vrightz * (cam->fovw / 2.0f));
    //pixel size
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
        ft_putendl("problem while parsing file.");
        return (-1);
    }
    init_mlx(&data);
    init_space(data->cam, &pix, &upleft);
    rayloop(data, upleft, pix);
    mlx_loop(data->mlx);
    return (0);
}