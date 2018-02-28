#include "../inc/rtv1.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
        free_heads(data);
		exit(0);
	}
	return (0);
}

int     *get_color(int *color, int *rgb, t_light *l, float dot)
{
    if (dot > 0.0f)
    {
        if (rgb[0] > 0)
            color[0] += (rgb[0] + l->color[0]) * dot * l->coef;
        if (rgb[1] > 0)
            color[1] += (rgb[1] + l->color[1]) *  dot * l->coef;
        if (rgb[2] > 0)
            color[2] += (rgb[2] + l->color[2]) * dot * l->coef;
        if (color[0] > 255)
            color[0] = 255;
        if (color[1] > 255)
            color[1] = 255;
        if (color[2] > 255)
            color[2] = 255;
    }
    return (color);
}

t_ray *normalize(float x, float y, float z)
{
    float longueur;
    t_ray   *r;

    r = malloc(sizeof(t_ray));
    longueur = sqrt((float)((x * x) + (y * y) + (z * z)));
    r->x = x / longueur;
    r->y = y / longueur;
    r->z = z / longueur;
    return (r);
}