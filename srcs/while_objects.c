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
        if (d > 0 && d < max_d + 0.01f)
        {
            max_d = d;
            data->max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_norme->x = data->intersection->x - c->x;
            data->object_norme->y = max_d / cos(c->ang * c->r);
            data->object_norme->z = data->intersection->z - c->z;
            *rgb = c->color;
            data->current = c; 
        }
        c = c->next;
    }
    return (max_d);
}

float while_sphere(t_data *data, t_ray *ray, int **rgb, float max_d)
{
    float d;
    t_sphere *s;

    d = 0;
    s = data->sphere_head;
    while (s)
    {
        d = calcul_sphere(data->cam, ray, s);
        if (d > 0 && d < max_d + 0.01f)
        {
            max_d = d;
            data->max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_norme->x = data->intersection->x - s->x;
            data->object_norme->y = data->intersection->y - s->y;
            data->object_norme->z = data->intersection->z - s->z;
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
        if (d > 0 && d < max_d + 0.01f)
        {
            max_d = d;
            data->max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_norme->x = p->dirx;
            data->object_norme->y = p->diry;
            data->object_norme->z = p->dirz;
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
        if (d > 0 && d < max_d + 0.01f)
        {
            max_d = d;
            data->max_d = d;
            data->intersection = get_intersection(data->cam, ray, max_d);
            data->object_norme->x = data->intersection->x - c->x;
            data->object_norme->y = 0;
            data->object_norme->z = data->intersection->z - c->z;
            *rgb = c->color;
            data->current = c;
        }
        c = c->next;
    }
    return (max_d);
}