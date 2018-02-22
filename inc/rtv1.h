/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:08:14 by mfrisby           #+#    #+#             */
/*   Updated: 2018/02/07 17:09:03 by mfrisby          ###   ########.fr       */
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


#define WIDTH       500
#define HEIGHT      350

#define COLORBLUE   4349940
#define COLORRED    16204611
#define COLORGREEN  1893939

#define SPHERE      1
#define PLAN        2
#define CYLINDRE    3
#define CONE        4
#define CAM         5

typedef struct      s_cam {
    //origine
    float           camx;
    float           camy;
    float           camz;
    //vecteur directeur
    float           vdirx;
    float           vdiry;
    float           vdirz;
    //vecteur droit
    float           vrightx;
    float           vrighty;
    float           vrightz;
    //vecteur haut
    float           vupx;
    float           vupy;
    float           vupz;
    //fov
    float           fovh;
    float           fovw;
    float           fovd;
}                   t_cam;

typedef struct      s_light {
    float           x;
    float           y;
    float           z;
    float           coef;
    struct s_light  *next;
}                   t_light;

typedef struct          s_sphere {
    float               x;
    float               y;
    float               z;
    float               r;
    int                color[3];
    struct s_sphere     *next;
}                       t_sphere;

typedef struct          s_plan {
    float               dirx;
    float               diry;
    float               dirz;
    float               posx;
    float               posy;
    float               posz;
    long                color;
    struct s_plan       *next;
}                       t_plan;

typedef struct      s_upleft {
    float             x;
    float             y;
    float             z;
}                   t_upleft;

typedef struct      s_ray {
    float             x;
    float             y;
    float             z;
}                   t_ray;

typedef struct              s_pix {
    float                   xindent;
    float                   yindent;
}                           t_pix;

typedef struct              s_data {
    struct s_sphere         *sphere_head;
    struct s_light          *light_head;
    struct s_plan           *plan_head;
    struct s_cam            *cam;
    void                    *mlx;
    void                    *win;
}                           t_data;

//functions
void                rayloop(t_data *data, t_upleft *upleft, t_pix *pix);
float    calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere);
//float               calcul_plan(t_cam *cam, t_ray *ray);
//parsing
t_cam               *get_cam(char *s);
t_sphere            *get_sphere(char *s);
int                 parse_file(char *file, t_data **data);
int                add_sphere_lst(t_data **data, t_sphere *elem);
float               ft_getfloat(char *str);
//utils
t_ray *normalize(float x, float y, float z);
float get_dot(float ax, float ay, float az, float bx, float by, float bz);

#endif
