#include "../inc/rtv1.h"

t_ray *get_intersection(t_cam *cam, t_ray *ray, float d)
{
    t_ray   *intersection;

    intersection = malloc(sizeof(t_ray));
    intersection->x = cam->camx + ray->x * d;
    intersection->y = cam->camy + ray->y * d;
    intersection->z = cam->camz + ray->z * d;
    return (intersection);
}

int  get_light_at(float x, float y, float z, int *color, t_ray *intersection)
{
    float dot;
    t_ray *r;
    t_ray *p;
    t_light *light;

    light = malloc(sizeof(t_light));
    light->x = 0.2f;
    light->y = 0.2f;
    light->z = -1.0f;
    light->coef = 1;
    r = malloc(sizeof(t_ray));
    p = malloc(sizeof(t_ray));
    r->x = light->x- intersection->x;
    r->y = light->y - intersection->y;
    r->z = light->z - intersection->z;
    r = normalize(r->x, r->y, r->z);
    p->x = intersection->x - x;
    p->y = intersection->y - y;
    p->z = intersection->z - z;
    p = normalize(p->x, p->y, p->z);
    dot = get_dot(p->x, p->y, p->z, r->x, r->y, r->z);
    return (get_color(color[0], color[1], color[2], 0.2f, dot));
}