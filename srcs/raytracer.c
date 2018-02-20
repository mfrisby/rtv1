#include "../inc/rtv1.h"

static t_ray    *init_ray(int x, int y, t_upleft *upleft, t_cam *cam, t_pix *pix)
{
    t_ray   *ray;

    float pixX = 0;
    float pixY = 0;
    float pixZ = 0;
    float longueur = 0;

    ray = malloc(sizeof(t_ray));
    //position du pixel courant
    pixX = upleft->x + cam->vrightx * pix->xindent * x - cam->vupx * pix->yindent * y;
    pixY = upleft->y + cam->vrighty * pix->xindent * x - cam->vupy * pix->yindent * y;
    pixZ = upleft->z + cam->vrightz * pix->xindent * x - cam->vupz * pix->yindent * y;
    
    longueur = sqrt((float)((pixX * pixX) + (pixY * pixY) + (pixZ * pixZ)));
    
    ray->x = (pixX - cam->camx) / longueur;
    ray->y = (pixY - cam->camy) / longueur;
    ray->z = (pixZ - cam->camz) / longueur;
   
    return (ray);
}

static void  raytrace(t_ray *ray, t_data *data, int x, int y)
{
    long            color;
    float           max_d;
    float           d;
    t_objects       *obj;

    d = 0;
    max_d = 3.4028234664e+38;
    obj = data->head;
    color = 0;
    while (obj)
    {
        if (obj->type == SPHERE)
            d = calcul_sphere(data->cam, ray, obj->ptr);
        if (d > 0 && d < max_d)
        {
            max_d = d;
            t_sphere *s = obj->ptr;
            color = s->color;
        }
        obj = obj->next;
    }
    if (max_d > 0 && max_d < 3.4028234664e+38)
        mlx_pixel_put(data->mlx, data->win, x, y, color);
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
            if (data->head == NULL)
            {
                printf("error");
            }
            raytrace(ray, data, x, y);
            x++;
        }
        y++;
    }
}