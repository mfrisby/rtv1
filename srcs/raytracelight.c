#include "../inc/rtv1.h"

// static int     get_light_colision_cone_plan(t_ray *r, t_data *data)
// {
//     t_cam fakecam;
//     t_cone *cone;
//     t_plan *plan;

//     fakecam.camx = data->intersection->x;
//     fakecam.camy = data->intersection->y;
//     fakecam.camz = data->intersection->z;
//     cone = data->cone_head;
//     while (cone)
//     {
//         if (cone != data->current && (calcul_cone(&fakecam, r, cone)) > 0)
//             return(-1);
//         cone = cone->next;
//     }
//     plan = data->plan_head;
//     while (plan)
//     {
//         if (plan != data->current && (calcul_plan(&fakecam,r,plan)) > 0)
//             return(-1);
//         plan = plan->next;
//     }
//     return (0);
// }

// static int     get_light_colision_cy_sphere(t_ray *r, t_data *data)
// {
//     t_cam fakecam;
//     t_sphere *sphere;
//     t_cylindre *cylindre;

//     fakecam.camx = data->intersection->x;
//     fakecam.camy = data->intersection->y;
//     fakecam.camz = data->intersection->z;
//     sphere = data->sphere_head;
//     while (sphere)
//     {
//         if (sphere != data->current && (calcul_sphere(&fakecam, r, sphere)) > 0)
//             return(-1);
//         sphere = sphere->next;
//     }
//     cylindre = data->cylindre_head;
//     while (cylindre)
//     {
//         if (cylindre != data->current && (calcul_cylindre(&fakecam,r,cylindre)) > 0)
//             return(-1);
//         cylindre = cylindre->next;
//     }
//     return (0);
// }

static float  get_dot(t_light *l, t_data *data)
{
    t_ray *r;
    r = malloc(sizeof(t_ray));
    // if ((get_light_colision_cy_sphere(r, data)) == -1
    //     || (get_light_colision_cone_plan(r, data)) == -1)
    //         return (-1);
    r->x = l->x - data->intersection->x;
    r->y = l->y - data->intersection->y;
    r->z = l->z - data->intersection->z;
    r = normalize(r);
    data->object_vect = normalize(data->object_vect);
    return ((data->object_vect->x * r->x) + (data->object_vect->y * r->y) + (data->object_vect->z * r->z));
}

int while_light(int *rgb, t_data *data)
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
        dot = get_dot(l, data);
        color = get_color(color, rgb, l, dot);
        l = l->next;
    }
    return (int)(((color[0] & 0xff) << 16) + ((color[1] & 0xff) << 8) + (color[2] & 0xff));
}