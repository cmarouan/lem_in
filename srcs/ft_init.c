#include "lem_in.h"

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

t_lemin *initlemin(char *line)
{
    t_lemin *lemin;

    lemin = (t_lemin *)malloc(sizeof(t_lemin));
    lemin->lines = NULL;
    lemin->nodes = NULL;
    lemin->groups = NULL;
    lemin->start = START;
    lemin->goal = END;
    lemin->nopath = 0;
    while (get_next_line(0,&line))
        if (line[0] == '#')
            lemin->lines = ft_addline(lemin->lines, line);
        else
            break ;
    lemin->n_ant = ft_atoli(line);
    if (lemin->n_ant == 0)
        ft_outerror();
    lemin->lines = ft_addline(lemin->lines, line);
    lemin = ft_readallnode(&line, lemin);
    lemin->names = ft_buildnames(lemin->nodes, lemin->size);
    lemin->graph = ft_initmat(lemin->size);
    lemin = ft_readlink(lemin, line);
    return (lemin);
}

void initfunct(t_lemin *lemin, int i, int u, int v)
{
    t_adj **adj;

    lemin->tmp = (char **)malloc(sizeof(char *) * lemin->size);
    while (i < lemin->size)
        lemin->tmp[i++] = (char *)malloc(sizeof(char) * lemin->size);
    adj = (t_adj **)malloc(sizeof(t_adj *) * lemin->size);
    lemin->visited = (int *)malloc(sizeof(int) * lemin->size);
    lemin->used = (int *)malloc(sizeof(int) * lemin->size);
    lemin->pred = (int *)malloc(sizeof(int) * lemin->size);
    lemin->checker = (int *)malloc(sizeof(int) * lemin->size);
    while (++u < lemin->size)
    {
        v = -1;
        adj[u] = NULL;
        lemin->visited[u] = 0;
        lemin->used[u] = 0;
        lemin->checker[u] = 0;
        while (++v < lemin->size)
        {
            lemin->tmp[u][v] = lemin->graph[u][v];
            if (lemin->graph[u][v] == '1')
                adj[u] = ft_addadj(adj[u], v);
        }
    }
    lemin->adj = adj;
}

void ft_fillgraph(t_lemin *lemin, char *line)
{
    char **tab;
    int i;
    int j;

    tab = ft_strsplit(line, '-');
    if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
        ft_outerror();
    i = ft_getindex(tab[0], lemin->names, lemin->size);
    j = ft_getindex(tab[1], lemin->names, lemin->size);
    if (i == -1 || j == -1)
        ft_outerror();
    lemin->graph[i][j] = '1';
    lemin->graph[j][i] = '1';
    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}