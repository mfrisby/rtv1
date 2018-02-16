#include "../inc/rtv1.h"

void    init_cam(t_cam **cam)
{
    (*cam) = malloc(sizeof(t_cam));
    //origine
    (*cam)->camx = 0.0f;
    (*cam)->camy = 0.0f;
    (*cam)->camz = 0.0f;
    //vecdir
    (*cam)->vdirx = 0.0f;
    (*cam)->vdiry = 0.0f;
    (*cam)->vdirz = -1.0f;
    //vecright
    (*cam)->vrightx = 1.0f;
    (*cam)->vrighty = 0.0f;
    (*cam)->vrightz = 0.0f;
    //vecup
    (*cam)->vupx = 0.0f;
    (*cam)->vupy = 1.0f;
    (*cam)->vupz = 0.0f;
    //fov
    (*cam)->fovh = 0.35f;
    (*cam)->fovw = 0.5f;
    (*cam)->fovd = 1.0f;
}

void        init_mlx(t_mlx **mlx)
{
    (*mlx) = malloc(sizeof(t_mlx));
    (*mlx)->mlx = mlx_init();
    (*mlx)->win = mlx_new_window((*mlx)->mlx, WIDTH, HEIGHT, "RTV1");
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


int     main(void)
{
    t_mlx       *mlx;
    t_cam       *cam;
    t_upleft    *upleft;
    t_pix       *pix;
    
    mlx = NULL;
    cam = NULL;
    upleft = NULL;
    pix = NULL;
    init_mlx(&mlx);
    init_cam(&cam);
    init_space(cam, &pix, &upleft);
    rayloop(mlx, cam, upleft, pix);
    mlx_loop(mlx->mlx);
    return (0);
}