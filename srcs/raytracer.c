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

static void  raytrace(t_ray *ray, t_data *data, int x, int y)
{
    int             color;
    float           max_d;
    float           d;
    t_sphere        *s;
    t_plan          *p;
    float           xyz[3];
    int             *rgb;
    
    color = 0;
    max_d = 3.4028234664e+38;
    d = 0;
    s = data->sphere_head;
    p = data->plan_head;
    while (s || p)
    {
        if (s)
        {
            d = calcul_sphere(data->cam, ray, s);
            if (d > 0 && d < max_d)
            {
                max_d = d;
                xyz[0] = s->x;
                xyz[1] = s->y;
                xyz[2] = s->z;
                rgb = s->color;
            }
            s = s->next;
        }
        if (p)
        {
            d = calcul_plan(data->cam, ray, p);
            if (d > 0 && d < max_d)
            {
                max_d = d;
                xyz[0] = p->x;
                xyz[1] = p->y;
                xyz[2] = p->z;
                rgb = p->color;
            }
            p = p->next;
        }
    }
    if (max_d > 0 && max_d < 3.4028234664e+37)
    {
        color = get_light_at(xyz[0], xyz[1], xyz[2], rgb, get_intersection(data->cam, ray, max_d));
        mlx_pixel_put(data->mlx, data->win, x, y, color);
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