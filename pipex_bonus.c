/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:39:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/06/13 16:50:29 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_arg_list	*ft_define_lst(int argc, char **argv, char **flags, char **envp)
{
	t_arg_list	*aux;

	aux = malloc(sizeof(t_arg_list));
	aux->argc = argc;
	aux->argv = argv;
	aux->flags = flags;
	aux->envp = envp;
	aux->next = NULL;
	return (aux);
}

static char	*ft_pathfinder(char *argv, char **envp, char ***flags)
{
	char	**d_paths;
	char	*path;
	char	*endl;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	d_paths = ft_split(path, ':');
	free(path);
	if (!d_paths)
		ft_puterrorstr("Error: Command not found");
	*flags = ft_split(argv, ' ');
	i = 0;
	endl = ft_strjoin("/", *flags[0]);
	path = ft_strjoin(d_paths[0], endl);
	while (d_paths[i++] && access(path, X_OK) < 0)
	{
		free(path);
		path = ft_strjoin(d_paths[i], endl);
	}
	free(endl);
	//ft_free(*flags);
	return (path);
}

static void	ft_execute_cmd(t_arg_list *lst, int *pipefd, int i)
{
	char	*path;

	close(pipefd[0]);
	//dup2(pipefd[1], STDOUT_FILENO);
	path = ft_pathfinder(lst->argv[i], lst->envp, &lst->flags);
	printf("%s %s %s\n", path, lst->flags[0], lst->flags[1]);
	if (execve(path, lst->flags, lst->envp) < 0)
	{
		free(path);
		perror("Error: ");
		exit(1);
	}
}

static void	do_cmd(t_arg_list *lst, int fd)
{
	int		pipefd[2];
	int		child;
	int		i;

	i = 2;
	dup2(fd, STDIN_FILENO);
	while (i < lst->argc - 2)
	{
		if (pipe(pipefd) == -1)
			perror("Error: ");
		child = fork();
		if (child == 0)
			ft_execute_cmd(lst, pipefd, i);
		else if (child == -1)
			perror("Error: ");
		wait(0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		i++;
	}
	free(lst);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	char	**flags;

	flags = NULL;
	if (access(argv[1], R_OK | F_OK) == -1)
		return (perror("Error: "), 0);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		return (1);
	do_cmd(ft_define_lst(argc, argv, flags, envp), fd);
	close(fd);
	fd = open(argv[argc - 1], O_WRONLY, 0777);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	if (execve(ft_pathfinder(argv[argc - 2], envp, &flags), flags, envp) < 0)
	{
		ft_free(flags);
		close(fd);
		perror("Error: ");
		return (1);
	}
	return (0);
}
