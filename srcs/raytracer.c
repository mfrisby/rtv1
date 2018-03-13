/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:31:40 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/13 11:57:52 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int			raytrace(t_ray *ray, t_ray *light_ray, t_data *data)
{
	float			max_d;
	int				*rgb;

	max_d = 3.4028234664e+38;
	max_d = while_sphere(data, ray, &rgb, max_d);
	max_d = while_plan(data, ray, &rgb, max_d);
	max_d = while_cylindre(data, ray, &rgb, max_d);
	max_d = while_cone(data, ray, &rgb, max_d);
	if (max_d > 0.01f && max_d < 3.4028234664e+37)
	{
		return (while_light(rgb, light_ray, data));
	}
	return (0);
}

void				rayloop(t_data *data, t_upleft *upleft, t_pix *pix)
{
	int				x;
	int				y;
	t_ray			*ray;
	t_ray			*light_ray;

	ray = malloc(sizeof(t_ray));
	light_ray = malloc(sizeof(t_ray));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_hook(data->win, 3, 3, key_hook, data);
			ray->x = upleft->x + data->cam->vrightx * pix->xindent
				* x - data->cam->vupx * pix->yindent * y;
			ray->y = upleft->y + data->cam->vrighty * pix->xindent
				* x - data->cam->vupy * pix->yindent * y;
			ray->z = upleft->z + data->cam->vrightz * pix->xindent
				* x - data->cam->vupz * pix->yindent * y;
			ray = normalize(ray);
			mlx_pixel_put(data->mlx, data->win, x, y, raytrace(ray, light_ray, data));
			x++;
		}
		y++;
	}
	free(ray);
	free(light_ray);
}
