/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:31:40 by mfrisby           #+#    #+#             */
/*   Updated: 2018/04/11 15:22:18 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static void			free_norme(t_ray *r, t_ray *light_ray)
{
	free(r);
	free(light_ray);
}

static void			malloc_norme(t_ray **r, t_ray **light_ray)
{
	*r = malloc(sizeof(t_ray));
	*light_ray = malloc(sizeof(t_ray));
}

static int			raytrace(t_ray *ray, t_ray *light_ray, t_data *data)
{
	double			max_d;
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

void				rayloop(t_data *da, t_upleft *upleft, t_pix *pix)
{
	int				x;
	int				y;
	t_ray			*r;
	t_ray			*light_ray;

	malloc_norme(&r, &light_ray);
	y = -1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		{
			mlx_hook(da->win, 3, 3, key_hook, da);
			r->x = upleft->x + da->cam->vrightx * pix->xindent
				* x - da->cam->vupx * pix->yindent * y;
			r->y = upleft->y + da->cam->vrighty * pix->xindent
				* x - da->cam->vupy * pix->yindent * y;
			r->z = upleft->z + da->cam->vrightz * pix->xindent
				* x - da->cam->vupz * pix->yindent * y;
			r = normalize(r);
			mlx_pixel_put(da->mlx, da->win, x, y, raytrace(r, light_ray, da));
		}
	}
	free_norme(r, light_ray);
}
