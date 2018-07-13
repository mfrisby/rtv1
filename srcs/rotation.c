/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 13:25:30 by mfrisby           #+#    #+#             */
/*   Updated: 2018/07/13 14:16:20 by mfrisby          ###   ########.fr       */
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