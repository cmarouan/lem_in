
#include "lem_in.h"

t_lemin     *ft_readallnode(char **line, t_lemin *lemin)
{
    while (get_next_line(0, line))
    {
        lemin->lines = ft_addline(lemin->lines, *line);
        if (!ft_strcmp("##start", *line))
            lemin = ft_readnode(NULL, START, lemin);
        else if (!ft_strcmp("##end", *line))
            lemin = ft_readnode(NULL, END, lemin);
        else if (!ft_strncmp("#", *line, 1))
            continue;
        else if (ft_linetype(*line) == ROOM)
               lemin = ft_readnode(*line, ROOM, lemin);
        else
            break;
        lemin->size++;
    }
    return (lemin);
}


t_lemin     *ft_readnode(char *line, int node_name, t_lemin *lemin)
{
    char **tab;
    int     i;

    if(!line)
    {
        get_next_line(0, &line);
        lemin->lines = ft_addline(lemin->lines, line);
    }
    tab = ft_strsplit(line, ' ');
    if (tab[0] == NULL || tab[1] == NULL || tab[2] == NULL || tab[3] != NULL)
        ft_outerror();
    ft_add_node(&lemin->nodes, ft_create_node(node_name, ft_strdup(tab[0]),
        ft_atoli(tab[1]), ft_atoli(tab[2])));
    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
    return(lemin);
}

t_lemin    *ft_readlink(t_lemin *lemin, char *line)
{
    if (!line)
        ft_outerror();
    ft_fillgraph(lemin, line);
    while (get_next_line(0, &line))
    {
        lemin->lines = ft_addline(lemin->lines, line);
        if (!ft_strncmp("#", line, 1))
            continue;
        else
            ft_fillgraph(lemin, line);
    }
    free(line);
    return (lemin);
}

int     ft_linetype(char *line)
{
    int c;

    c = 0;
    while (*line)
    {
        if (*line == ' ')
            c++;
        line++;
    }
    if (c == 2) 
        return (ROOM);
    else if (c == 0)
        return (LINK);
    else
        return (ERROR); 
        
}

int     ft_getindex(char *name, char **names, int size)
{
    int i;

    i = 0;
    if (!name)
        return (-1);
    while (i < size)
    {
        if (!ft_strcmp(name, names[i]))
            return (i);
        i++;
    }
    return (-1);
}