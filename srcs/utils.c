/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:28:27 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/07 14:24:40 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void        rotate(t_ray *ray, float rot)
{
    float xprime;
    float yprime;

	//axe y
	//yprime = ray->y * cos(rot) - ray->z * sin(rot)
	//zprime = ray->y * sin(rot) + ray->z * cos(rot)
	xprime = ray->x * cos(rot) - ray->y * sin(rot);
	yprime = ray->x * sin(rot) + ray->y * cos(rot);
	ray->x = xprime;
	ray->y = yprime;
}

int			key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		free_heads(data);
		exit(0);
	}
	return (0);
}

t_ray		*get_intersection(t_cam *cam, t_ray *ray, float d)
{
	t_ray	*intersection;

	if ((intersection = malloc(sizeof(t_ray))) == NULL)
	{
		ft_putendl(strerror(errno));
		exit(0);
    }
	intersection->x = cam->camx + ray->x * d;
	intersection->y = cam->camy + ray->y * d;
	intersection->z = cam->camz + ray->z * d;
	return (intersection);
}

int			*get_color(int *color, int *rgb, t_light *l, float dot)
{
	if (dot >= 0.0 && dot <= 1.0)
	{
		if (rgb[0] > 0)
			color[0] += (rgb[0] + l->color[0]) * dot * l->coef;
		if (rgb[1] > 0)
			color[1] += (rgb[1] + l->color[1]) * dot * l->coef;
		if (rgb[2] > 0)
			color[2] += (rgb[2] + l->color[2]) * dot * l->coef;
		if (color[0] > 255)
			color[0] = 255;
		if (color[1] > 255)
			color[1] = 255;
		if (color[2] > 255)
			color[2] = 255;
	}
	return (color);
}

t_ray		*normalize(t_ray *r)
{
	float	longueur;

	longueur = sqrt((float)((r->x * r->x) + (r->y * r->y) + (r->z * r->z)));
	r->x /= longueur;
	r->y /= longueur;
	r->z /= longueur;
	return (r);
}
