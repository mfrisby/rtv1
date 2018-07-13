/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:52:20 by mfrisby           #+#    #+#             */
/*   Updated: 2018/04/27 16:52:54 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static void	ft_quater_mult(t_quater *first, t_quater *second, t_quater *result)
{
	result->w = (first->w * second->w - first->x * second->x -
								first->y * second->y - first->z * second->z);
	result->x = (first->w * second->x + first->x * second->w +
								first->y * second->z - first->z * second->y);
	result->y = (first->w * second->y - first->x * second->z +
								first->y * second->w + first->z * second->x);
	result->z = (first->w * second->z + first->x * second->y -
								first->y * second->x + first->z * second->w);
}

void	ft_normalize_quater(t_quater *source)
{
	double magnitude;

	magnitude = sqrt(pow(source->w, 2) + pow(source->x, 2) + pow(source->y, 2)
														+ pow(source->z, 2));
	source->w = source->w / magnitude;
	source->x = source->x / magnitude;
	source->y = source->y / magnitude;
	source->z = source->z / magnitude;
}

static void	ft_quater_from_vec(t_quater *result, t_ray *source)
{
	result->w = 0;
	result->x = source->x;
	result->y = source->y;
	result->z = source->z;
}

static void	ft_quater_rot(t_ray *result, t_ray *source, t_ray *axe, double theta)
{
	t_quater h1;
	t_quater h2;
	t_quater tmp_src;
	t_quater tmp_res;
	t_quater tmp_res2;

	ft_quater_from_vec(&tmp_src, source);
	h1.w = cos(theta / 2);
	h1.x = axe->x * sin(theta / 2);
	h1.y = axe->y * sin(theta / 2);
	h1.z = axe->z * sin(theta / 2);
	h2.w = h1.w;
	h2.x = -1 * h1.x;
	h2.y = -1 * h1.y;
	h2.z = -1 * h1.z;
	ft_normalize_quater(&h1);
	ft_normalize_quater(&h2);
	ft_quater_mult(&h1, &tmp_src, &tmp_res);
	ft_quater_mult(&tmp_res, &h2, &tmp_res2);
	result->x = tmp_res2.x;
	result->y = tmp_res2.y;
	result->z = tmp_res2.z;
}

static t_quater		*init_quater(t_ray *r)
{
	t_quater *quater;
	
	quater = malloc(sizeof(t_quater));
	quater->x = r->x;
	quater->y = r->y;
	quater->z = r->z;
	quater->w = 0;
	return (quater);
}

void		get_rotation(t_cylindre *cy, t_cone *co)
{
	t_ray *r;
	t_ray *result;
	t_ray *axe;

	r = malloc(sizeof(t_ray));
	result = malloc(sizeof(t_ray));
	axe = malloc(sizeof(t_ray));
	result->x = 0;
	result->y = 0;
	result->z = 0;
	if (cy != NULL)
	{
		r->x = cy->x;
		r->y = cy->y;
		r->z = cy->z;
		axe->x = cy->dirx;
		axe->y = cy->diry;
		axe->z = cy->dirz;
		cy->quat = init_quater(r);
		ft_quater_rot(result, r, axe, cy->ang);
		cy->x = result->x;
		cy->y = result->y;
		cy->z = result->z;
	}
	else if (co != NULL)
	{
		r->x = co->x;
		r->y = co->y;
		r->z = co->z;
		axe->x = co->dirx;
		axe->y = co->diry;
		axe->z = co->dirz;
		co->quat = init_quater(r);
		ft_quater_rot(result, r, axe, co->ang);
		co->x = result->x;
		co->y = result->y;
		co->z = result->z;
	}
}