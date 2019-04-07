#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0 


typedef struct  s_nodes
{
    char    *name;
    int     index;
    int     x;
    int     y;
    int     visited;
    struct s_nodes *adj;
    struct s_nodes *next;

}               t_nodes;


t_nodes      *ft_create_node(int index, char *name, int x, int y)
{
    t_nodes *node;

    node = (t_nodes *)malloc(sizeof(t_nodes));
    node->name = strdup(name);
    node->x = x;
    node->y = y;
    node->index = index;
    node->next = NULL;
    node->adj = NULL;
    node->visited = FALSE;
    return (node); 
}

// void        *ft_add_adj(t_nodes **l, char *name, t_nodes *node)
// {
//     t_nodes *tmp;
//     t_nodes *tmp1;

//     tmp = *l;
//     while(tmp)
//     {
//         if (!strcmp(tmp->name, name))
//         {
//             ft_add_node()
//         }
//         tmp = tmp->next;
//     }

// }

t_nodes     *ft_get_node(char *name, t_nodes *l)
{
    while (l)
    {
        if (!strcmp(l->name, name))
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

void        *ft_add_adj(t_nodes **l, char *name, t_nodes *node)
{
    t_nodes *tmp;
    t_nodes *tmp1;

    tmp = ft_get_node(name, *l);
    node->adj = ft_add_node(&(node->adj), 
                                    ft_create_node(tmp->index, tmp->name, tmp->x, tmp->y));
    tmp = *l;
    while(tmp)
    {
        if (!strcmp(tmp->name, name))
        {
            tmp->adj = ft_add_node(&(tmp->adj), 
                                    ft_create_node(node->index, node->name, node->x, node->y));
        }
        tmp = tmp->next;
    }

}


void    ft_print_nodes(t_nodes *nodes)
{
    t_nodes *tmp;

    while(nodes)
    {
        printf("%s =>[", nodes->name);
        tmp = nodes->adj;
        while (tmp)
        {
            if (tmp->next)
                printf("%s-%d, ",tmp->name, tmp->visited);
            else
                 printf("%s-%d", tmp->name, tmp->visited);
            tmp = tmp->next;
        }
        printf("]\n");
        nodes = nodes->next;
    }
    
}




int main()
{
    t_nodes *l;

    l = NULL;

    l = ft_add_node(&l, ft_create_node(0, "1", 0, 0));
    l = ft_add_node(&l, ft_create_node(1, "2", 0, 0));
    l = ft_add_node(&l, ft_create_node(2, "3", 0, 0));
    l = ft_add_node(&l, ft_create_node(3, "4", 0, 0));
    l = ft_add_node(&l, ft_create_node(4, "5", 0, 0));
    l = ft_add_node(&l, ft_create_node(5, "6", 0, 0));
    l = ft_add_node(&l, ft_create_node(6, "7", 0, 0));
    l = ft_add_node(&l, ft_create_node(7, "0", 0, 0));
    ft_add_adj(&l , "0", ft_get_node("4", l));
    ft_add_adj(&l , "0", ft_get_node("6", l));
    ft_add_adj(&l , "1", ft_get_node("3", l));
    ft_add_adj(&l , "4", ft_get_node("3", l));
    ft_add_adj(&l , "5", ft_get_node("2", l));
    ft_add_adj(&l , "3", ft_get_node("5", l));
    ft_add_adj(&l , "4", ft_get_node("2", l));
    ft_add_adj(&l , "2", ft_get_node("1", l));
    ft_add_adj(&l , "7", ft_get_node("6", l));
    ft_add_adj(&l , "7", ft_get_node("2", l));
    ft_add_adj(&l , "7", ft_get_node("4", l));
    ft_add_adj(&l , "6", ft_get_node("5", l));
    ft_print_nodes(l);

    
    return (0);
}