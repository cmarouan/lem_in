#include "lem_in.h"

void ft_outerror()
{
    ft_putstr("ERROR");
    exit(ERROR);
}

int		ft_atoli(const char *str)
{
	int			i;
	long long	nbr;

	i = 0;
	nbr = 0;
	while (*str == '\t' || *str == '\n'
			|| *str == ' ' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str++;
	if (str[0] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
    if (!ft_isdigit(str[i]) && str[i] != '\0')
        ft_outerror();
	if (str[0] == '-')
		nbr = nbr * -1;
    if (nbr > INT_MAX)
        return (INT_MAX);
	return ((int)nbr);
}


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
    ft_add_node(&lemin->nodes, ft_create_node(node_name, ft_strdup(tab[0]), ft_atoli(tab[1]), ft_atoli(tab[2])));
    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
    return(lemin);
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

t_lemin    *ft_readlink(t_lemin *lemin, char *line)
{
    char **tab; 
    int i;
    int j;
    int x;

    x = 0;
    if (!line)
        ft_outerror();
    tab = ft_strsplit(line, '-');
    if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
        ft_outerror();
    i = ft_getindex(tab[0], lemin->names, lemin->size);
    j = ft_getindex(tab[1], lemin->names, lemin->size);
    if (i == -1 || j == -1)
        ft_outerror();
    lemin->graph[i][j] = '1';
    lemin->graph[j][i] = '1';
    while (tab[x])
        free(tab[x++]);
    free(tab);
    while (get_next_line(0, &line))
    {
        lemin->lines = ft_addline(lemin->lines, line);
        if (!ft_strncmp("#", line, 1))
            continue;
        else
        {
            tab = ft_strsplit(line, '-');
            if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
                ft_outerror();
            i = ft_getindex(tab[0], lemin->names, lemin->size);
            j = ft_getindex(tab[1], lemin->names, lemin->size);
            if (i == -1 || j == -1)
                ft_outerror();
            lemin->graph[i][j] = '1';
            lemin->graph[j][i] = '1';
            x = 0;
            while (tab[x])
                free(tab[x++]);
            free(tab);
        }
    }
    free(line);
    return (lemin);
}

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

void freelines(t_line *lines)
{
    t_line *tmp;
    t_line *last;

    last = lines->last;

    while (lines)
    {
    
        free(lines->line);
        tmp = lines;
        free(tmp);
        lines = lines->next;
    }
}

void freenodes(t_nodes *nodes)
{
    t_nodes *tmp;

    while (nodes)
    {
       free(nodes->name);
       tmp = nodes;
       nodes = nodes->next;
       free(tmp);
    }    
}

void freetab(char **names, int size)
{
    int i;

    i = 0;
    while (i < size)
        free(names[i++]);
    free(names);
}

void freeadj(t_adj **adj, int size)
{
    t_adj *tmp;
    t_adj *t;
    int i;

    i = 0;
    while (i < size)
    {
        tmp = adj[i];
        while (tmp)
        {
            t = tmp;
            tmp = tmp->next;
            free(t);
        }
        i++;
    }
    free(adj);
}

void freegroups(t_group *grps)
{
    t_group *temp;
    t_path *ptemp;
    t_path *pt2;
    t_listpath *ltemp;
    t_listpath *lt2;
     
    while (grps)
    {
        ltemp = grps->paths;
        temp = grps;
        while (ltemp)
        {
            ptemp = ltemp->path;
            lt2 = ltemp;
            while (ptemp)
            {
                pt2 = ptemp;
                ptemp = ptemp->next;
                free(pt2);
            }
            ltemp = ltemp->next;
            free(lt2);
        }
        grps = grps->next;
        free(temp);
    }
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

void implfordfulkerson(t_lemin *lemin, int count, int v, int u)
{
    int change;

    while (count)
    {
        count--;
        change = 0;
        lemin->tmp = fordfulkerson(lemin);
        while (u < lemin->size)
        {
            lemin->used[u] = 0;
            while (v < lemin->size)
            {
                if (lemin->graph[u][v] == '1' && lemin->tmp[u][v] == '0' && lemin->tmp[v][u]  == '0')
                {
                    lemin->graph[u][v] = '0';
                    change++;
                }
                lemin->tmp[u][v] = lemin->graph[u][v];
                v++;
            }
            u++;
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
    freegroups(lemin->groups);
    freearrays(s);
    free(lemin);
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
    get_next_line(0,&line);
    lemin->n_ant = ft_atoli(line);
    lemin->lines = ft_addline(lemin->lines, line);
    lemin = ft_readallnode(&line, lemin);
    lemin->names = ft_buildnames(lemin->nodes, lemin->size);
    lemin->graph = ft_initmat(lemin->size);
    lemin = ft_readlink(lemin, line);
    return (lemin);
}

int main()
{
    t_lemin *lemin;
    char *line;
    int count;
    t_group *teemp;
    t_group *tmp;
    t_arrays *s;

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
    s = createarrays(tmp);
    pass_ants(s, lemin->n_ant, lemin, teemp->paths);
    allfreefunction(lemin, s);
    return (0);
}