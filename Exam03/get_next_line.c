
#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 48

# endif

int	tt_memchr(char *str, int c)
{
	int idx = -1;
	if (!str)
		return (1);
	while (*(str + ++idx))
		if (*(str + idx) == c)
			return (0);
	return (1);
}

size_t	tt_strlen(const char *str)
{
	const char	*ptr;
	ptr = str;
	while (str && *str)
		str++;
	return (str - ptr);
}

char	*tt_strjoin(char *str1, char *str2)
{
	size_t	str1_ln, str2_ln;
	char	*str_t;
	if (!str1)
	{
		str1 = malloc(sizeof(char));
		if (!str1)
			return NULL;
		*str1 = 0;
	}
	str1_ln = tt_strlen(str1);
	str2_ln = tt_strlen(str2);
	str_t = malloc(str1_ln + str2_ln + 1);
	if (!str_t)
		return NULL;
	int idex = -1;
	while (++idex < (int)(str1_ln))
		str_t[idex] = str1[idex];
	idex = -1;
	while (++idex < (int)str2_ln)
		str_t[str1_ln + idex] = str2[idex];
	str_t[str1_ln + idex] = 0;
	return (free(str1), str_t);
}

void	read_line(int fd, char **r_line)
{
	char	*buffer;
	char	*tmp;
	int		b_read;
	b_read = 1;
	buffer = NULL;
	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return ;
	while (tt_memchr(buffer, '\n') && b_read)
	{
		b_read = read(fd, tmp, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(tmp);
			return ;
		}
		tmp[b_read] = 0;
		if (b_read)
		{
			buffer = tt_strjoin(buffer, tmp);
			if (!buffer)
			{
				free(tmp);
				return ;
			}	
		}
	}
	free(tmp);
	*r_line = buffer;
}

char	*out_line(char *r_line, char **buf, int *count)
{
	char	*line;
	int		idx;
	char	*tmp;
	if (!r_line)
		return (NULL);
	while (*(r_line + ++(*count)))
		if (*(r_line + *count) == '\n')
			break ;
	if (*(r_line + *count) == '\n' && *(r_line + *count + 1))
	{
		idx = -1;
		line = malloc(*count + 2);
		while (++idx <= *count)
			line[idx] = r_line[idx];
		line[idx] = 0;
		int to_alloc = tt_strlen(r_line) - idx;
		tmp = malloc(to_alloc + 1);
		int indx = -1;
		while (*(r_line + (idx) + ++indx))
			tmp[indx] = r_line[idx + indx];
		tmp[indx] = 0;
		*buf = tmp;
		// printf("%s\n", tmp);
		free((void*)r_line);
		return line;
	}
	*buf = NULL;
	return r_line;
}

char *get_next_line(int fd)
{
	static char *buffer;
	char		*r_line;
	char		*out_ln;
	char		*tmp;
	int			opr;

	r_line = NULL;
	tmp = NULL;
	opr = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(fd, &r_line);
	if (buffer)
	{
		if (!r_line)
		{
			r_line = malloc(sizeof(char));
			*r_line = 0;
		}
		tmp = tt_strjoin(buffer, r_line);
		free(r_line);
		r_line = tmp;
		buffer = NULL;
	}
	out_ln = out_line(r_line, &tmp, &opr);
	buffer = tmp;
	return (out_ln);
}
