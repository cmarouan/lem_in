

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lem_in.h"

#define ISEMPTY(q) (q == NULL)
 //char *names = "ABCDEFGHIJKLMN";
typedef struct s_queue
{
    int     node;
    struct s_queue *next;
}               t_queue;


t_queue *ft_createelm(int node)
{
    t_queue *elm;

    elm = (t_queue *)malloc(sizeof(t_queue));
    elm->next = NULL;
    elm->node = node;
    return elm;
}

t_queue *ft_enqueue(t_queue *queue, t_queue *new)
{
    t_queue *tmp;

    tmp = queue;
    if (!tmp)
        return new;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return queue;
}

int ft_dequeue(t_queue **queue)
{
    t_queue *tmp;
    int     ret;


    if (!*queue)
        return -1;
    tmp = *queue;
    *queue = (*queue)->next;
    ret = tmp->node;
    //ft_memdel(&tmp);
    return (ret);
}
//char **Names;
int checknode(t_lemin *l, int node)
{
    int     value;
    int     index;
    t_adj   *tmp;

    tmp = l->adj[node];
    value = 0;

    while (tmp)
    {
        index = tmp->node;
        // if (l->graph[node][index] == '1' && index != l->start)
        //     value++;
        if (l->used[index] && l->tmp[node][index] == '1')
            value++;
        tmp = tmp->next;
    }
    if (value > 0)
        return (1);
    return (0);
}


int bfs(t_lemin *l)
{
    int print = 0;
    t_queue *queue;
   // int visited[l->size];
    int v;
    int i;
    //int *pred = *p;
    i = 0;
    //printf("kagsidjkas fka");
    while (i < l->size)
    {
        l->pred[i] = -1;
        l->visited[i] = 0;
        l->checker[i] = 0;
        i++;
    }
    l->visited[l->start] = 1;
    queue = ft_enqueue(NULL, ft_createelm(l->start));
    l->pred[l->start] = -1;
    //printf("kagsidjkas fka");
    //int done = 0;
    char k = l->names[0][0];
    l->names[0][0] = k;
    while (queue)
    {
       
        v = ft_dequeue(&queue);
        i = 0;
        if (print)
            printf("%s |\n", l->names[v]);
        t_adj *tmp;
        tmp =  l->adj[v];
        while (tmp/*i < l->size*/)
        {
            i = tmp->node;
            int alr = 1;
            if (!l->visited[i] && l->tmp[v][i] == '1' && i != 0)
            {
                if(l->used[v] && !l->used[l->pred[v]] && !l->used[i])
                {
                    //printf("--inside %s\n", l->names[v]);
                    l->visited[v] = 0;
                    tmp = tmp->next;
                    continue;
                }
                if (print)
                {
                    printf("valide[ {%d, %s}] ",i, l->names[i]);
                    alr = 0;
                }
                // if (l->used[i])
                //     l->check = 0;

                /*if (l->used[i] && !checknode(l, i))
                {
                    
                    //l->used[i] = 0;
                    //i++;
                    //l->check = 0;
                    tmp = tmp->next;
                    continue;
                }*/
                //printf(" {%d, %s} ",i, names[i]);
                l->visited[i] = 1;
                l->pred[i] = v;
                //l->used[i] = 1;
                queue = ft_enqueue(queue, ft_createelm(i));  
            }
                
            if (print && alr)
                    printf(" {%d, %s} ",i, l->names[i]);
            //i++;
            tmp = tmp->next;
        }
        if (print)
            printf("\n");
       
    }
    //*p = pred;
    return (l->visited[l->goal] == 1);
}

void printmat(int **m, int size)
{
    int u = 0, v = 0;
    printf("*********************\n");
    for (u = 0; u < size; u++) 
    {
        for (v = 0; v < size; v++) 
        {
            printf(" %d ", m[u][v]);
        }
        printf("\n");
    }
    printf("*********************\n");
}

t_path *addnode(t_path *path, int node)
{
    t_path *newnode;

    newnode = (t_path *)malloc(sizeof(t_path));
    newnode->node = node;
    newnode->size = 1;
    newnode->next = NULL;
    if (!path)
        return newnode;
    newnode->next = path;
    newnode->size = ++path->size;
    return newnode;
}

t_listpath *addpath(t_listpath *paths, t_path *newpath, int nbrant)
{
    t_listpath *list;

    list = (t_listpath *)malloc(sizeof(t_listpath));
    newpath->nbr_inst = newpath->size - 2 + nbrant;
    newpath->all_prev_inst = 0;
    list->path = newpath;
    list->size = 1;
    list->v_node = newpath->size - 1;
    list->next = NULL;
    list->last = list;
    if (!paths)
    {
        return list;
    }
    paths->last->next = list;
    list->size = ++paths->size;
    paths->last = list;
    return paths;
}


t_group *addgroup(t_group *grps, t_listpath *paths)
{
    t_group *newgroup = NULL;

    newgroup = (t_group *)malloc(sizeof(t_group));
     
    newgroup->next = NULL;
    newgroup->paths = paths;
    newgroup->last = newgroup;
    if (!grps)
        return newgroup;
    grps->last->next = newgroup;
    grps->last = newgroup;
    return grps;
}

char **fordfulkerson(t_lemin *l)
{
    int u, v;
    t_listpath *paths = NULL;
    t_path *newpath = NULL;

    //int i = 0;
    l->check = 1;
    while (bfs(l))
    {
        
        u = l->goal;
        newpath = NULL;
        l->check = 0;
       // printf("****bfs****\n");
       // printf("#\n %s <- ", l->names[l->goal]);
        while (u != l->start)
        {
           // printf("****inside = %d -- %d****\n", i++, u);
            if (l->checker[u])
                break;
            l->checker[u] = 1;
            if (l->used[u]) l->check++;
            //    printf("%s <- ", l->names[l->pred[u]]);
           // else printf("[used %s] <- ", l->names[l->pred[u]]);
            newpath = addnode(newpath, u);
            if (u != l->goal && u != l->start)
                l->used[u] = 1;
            v = l->pred[u];
            l->tmp[v][u] = '0';
           // l->tmp[u][v] = '1';
            u = v;
        }
        if (u == l->start) newpath = addnode(newpath, u);
      //  u = 0;
        //while (u < l->size) l->checker[u++] = 0;
        //int khalid = 0;
        if (l->check == 0)
        {
            paths = addpath(paths, newpath, l->n_ant);
            //khalid = paths->size;
          //  while (newpath) { printf("%s ", l->names[newpath->node]); newpath = newpath->next;}
        }
       // printf("\n");
        
        //break;
        
        
        
    }

    l->groups = addgroup(l->groups, paths);
   // printf(" %p , %d \n", l->groups, paths->size);
    return l->tmp;


}



/*int main(void)
{

    

    int **g;
    int size;
    int start = 0;
    int goal = 7;
 //
 
    scanf("%d", &size);
    g = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
        g[i] = (int *)malloc(sizeof(int) * size);

    for (int u = 0; u < size; u++) 
        for (int v = 0; v < size; v++) 
            scanf("%d", &g[u][v]);
    
    //printmat(g, size);
    printf("iteration 1 \n");
    int **t =fordfulkerson(g, start, goal, size);

    for (int u = 0; u < size; u++) 
        for (int v = 0; v < size; v++) 
        {
            if (g[u][v] && !t[u][v] && !t[v][u])
                g[u][v] = 0;
        }
    printf("iteration 2 \n");
    t = fordfulkerson(g, start, goal, size);
    for (int u = 0; u < size; u++) 
        for (int v = 0; v < size; v++) 
        {
            if (g[u][v] && !t[u][v] && !t[v][u])
                g[u][v] = 0;
        }
    printf("iteration 3 \n");
    t = fordfulkerson(g, start, goal, size);
        
   

    





    // queue = NULL;
    // int i = -1;

    // while (++i < 10)
    // {
    //     printf("%p\n", queue);
    //     queue = ft_enqueue(queue, ft_createelm(i));
    // }

    // while (queue)
    // {
    //     printf("%d -> ", queue->node);
    //     queue = queue->next;
    // }
    // printf("\n");
    



    return 0;
}*/



