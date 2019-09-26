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

void ft_printerr(char *s, int c)
{
    printf("here %s\n", s);
    if (c)
        exit(0);
}

t_lemin     *ft_readallnode(char **line, t_lemin *lemin)
{
    //list = &lemin->nodes;
    while (get_next_line(0, line))
    {
        //ft_printerr(*line, 0);
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
    //exit(0);
    j = ft_getindex(tab[1], lemin->names, lemin->size);
    
    if (i == -1 || j == -1)
        ft_outerror();
    lemin->graph[i][j] = '1';
    lemin->graph[j][i] = '1';
    while (tab[x])
        free(tab[x++]);
    free(tab);
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
        //ft_strdel(&line);
    }
    //last line has been freed
    free(line);
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
/*
void print_ant(char* arrays, int ants, int all_ants, int count)
{
    int i;
    int an;
    int before;
    int after;

    before = 0;
    after = 0;
    an = ants;
    i = 0;
    while (arrays[i])
    {
        if (arrays[i] == '1')
        {
            //printf("%d %d %d %d\n", all_ants,before,after, count);
            printf("L%d-X ", );
        }
        i++;
    }
}*/

int*    ft_bzero_me(int *s, int size)
{
        int  i;

        i = 0;
        //printf("|%d|\n", size);
        while (i < size)
        {
                s[i] = 0;
                i++;
        }
        //s[--i] = -1;
        return (s);
}

t_arrays *addtoarray(t_arrays *arr, int size, int nbrant)
{
    t_arrays *new;

    new = (t_arrays *)malloc(sizeof(t_arrays));
    new->size = size;
    new->patharray = (int *)malloc(sizeof(int) * size);
    new->patharray = ft_bzero_me(new->patharray, size);
    new->patharray[0] = nbrant;
    new->last = new;
    new->next = NULL;
    if (!arr)
        return (new);
    arr->last->next = new;
    arr->last = new;
    return (arr);
}


t_arrays* createArrays(t_group* grps)
{
    t_arrays* arrays = NULL;
    t_arrays* first;
    int nbr_nodes;

    nbr_nodes = 0;
    int stop = grps->stop;
    first = NULL;
    t_group* grp = grps;
    //arrays = (t_arrays *)malloc(sizeof(t_arrays));
    t_listpath* temp = grp->paths;
    while (temp && stop > 0)
    {
        //printf("stop %d | nbr ant %d\n",stop,temp->nbr_ant);
        stop--;
        nbr_nodes = temp->path->size + 1;

        arrays = addtoarray(arrays, nbr_nodes, temp->nbr_ant);

       // arrays->patharray = (int *)malloc(sizeof(int) * nbr_nodes);
        //arrays->patharray = ft_bzero_me(arrays->patharray, nbr_nodes);
        //arrays->patharray[0] = temp->nbr_ant;
        //arrays->size = nbr_nodes;
        temp = temp->next;
        //if (temp && stop > 0)
          //  arrays->next = (t_arrays *)malloc(sizeof(t_arrays));
       // if (first == NULL)
         //   first = arrays;
        //arrays = arrays->next;
    }
    return (arrays);
}


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


char  *getname(t_lemin* lemin, t_path* path, int index)
{
    int i;
    char *name;
    t_path *temp;

    temp = path;
    i = 0;
    while (temp)
    {
        if (i == index)
        {
            name = lemin->names[temp->node];
            return (name);
        }
        i++;
        temp = temp->next;
    }
    return (NULL);
}

void passAllAnts(int ants, t_lemin* lemin, t_path *path)
{
    int i;

    i = 0;
    while (i < ants)
    {
        i++;
        ft_putstr("L");
        ft_putnbr(i);
        ft_putstr("-");
        ft_putstr(getname(lemin, path, 1));
        if (i != ants)
            ft_putstr(" ");
    }
    ft_putstr("\n");
}

void pass_ants(t_arrays* s, int n_ant, t_lemin *lemin, t_listpath *paths)
{
    int size;
    int nb;
    int done;
    int nameAnt;
    nb = n_ant;


    nameAnt = 1;
    t_arrays* temp = s;
    t_listpath* tempPath = paths;
    done = 0;

    while (done < n_ant)
    {
            while (s)
            {
                size = s->size - 2;
                //printf("size = %d\n", size);
                s->patharray[size + 1] = done;
                while (size > 0)
                {
                    if (s->patharray[size] != 0)
                    {
                        if (size == s->size - 2)
                        {
                            s->patharray[size + 1] += 1;
                        }
                        else
                        {
                            s->patharray[size + 1] = s->patharray[size];
                            ft_putstr("L");
                            ft_putnbr(s->patharray[size + 1]);
                            ft_putstr("-");
                            ft_putstr(getname(lemin, paths->path, size + 1));
                            ft_putstr(" ");
                        }
                        s->patharray[size] = 0;
                    }
                    size--;
                    if (size == 0 && s->patharray[size] > 0)
                    {
                        s->patharray[size + 1] = nameAnt;
                        nameAnt++;
                        ft_putstr("L");
                        ft_putnbr(s->patharray[size + 1]);
                        ft_putstr("-");
                        ft_putstr(getname(lemin, paths->path, size + 1));
                        ft_putstr(" ");
                        //printf("L%d-%s ", s->patharray[size + 1], getname(lemin, paths->path, size + 1));
                        s->patharray[size] -= 1;
                    }
                }
                done = s->patharray[s->size - 1];
                paths = paths->next;
                s = s->next;
            }
            s = temp;
            paths = tempPath;
            //printf("kakk");
            if (done != n_ant)
                ft_putstr("\n");
    }
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
    
        //if (!lines->next)
        free(lines->line);
        //printf("%p\n",lines->line);
        tmp = lines;
        free(tmp);
        lines = lines->next;
       // break;
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
    lemin->nopath = 0;
    
    
    //number of ants
    get_next_line(0,&line);
    lemin->n_ant = ft_atoli(line);
    //printf("%d\n", lemin->n_ant);
    //exit(0);
    
    
    lemin->lines = ft_addline(lemin->lines, line);
    
    
    //result = ft_strjoin_me(line, ENDLINE, TRUE);
    // ft_putnbr_fd(number_of_ants, 1);
    // ft_putendl_fd("", 1);
    // read node 
    
    lemin = ft_readallnode(&line, lemin);
    
    
    //freenodes(lemin->nodes);
    //freelines(lemin->lines);
    //free(lemin);
    // list of name
    //t_line *ln = lemin->lines;
    
    //freelines(lemin->lines);
   // freenodes(lemin->nodes);
    //free(lemin);
    /*while (ln)
    {
        
        printf("%s\n", ln->line);
        //printf("e\n");
        ln = ln->next;
    }*/
   // exit(0);
    lemin->names = ft_buildnames(lemin->nodes, lemin->size);
   
    // Mat adj
    lemin->graph = ft_initmat(lemin->size);
    
    // read links
    lemin = ft_readlink(lemin, line);
    
    //Names = name.names;

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

    //t_line *ln = lemin->names;
    // int i = 0;
    // while (i < lemin->size)
    // {
    //     printf("%s\n", lemin->names[i]);
    //     i++;
    // }



    //ft_printmat(lemin->graph, lemin->size);
    




    

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
       int change = 0;
        lemin->tmp = fordfulkerson(lemin);
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
                    change++;
                }
                lemin->tmp[u][v] = lemin->graph[u][v];
            }
        }
        if (!change)
            break;
        else change = 0;
        //printf("%s\n", mat[1]);
    }
    // t_group *temp = lemin->groups;
    // while (temp)
    // {
    //     printf("Group & size %d \n", temp->paths->size);
    //     t_listpath *paths = temp->paths;
    //     while (paths)
    //     {
    //         t_path *newpath = paths->path; 
    //         int khalid = paths->nbr_ant;
    //         while (newpath) { printf("%s ", lemin->names[newpath->node]); newpath = newpath->next;}
    //         printf(" antnbr : %d \n", khalid);
    //         paths = paths->next;
    //     }
        
    //     temp = temp->next;
    // }
    // printf("******\n");

    // exit(0);

    t_group *teemp = best_groups(lemin->groups, lemin->n_ant);

    
    teemp = dispatchant(teemp, lemin);
   
    if (teemp->paths->path->size == 2)
    {
        passAllAnts(lemin->n_ant, lemin, teemp->paths->path);
        return 0;
    }
    
    /*
    t_group *temp = teemp;
    while (temp)
    {
        printf("Group & size %d \n", temp->paths->size);
        t_listpath *paths = temp->paths;
        while (paths)
        {
            t_path *newpath = paths->path; 
            int khalid = paths->nbr_ant;
            while (newpath) { printf("%s ", lemin->names[newpath->node]); newpath = newpath->next;}
            printf(" antnbr : %d \n", khalid);
            paths = paths->next;
        }
        
        temp = temp->next;
    }
    printf("******\n");
*/
    // freelines(lemin->lines);
    // freenodes(lemin->nodes);
    // freetab(lemin->names, lemin->size);
    // freetab(lemin->graph, lemin->size);
    // freetab(lemin->tmp, lemin->size);
    // freeadj(lemin->adj, lemin->size);
    // free(lemin->used);
    // free(lemin->visited);
    // free(lemin->pred);
    // free(lemin->checker);
    // freegroups(lemin->groups);
    // free(lemin);
    // return 0;
    
    t_group *tmp = teemp;
    
    t_arrays* s = createArrays(tmp);
    
    //printf("%p\n", s);
    /*t_arrays* s2 = s;
    while (s){
        int i = 0;
        printf("hey*\n");
        while (i < s->size)
        {
            printf("%d ", s->patharray[i]);
            i++;
        }
        printf("\n");
        s = s->next;
        printf("%p\n", s);
    }*/
    pass_ants(s, lemin->n_ant, lemin, teemp->paths);

    
//exit(0);
    

    //printf("nbr inst : %d nbr paths : %d", tmp->best, tmp->stop);
    //getname(lemin, teemp->paths->path, 2);
    /*while (s->next)
    {
        int size = 0;
        int i = 0;
        //printf("|%d|\n",s->patharray[0]);
        size = s->size;
        while (i < size){
            printf("%d ", s->patharray[i]);
            i++;
        }
        printf("\n");
        s = s->next;
    }*/
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

    
    return (0);
}