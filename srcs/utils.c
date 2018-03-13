/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:28:27 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/13 14:19:35 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int			key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		free_heads(data);
		exit(0);
	}
	return (0);
}

void		get_intersection(t_data *data, t_ray *ray, double d)
{
	data->intersection->x = data->cam->camx + ray->x * d;
	data->intersection->y = data->cam->camy + ray->y * d;
	data->intersection->z = data->cam->camz + ray->z * d;
}

int			*get_color(int *color, int *rgb, t_light *l, double dot)
{
	if (dot > 1)
		dot = 1;
	if (dot > 0.0)
	{
		if (rgb[0] > 0)
			color[0] += rgb[0] * dot * l->coef;
		if (rgb[1] > 0)
			color[1] += rgb[1] * dot * l->coef;
		if (rgb[2] > 0)
			color[2] += rgb[2] * dot * l->coef;
	}
	return (color);
}

double		get_dot(t_ray *r1, t_ray *r2)
{
	return ((r1->x * r2->x) + (r1->y * r2->y) + (r1->z * r2->z));
}

t_ray		*normalize(t_ray *r)
{
	double	longueur;

	longueur = sqrt((double)((r->x * r->x) + (r->y * r->y) + (r->z * r->z)));
	r->x /= longueur;
	r->y /= longueur;
	r->z /= longueur;
	return (r);
}
