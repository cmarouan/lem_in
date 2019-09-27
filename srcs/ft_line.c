#include "lem_in.h"

t_line *ft_createline(char *line)
{
    t_line  *l;

    l = (t_line *)malloc(sizeof(t_line));
    l->last = l;
    l->line = line;
    l->next = NULL;
    return (l);
}

t_line  *ft_addline(t_line *list, char *line)
{
    t_line *tmp;

    tmp = ft_createline(line); 
    if (!list)
        return (tmp);
    list->last->next = tmp;
    list->last = tmp;
    return (list);
}

void ft_printlines(t_line *lines)
{
    t_line *tmp;

    tmp = lines;
    while (tmp)
    {
        ft_putstr(tmp->line);
        ft_putstr("\n");
        tmp = tmp->next;
    }
    ft_putstr("\n");
    
}
