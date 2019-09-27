#include "lem_in.h"

int countnodefromstart(char *g, int size)
{
    int i;
    int c;
    
    c = 0;
    i = 0;
    while (i < size)
    {
        if (g[i] == '1')
            c++;
        i++;
    }
    return c;
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
     if (!names[START] || !names[END])
        ft_outerror();
    return (names);
}

t_adj *ft_addadj(t_adj *l, int node)
{
    t_adj *t = (t_adj *)malloc(sizeof(t_adj));
    t->node = node;
    t->next = NULL;
    if (!l)
        return t;
    t->next = l;
    return t;
}

t_group *dispatchant(t_group *teemp, t_lemin *lemin)
{
    int i = 0;
    int nbrant = lemin->n_ant;

    while (nbrant)
    {
        i = 0;
        t_listpath *ansr;
        t_listpath *it = teemp->paths;
        ansr = it; 
        while (i < teemp->stop)
        {
            if (ansr->v_node > it->v_node)
                ansr = it;
            it = it->next;
            i++;
        }
        ansr->v_node++;
        ansr->nbr_ant++;
        nbrant--;
    }
    return teemp;
}
