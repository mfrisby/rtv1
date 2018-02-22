#include "../inc/rtv1.h"

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
