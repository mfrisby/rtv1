/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:16:48 by mfrisby           #+#    #+#             */
/*   Updated: 2018/03/14 11:28:38 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double		calcul_plan(t_cam *cam, t_ray *ray, t_plan *plan)
{
	double	d;
	double	t;

	d = -(plan->dirx * plan->x + plan->diry * plan->y + plan->dirz * plan->z);
	t = -((plan->dirx * (cam->camx - plan->x) + plan->diry
				* (cam->camy - plan->y)
				+ plan->dirz * (cam->camz - plan->z) + d) / (plan->dirx * ray->x
				+ plan->diry * ray->y + plan->dirz * ray->z));
	return (t);
}

double		calcul_cylindre(t_cam *cam, t_ray *ray, t_cylindre *cy)
{
	double	delta;
	double	t[2];
	double	abc[3];

	abc[0] = pow(ray->x, 2) + pow(ray->z, 2) + pow(ray->y, 2) -
    (cy->dirx* cy->dirx* ray->x * ray->x + cy->diry* cy->diry* ray->y * ray->y + cy->dirz* cy->dirz*
		ray->z * ray->z + 2 * cy->dirx* cy->diry* ray->x * ray->y + 2 * cy->dirx* cy->dirz
		* ray->x * ray->z + 2 * cy->diry* cy->dirz* ray->y * ray->z) /
        (cy->dirx* cy->dirx + cy->diry* cy->diry+ cy->dirz* cy->dirz);
    abc[1] = (2 * (cam->camx - cy->x) * ray->x) + (2 * (cam->camy - cy->y) * ray->y) +
		(2 * (cam->camz - cy->z) * ray->z) -(2 * cy->dirx* cy->dirx* (cam->camx - cy->x) * ray->x
		+ 2 * cy->dirx* cy->diry* (cam->camx - cy->x) * ray->y + 2 * cy->dirx* cy->dirz* (cam->camx - cy->x) * ray->z +
		2 * cy->diry* cy->dirx* (cam->camy - cy->y) * ray->x + 2 * cy->diry* cy->diry* (cam->camy - cy->y) * ray->y + 2
		* cy->diry* cy->dirz* (cam->camy - cy->y) * ray->z + 2 * cy->dirx* cy->dirz* (cam->camz - cy->z) * ray->x + 2
		* cy->dirz* cy->diry* (cam->camz - cy->z) * ray->y + 2 * cy->dirz* cy->dirz* (cam->camz - cy->z) * ray->z) /
		(cy->dirx* cy->dirx + cy->diry* cy->diry+ cy->dirz* cy->dirz);
    abc[2] = pow((cam->camx - cy->x), 2) + pow((cam->camy - cy->y), 2) + pow((cam->camz - cy->z), 2)
		- pow(cy->r, 2) - (cy->dirx* cy->dirx* (cam->camx - cy->x) * (cam->camx - cy->x) + cy->diry* cy->diry* (cam->camy - cy->y) * (cam->camy - cy->y) + cy->dirz* cy->dirz* (cam->camz - cy->z) * (cam->camz - cy->z) +
        2 * cy->dirx* cy->diry* (cam->camx - cy->x) * (cam->camy - cy->y) + 2 * cy->dirx* cy->dirz* (cam->camx - cy->x) * (cam->camz - cy->z) + 2 * cy->dirz* cy->diry* (cam->camz - cy->z) * (cam->camy - cy->y)) /
        (cy->dirx* cy->dirx + cy->diry* cy->diry+ cy->dirz* cy->dirz);
	delta = (abc[1]* abc[1]) - 4 * abc[0] * abc[2];
	abc[1]= -abc[1];
	if (delta > 0.0f)
	{
		t[0] = (abc[1]+ sqrt(delta)) / (2 * abc[0]);
		t[1] = (abc[1]- sqrt(delta)) / (2 * abc[0]);
		if (t[0] < t[1])
			return (t[0]);
		return (t[1]);
	}
	else if (delta == 0)
		return (abc[1]/ (2 * abc[0]));
	return (-1);
}

double		calcul_cone(t_cam *cam, t_ray *ray, t_cone *cone)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t[2];

	a = pow(ray->x, 2) + pow(ray->z, 2) - pow(ray->y, 2) * cone->ang;
	b = 2 * (ray->x * (cam->camx - cone->x) + ray->z *
			(cam->camz - cone->z) - ray->y * (cam->camy - cone->y) * cone->ang);
	c = (pow(cam->camx - cone->x, 2) + pow(cam->camz - cone->z, 2)
			- pow(cam->camy - cone->y, 2) * cone->ang);
	delta = (b * b) - 4 * a * c;
	b = -b;
	if (delta > 0.0f)
	{
		t[0] = (b + sqrt(delta)) / (2 * a);
		t[1] = (b - sqrt(delta)) / (2 * a);
		if (t[0] <= t[1])
			return (t[0]);
		return (t[1]);
	}
	else if (delta == 0)
		return (b / (2 * a));
	return (-1);
}

double		calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t[2];

	a = pow(ray->x, 2) + pow(ray->y, 2) + pow(ray->z, 2);
	b = 2 * (ray->x * (cam->camx - sphere->x) + ray->y *
			(cam->camy - sphere->y) + ray->z * (cam->camz - sphere->z));
	c = (pow(cam->camx - sphere->x, 2) + pow(cam->camy - sphere->y, 2)
			+ pow(cam->camz - sphere->z, 2)) - pow(sphere->r, 2);
	delta = (b * b) - 4 * a * c;
	b = -b;
	if (delta > 0.0f)
	{
		t[0] = (b + sqrt(delta)) / (2 * a);
		t[1] = (b - sqrt(delta)) / (2 * a);
		if (t[0] <= t[1])
			return (t[0]);
		return (t[1]);
	}
	else if (delta == 0)
		return (b / (2 * a));
	return (-1);
}