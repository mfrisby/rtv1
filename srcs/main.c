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

void        init_sphere(t_sphere **sphere)
{
    (*sphere) = malloc(sizeof(t_sphere));
    (*sphere)->x = 0;
    (*sphere)->y = 0;
    (*sphere)->z = 5;
    (*sphere)->r = 0.8;
    (*sphere)->color = COLORBLUE;
}
void        init_sphere2(t_sphere **sphere)
{
    (*sphere) = malloc(sizeof(t_sphere));
    (*sphere)->x = 0.5;
    (*sphere)->y = 0;
    (*sphere)->z = 3;
    (*sphere)->r = 0.6;
    (*sphere)->color = COLORGREEN;
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

t_ray    *init_ray(int x, int y, t_upleft *upleft, t_cam *cam, t_pix *pix)
{
    t_ray   *ray;

    float pixX = 0;
    float pixY = 0;
    float pixZ = 0;
    float longueur = 0;

    ray = malloc(sizeof(t_ray));
    //position du pixel courant
    pixX = upleft->x + cam->vrightx * pix->xindent * x - cam->vupx * pix->yindent * y;
    pixY = upleft->y + cam->vrighty * pix->xindent * x - cam->vupy * pix->yindent * y;
    pixZ = upleft->z + cam->vrightz * pix->xindent * x - cam->vupz * pix->yindent * y;
    
    longueur = sqrt((float)((pixX * pixX) + (pixY * pixY) + (pixZ * pixZ)));
    
    ray->x = (pixX - cam->camx) / longueur;
    ray->y = (pixY - cam->camy) / longueur;
    ray->z = (pixZ - cam->camz) / longueur;
   
    return (ray);
}

void    calcul_sphere(t_sphere *s, t_cam *cam, t_ray *ray, t_mlx *mlx, int x, int y)
{
    int delta;
    float a;
    float b;
    float c;
    float csx;
    float csy;
    float csz;

    csz = cam->camz - s->z;
    csy= cam->camy - s->y;
    csx = cam->camx - s->x;
    a = (ray->x * ray->x) + (ray->y * ray->y) + (ray->z * ray->z);
    b = 2 * (ray->x * (cam->camx - s->x) + ray->y * (cam->camy - s->y) + ray->z * (cam->camz - s->z));
    c = (csx * csx) + (csy * csy) + (csz * csz) - (s->r * s->r);
    delta = (b * b) - 4 * a * c;
    b *= -1;
    if (delta > 0)
    {
        //deux intersection, on prend la plus proche
        float t1 = (b + sqrt(delta)) / (2 * a);
        float t2 = (b - sqrt(delta)) / (2 * a);
        //si t < 0 l'intersection est derriere la cam
        if (t1 < t2 && t1 < 0)
        {
            mlx_pixel_put(mlx->mlx, mlx->win, x, y, s->color);
        }
        else if (t2 <= t1 && t2 < 0)
        {
            mlx_pixel_put(mlx->mlx, mlx->win, x, y, s->color);
        }
    }
    else if (delta == 0)
    {
        //une seule intersection
        float t = b / (2 * a);
        if (t > 0)
            mlx_pixel_put(mlx->mlx, mlx->win, x, y, s->color);
    }
}


int     main(void)
{
    int         x;
    int         y;
    t_mlx       *mlx;
    t_cam       *cam;
    t_upleft    *upleft;
    t_ray       *ray;    
    t_sphere    *sphere;
    t_sphere    *sphere2;
    t_pix       *pix;
    
    x = 0;
    y = 0;
    mlx = NULL;
    upleft = NULL;
    pix = NULL;
    cam = NULL;
    ray = NULL;
    sphere = NULL;
    sphere2 = NULL;
    init_mlx(&mlx);
    init_cam(&cam);
    init_space(cam, &pix, &upleft);
    init_sphere(&sphere);
    init_sphere2(&sphere2);
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ray = init_ray(x, y, upleft, cam, pix);
            calcul_sphere(sphere, cam, ray, mlx, x, y);
            calcul_sphere(sphere2, cam, ray, mlx, x, y);
            x++;
        }
        y++;
    }
    mlx_loop(mlx->mlx);
    return (0);
}