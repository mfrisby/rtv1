#include "../inc/rtv1.h"

static void     free_s_cy(t_sphere *s, t_cylindre *cy)
{
    t_sphere *tmp;
    t_cylindre *tmp2;

    while (s && s->next)
    {
        tmp = s->next;
        free(s);
        s = tmp;
    }
    free(s);
    while (cy && cy->next)
    {
        tmp2 = cy->next;
        free(cy);
        cy = tmp2;
    }
    free(cy);
}

static void     free_cone_plan(t_cone *c, t_plan *p)
{
    t_cone *tmp;
    t_plan *tmp2;

    while (c && c->next)
    {
        tmp = c->next;
        free(c);
        c = tmp;
    }
    free(c);
    while (p && p->next)
    {
        tmp2 = p->next;
        free(p);
        p = tmp2;
    }
    free(p);
}

static void    free_heads_objects(t_data *data)
{
    t_sphere *s;
    t_plan *p;
    t_cone *c;
    t_cylindre *cy;
    
    s = data->sphere_head;
    c = data->cone_head;
    p = data->plan_head;
    cy = data->cylindre_head;
    free_s_cy(s, cy);
    free_cone_plan(c, p);
}

void    free_heads(t_data *data)
{
    ft_putendl("Freeing structs");
    t_light *light;
    t_light *tmp;

    light = data->light_head;
    free(data->cam);
    while (light && light->next)
    {
        tmp = light->next;
        free(light);
        light = tmp;
    }
    free(light);
    free_heads_objects(data);
}