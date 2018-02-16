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

# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include <stdlib.h>
#include <math.h>

#define WIDTH       500
#define HEIGHT      350

#define COLORBLUE   4349940
#define COLORRED    16204611
#define COLORGREEN  1893939

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

typedef struct      s_sphere {
    float             x;
    float             y;
    float             z;
    float             r;
    int               color;
}                   t_sphere;

typedef struct      s_plan {
    float             dirx;
    float             diry;
    float             dirz;
    float             posx;
    float             posy;
    float             posz;
    int               color;
}                   t_plan;

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

typedef struct      s_pix {
    float           xindent;
    float           yindent;
}                   t_pix;

typedef struct      s_mlx {
    void            *mlx;
    void            *win;
}                   t_mlx;

void        rayloop(t_mlx *mlx, t_cam *cam, t_upleft *upleft, t_pix *pix);
void        calcul_sphere(t_cam *cam, t_ray *ray, t_mlx *mlx, int x, int y);
void        calcul_plan(t_cam *cam, t_ray *ray, t_mlx *mlx, int x, int y);

#endif
