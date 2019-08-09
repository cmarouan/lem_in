

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
        if (l->graph[index][node] == '0' && index != l->start)
            value++;
        tmp = tmp->next;
    }
    if (value >= 0)
        return (0);
    return (1);
}


int bfs(t_lemin *l)
{
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
        printf("%s |\n", l->names[v]);
        t_adj *tmp;
        tmp =  l->adj[v];
        while (tmp/*i < l->size*/)
        {
            i = tmp->node;
            if (!l->visited[i] && l->tmp[v][i] == '1' && i != 0)
            {
                printf(" {%d, %s} ",i, l->names[i]);
                // if (l->used[i])
                //     l->check = 0;

                if (l->used[i] && !checknode(l, i))
                {
                    
                    //l->used[i] = 0;
                    //i++;
                    //l->check = 0;
                    tmp = tmp->next;
                    continue;
                }
                //printf(" {%d, %s} ",i, names[i]);
                l->visited[i] = 1;
                l->pred[i] = v;
                //l->used[i] = 1;
                queue = ft_enqueue(queue, ft_createelm(i));
                
            }
            //i++;
            tmp = tmp->next;
        }
        printf("\n");
       
    }
   // *p = pred;
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

char **fordfulkerson(t_lemin *l)
{
    int u, v;

    l->check = 1;
    while (bfs(l))
    {
        
        u = l->goal;
        
        printf("#\n %s <- ", l->names[l->goal]);
        u = l->goal;
        while (u != l->start)
        {
            printf("%s <- ", l->names[l->pred[u]]);
            if (u != l->goal && u != l->start)
                l->used[u] = 1;
            v = l->pred[u];
            l->tmp[v][u] = '0';
           // l->tmp[u][v] = '1';
            u = v;
        }
        printf("\n");
        
    }
    
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



