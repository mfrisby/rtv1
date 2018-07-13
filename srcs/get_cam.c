/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:21:55 by mfrisby           #+#    #+#             */
/*   Updated: 2018/04/11 15:07:00 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int		get_pos(char *s, t_cam *cam)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cam->camx = ft_getnbr(tab[0]);
	cam->camy = ft_getnbr(tab[1]);
	cam->camz = ft_getnbr(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_dir(char *s, t_cam *cam)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cam->vdirx = ft_getnbr(tab[0]);
	cam->vdiry = ft_getnbr(tab[1]);
	cam->vdirz = ft_getnbr(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static void		sup_var(t_cam *cam)
{
	cam->vrightx = 1.0f;
	cam->vrighty = 0.0f;
	cam->vrightz = 0.0f;
	cam->vupx = 0.0f;
	cam->vupy = 1.0f;
	cam->vupz = 0.0f;
	cam->fovh = 1.0;
	cam->fovw = 1.0;
	cam->fovd = 0.8;
	cam->is_init = INIT;
}

static void		free_tab(char **tab)
{
	int			i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_cam			*get_cam(char *s)
{
	int			i;
	char		**tab;
	char		**tab2;
	t_cam		*cam;

	i = 0;
	cam = malloc(sizeof(t_cam));
	cam->is_init = NOTINIT;
	tab = ft_strsplit(s, ';');
	while (tab[i])
	{
		tab2 = ft_strsplit(tab[i], ':');
		if (ft_strcmp(tab2[0], "pos") == 0)
			get_pos(tab2[1], cam);
		if (ft_strcmp(tab2[0], "dir") == 0)
			get_dir(tab2[1], cam);
		free(tab2[0]);
		free(tab2[1]);
		free(tab2);
		i++;
	}
	free_tab(tab);
	sup_var(cam);
	return (cam);
}
