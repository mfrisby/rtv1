/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracelight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:36:03 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/07 10:37:26 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static void		init_ray_light(t_ray *r, t_data *data, t_light *l)
{
	r->x = l->x - data->intersection->x;
	r->y = l->y - data->intersection->y;
	r->z = l->z - data->intersection->z;
	r = normalize(r);
}

int				while_light(int *rgb, t_data *data)
{
	float		dot;
	int			*color;
	t_light		*l;
	t_ray		*r;

	r = malloc(sizeof(t_ray));
	color = malloc(sizeof(int) * 3);
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	l = data->light_head;
	data->object_norme = normalize(data->object_norme);
	while (l)
	{
		init_ray_light(r, data, l);
		if (get_colision(r, data) == 0)
		{
			dot = (data->object_norme->x * r->x) + (data->object_norme->y
					* r->y) + (data->object_norme->z * r->z);
			color = get_color(color, rgb, l, dot);
		}
		l = l->next;
	}
	return (int)(((color[0] & 0xff) << 16)
			+ ((color[1] & 0xff) << 8) + (color[2] & 0xff));
}
