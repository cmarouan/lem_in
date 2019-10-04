#include "lem_in.h"
#include "get_next_line.h"

void ft_err(char *msg)
{
	ft_putendl(msg);
	exit(-1);
}

char *ft_concat(char *src, char *c)
{
	char	*new;
	int	size;

	size = ft_strlen(src);
	new = ft_strnew(size + 1);
	new = ft_strcpy(new, src);
	free(src);
	new[size] = *c;
	return (new);
}

int read_line(const int fd, char **line)
{
	char *r;
	char *src;
	int  ret = 0;

	src = ft_strnew(1);
	r = ft_strnew(1);
	while ((ret = read(fd, r, 1)))
	{
		if (r[0] == '\n')
			break;
		src = ft_concat(src, r);
	}
	free(r);
	*line = src;
	if (ft_strlen(src) > 0)
		return (1);
	free(src);
	return (0);
}


typedef struct	s_pars 
{
	int	next_is_start;
	int	next_is_end;
}		t_pars;

int ft_is_node(char *line)
{
	int c;
	int i;

	i = 0;
	c = 0;
	while (line[i])
		if (line[i++] == ' ')
			c++;
	if (c == 2)
		return (1);
	else if (c != 0)
		ft_err("Wrong data for Node");

	return (0);
}

int ft_is_link(char *line)
{
	int c;
	int i;

	i = 0;
	c = 0;
	while (line[i])
		if (line[i++] == '-')
			c++;
	if (c == 1)
		return (1);
	else if (c != 0)
		ft_err("Wrong Data for link");
	return (0);
}

int ft_is_number(char *line)
{
	int i;

	i = 0;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;

	//ft_putnbr('\n');
	if ((!line[i] || line[i] == '\r') && i > 0)
		return (1);
	return (0);

}


# define IS_START 100
# define IS_END 101
# define IS_COMMENT 102
# define IS_NODE 103
# define IS_LINK 104
# define IS_ANT_NUMBER 105
# define UNKNOWN_TYPE 106


int ft_linetype(char *line)
{
	if (!ft_strncmp("##start", line, 7))
		return (IS_START);
	else if (!ft_strncmp("##end", line, 5))
		return (IS_END);
	else if (line[0] == '#')
		return (IS_COMMENT);
	else if (ft_is_node(line))
		return (IS_NODE);
	else if (ft_is_link(line))
		return (IS_LINK);
	else if (ft_is_number(line))
		return (IS_ANT_NUMBER);
	else 
		return (UNKNOWN_TYPE);

}

char *ft_info(int n)
{
	if (n == IS_START)
		return ("Is_start");
	else if (n == IS_END)
		return ("Is_end");
	else if (n == IS_COMMENT)
		return ("Is_comment");
	else if (n == IS_NODE)
		return ("Is_node");
	else if (n == IS_LINK)
		return ("Is_link");
	else if (n == IS_ANT_NUMBER)
		return ("Is_ant_number");
	else
		return ("Uknown line type");		
}



int ft_read_node(t_lemin *l, char *line, int nodetype)
{
	char		**tab;
	int		i;

	tab = ft_strsplit(line, ' ');
	if (tab[0] == NULL || tab[1] == NULL || tab[2] == NULL
				|| tab[3] != NULL)
		ft_err("Wrong node Data");
	ft_add_node(&l->nodes, ft_create_node(nodetype, ft_strdup(tab[0]),
				ft_atoli(tab[1]), ft_atoli(tab[2])));
	l->size++;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (-1);
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
	if (!ft_isdigit(str[i]) && str[i] != '\0' && str[i] != 13)
		ft_err("Not number");
	if (str[0] == '-')
		nbr = nbr * -1;
	if (nbr > INT_MAX || nbr <= 0)
		ft_err("To many Ant/ 0 Ant");
	return ((int)nbr);
}

char		**ft_build_names(t_nodes *tmp, int size)
{
	int		index;
	char	**names;

	index = 2;
	names = (char **)malloc(size * sizeof(char *));
	while (tmp)
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
		ft_err("Start/End not found");
	return (names);
}

int	ft_get_index(char *name, char **names, int size)
{	
	int	i;

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
char **ft_init_mat(int size)
{
	char	**mat;
	int		index;

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

void ft_read_link(t_lemin *lemin, char *line, int flink)
{
	char	**tab;
	int	i;
	int	j;
	
	if (flink == 0)
	{
		lemin->names = ft_build_names(lemin->nodes, lemin->size);
		lemin->graph = ft_init_mat(lemin->size);
	}
	tab = ft_strsplit(line, '-');
	if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
		ft_err("Wrong link data");
	i = ft_get_index(tab[0], lemin->names, lemin->size);
	///printf("|%p, %p, %p|\n", tab[0], tab[1], tab[2]);
	j = ft_get_index(tab[1], lemin->names, lemin->size);
	if (i == -1 || j == -1)
		ft_err("Node not found");
	lemin->graph[i][j] = '1';
	lemin->graph[j][i] = '1';
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}


void ft_parse(t_lemin *lemin)
{	
	char *line;
	int linetype;
	int nodetype = -1;
	int flink = 0;

	line = NULL;
	while (read_line(0, &line))
	{	
		lemin->lines = ft_addline(lemin->lines, line);
		linetype = ft_linetype(line);
		if (linetype == UNKNOWN_TYPE)
			ft_err("Unkown line type");
		else if (linetype == IS_START)
			nodetype = 0;
		else if (linetype == IS_END)
			nodetype = 1;
		else if (linetype == IS_NODE)
			nodetype = ft_read_node(lemin, line, nodetype);
		else if (linetype == IS_LINK)
			ft_read_link(lemin, line, flink++);
		else if (linetype == IS_ANT_NUMBER)
			lemin->n_ant = ft_atoli(line);
			//ft_read_link(lemin, line);
		//ft_putendl(ft_info(linetype));
		//free(line);
	}
}

t_lemin	*ft_initlemin()
{
	t_lemin	*lemin;

	lemin = (t_lemin *)malloc(sizeof(t_lemin));
	lemin->lines = NULL;
	lemin->nodes = NULL;
	lemin->groups = NULL;
	lemin->fend = 0;
	lemin->fstart = 0;
	lemin->start = START;
	lemin->goal = END;
	lemin->nopath = 0;
	lemin->size = 0;

	//lemin->n_ant = ft_atoli(line);
	//if (lemin->n_ant == 0)
	//	ft_outerror();
	//lemin->lines = ft_addline(lemin->lines, line);
	//lemin = ft_readallnode(&line, lemin);
	//lemin->names = ft_buildnames(lemin->nodes, lemin->size);
	//lemin = ft_readlink(lemin, line);
	return (lemin);
}



void	ft_init_bfs(t_lemin *lemin, int i, int u, int v)
{
	t_adj	**adj;

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


int main(void)
{

	t_lemin *lemin;

	lemin = ft_initlemin();
	ft_parse(lemin);
	//printf("nbr node %d\n",lemin->size);
	ft_printlines(lemin->lines);
	//t_nodes *tmp = lemin->nodes;
	//while(tmp)
	//{
	//	printf("%s , %d\n", tmp->name, tmp->type);
	//	tmp = tmp->next;
	//}
	ft_init_bfs(lemin, 0, -1, -1);
	solve(lemin);	


	return (0);
}
