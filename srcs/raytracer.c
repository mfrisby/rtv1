#include "../inc/rtv1.h"

static t_ray *init_ray(int x, int y, t_upleft *upleft, t_cam *cam, t_pix *pix)
{
    t_ray *ray;
    float pixX = 0.0f;
    float pixY = 0.0f;
    float pixZ = 0.0f;

    pixX = upleft->x + cam->vrightx * pix->xindent * x - cam->vupx * pix->yindent * y;
    pixY = upleft->y + cam->vrighty * pix->xindent * x - cam->vupy * pix->yindent * y;
    pixZ = upleft->z + cam->vrightz * pix->xindent * x - cam->vupz * pix->yindent * y;
    ray = normalize(pixX, pixY, pixZ);
    return (ray);
}

static float while_cone(t_data *data, t_ray *ray, float *xyz, int **rgb, float max_d)
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
            xyz[0] = c->x;
            xyz[1] = c->y;
            xyz[2] = c->z;
            *rgb = c->color;
            data->current = c; 
        }
        c = c->next;
    }
    return (max_d);
}

static float while_sphere(t_data *data, t_ray *ray, float *xyz, int **rgb)
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
            xyz[0] = s->x;
            xyz[1] = s->y;
            xyz[2] = s->z;
            *rgb = s->color;
            data->current = s; 
        }
        s = s->next;
    }
    return (max_d);
}

static float while_plan(t_data *data, t_ray *ray, float *xyz, int **rgb, float max_d)
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
            xyz[0] = p->x;
            xyz[1] = p->y;
            xyz[2] = p->z;
            *rgb = p->color;
            data->current = p;
        }
        p = p->next;
    }
    return (max_d);
}

static float while_cylindre(t_data *data, t_ray *ray, float *xyz, int **rgb, float max_d)
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
            xyz[0] = c->x;
            xyz[1] = 0;//fix lumiere temporaire
            xyz[2] = c->z;
            *rgb = c->color;
            data->current = c;
        }
        c = c->next;
    }
    return (max_d);
}

static void raytrace(t_ray *ray, t_data *data, int x, int y)
{
    int color;
    int max_color;
    float max_d;
    float d;
    t_light *l;
    float xyz[3];
    int *rgb;

    color = 0;
    max_color = 0;
    max_d = 3.4028234664e+38;
    d = 0;
    l = data->light_head;
    max_d = while_sphere(data, ray, xyz, &rgb);
    max_d = while_plan(data, ray, xyz, &rgb, max_d);
    max_d = while_cylindre(data, ray, xyz, &rgb, max_d);
    max_d = while_cone(data, ray, xyz, &rgb, max_d);
    if (max_d > 0 && max_d < 3.4028234664e+37)
    {
        //multispot
        while (l)
        {
            color = get_light_at(xyz, rgb, get_intersection(data->cam, ray, max_d), l, data);
            if (color > max_color)
                max_color = color;
            mlx_pixel_put(data->mlx, data->win, x, y, max_color);
            l = l->next;
        }
    }
}

void rayloop(t_data *data, t_upleft *upleft, t_pix *pix)
{
    int x;
    int y;
    t_ray *ray;

    ray = NULL;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {

		    mlx_hook(data->win, 3, 3, key_hook, data);
            ray = init_ray(x, y, upleft, data->cam, pix);
            raytrace(ray, data, x, y);
            x++;
        }
        y++;
    }
}