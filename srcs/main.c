#include "../inc/rtv1.h"

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
    
    pix = NULL;
    upleft = NULL;
    data = malloc(sizeof(t_data));
    data->head = NULL;
    if (ac < 2)
    {
        printf("File needed.");
        return (0);
    }
    parse_file(av[1], &data);
   // data->head->next = NULL;
    init_mlx(&data);
    init_space(data->cam, &pix, &upleft);
    printf("cam: x %f y %f z %f \n", data->cam->camx, data->cam->camy, data->cam->camz);
    printf("cam: dirx %f diry %f dirz %f\n", data->cam->vdirx, data->cam->vdiry, data->cam->vdirz);
    rayloop(data, upleft, pix);
    mlx_loop(data->mlx);
    return (0);
}