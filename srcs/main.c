#include "lem_in.h"

void ft_outerror()
{
    ft_putstr("ERROR");
    exit(ERROR);
}

void freearrays(t_arrays *arr)
{
    t_arrays *temp;

    while (arr)
    {
        temp = arr;
        arr = arr->next;
        free(temp->patharray);
        free(temp); 
    }
}



void implfordfulkerson(t_lemin *lemin, int count, int v, int u)
{
    int change;

    while (count--)
    {
        change = 0;
        lemin->tmp = fordfulkerson(lemin);
        while (u < lemin->size)
        {
            lemin->used[u++] = 0;
            while (v < lemin->size)
            {
                if (lemin->graph[u - 1][v] == '1'
                && lemin->tmp[u - 1][v] == '0' && lemin->tmp[v][u - 1]  == '0')
                {
                    lemin->graph[u - 1][v] = '0';
                    change++;
                }
                lemin->tmp[u - 1][v] = lemin->graph[u - 1][v];
                v++;
            }
        }
        if (!change)
            break;
        else change = 0;
    }
}

void allfreefunction(t_lemin *lemin, t_arrays *s)
{
    freelines(lemin->lines);
    freenodes(lemin->nodes);
    freetab(lemin->names, lemin->size);
    freetab(lemin->graph, lemin->size);
    freetab(lemin->tmp, lemin->size);
    freeadj(lemin->adj, lemin->size);
    free(lemin->used);
    free(lemin->visited);
    free(lemin->pred);
    free(lemin->checker);
    freegroups(lemin->groups, NULL);
    freearrays(s);
    free(lemin);
}



int main()
{
    t_lemin *lemin;
    char *line;
    int count;
    t_group *teemp;
    t_group *tmp;

    line = NULL;
    lemin = initlemin(line);
    initfunct(lemin, 0, -1, -1);
    count = countnodefromstart(lemin->graph[0], lemin->size);
    implfordfulkerson(lemin, count, 0, 0);
    teemp = best_groups(lemin->groups, lemin->n_ant);
    teemp = dispatchant(teemp, lemin);
    if (teemp->paths->path->size == 2)
    {
        passallants(lemin->n_ant, lemin, teemp->paths->path);
        return 0;
    }
    tmp = teemp;
    lemin->arrays = createarrays(tmp);
    ft_printlines(lemin->lines);
    pass_ants(lemin->arrays, lemin->n_ant, lemin, teemp->paths);
    allfreefunction(lemin, lemin->arrays);
    return (0);
}