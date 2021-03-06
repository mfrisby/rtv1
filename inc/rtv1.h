/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:08:14 by mfrisby           #+#    #+#             */
/*   Updated: 2018/07/13 13:54:48 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define WIDTH 700
# define HEIGHT 700

# define COLORBLUE 4349940
# define COLORRED 16204611
# define COLORGREEN 1893939

# define SPHERE 1
# define PLAN 2
# define CYLINDRE 3
# define CONE 4
# define CAM 5
# define LIGHT 6
# define INIT    42
# define NOTINIT -42

typedef struct			s_cam
{
	double				camx;
	double				camy;
	double				camz;
	double				vdirx;
	double				vdiry;
	double				vdirz;
	double				vrightx;
	double				vrighty;
	double				vrightz;
	double				vupx;
	double				vupy;
	double				vupz;
	double				fovh;
	double				fovw;
	double				fovd;
	int					is_init;
}						t_cam;

typedef struct			s_light
{
	int					color[3];
	double				x;
	double				y;
	double				z;
	double				coef;
	struct s_light		*next;
}						t_light;

typedef struct			s_sphere
{
	int					color[3];
	double				x;
	double				y;
	double				z;
	double				r;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_cylindre
{
	int					color[3];
	double				x;
	double				y;
	double				z;
	double				r;
	double				rot;
	double				ang;
	struct s_cylindre	*next;
}						t_cylindre;

typedef struct			s_cone
{
	int					color[3];
	double				x;
	double				y;
	double				z;
	double				ang;
	double				rot;
	struct s_cone		*next;
}						t_cone;

typedef struct			s_plan
{
	int					color[3];
	double				x;
	double				y;
	double				z;
	double				dirx;
	double				diry;
	double				dirz;
	struct s_plan		*next;
}						t_plan;

typedef struct			s_upleft
{
	double				x;
	double				y;
	double				z;
}						t_upleft;

typedef struct			s_ray
{
	double				x;
	double				y;
	double				z;
}						t_ray;

typedef struct			s_pix
{
	double				xindent;
	double				yindent;
}						t_pix;

typedef struct			s_data
{
	double				max_d;
	struct s_sphere		*sphere_head;
	struct s_light		*light_head;
	struct s_plan		*plan_head;
	struct s_cone		*cone_head;
	struct s_cylindre	*cylindre_head;
	struct s_cam		*cam;
	struct s_ray		*object_norme;
	struct s_ray		*intersection;
	struct s_ray		*ray;
	void				*current;
	void				*mlx;
	void				*win;
}						t_data;

void					rayloop(t_data *da, t_upleft *upleft, t_pix *pix);
double					calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere);
double					calcul_plan(t_cam *cam, t_ray *ray, t_plan *plan);
double					calcul_cylindre(t_cam *cam, t_ray *ray, t_cylindre *c);
double					calcul_cone(t_cam *cam, t_ray *ray, t_cone *cone);
double					while_plan(t_data *data, t_ray *ray,
							int **rgb, double max_d);
double					while_sphere(t_data *data, t_ray *ray,
							int **rgb, double max_d);
double					while_cylindre(t_data *da, t_ray *ray,
							int **rgb, double max_d);
double					while_cone(t_data *data, t_ray *ray,
							int **rgb, double max_d);
t_cam					*get_cam(char *s);
t_sphere				*get_sphere(char *s);
t_plan					*get_plan(char *s);
t_cone					*get_cone(char *s);
t_cylindre				*get_cylindre(char *s);
t_light					*get_light(char *s);
int						parse_file(char *file, t_data **data);
int						add_cylindre_lst(t_data **data, t_cylindre *elem);
int						add_cone_lst(t_data **data, t_cone *elem);
int						add_sphere_lst(t_data **data, t_sphere *elem);
int						add_plan_lst(t_data **data, t_plan *elem);
int						add_light_lst(t_data **data, t_light *elem);
t_ray					*normalize(t_ray *r);
void					free_heads(t_data *data);
int						key_hook(int keycode, t_data *data);
void					get_intersection(t_data *data, t_ray *ray, double d);
int						while_light(int *rgb, t_ray *light_ray, t_data *data);
int						*get_color(int *color, int *rgb, t_light *l,
							double dot);
double					get_dot(t_ray *r1, t_ray *r2);
int						get_colision(t_ray *r, t_data *data);
void					get_rotation(t_cylindre *cy, t_cone *co);
void					rotate(t_ray *ray, float rot);
#endif
