#include "../inc/rtv1.h"

static int colision_cone(t_ray *r, t_data *data)
{
    float d;
    t_cam fakecam;
    t_cone *cone;

    fakecam.camx = data->intersection->x;
    fakecam.camy = data->intersection->y;
    fakecam.camz = data->intersection->z;
    cone = data->cone_head;
    while (cone)
    {
        if (cone != data->current)
        {
            d = calcul_cone(&fakecam, r, cone);
            if (d > 0 && d < data->max_d)
                return(-1);
        }
        cone = cone->next;
    }
    return (0);
}

static int colision_sphere(t_ray *r, t_data *data)
{
    float d;
    t_cam fakecam;
    t_sphere *sphere;

    fakecam.camx = data->intersection->x;
    fakecam.camy = data->intersection->y;
    fakecam.camz = data->intersection->z;
    sphere = data->sphere_head;
    while (sphere)
    {
        if (sphere != data->current)
        {
            d = calcul_sphere(&fakecam, r, sphere);
            if (d > 0 && d < data->max_d)
                return(-1);
        }
        sphere = sphere->next;
    }
    return (0);
}

static int colision_cylindre(t_ray *r, t_data *data)
{
    float d;
    t_cam fakecam;
    t_cylindre *cylindre;

    fakecam.camx = data->intersection->x;
    fakecam.camy = data->intersection->y;
    fakecam.camz = data->intersection->z;
    cylindre = data->cylindre_head;
    while (cylindre)
    {
        if (cylindre != data->current)
        {
            d = calcul_cylindre(&fakecam, r, cylindre);
            if (d > 0 && d < data->max_d)
                return(-1);
        }
        cylindre = cylindre->next;
    }
    return (0);
}

static int colision_plan(t_ray *r, t_data *data)
{
    float d;
    t_cam fakecam;
    t_plan *plan;
    fakecam.camx = data->intersection->x;
    fakecam.camy = data->intersection->y;
    fakecam.camz = data->intersection->z;
    plan = data->plan_head;
    while (plan)
    {
        if (plan != data->current)
        {
            d = calcul_plan(&fakecam, r, plan);
            if (d > 0 && d < data->max_d)
                return(-1);
        }
        plan = plan->next;
    }
    return (0);
}

int         get_colision(t_ray *r, t_data *data)
{
    if ((colision_cone(r, data)) == -1 || (colision_cylindre(r, data)) == -1
        || (colision_plan(r, data)) == -1 || (colision_sphere(r, data)) == -1)
        return (-1);
    return (0);
}