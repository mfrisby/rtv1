#include "../inc/rtv1.h"

static t_plan        *init_plan()
{
    t_plan *plan;

    plan = malloc(sizeof(t_plan));
    //dir correspond au produit vectoriel (quon definit plutot que de calculer)
    plan->dirx = 0.0f;
    plan->diry = -1.0f;
    plan->dirz = 0.0f;
    //pos correspond a un point quelquonc dans le plan 
    plan->posx = 0.0f;
    plan->posy = 1.0f;
    plan->posz = 0.0f;
    plan->color = COLORRED;
    return (plan);
}

static t_sphere        *init_sphere()
{
    t_sphere    *sphere;

    sphere = malloc(sizeof(t_sphere));
    sphere->x = 0;
    sphere->y = 0.2;
    sphere->z = 5;
    sphere->r = 0.8;
    sphere->color = COLORBLUE;
    return (sphere);
}

void        calcul_plan(t_cam *cam, t_ray *ray, t_mlx *mlx, int x, int y)
{
    float   d;
    float   t;
    t_plan *plan;

    plan = init_plan();
    d = -(plan->dirx * plan->posx + plan->diry * plan->posy + plan->dirz * plan->posz);
    t = -((plan->posx * cam->camx + plan->posy * cam->camy + plan->posz * cam->camz + d) / (plan->posx * ray->x + plan->posy * ray->y + plan->posz * ray->z));
    if (t > 0)
    {
        mlx_pixel_put(mlx->mlx, mlx->win, x, y, plan->color);
    }
}

void    calcul_sphere(t_cam *cam, t_ray *ray, t_mlx *mlx, int x, int y)
{
    int delta;
    float a;
    float b;
    float c;
    float csx;
    float csy;
    float csz;
    t_sphere *s;

    s = init_sphere();
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