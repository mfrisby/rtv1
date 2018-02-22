#include "../inc/rtv1.h"

int        add_sphere_lst(t_data **data, t_sphere *elem)
{
    t_sphere *tmp;

    if (elem == NULL)
        return (-1);
    if ((*data)->sphere_head == NULL)
    {
        (*data)->sphere_head = elem;
        return (0);
    }
    tmp = (*data)->sphere_head;
    while (tmp->next)
    {
        tmp = tmp->next;   
    }
    tmp->next = elem;
    return (0);
}