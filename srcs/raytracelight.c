#include "../inc/rtv1.h"

t_ray *get_intersection(t_cam *cam, t_ray *ray, float d)
{
    t_ray   *intersection;

    if ((intersection = malloc(sizeof(t_ray))) == NULL)
    {
        ft_putendl(strerror(errno));
        exit (0);
    }
    intersection->x = cam->camx + ray->x * d;
    intersection->y = cam->camy + ray->y * d;
    intersection->z = cam->camz + ray->z * d;
    return (intersection);
}

int  get_light_at(float x, float y, float z, int *color, t_ray *intersection, t_light *light)
{
    float dot;
    t_ray *r;
    t_ray *p;
    
    r = malloc(sizeof(t_ray));
    p = malloc(sizeof(t_ray));
    if (r == NULL || p == NULL)
    {
        ft_putendl(strerror(errno));
        exit (0);
    }
    r->x = light->x- intersection->x;
    r->y = light->y - intersection->y;
    r->z = light->z - intersection->z;
    r = normalize(r->x, r->y, r->z);
    p->x = intersection->x - x;
    p->y = intersection->y - y;
    p->z = intersection->z - z;
    p = normalize(p->x, p->y, p->z);
    dot = get_dot(p->x, p->y, p->z, r->x, r->y, r->z);
    return (get_color(color[0], color[1], color[2], 0.8f, dot));
}

