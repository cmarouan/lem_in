#include "lem_in.h"


t_nodes      *ft_create_node(int type, char *name, int x, int y)
{
    t_nodes *node;

    node = (t_nodes *)malloc(sizeof(t_nodes));
    node->name = name;
    node->x = x;
    node->y = y;
    node->type = type;
    node->next = NULL;
    return (node); 
}

t_nodes     *ft_get_node(char *name, t_nodes *l)
{
    while (l)
    {
        if (!ft_strcmp(l->name, name))
            return (l);
        l = l->next;
    }
    return (NULL);
}

t_nodes     *ft_add_node(t_nodes **l, t_nodes *node)
{
    if (*l == NULL)
    {
        *l = node;
        return (*l);
    }
    node->next = *l;
    *l = node;
    return (*l);
}