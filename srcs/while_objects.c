/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:05:21 by mfrisby           #+#    #+#             */
/*   Updated: 2018/04/27 13:19:32 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double			while_cone(t_data *data, t_ray *ray, int **rgb, double max_d)
{
	double		d;
	t_cone		*c;

	d = 0;
	c = data->cone_head;
	while (c)
	{
		d = calcul_cone(data->cam, ray, c);
		if (d > 0 && d < max_d + 0.01f)
		{
			max_d = d;
			data->max_d = d;
			get_intersection(data, ray, max_d);
			data->object_norme->x = data->intersection->x - c->x;
			data->object_norme->y = 0;
			data->object_norme->z = data->intersection->z - c->z;
			*rgb = c->color;
			data->current = c;
		}
		c = c->next;
	}
	return (max_d);
}

double			while_sphere(t_data *data, t_ray *ray, int **rgb, double max_d)
{
	double		d;
	t_sphere	*s;

	d = 0;
	s = data->sphere_head;
	while (s)
	{
		d = calcul_sphere(data->cam, ray, s);
		if (d > 0 && d < max_d + 0.01f)
		{
			max_d = d;
			data->max_d = d;
			get_intersection(data, ray, max_d);
			data->object_norme->x = data->intersection->x - s->x;
			data->object_norme->y = data->intersection->y - s->y;
			data->object_norme->z = data->intersection->z - s->z;
			*rgb = s->color;
			data->current = s;
		}
		s = s->next;
	}
	return (max_d);
}

double			while_plan(t_data *data, t_ray *ray, int **rgb, double max_d)
{
	double		d;
	t_plan		*p;

	d = 0;
	p = data->plan_head;
	while (p)
	{
		d = calcul_plan(data->cam, ray, p);
		if (d > 0 && d < max_d + 0.01f)
		{
			max_d = d;
			data->max_d = d;
			get_intersection(data, ray, max_d);
			data->object_norme->x = p->dirx;
			data->object_norme->y = p->diry;
			data->object_norme->z = p->dirz;
			*rgb = p->color;
			data->current = p;
		}
		p = p->next;
	}
	return (max_d);
}

double			while_cylindre(t_data *da, t_ray *ray, int **rgb, double max_d)
{
	double		d;
	t_cylindre	*c;

	d = 0;
	c = da->cylindre_head;
	while (c)
	{
		d = calcul_cylindre(da->cam, ray, c);
		if (d > 0 && d < max_d + 0.01f)
		{
			max_d = d;
			da->max_d = d;
			get_intersection(da, ray, max_d);
			da->object_norme->x = da->intersection->x - c->x;
			da->object_norme->y = 0;
			da->object_norme->z = da->intersection->z - c->z;
			*rgb = c->color;
			da->current = c;
		}
		c = c->next;
	}
	return (max_d);
}
