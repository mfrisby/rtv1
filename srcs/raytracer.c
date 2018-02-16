#include "../inc/rtv1.h"

static t_ray    *init_ray(int x, int y, t_upleft *upleft, t_cam *cam, t_pix *pix)
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

static void  raytrace(t_ray *ray, t_cam *cam, t_mlx *mlx, int x, int y)
{
    float t1;
    float t2;

    //TODO
    //parcourir chque objet
    //recuperer la taille du rayon
    //colorier le pixel de l'object le plus proche
    t1 = calcul_plan(cam, ray);
    t2 = calcul_sphere(cam, ray);
    if (t1 > 0 && t1 > t2)
         mlx_pixel_put(mlx->mlx, mlx->win, x, y, COLORRED);
    else if (t2 > 0)
        mlx_pixel_put(mlx->mlx, mlx->win, x, y, COLORBLUE);
    //return (color);
}

void        rayloop(t_mlx *mlx, t_cam *cam, t_upleft *upleft, t_pix *pix)
{
    int     x;
    int     y;
    t_ray   *ray;

    ray = NULL;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ray = init_ray(x, y, upleft, cam, pix);
            raytrace(ray, cam, mlx, x, y);
            x++;
        }
        y++;
    }
}