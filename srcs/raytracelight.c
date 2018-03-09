/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracelight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:36:03 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/09 13:55:04 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static t_ray		*init_ray_light(t_ray *r, t_data *data, t_light *l)
{
	r->x = l->x - data->intersection->x;
	r->y = l->y - data->intersection->y;
	r->z = l->z - data->intersection->z;
	return (normalize(r));
}

static t_ray		*init_ray_light_spec(t_ray *r, t_data *data, t_light *l)
{
	r->x = data->intersection->x - l->x;
	r->y = data->intersection->y - l->y;
	r->z = data->intersection->z - l->z;
	return (normalize(r));
}
static float		get_specular_dot(t_ray *l, float dot, t_data *data)
{
	t_ray *r;
	
	r = malloc(sizeof(t_ray));
	r->x = 2.0f * dot * data->object_norme->x - l->x;
	r->y = 2.0f * dot * data->object_norme->y - l->y;
	r->z = 2.0f * dot * data->object_norme->z - l->z;
	r = normalize(r);
	return ((r->x * data->object_norme->x) + (r->y * data->object_norme->y) + (r->z * data->object_norme->z));
}

int			*get_color_specular(int *color, int *rgblight, float dot)
{
	if (dot > 0.0)
	{
		color[0] += rgblight[0] * pow(dot, 70) * 0.5;
		color[1] += rgblight[0] * pow(dot, 70) * 0.5;
		color[2] += rgblight[0] * pow(dot, 70) * 0.5;
		if (color[0] > 255)
			color[0] = 255;
		if (color[1] > 255)
			color[1] = 255;
		if (color[2] > 255)
			color[2] = 255;
	}
	return (color);
}

int				while_light(int *rgb, t_data *data)
{
	float		dot;
	float		dot2; 
	int			*color;
	t_light		*light;
	t_ray		*light_ray;//rayon lumiere

	light_ray = malloc(sizeof(t_ray));
	color = malloc(sizeof(int) * 3);
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	light = data->light_head;
	data->object_norme = normalize(data->object_norme);
	while (light)
	{
		light_ray = init_ray_light(light_ray, data, light);
		if (get_colision(light_ray, data) == 0)
		{
			dot = get_dot(data->object_norme, light_ray);
			color = get_color(color, rgb, light, dot);
			light_ray = init_ray_light_spec(light_ray, data, light);
			dot2 = get_specular_dot(light_ray, dot, data);
			color = get_color_specular(color, light->color, dot2);
		}
		light = light->next;
	}
	return (int)(((color[0] & 0xff) << 16)
			+ ((color[1] & 0xff) << 8) + (color[2] & 0xff));
}
