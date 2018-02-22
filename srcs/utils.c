#include "../inc/rtv1.h"

int     get_color(int r, int g, int b, float coef, float dot)
{
    coef = 0;
    if (dot > 0.0f)
    {
        if (r > 0)
            r *= dot * 0.8;
        if (g > 0)
            g *= dot * 0.8;
        if (b > 0)
            b *= dot * 0.8;
        return ((int)(((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)));
    }
    return (0);
}

float get_dot(float ax, float ay, float az, float bx, float by, float bz)
{
    return ((ax * bx) + (ay * by) + (az * bz));
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
