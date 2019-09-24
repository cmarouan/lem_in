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
#define ERROR -1
#define ENDLINE ft_strdup("\n")

char **fordfulkerson(t_lemin *lemin);

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

void ft_outerror()
{
    ft_putstr("ERROR");
    exit(ERROR);
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

void    ft_print_nodes(t_nodes *nodes)
{

    while(nodes)
    {
        ft_putendl_fd(nodes->name, 1);
        nodes = nodes->next;
    }
    
}

t_lemin     *ft_readnode(char *line, int node_name, t_lemin *lemin)
{
    char **tab;

    if(!line)
    {
        get_next_line(0, &line);
        lemin->lines = ft_addline(lemin->lines, line);
    }
    tab = ft_strsplit(line, ' ');
    ft_add_node(&lemin->nodes, ft_create_node(node_name, tab[0], ft_atoi(tab[1]), ft_atoi(tab[2])));
   // if (node_name != ROOM)
     //   ft_strdel(&line);
     return(lemin);
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
    //list = &lemin->nodes;
    while (get_next_line(0, line))
    {
        lemin->lines = ft_addline(lemin->lines, *line);
        if (!ft_strcmp("##start", *line))
            lemin = ft_readnode(NULL, START, lemin);
        else if (!ft_strcmp("##end", *line))
            lemin = ft_readnode(NULL, END, lemin);
        else if (!ft_strncmp("#", *line, 1))
        {
            lemin->lines = ft_addline(lemin->lines, *line);
            continue;
        }
        else if (ft_linetype(*line) == ROOM)
               lemin = ft_readnode(*line, ROOM, lemin);
        else
            break;
        lemin->size++;
        //ft_strdel(line);
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
    if (!line)
        ft_outerror();
    tab = ft_strsplit(line, '-');
    i = ft_getindex(tab[0], lemin->names, lemin->size);
    j = ft_getindex(tab[1], lemin->names, lemin->size);
    if (i == -1 || j == -1)
        ft_outerror();
    lemin->graph[i][j] = '1';
    lemin->graph[j][i] = '1';
    //ft_strdel(&line);
    while (get_next_line(0, &line))
    {
        //ft_putendl_fd(line, 1);
        lemin->lines = ft_addline(lemin->lines, line);
        if (!ft_strncmp("#", line, 1))
            //ft_strdel(&line);
            continue;
        else
        {
            tab = ft_strsplit(line, '-');
            i = ft_getindex(tab[0], lemin->names, lemin->size);
            j = ft_getindex(tab[1], lemin->names, lemin->size);
            if (i == -1 || j == -1)
                ft_outerror();
            lemin->graph[i][j] = '1';
            lemin->graph[j][i] = '1';
        }
        //ft_strdel(&line);
    }
    return (lemin);
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

      //printf("---%d %d %d---\n",nbNode , nb_ants,nbPath);

t_group* best_groups(t_group* grps, int nb_ants)
{
   t_group  *bestG;
   t_group *grp;
   int nbPath;
   int nbNode;
   int count = 0;
   int m = 21425384;

   bestG = NULL;
   grp = grps;
   while (grp)
   {
       //groups iterat
       nbNode = 0;
       nbPath = grp->paths->size;
       t_listpath *tmp = grp->paths;
       m = 21425384;
       count = 0;
       while (tmp)
       {
            //path iterat
            count++;
            if (tmp->path)
                nbNode += tmp->path->size;
            tmp->path->all_prev_inst =  ceil((double)(nb_ants + nbNode - count*2) / (double)count);
            if (m > tmp->path->all_prev_inst)
            { 
                grp->stop = count;
                m = tmp->path->all_prev_inst;
            }
            //printf(" %d paths has %d instructon\n", count, tmp->path->all_prev_inst);
            tmp = tmp->next;
       }
       grp->best = m;
       
      // printf("---%d %d %d---\n",nbNode , nb_ants,nbPath);
       //printf("%f\n", ceil(((nbNode + nb_ants) - (nbPath * 2)) / nbPath));
       grp->instr = ceil((double)((nbNode + nb_ants) - (nbPath * 2)) / (double)nbPath);
       //printf("|%d|\n",  grp->instr);
       if (bestG == NULL)
           bestG = grp;
       else if (bestG->best > grp->best)
           bestG = grp;
       grp = grp->next;
   }
   //printf("best result is : %d\n", m);
   return (bestG);
}

int main()
{

    t_lemin *lemin;
   // t_nodes *l;
    //int size;
    char *line;
    //t_names name;
    //int number_of_ants;
    //char **mat;
    //char *result;

    //l = NULL;
    

    lemin = (t_lemin *)malloc(sizeof(t_lemin));
    lemin->lines = NULL;
    lemin->nodes = NULL;
    lemin->groups = NULL;
    lemin->start = START;
    lemin->goal = END;
    
    
    //number of ants
    get_next_line(0,&line);
    lemin->n_ant = ft_atoi(line);

    lemin->lines = ft_addline(lemin->lines, line);
    //result = ft_strjoin_me(line, ENDLINE, TRUE);
    // ft_putnbr_fd(number_of_ants, 1);
    // ft_putendl_fd("", 1);
    // read node 
    lemin = ft_readallnode(&line, lemin);
    // list of name
    
    lemin->names = ft_buildnames(lemin->nodes, lemin->size);
    // Mat adj
    lemin->graph = ft_initmat(lemin->size);
    // read links
    lemin = ft_readlink(lemin, line);
    //Names = name.names;

    lemin->tmp = (char **)malloc(sizeof(char *) * lemin->size);
    for (int i = 0; i < lemin->size; i++)
        lemin->tmp[i] = (char *)malloc(sizeof(char) * lemin->size);

    t_adj **adj;
    adj = (t_adj **)malloc(sizeof(t_adj *) * lemin->size);
    lemin->visited = (int *)malloc(sizeof(int) * lemin->size);
    lemin->used = (int *)malloc(sizeof(int) * lemin->size);
    lemin->pred = (int *)malloc(sizeof(int) * lemin->size);
    lemin->checker = (int *)malloc(sizeof(int) * lemin->size);
    for (int u = 0; u < lemin->size; u++) 
    {
        //used[u] = 0;}
       //printf("%p\n", lemin->tmp);
        adj[u] = NULL;
        lemin->visited[u] = 0;
        lemin->used[u] = 0;
        lemin->checker[u] = 0;
        for (int v = 0; v < lemin->size; v++) 
        {
           // printf("%p - %p\n", &lemin->tmp[u][v], &graph[u][v] );
           
            lemin->tmp[u][v] = lemin->graph[u][v];
            if (lemin->graph[u][v] == '1')
            {
               // printf("%s ", lemin->names[j]);
                adj[u] = ft_addadj(adj[u], v);
            }
        }
    }
    lemin->adj = adj;

    // t_line *ln = lemin->lines;
    // while (ln)
    // {
    //     printf("%s\n", ln->line);
    //     ln = ln->next;
    // }
    

    
    int count = countnodefromstart(lemin->graph[0], lemin->size);
    //count = 5;
    while (count)
    {
       // printf("iteration %d \n", 5 - count--);
       count--;
       int chnage = 0;
        lemin->tmp =fordfulkerson(lemin);
        //return 0;
        //break;
        for (int u = 0; u < lemin->size; u++) 
        { 
            //if (t[u][1] == '0')
              //  mat[u][1] = '0';
            lemin->used[u] = 0;
            for (int v = 0; v < lemin->size; v++) 
            {
                if (lemin->graph[u][v] == '1' && lemin->tmp[u][v] == '0' && lemin->tmp[v][u]  == '0')
                {
                    lemin->graph[u][v] = '0';
                    chnage++;
                }
                lemin->tmp[u][v] = lemin->graph[u][v];
            }
        }
        if (!chnage)
            break;
        else chnage = 0;

        //printf("%s\n", mat[1]);
    }

/*
    t_group *temp = lemin->groups;
    while (temp)
    {
        printf("Group & size %d :\n", temp->paths->size);
        t_listpath *paths = temp->paths;
        while (paths)
        {
            t_path *newpath = paths->path; 
            int khalid = newpath->size;
            while (newpath) { printf("%s ", lemin->names[newpath->node]); newpath = newpath->next;}
            printf(" size : %d \n", khalid);
            paths = paths->next;
        }
        
        temp = temp->next;
    }
    printf("******\n");
*/

    t_group *teemp = best_groups(lemin->groups, lemin->n_ant);
    printf("nbr inst : %d nbr paths : %d \n", teemp->best, teemp->stop);

   // char **t = fordfulkerson(mat, 0, 1, size);
    //printf("%s", result);
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


    
    // for (int i = 0; i < lemin->size; i++)
    // {
    //     printf("%s -> ",lemin->names[i]);
    //     t_adj *tmp = lemin->adj[i];
    //     while (tmp )
    //     {
    //         printf("%s ", lemin->names[tmp->node]);
    //         tmp = tmp->next;
    //     }
           
    //     printf("\n");
    // }
    // ft_printmat(lemin->graph, lemin->size);
    
    




    
    return (0);
}