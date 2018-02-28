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

static int     get_light_colision_cone_plan(t_ray *i, t_ray *r, t_data *data)
{
    t_cam fakecam;
    t_cone *cone;
    t_plan *plan;

    fakecam.camx = i->x;
    fakecam.camy = i->y;
    fakecam.camz = i->z;
    cone = data->cone_head;
    while (cone)
    {
        if (cone != data->current && calcul_cone(&fakecam, r, cone) > 0)
            return(-1);
        cone = cone->next;
    }
    plan = data->plan_head;
    while (plan)
    {
        if (plan != data->current && calcul_plan(&fakecam,r,plan) > 0)
            return(-1);
        plan = plan->next;
    }
    return (0);
}

static int     get_light_colision_cy_sphere(t_ray *i, t_ray *r, t_data *data)
{
    t_cam fakecam;
    t_sphere *sphere;
    t_cylindre *cylindre;

    fakecam.camx = i->x;
    fakecam.camy = i->y;
    fakecam.camz = i->z;
    sphere = data->sphere_head;
    while (sphere)
    {
        if (sphere != data->current && calcul_sphere(&fakecam, r, sphere) > 0)
            return(-1);
        sphere = sphere->next;
    }
    cylindre = data->cylindre_head;
    while (cylindre)
    {
        if (cylindre != data->current && calcul_cylindre(&fakecam,r,cylindre) > 0)
            return(-1);
        cylindre = cylindre->next;
    }
    return (0);
}

static float  get_dot(float *xyz, t_ray *intersection, t_light *light, t_data *data)
{
    t_ray *r;
    t_ray *p;
    
    r = malloc(sizeof(t_ray));
    r->x = light->x - intersection->x;
    r->y = light->y - intersection->y;
    r->z = light->z - intersection->z;
    r = normalize(r->x, r->y, r->z);
    if ((get_light_colision_cy_sphere(intersection, r, data)) == -1
        || (get_light_colision_cone_plan(intersection, r, data)) == -1)
            return (0);
    p = malloc(sizeof(t_ray));
    p->x = intersection->x - xyz[0];
    p->y = intersection->y - xyz[1];
    p->z = intersection->z - xyz[2];
    p = normalize(p->x, p->y, p->z);
    return ((p->x * r->x) + (p->y * r->y)  + (p->z * r->z));
}

int while_light(int *rgb, float *xyz, t_ray *intersection, t_data *data)
{
    float dot;
    int *color;
    t_light *l;

    color = malloc(sizeof(int) * 3);
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    l = data->light_head;
    while (l)
    {
        dot = get_dot(xyz, intersection, l, data);
        color = get_color(color, rgb, l->coef, dot);
        l = l->next;
    }
    return (int)(((color[0] & 0xff) << 16) + ((color[1] & 0xff) << 8) + (color[2] & 0xff));
}