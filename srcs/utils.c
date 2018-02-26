#include "../inc/rtv1.h"

int     get_color(int r, int g, int b, float coef, float dot)
{
    float minr;
    float minb;
    float ming;

    minr = r * 0.2f;
    ming = g * 0.2f;
    minb = b * 0.2f;
    coef += 0.2f;
    if (dot > 0.0f)
    {
        if (r > 0)
            r *= dot * coef;
        if (g > 0)
            g *= dot * coef;
        if (b > 0)
            b *= (dot * coef);
        if (r > 255)
            r = 255;
        if (g > 255)
            g = 255;
        if (b > 255)
            b = 255;
        if (minr > r)
            r = minr;
        if (ming > g)
            g = ming;
        if (minb > b)
            b = minb;
        return ((int)(((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)));
    }
    return (0);
    // r *= 0.2f;
    // g *= 0.2f;
    // b *= 0.2f;
    // return ((int)(((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)));
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
