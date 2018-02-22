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
            return (-1);
    }
    return (0);
}

static int  open_file(char *file)
{
    int fd;
    
    fd = open(file, O_RDONLY);
    return (fd);
}

int    parse_file(char *file, t_data **data)
{
    int fd;
    t_cam *cam;
    
    cam = malloc(sizeof(t_cam));
    if (!cam || !file || ft_strlen(file) <= 0)
        return (-1);
    fd = open_file(file);
    if (fd == -1)
        return (-1);
    if (read_file(fd, data) == -1)
        return (-1);
    return (0);
}