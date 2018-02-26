/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <mfrisby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:04:58 by mfrisby           #+#    #+#             */
/*   Updated: 2018/02/26 14:45:51 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int get_object(char *s, int type, t_data **data)
{
    if (type == CAM)
        (*data)->cam = get_cam(s);
    else if (type == SPHERE)
    {
        if ((add_sphere_lst(data, get_sphere(s))) == -1)
            return (-1);
    }
    else if (type == PLAN)
    {
        if ((add_plan_lst(data, get_plan(s))) == -1)
            return (-1);
    }
    else if (type == CYLINDRE)
    {
        if ((add_cylindre_lst(data, get_cylindre(s))) == -1)
            return (-1);
    }
    else if (type == CONE)
    {
        if ((add_cone_lst(data, get_cone(s))) == -1)
            return (-1);
    }
    else if (type == LIGHT)
    {
        if ((add_light_lst(data, get_light(s))) == -1)
            return (-1);
    }
    return (0);
}

static int parse(char *s, int *type, t_data **data)
{
    if (ft_strcmp(s, "[cam]") == 0)
        *type = CAM;
    else if (ft_strcmp(s, "[sphere]") == 0)
        *type = SPHERE;
    else if (ft_strcmp(s, "[plan]") == 0)
        *type = PLAN;
    else if (ft_strcmp(s, "[cylindre]") == 0)
        *type = CYLINDRE;
    else if (ft_strcmp(s, "[cone]") == 0)
        *type = CONE;
    else if (ft_strcmp(s, "[light]") == 0)
        *type = LIGHT;
    else if (*type != -1)
        return (get_object(s, *type, data));
    else
        *type = -1;
    return (0);
}

static int read_file(int fd, t_data **data)
{
    int     type;
    char *buf;

    type = -1;
    buf = NULL;
    while (get_next_line(fd, &buf))
    {
        if (!buf || ft_strlen(buf) <= 0)
            break;
        else if (buf[0] == '#')
            continue;
        if (parse(buf, &type, data) == -1)
            continue;
    }
    return (0);
}

static int  open_file(char *file)
{
    int fd;
    
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        ft_printf("\033[0;31mError: %s\033[0m",strerror(errno));
        exit (0);
    }
    return (fd);
}

int    parse_file(char *file, t_data **data)
{
    int fd;
    
    ft_putendl("Parse file.");
    if (!file || ft_strlen(file) <= 0)
        return (-1);
    fd = open_file(file);
    if (read_file(fd, data) == -1)
        return (-1);
    if ((*data)->cam == NULL || (*data)->cam->is_init == NOTINIT)
    {
        ft_putendl("\033[0;31mError : you need to add cam in your config file; Format:\033[0m");
        ft_putendl("[cam]\npos:x,y,z;dir:x,y,z");
        exit(0);
    }
    if ((*data)->light_head == NULL)
        ft_putendl("\033[0;33mWarning: no light in config file.\033[0m");
    return (0);
}