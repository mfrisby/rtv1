/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:27:20 by mfrisby           #+#    #+#             */
/*   Updated: 2018/04/27 16:27:45 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int		get_pos(char *s, t_cone *cone)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cone->x = ft_atof(tab[0]);
	cone->y = ft_atof(tab[1]);
	cone->z = ft_atof(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_dir(char *s, t_cone *cone)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cone->dirx = ft_atof(tab[0]);
	cone->diry = ft_atof(tab[1]);
	cone->dirz = ft_atof(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_col(char *s, t_cone *cone)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cone->color[0] = ft_getnbr(tab[0]);
	cone->color[1] = ft_getnbr(tab[1]);
	cone->color[2] = ft_getnbr(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_attribu(char **tab, int i, t_cone *cone)
{
	char		**tab2;

	tab2 = ft_strsplit(tab[i], ':');
	if (!tab2 || !tab2[0] || !tab2[1])
		return (-1);
	if (ft_strcmp(tab2[0], "pos") == 0
		&& get_pos(tab2[1], cone) == -1)
		return (-1);
	else if (ft_strcmp(tab2[0], "ang") == 0)
		cone->ang = pow(tan(ft_getnbr(tab2[1]) * 0.0174533f), 2);
	// else if (ft_strcmp(tab2[0], "rot") == 0)
	// 	cone->rot = 3.14f * ft_getnbr(tab2[1]) / 180.0;
	else if (ft_strcmp(tab2[0], "color") == 0
		&& get_col(tab2[1], cone) == -1)
		return (-1);
	else if (ft_strcmp(tab2[0], "dir") == 0
		&& get_dir(tab2[1], cone) == -1)
		return (-1);
	free(tab2[0]);
	free(tab2[1]);
	free(tab2);
	return (0);
}

t_cone			*get_cone(char *s)
{
	int			i;
	char		**tab;
	t_cone		*cone;

	i = 0;
	tab = ft_strsplit(s, ';');
	if (!tab)
		return (NULL);
	if ((cone = malloc(sizeof(t_cone))) == NULL)
		return (NULL);
	cone->next = NULL;
	while (tab[i])
	{
		if (get_attribu(tab, i, cone) == -1)
			return (NULL);
		i++;
	}
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	get_rotation(NULL, cone);
	return (cone);
}
