#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lem_in.h"
#define TRUE 1
#define FALSE 0
#define START 0
#define END 1
#define ROOM 2
#define LINK 3


typedef struct  s_nodes
{
    char    *name;
    int     type;
    int     x;
    int     y;
    struct s_nodes *next;

}               t_nodes;


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

void    ft_print_nodes(t_nodes *nodes)
{

    while(nodes)
    {
        ft_putendl_fd(nodes->name, 1);
        nodes = nodes->next;
    }
    
}

void    ft_readnode(char *line, t_nodes **l, int node_name, char **result)
{
    char **tab;

    if(!line)
    {
        get_next_line(0, &line);
        *result = ft_strjoin(*result, line);
        *result = ft_strjoin(*result, "\n");
    }
    tab = ft_strsplit(line, ' ');
    ft_add_node(l, ft_create_node(node_name, tab[0], ft_atoi(tab[1]), ft_atoi(tab[2])));
    if (node_name != ROOM)
        ft_strdel(&line);
}
int     ft_linetype(char *line)
{
    int c;

    //char *tmp = line;
    c = 0;
    while (*line)
    {
        if (*line == ' ')
            c++;
        line++;
    }
    //printf("%s -- %d\n", tmp, c);
    return (c == 2 ? ROOM : LINK); 
        
}

int     ft_getindex(char *name, char **names, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        if (!ft_strcmp(name, names[i]))
            return (i);
        i++;
    }
    return (-1);
}

int     ft_readallnode(t_nodes **l, char **line, int size, char **result)
{
    while (get_next_line(0, line))
    {
        *result = ft_strjoin(*result, *line);
        *result = ft_strjoin(*result, "\n");
        if (!ft_strcmp("##start", *line))
            ft_readnode(NULL, l, START, result);
        else if (!ft_strcmp("##end", *line))
            ft_readnode(NULL, l, END, result);
        else if (!ft_strncmp("#", *line, 1))
        {
            ft_strdel(line);
            continue;
        }
        else if (ft_linetype(*line) == ROOM)
                ft_readnode(*line, l, ROOM, result);
        else
            break;
        size++;
        ft_strdel(line);
    }
    return (size);
}

char **ft_buildnames(t_nodes *tmp, int size)
{
    int     index;
    char    **names;

    index = 2;
    names = (char **)malloc(size * sizeof(char *));
     while(tmp)
    {
        if (tmp->type == START)
            names[START] = ft_strdup(tmp->name);
        else if (tmp->type == END)
            names[END] = ft_strdup(tmp->name);
        else
        {
            names[index] = ft_strdup(tmp->name);
            index++;
        }
        tmp = tmp->next;
    }
    return (names);
}

char **ft_initmat(int size)
{
    char **mat;
    int index;

    index = 0;
    mat = (char **)malloc(size * sizeof(char *));
    while (index < size)
    {
        mat[index] = (char *)ft_memalloc(sizeof(char) * (size + 1));
        ft_memset(mat[index], '0', size);
        index++;
    }
    return (mat);
}
char    **ft_readlink(char **mat, char *line, char **names, int size)
{
    char **tab; 
    int i;
    int j;

    tab = ft_strsplit(line, '-');
    i = ft_getindex(tab[0], names, size);
    j = ft_getindex(tab[1], names, size);
    mat[i][j] = '1';
    mat[j][i] = '1';
    ft_strdel(&line);
    while (get_next_line(0, &line))
    {
        ft_putendl_fd(line, 1);
        if (!ft_strncmp("#", line, 1))
        {
            ft_strdel(&line);
            continue;
        }
        else
        {
            tab = ft_strsplit(line, '-');
            i = ft_getindex(tab[0], names, size);
            j = ft_getindex(tab[1], names, size);
            mat[i][j] = '1';
            mat[j][i] = '1';
        }
        ft_strdel(&line);
    }
    return (mat);
}
void ft_printmat(char **mat, int size)
{
    int index = 0;

    ft_putendl("x| 0 1 2 3 4 5 6 7");
    ft_putendl("-----------------");
    while (index < size)
    {
        int i = 0;
        ft_putnbr(index);
        ft_putstr("| ");
        while (mat[index][i])
        {
            ft_putchar(mat[index][i]);
            ft_putchar(' ');
            i++;
        }
        ft_putchar('\n');
        index++;
    }
}

int main()
{
    t_nodes *l;
    int size;
    char *line;
    char **names;
    int number_of_ants;
    char **mat;
    char *result;

    l = NULL;
    
    //number of ants
    get_next_line(0,&line);
    number_of_ants = ft_atoi(line);
    result = ft_strjoin(line, "\n");
    // ft_putnbr_fd(number_of_ants, 1);
    // ft_putendl_fd("", 1);
    // read node 
    size = ft_readallnode(&l, &line, 0, &result);
    // list of name
    printf("%s", result);
    names = ft_buildnames(l, size);
    // Mat adj
    mat = ft_initmat(size);
    // read links
    mat = ft_readlink(mat, line, names, size);
    //ft_print_nodes(l);
    // ft_putendl_fd("*****", 1);
    // int index = 0;
    // while (index < size)
    // {
    //     ft_putnbr(index);
    //     ft_putchar_fd(' ', 1);
    //     ft_putendl_fd(names[index], 1);
    //     index++;
    // }
    // char **mat;
    // mat = (char **)malloc(size * sizeof(char *));
    // index = 0;
    // while (index < size)
    // {
    //     mat[index] = (char *)ft_memalloc(sizeof(char) * (size + 1));
    //     ft_memset(mat[index], '0', size);
    //     index++;
    // }
    ft_printmat(mat, size);
    




    
    return (0);
}