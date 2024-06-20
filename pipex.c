/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:44 by aarenas-          #+#    #+#             */
/*   Updated: 2024/06/20 16:34:40 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_definitive_path(t_arg_list *lst, int pos, char **d_paths)
{
	char	*endl;
	char	*path;
	int		i;

	i = 0;
	if (lst->flags)
		ft_free(lst->flags);
	lst->flags = ft_split(lst->argv[pos], ' ');
	i = 0;
	endl = ft_strjoin("/", lst->flags[0]);
	path = ft_strjoin(d_paths[0], endl);
	while (d_paths[i] && access(path, X_OK) < 0)
	{
		free(path);
		path = ft_strjoin(d_paths[i], endl);
		i++;
	}
	if (d_paths[i])
		return (free(endl), path);
	free(path);
	return (free(endl), NULL);
}

static char	*ft_pathfinder(t_arg_list *lst, int pos)
{
	char	**d_paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strncmp(lst->envp[i], "PATH=", 5) != 0)
		i++;
	if (lst->envp[i] == NULL)
		return (NULL);
	path = ft_substr(lst->envp[i], 5, ft_strlen(lst->envp[i]) - 5);
	if (path == NULL)
		return (NULL);
	d_paths = ft_split(path, ':');
	free(path);
	path = ft_definitive_path(lst, pos, d_paths);
	if (!path)
		ft_puterrorstr("Error: Command not found\n");
	return (path);
}

static void	ft_execute_cmd(t_arg_list *lst, int *pipefd, int i)
{
	char	*path;

	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	path = ft_pathfinder(lst, i);
	if (execve(path, lst->flags, lst->envp) < 0)
	{
		free(path);
		ft_free(lst->flags);
		perror("Error");
		exit(1);
	}
}

static void	ft_do_cmd(t_arg_list *lst, int fd)
{
	int		pipefd[2];
	int		child;
	int		i;

	i = 2;
	dup2(fd, STDIN_FILENO);
	while (i < lst->argc - 2)
	{
		if (pipe(pipefd) == -1)
			perror("Error");
		child = fork();
		if (child == 0)
			ft_execute_cmd(lst, pipefd, i);
		else if (child == -1)
			perror("Error");
		if (waitpid(-1, NULL, 0) == -1)
		{
			perror("Error");
			exit(1);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			fd;
	t_arg_list	*lst;

	if (access(argv[1], R_OK) == -1)
		return (perror("Error"), 0);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		return (1);
	lst = ft_define_lst(argc, argv, envp);
	ft_do_cmd(lst, fd);
	close(fd);
	fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (ft_freeanderror(lst), 1);
	dup2(fd, STDOUT_FILENO);
	if (execve(ft_pathfinder(lst, argc - 2), lst->flags, envp) < 0)
	{
		ft_free(lst->flags);
		free(lst);
		close(fd);
		perror("Error");
		return (1);
	}
	return (0);
}
