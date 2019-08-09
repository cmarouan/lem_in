

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lem_in.h"

#define ISEMPTY(q) (q == NULL)
char *names = "ABCDEFGHIJKLMN";



t_path *ft_createelmpath(int node)
{
    t_path *elm;

    elm = (t_path *)malloc(sizeof(t_path));
    elm->next = NULL;
    elm->lastnode = node;
    elm->size = 1;
    elm->node = node;
    return elm;
}

t_queue *ft_createelm(t_path *path)
{
    t_queue *elm;

    elm = (t_queue *)malloc(sizeof(t_queue));
    elm->next = NULL;
    elm->path = path;
    elm->size = 1;
    return elm;
}

t_queue *ft_enqueue(t_queue *queue, t_queue *new)
{
    t_queue *tmp;

    tmp = queue;
    if (!tmp)
        return new;
    tmp->size++;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return queue;
}
t_path *ft_enqueuepath(t_path *path, t_path *new)
{
    t_path *tmp;

    tmp = path;
    if (!tmp)
        return new;
    path->lastnode = new->node;
    path->size++;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return path;
}

t_path *ft_dequeue(t_queue **queue)
{
    t_queue *tmp;
    t_path  *ret;


    if (!*queue)
        return NULL;
    tmp = *queue;
    *queue = (*queue)->next;
    ret = tmp->path;
    //ft_memdel(&tmp);
    return (ret);
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

void printpath(t_path *path)
{
   // goal = goal + 1;
    //printf("|%s|\n*********************\n", str);
    while (path)
    {
        printf("[%d] ->", path->node);
        path = path->next;
    }
    //printf("\n*********************\n");
    printf("\n");
}

int checkback(int **g, int size, int i, int j, int start)
{
    
    size = size - 1;
    j = start;
    if(g[i][start] > 0)
        return 0;
    return (1);
}
int isnotvisited(int node, t_path *path)
{
    while (path)
    {
        if (path->node == node)
            return (0);
        path = path->next;
        
    }
    return (1);
    
}
t_path *ft_duppath(t_path *path)
{
    t_path *tmp;

    tmp = NULL;
    while (path)
    {
       
        tmp = ft_enqueuepath(tmp, ft_createelmpath(path->node));
        path = path->next;
    }
    return (tmp);
}

t_queue *bfs(char **graph, int start, int size, int goal)
{
    printf("start bfs\n");
    t_queue *q;
    t_queue *result;

    t_path *path, *newpath;

    result = NULL;
    path = ft_enqueuepath(NULL, ft_createelmpath(start));
    q = ft_enqueue(NULL, ft_createelm(path));
    
    //int count = 2;
     while (q)
     {
         //break;
         path = ft_dequeue(&q);
         
         int last = path->lastnode;
        //printpath("dfd ", path, goal);
       // printf(" %d \n", last);
         if (last == goal)
            {
                result = ft_enqueue(result, ft_createelm(path));
               // result->size++;
            }
             //printpath("complet path : ", path, goal);
         int i =0;

        while (i < size)
        {
            if (graph[last][i] == '1')
            {
                 
                 if (isnotvisited(i, path))
                {
                    //printf("%c ", names[i]);
                     
                    newpath = ft_duppath(path);
                    //printpath("old path",path, goal);
                    //printpath("new path",newpath, goal);
                    newpath = ft_enqueuepath(newpath, ft_createelmpath(i));
                   // printpath("new path",newpath, goal);
                    q = ft_enqueue(q, ft_createelm(newpath));
                }
            }
            i++;
        }
        
        
        // printf("------------------------\n");



        
        // q= NULL;
        // size = start;
        // goal +=size;
        // graph[0][0] = size;
        //if ()
    }
    return result;
    
}



int ft_min(int a, int b)
{
    return ((a < b) ? a : b);
}

/*int **fordfulkerson(int **graph, int start, int goal, int size)
{
    int u, v, **tmp;
   
   //char *names = "0123456789";
    tmp = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
        tmp[i] = (int *)malloc(sizeof(int) * size);
    int used[size];
    for (u = 0; u < size; u++) 
    {
        used[u] = 0;
        for (v = 0; v < size; v++) 
            tmp[u][v] = graph[u][v];
    }
             
    int *pred = (int *)malloc(sizeof(int) * size);
    int *oldpred = (int *)malloc(sizeof(int) * size);
    for(u = 0; u < size; u++)
            oldpred[u] = -1;
    //int count = 5;
    // printf("here\n");
    //int maxflow = 0;
    
    int pathcount = 1;
    //printf("bfs 1\n");
    while (bfs(tmp, start, size, goal, &pred, used))
    {
        
        u = goal;
        
        printf("#\n %c <- ", names[goal]);
        
        for (u = goal; u != start; u = pred[u])
        {
            if (u != goal && u != start)
                used[u] = 1;
            printf("%c <- ", names[pred[u]]);
        }
        printf("\n");
        for(u = 0; u < size; u++)
            oldpred[u] = pred[u];

        //if (pathcount > 0 && (alreadyuse[pathcount] & alreadyuse[pathcount - 1]) != 0)
          //      printf("\n path %d and %d has intersection \n", pathcount, pathcount - 1);
       
       // u = goal;
        // while (u != start)
        // {
        //     flowpath = ft_min(tmp[pred[u]][u], flowpath);
        //     u = pred[u];
        // }
        u = goal;
        while (u != start)
        {
            v = pred[u];
            tmp[v][u] = 0;
            u = v;
        }
        
        //maxflow += flowpath;
        //printmat(tmp, size);
        pathcount++;
        //printf("bfs %d\n", pathcount);
        

    }
   // printf("flow max : %d\n", maxflow);
    return tmp;


}*/



/*int main(void)
{

    

    int **g;
    int size;
    int start = 0;
    int goal = 1;
 
 
    scanf("%d", &size);
   
    g = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
        g[i] = (int *)malloc(sizeof(int) * size);
    for (int u = 0; u < size; u++) 
        for (int v = 0; v < size; v++) 
            {
                scanf("%d", &g[u][v]);
                
            }
            
    //printmat(g, size);
    t_queue *t = bfs(g, start, size, goal);
    printf("%d\n", t->size);
    while(t)
    {
       printpath(t->path);
       
        t = t->next;
    }

    return 0;
}*/



