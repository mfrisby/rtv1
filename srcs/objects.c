#include "../inc/rtv1.h"

// static t_plan        *init_plan()
// {
//     t_plan *plan;

//     plan = malloc(sizeof(t_plan));
//     //dir correspond au produit vectoriel (quon definit plutot que de calculer)
//     //normale du plan
//     plan->dirx = -0.5f;
//     plan->diry = -0.2f;
//     plan->dirz = -3.0f;
//     //pos correspond a un point quelquonc dans le plan 
//     plan->posx = -0.2f;
//     plan->posy = -0.5f;
//     plan->posz = -0.2f;
//     plan->color = COLORRED;
//     return (plan);
// }

// float        calcul_plan(t_cam *cam, t_ray *ray)
// {
//     float   d;
//     float   t;
//     t_plan *plan;

//     plan = init_plan();
//     d = -(plan->dirx * plan->posx + plan->diry * plan->posy + plan->dirz * plan->posz);
//     t = -((plan->posx * cam->camx + plan->posy * cam->camy + plan->posz * cam->camz + d) / (plan->posx * ray->x + plan->posy * ray->y + plan->posz * ray->z));
//     return (t);
// }

float    calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere)
{
    int delta;
    float a;
    float b;
    float c;
    float csx;
    float csy;
    float csz;
    
    csz = cam->camz - sphere->z;
    csy= cam->camy - sphere->y;
    csx = cam->camx - sphere->x;
    a = (ray->x * ray->x) + (ray->y * ray->y) + (ray->z * ray->z);
    b = 2 * (ray->x * (cam->camx - sphere->x) + ray->y * (cam->camy - sphere->y) + ray->z * (cam->camz - sphere->z));
    c = (csx * csx) + (csy * csy) + (csz * csz) - (sphere->r * sphere->r);
    delta = (b * b) - 4 * a * c;
    b *= -1;
    if (delta > 0)
    {
        float t1 = (b + sqrt(delta)) / (2 * a);
        float t2 = (b - sqrt(delta)) / (2 * a);
        if (t1 <=t2)
            return (t1);
        else
            return (t2);
    }
    else if (delta == 0)
    {
        float t = b / (2 * a);
        return (t);
    }
    return (-1);
}