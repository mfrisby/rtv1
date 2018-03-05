#include "../inc/rtv1.h"

static t_ray *init_ray(int x, int y, t_upleft *upleft, t_cam *cam, t_pix *pix)
{
    t_ray *ray;

    ray = malloc(sizeof(t_ray));
    ray->x = upleft->x + cam->vrightx * pix->xindent * x - cam->vupx * pix->yindent * y;
    ray->y = upleft->y + cam->vrighty * pix->xindent * x - cam->vupy * pix->yindent * y;
    ray->z = upleft->z + cam->vrightz * pix->xindent * x - cam->vupz * pix->yindent * y;
    ray = normalize(ray);
    return (ray);
}

static void raytrace(t_ray *ray, t_data *data, int x, int y)
{
    int color;
    float max_d;
    int *rgb;

    color = 0;
    max_d = 3.4028234664e+38;
    max_d = while_sphere(data, ray, &rgb);
    max_d = while_plan(data, ray, &rgb, max_d);
    max_d = while_cylindre(data, ray, &rgb, max_d);
    max_d = while_cone(data, ray, &rgb, max_d);
    data->ray = ray;
    if (max_d > 0 && max_d < 3.4028234664e+37)
    {
        color = while_light(rgb, data);
        mlx_pixel_put(data->mlx, data->win, x, y, color);
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