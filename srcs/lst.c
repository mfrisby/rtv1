/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:26:42 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/07 10:28:23 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int				add_sphere_lst(t_data **data, t_sphere *elem)
{
	t_sphere	*tmp;

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

int				add_plan_lst(t_data **data, t_plan *elem)
{
	t_plan		*tmp;

	if (elem == NULL)
		return (-1);
	if ((*data)->plan_head == NULL)
	{
		(*data)->plan_head = elem;
		return (0);
	}
	tmp = (*data)->plan_head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
	return (0);
}

int				add_cylindre_lst(t_data **data, t_cylindre *elem)
{
	t_cylindre	*tmp;

	if (elem == NULL)
		return (-1);
	if ((*data)->cylindre_head == NULL)
	{
		(*data)->cylindre_head = elem;
		return (0);
	}
	tmp = (*data)->cylindre_head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
	return (0);
}

int				add_cone_lst(t_data **data, t_cone *elem)
{
	t_cone		*tmp;

	if (elem == NULL)
		return (-1);
	if ((*data)->cone_head == NULL)
	{
		(*data)->cone_head = elem;
		return (0);
	}
	tmp = (*data)->cone_head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
	return (0);
}

int				add_light_lst(t_data **data, t_light *elem)
{
	t_light		*tmp;

	if (elem == NULL)
		return (-1);
	if ((*data)->light_head == NULL)
	{
		(*data)->light_head = elem;
		return (0);
	}
	tmp = (*data)->light_head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
	return (0);
}
