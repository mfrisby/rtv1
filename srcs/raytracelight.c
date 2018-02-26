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

static int     get_light_colision(t_ray *i, t_ray *r, t_data *data)
{
    t_cam *fakecam;
    t_cone *cone;
    t_sphere *sphere;
    t_cylindre *cylindre;
    t_plan *plan;

    fakecam = malloc(sizeof(t_cam));
    fakecam->camx = i->x;
    fakecam->camy = i->y;
    fakecam->camz = i->z;
    cone = data->cone_head;
    while (cone)
    {
        if (cone != data->current && calcul_cone(fakecam,r,cone) > 0)
            return(-1);
        cone = cone->next;
    }
    sphere = data->sphere_head;
    while (sphere)
    {
        if (sphere != data->current && calcul_sphere(fakecam,r,sphere) > 0)
            return(-1);
        sphere = sphere->next;
    }
    cylindre = data->cylindre_head;
    while (cylindre)
    {
        if (cylindre != data->current && calcul_cylindre(fakecam,r,cylindre) > 0)
            return(-1);
        cylindre = cylindre->next;
    }
    plan = data->plan_head;
    while (plan)
    {
        if (plan != data->current && calcul_plan(fakecam,r,plan) > 0)
            return(-1);
        plan = plan->next;
    }
     return (0);
}

int  get_light_at(float *xyz, int *color, t_ray *intersection, t_light *light, t_data *data)
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
    p->x = intersection->x - xyz[0];
    p->y = intersection->y - xyz[1];
    p->z = intersection->z - xyz[2];
    p = normalize(p->x, p->y, p->z);
    r->x = light->x - intersection->x;
    r->y = light->y - intersection->y;
    r->z = light->z - intersection->z;
    r = normalize(r->x, r->y, r->z);
    if ((get_light_colision(intersection, r, data)) == -1)
        return (get_color(color[0], color[1], color[2], 0.8f, 0));//ombre lumiere ambiance
    dot = get_dot(p->x, p->y, p->z, r->x, r->y, r->z);
    return (get_color(color[0], color[1], color[2], 0.8f, dot));
}

