/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylindre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:28:45 by mfrisby           #+#    #+#             */
/*   Updated: 2018/04/27 16:34:49 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int		get_pos(char *s, t_cylindre *cylindre)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cylindre->x = ft_getnbr(tab[0]);
	cylindre->y = ft_getnbr(tab[1]);
	cylindre->z = ft_getnbr(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_dir(char *s, t_cylindre *cylindre)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cylindre->dirx = ft_getnbr(tab[0]);
	cylindre->diry = ft_getnbr(tab[1]);
	cylindre->dirz = ft_getnbr(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_col(char *s, t_cylindre *cylindre)
{
	char		**tab;

	tab = ft_strsplit(s, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (-1);
	cylindre->color[0] = ft_getnbr(tab[0]);
	cylindre->color[1] = ft_getnbr(tab[1]);
	cylindre->color[2] = ft_getnbr(tab[2]);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (0);
}

static int		get_attribu(char **tab, int i, t_cylindre *cylindre)
{
	char		**tab2;

	tab2 = ft_strsplit(tab[i], ':');
	if (!tab2 || !tab2[0])
		return (-1);
	if (ft_strcmp(tab2[0], "pos") == 0
		&& get_pos(tab2[1], cylindre) == -1)
		return (-1);
	// else if (ft_strcmp(tab2[0], "rot") == 0)
	// 	cylindre->rot = 3.14f * ft_getnbr(tab2[1]) / 180.0f;
	else if (ft_strcmp(tab2[0], "rad") == 0)
		cylindre->r = (double)ft_getnbr(tab2[1]) / 10.0;
	else if (ft_strcmp(tab2[0], "ang") == 0)
		cylindre->ang = ft_getnbr(tab2[1]);
	else if (ft_strcmp(tab2[0], "dir") == 0
		&& get_dir(tab2[1], cylindre) == -1)
		return (-1);
	else if (ft_strcmp(tab2[0], "color") == 0
		&& get_col(tab2[1], cylindre) == -1)
		return (-1);
	free(tab2[0]);
	free(tab2[1]);
	free(tab2);
	return (0);
}

t_cylindre		*get_cylindre(char *s)
{
	int			i;
	char		**tab;
	t_cylindre	*cylindre;

	i = 0;
	tab = ft_strsplit(s, ';');
	if (!tab)
		return (NULL);
	if ((cylindre = malloc(sizeof(t_cylindre))) == NULL)
		return (NULL);
	cylindre->next = NULL;
	while (tab[i])
	{
		if (get_attribu(tab, i, cylindre) == -1)
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
	get_rotation(cylindre, NULL);
	return (cylindre);
}
