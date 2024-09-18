#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_data
{
	char	**s_arg;
	char	**e_arg;
	int		mv_idx;
	int		stat;
}	t_data;

int	err_handl(char *err_msg)
{
	while (*err_msg)
		write(2, err_msg++, 1);
	return 1;
}

void	init(t_data *data, char **av, char **env)
{
	data->s_arg = av;
	data->e_arg = env;
	data->mv_idx = 0;
	data->stat = 0;
}

int	cd(t_data *data)
{
	if (data->mv_idx != 2)
		return err_handl("error: cd: bad arguments"), err_handl("\n"); 
	if (chdir(data->s_arg[1]) == -1)
		return err_handl("error: cd: cannot change directory to "), err_handl((data->s_arg[1])), err_handl("\n"); 
	return 0;
}

int	execute(t_data data)
{
	int fd[2];
	int is_pipe;
	int status;
	int pid;
	is_pipe = data.s_arg[data.mv_idx] && !strcmp(data.s_arg[data.mv_idx], "|");
	if (is_pipe && pipe(fd) == -1)
		return (err_handl("error: fatal\n"));
	pid = fork();
	if (!pid)
	{
		data.s_arg[data.mv_idx] = 0;
		if (is_pipe && (dup2(fd[1], 1) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1))
			return err_handl("error: fatal\n");
		execve(*(data.s_arg), data.s_arg, data.e_arg);
		return (err_handl("error: cannot execute "), err_handl(*(data.s_arg)), err_handl("\n"));
	}
	waitpid(pid, &status, 0);
	if (is_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return err_handl("error: fatal\n");
	return WIFEXITED(status) && WEXITSTATUS(status);
}

void	micro_shell(t_data *data)
{
	if (!(data->s_arg[data->mv_idx] && data->s_arg[++(data->mv_idx)]))
		return ;
	data->s_arg += data->mv_idx;
	data->mv_idx = 0;
	while (data->s_arg[data->mv_idx] && strcmp(data->s_arg[data->mv_idx], "|") && strcmp(data->s_arg[data->mv_idx], ";"))
		data->mv_idx++;
	if (!strcmp(*(data->s_arg), "cd"))
		data->stat = cd(data);
	else if (data->mv_idx)
		execute(*data);
	micro_shell(data);
}

int main(int ac, char **av, char **env)
{
	t_data data;
	init(&data, av, env);
	if (ac > 1)
		micro_shell(&data);
	return data.stat;
}

