#include "../inc/rtv1.h"

static int get_object(char *s, int type, t_data **data)
{
    if (type == CAM)
        (*data)->cam = get_cam(s);
    else if (type == SPHERE)
        add_elem(data, get_sphere(s), type);
    // else if (ft_strcmp(current, "plan"))
    //     get_plan()
    // else if (ft_strcmp(current, "cylindre"))
    //     get_cylindre();
    // else if (ft_strcmp(current, "cone"))
    //     get_cone();
    return (0);
}

static int parse(char *s, int type, t_data **data)
{
    if (ft_strcmp(s, "[cam]") == 0)
        return (CAM);
    else if (ft_strcmp(s, "[sphere]") == 0)
        return (SPHERE);
    else if (ft_strcmp(s, "[plan]") == 0)
        return (PLAN);
    else if (ft_strcmp(s, "[cylindre]") == 0)
        return (CYLINDRE);
    else if (ft_strcmp(s, "[cone]") == 0)
        return (CONE);
    else if (type != -1)
        get_object(s, type, data);
    else
        type = -1;
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
        type = parse(buf, type, data);
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
    t_objects *obj;
    
    cam = malloc(sizeof(t_cam));
    obj = malloc(sizeof(t_objects));
    if (!cam || !obj || !file || ft_strlen(file) <= 0)
        return (-1);
    fd = open_file(file);
    if (fd == -1)
        return (-1);
    read_file(fd, data);
    return (0);
}