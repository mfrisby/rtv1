#include "../inc/rtv1.h"

float while_cone(t_data *data, t_ray *ray, int **rgb, float max_d)
{
    float d;
    t_cone *c;

    d = 0;
    c = data->cone_head;
    while (c)
    {
        d = calcul_cone(data->cam, ray, c);
        if (d > 0 && d < max_d)
        {
            max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_vect->x = c->x;
            data->object_vect->y = c->y;
            data->object_vect->z = c->z;
            *rgb = c->color;
            data->current = c; 
        }
        c = c->next;
    }
    return (max_d);
}

float while_sphere(t_data *data, t_ray *ray, int **rgb)
{
    float max_d;
    float d;
    t_sphere *s;

    d = 0;
    max_d = 3.4028234664e+38;
    s = data->sphere_head;
    while (s)
    {
        d = calcul_sphere(data->cam, ray, s);
        if (d > 0 && d < max_d)
        {
            max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_vect->x = data->intersection->x - s->x;
            data->object_vect->y = data->intersection->y - s->y;
            data->object_vect->z = data->intersection->z - s->z;
            *rgb = s->color;
            data->current = s; 
        }
        s = s->next;
    }
    return (max_d);
}

float while_plan(t_data *data, t_ray *ray, int **rgb, float max_d)
{
    float d;
    t_plan *p;

    d = 0;
    p = data->plan_head;
    while (p)
    {
        d = calcul_plan(data->cam, ray, p);
        if (d > 0 && d < max_d)
        {
            max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_vect->x = p->dirx;
            data->object_vect->y = p->diry;
            data->object_vect->z = p->dirz;
            *rgb = p->color;
            data->current = p;
        }
        p = p->next;
    }
    return (max_d);
}

float while_cylindre(t_data *data, t_ray *ray, int **rgb, float max_d)
{
    float d;
    t_cylindre *c;

    d = 0;
    c = data->cylindre_head;
    while (c)
    {
        d = calcul_cylindre(data->cam, ray, c);
        if (d > 0 && d < max_d)
        {
            max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_vect->x = c->x;
            data->object_vect->y = c->y;
            data->object_vect->z = c->z;
            *rgb = c->color;
            data->current = c;
        }
        c = c->next;
    }
    return (max_d);
}