#include "../inc/rtv1.h"

static t_ray    *init_ray(int x, int y, t_upleft *upleft, t_cam *cam, t_pix *pix)
{
    t_ray   *ray;

    float pixX = 0.0f;
 
    float pixY = 0.0f;
    float pixZ = 0.0f;

    pixX = upleft->x + cam->vrightx * pix->xindent * x - cam->vupx * pix->yindent * y;
    pixY = upleft->y + cam->vrighty * pix->xindent * x - cam->vupy * pix->yindent * y;
    pixZ = upleft->z + cam->vrightz * pix->xindent * x - cam->vupz * pix->yindent * y;
    ray = normalize(pixX, pixY, pixZ);
    return (ray);
}

// static t_ray *get_intersection(t_cam *cam, t_ray *ray, float d)
// {
//     t_ray   *intersection;

//     intersection = malloc(sizeof(t_ray));
//     intersection->x = cam->camx + ray->x * d;
//     intersection->y = cam->camy + ray->y * d;
//     intersection->z = cam->camz + ray->z * d;
//     return (intersection);
// }

// static int  get_light_at(t_sphere *sphere, t_ray *intersection, t_light *light)
// {
//     float dot;
//     t_ray *r;
//     t_ray *p;

//     r = malloc(sizeof(t_ray));
//     p = malloc(sizeof(t_ray));
//     r->x = intersection->x -light->x;
//     r->y = intersection->y - light->y;
//     r->z = intersection->z - light->z;
//     r = normalize(r->x, r->y, r->z);
//     p->x = intersection->x - sphere->x;
//     p->y = intersection->y - sphere->y;
//     p->z = intersection->z - sphere->z;
//     p = normalize(p->x, p->y, p->z);
//     dot = get_dot(p->x, p->y, p->z, r->x, r->y, r->z);
//     if (dot > 0)
//     {
//        // printf("dot: %f", dot);
//         int c1 = (int)(sphere->color[0] * dot);
//         int c2 = (int)(sphere->color[1] * dot);
//         int c3 = (int)(sphere->color[2] * dot);
//         return ((int)(((c1 & 0xff) << 16) + ((c2 & 0xff) << 8) + (c3 & 0xff)));
//     }
//     return (0);
// }

// static t_light *get_light()
// {
//     t_light *light;

//     light = malloc(sizeof(t_light));
//     light->x = 1.0f;
//     light->y = 0.0f;
//     light->z = 1.0f;
//     light->coef = 1;
//     return (light);
// }

static void  raytrace(t_ray *ray, t_data *data, int x, int y)
{
    float           max_d;
    float           d;
    t_sphere        *s;
    t_sphere        *current;
   // t_ray           *intersection;
   // t_light         *light;
    
    max_d = 3.4028234664e+38;
    d = 0;
    current = malloc(sizeof(t_sphere));
    s = data->sphere_head;
    while (s)
    {
        d = calcul_sphere(data->cam, ray, s);
        if (d > 0 && d < max_d)
        {
            max_d = d;
            current = s;
        }
        s = s->next;
    }
    if (max_d > 0 && max_d < 3.4028234664e+37)
    {
        // if (!current)
        // {
        //     printf("NO CURRENT");
        //     exit (0);
        // }
        // light = get_light();
        // intersection = get_intersection(data->cam, ray, max_d);
        // int color = get_light_at(current, intersection, light);
        // color = 0;
        mlx_pixel_put(data->mlx, data->win, x, y, COLORRED);
    }
}

void        rayloop(t_data *data, t_upleft *upleft, t_pix *pix)
{
    int     x;
    int     y;
    t_ray   *ray;

    ray = NULL;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ray = init_ray(x, y, upleft, data->cam, pix);
            raytrace(ray, data, x, y);
            x++;
        }
        y++;
    }
}