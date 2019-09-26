/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 13:46:59 by kmoussai          #+#    #+#             */
/*   Updated: 2019/09/26 21:26:34 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# define CEILL(a) ((double)((int)a) == a ? (int)a : (int)a + 1)




// create own ceil function;
typedef struct s_line
{
    char    *line;
    struct s_line *last; 
    struct s_line *next; 
}               t_line;

typedef struct  s_nodes
{
    char    *name;
    int     type;
    int     x;
    int     y;
    struct s_nodes *next;

}               t_nodes;

typedef struct s_adj
{
    int             node;
    struct s_adj    *next;
}   t_adj;

typedef struct s_path
{
    int node;
    int size;
    int nbr_inst;
    int all_prev_inst;
    struct s_path *next;
}               t_path;

typedef struct s_listpath
{
    t_path *path;
    int size;
    int nbr_ant;
    int v_node;
    struct s_listpath *last;
    struct s_listpath *next;
}               t_listpath;

typedef struct s_group
{
    t_listpath *paths;
    int instr;
    int stop;
    int best;
    struct s_group *last;
    struct s_group *next;
}               t_group;


typedef struct s_arrays
{
    int *patharray;
    int size;
    struct s_arrays *next;
    struct s_arrays *last;
}               t_arrays;

typedef struct s_queue
{
    int     node;
    struct s_queue *next;
}               t_queue;

typedef struct s_lemin
{
    int     size;
    int     start;
    int     goal;
    int     n_ant;
    int     check;
    int     nopath;
    t_nodes *nodes;
    t_queue *queue;
    char    **graph;
    char    **tmp;
    char    **names;
    int     *visited;
    int     *used;
    int     *pred;
    t_adj   **adj;
    t_line  *lines;
    int     *checker;
    t_group *groups;
}           t_lemin;



typedef struct s_passant
{
    int         size;
    int         nb;
    int         done;
    int         nameant;
}               t_passant;

typedef struct s_vargrp
{
    int nbpath;
	int nbnode;
	int count;
	int m;
}               t_vargrp;



char **fordfulkerson(t_lemin *lemin);
void ft_outerror();
char  *getname(t_lemin* lemin, t_path* path, int index);
void passallants(int ants, t_lemin* lemin, t_path *path);
void pass_ants(t_arrays* s, int n_ant, t_lemin *lemin, t_listpath *paths);
int*    ft_bzero_me(int *s, int size);
t_arrays *addtoarray(t_arrays *arr, int size, int nbrant);
t_arrays* createarrays(t_group* grps);
t_group* best_groups(t_group* grps, int nb_ants);

t_queue		*ft_createelm(int node);
t_queue		*ft_enqueue(t_queue *queue, t_queue *new);
t_queue		*ft_dequeue(t_queue *queue, int *v);

void		ft_inittab(t_lemin *l);
int			bfs(t_lemin *l, int i, int v, t_adj *tmp);
char		**fordfulkerson(t_lemin *l);

t_path		*addnode(t_path *path, int node);
t_listpath	*addpath(t_listpath *paths, t_path *newpath, int nbrant);
t_group		*addgroup(t_group *grps, t_listpath *paths);
void		freepath(t_path *newpath);
t_path		*ft_pathbuilder(t_lemin *l, t_path *newpath, int u);








// typedef struct  s_names
// {
//     char    **names;
//     int     size;
// }               t_names;

// typedef struct s_path
// {
//     int             node;
//     int             grpid;
//     int             lastnode;
//     int             size;
//     struct s_path   *next;
// }               t_path;

// typedef struct s_queue
// {
//     t_path          *path;
//     int             size;
//     struct s_queue  *next;
// }               t_queue;

#endif
