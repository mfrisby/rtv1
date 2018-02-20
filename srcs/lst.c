#include "../inc/rtv1.h"

static void add_first(t_data **data, void *elem, int type)
{
    t_sphere *myptr;

    (*data)->head = malloc(sizeof(t_objects));
    (*data)->head->next = NULL;
    (*data)->head->ptr = elem;
    (*data)->head->type = type;
    if (type == SPHERE)
    {
        myptr = elem;
        (*data)->head->color = myptr->color;
    }
}

void        add_elem(t_data **data, void *elem, int type)
{
    t_objects *tmp;
    t_sphere *myptr;

    tmp = NULL;
    if ((*data)->head == NULL)
        add_first(data, elem, type);
    else
    {
        tmp = (*data)->head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        myptr = elem;
        tmp->next = malloc(sizeof(t_objects));
        tmp->next->ptr = elem;
        tmp->next->type = type;
        tmp->color = myptr->color;
        tmp->next->next = NULL;
    }
}