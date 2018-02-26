/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:08:14 by mfrisby           #+#    #+#             */
/*   Updated: 2018/02/26 11:02:36 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H

#include "mlx.h"
#include "../libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WIDTH 500
#define HEIGHT 350

#define COLORBLUE 4349940
#define COLORRED 16204611
#define COLORGREEN 1893939

#define SPHERE 1
#define PLAN 2
#define CYLINDRE 3
#define CONE 4
#define CAM 5
#define LIGHT 6

typedef struct s_cam
{
    //origine
    float camx;
    float camy;
    float camz;
    //vecteur directeur
    float vdirx;
    float vdiry;
    float vdirz;
    //vecteur droit
    float vrightx;
    float vrighty;
    float vrightz;
    //vecteur haut
    float vupx;
    float vupy;
    float vupz;
    //fov
    float fovh;
    float fovw;
    float fovd;
} t_cam;

typedef struct s_light
{
    int color[3];
    float x;
    float y;
    float z;
    float coef;
    struct s_light *next;
} t_light;

typedef struct s_sphere
{
    int color[3];
    float x;
    float y;
    float z;
    float r;
    struct s_sphere *next;
} t_sphere;

typedef struct s_cylindre
{
    int color[3];
    float x;
    float y;
    float z;
    float r;
    struct s_cylindre *next;
} t_cylindre;

typedef struct s_cone
{
    int color[3];
    float x;
    float y;
    float z;
    float r;
    struct s_cone *next;
} t_cone;

typedef struct s_plan
{
    int color[3];
    float x;
    float y;
    float z;
    float dirx;
    float diry;
    float dirz;
    struct s_plan *next;
} t_plan;

typedef struct s_upleft
{
    float x;
    float y;
    float z;
} t_upleft;

typedef struct s_ray
{
    float x;
    float y;
    float z;
} t_ray;

typedef struct s_pix
{
    float xindent;
    float yindent;
} t_pix;

typedef struct s_data
{
    struct s_sphere *sphere_head;
    struct s_light *light_head;
    struct s_plan *plan_head;
    struct s_cone *cone_head;
    struct s_cylindre *cylindre_head;
    struct s_cam *cam;
    void *mlx;
    void *win;
} t_data;

//functions
void rayloop(t_data *data, t_upleft *upleft, t_pix *pix);
int get_color(int r, int g, int b, float coef, float dot);
//object
float calcul_sphere(t_cam *cam, t_ray *ray, t_sphere *sphere);
float calcul_plan(t_cam *cam, t_ray *ray, t_plan *plan);
float    calcul_cylindre(t_cam *cam, t_ray *ray, t_cylindre *c);
float    calcul_cone(t_cam *cam, t_ray *ray, t_cone *cone);
//parsing
t_cam *get_cam(char *s);
t_sphere *get_sphere(char *s);
t_plan *get_plan(char *s);
t_cone *get_cone(char *s);
t_cylindre *get_cylindre(char *s);
t_light *get_light(char *s);
int parse_file(char *file, t_data **data);
//lst
int add_cylindre_lst(t_data **data, t_cylindre *elem);
int add_cone_lst(t_data **data, t_cone *elem);
int add_sphere_lst(t_data **data, t_sphere *elem);
int add_plan_lst(t_data **data, t_plan *elem);
int add_light_lst(t_data **data, t_light *elem);
//utils
t_ray *normalize(float x, float y, float z);
float get_dot(float ax, float ay, float az, float bx, float by, float bz);
//light
int get_light_at(float x, float y, float z, int *color, t_ray *intersection, t_light *light);
t_ray *get_intersection(t_cam *cam, t_ray *ray, float d);

#endif
