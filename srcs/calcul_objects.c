#include "../inc/rtv1.h"

float        calcul_plan(t_cam *cam, t_ray *ray, t_plan *plan)
{
    float   d;
    float   t;
    
    d = -(plan->dirx * plan->x + plan->diry * plan->y + plan->dirz * plan->z);
    t = -((plan->dirx * (cam->camx - plan->x) + plan->diry * (cam->camy - plan->y)
        + plan->dirz * (cam->camz - plan->z) + d) / (plan->dirx * ray->x
        + plan->diry * ray->y + plan->dirz * ray->z));
    return (t);
}

float    calcul_cone(t_cam *cam, t_ray *ray, t_cone *cone)
{
    float delta;
    float a;
    float b;
    float c;
    float t[2];
    float my_tan;

    my_tan = pow(tan(cone->r), 2);
    a = pow(ray->x, 2) + pow(ray->z, 2) - pow(ray->y, 2) * my_tan;
    b = 2 * (ray->x * (cam->camx - cone->x) + ray->z * (cam->camz - cone->z) - ray->y * (cam->camy - cone->y) * my_tan);
    c = (pow(cam->camx - cone->x, 2) + pow(cam->camz - cone->z, 2) - pow(cam->camy - cone->y, 2) - pow(cone->r, 2));
    delta = (b * b) - 4 * a * c;
    b = -b;
    if (delta > 0.0f)
    {
        t[0] = (b + sqrt(delta)) / (2 * a);
        t[1] = (b - sqrt(delta)) / (2 * a);
        if (t[0] <= t[1])
            return (t[0]);
        return (t[1]);
    }
    else if (delta == 0)
       return (b / (2 * a));
    return (-1);
}

float    calcul_cylindre(t_cam *cam, t_ray *ray, t_cylindre *cy)
{
    float delta;
    float a;
    float b;
    float c;
    float t[2];

    a = pow(ray->x, 2) + pow(ray->z, 2);
    b = 2 * (ray->x * (cam->camx - cy->x) + ray->z * (cam->camz - cy->z));
    c = (pow(cam->camx - cy->x, 2) + pow(cam->camz - cy->z, 2) - pow(cy->r, 2));
    delta = (b * b) - 4 * a * c;
    b = -b;
    if (delta > 0.0f)
    {
        t[0] = (b + sqrt(delta)) / (2 * a);
        t[1] = (b - sqrt(delta)) / (2 * a);
        if (t[0] <= t[1])
            return (t[0]);
        return (t[1]);
    }
    else if (delta == 0)
       return (b / (2 * a));
    return (-1);
}

float    calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere)
{
    float delta;
    float a;
    float b;
    float c;
    float t[2];

    a = pow(ray->x, 2) + pow(ray->y, 2) + pow(ray->z, 2);
    b = 2 * (ray->x * (cam->camx - sphere->x) + ray->y * (cam->camy - sphere->y) + ray->z * (cam->camz - sphere->z));
    c = (pow(cam->camx - sphere->x, 2) + pow(cam->camy - sphere->y, 2) + pow(cam->camz - sphere->z, 2)) - pow(sphere->r, 2);
    delta = (b * b) - 4 * a * c;
    b = -b;
    if (delta > 0.0f)
    {
        t[0] = (b + sqrt(delta)) / (2 * a);
        t[1] = (b - sqrt(delta)) / (2 * a);
        if (t[0] <= t[1])
            return (t[0]);
        return (t[1]);
    }
    else if (delta == 0)
       return (b / (2 * a));
    return (-1);
}