#include "../inc/rtv1.h"

float        calcul_plan(t_cam *cam, t_ray *ray, t_plan *plan)
{
    float   d;
    float   t;

    d = -(plan->dirx * plan->posx + plan->diry * plan->posy + plan->dirz * plan->posz);
    t = -((plan->posx * cam->camx + plan->posy * cam->camy + plan->posz * cam->camz + d) / (plan->posx * ray->x + plan->posy * ray->y + plan->posz * ray->z));
    return (t);
}

float    calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere)
{
    float delta;
    float a;
    float b;
    float c;
    float t1;
    float t2;

    a = pow(ray->x, 2) + pow(ray->y, 2) + pow(ray->z, 2);
    b = 2 * (ray->x * (cam->camx - sphere->x) + ray->y * (cam->camy - sphere->y) + ray->z * (cam->camz - sphere->z));
    c = (pow(cam->camx - sphere->x, 2) + pow(cam->camy - sphere->y, 2) + pow(cam->camz - sphere->z, 2)) - pow(sphere->r, 2);
    delta = (b * b) - 4 * a * c;
    b = -b;
    if (delta > 0.0f)
    {
        ft_putstr("x");
        t1 = (b + sqrt(delta)) / (2 * a);
        t2 = (b - sqrt(delta)) / (2 * a);
        if (t1 <= t2)
            return (t1);
        return (t2);
    }
    else if (delta == 0)
       return (b / (2 * a));
    return (-1);
}