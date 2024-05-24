/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:44 by aarenas-          #+#    #+#             */
/*   Updated: 2024/05/24 15:20:11 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

static char	*ft_pathfinder(char *argv, char **d_paths)
{
	char	**flags;
	char	*path;
	int		i;

	i = 0;
	flags = ft_split(argv, ' ');
	while (access(ft_strjoin(d_paths[i], flags[0]), X_OK | F_OK) <= 0)
		i++;
	path = ft_strjoin(d_paths[i], flags[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		n;
	int		pipefd[2];
	char	**d_paths;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	d_paths = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5), ':');
	if(pipe(pipefd) == -1);
	{}
	n = fork();
	if (n == 0)
	{
		access(argv[1], R_OK | F_OK);
		fd = open(argv[1], O_RDONLY);
		path = ft_pathfinder(argv[1], d_paths);
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(fd);
		close(pipefd[1]);
		execve(path, ft_split(argv[1], ' '), envp);
	}
	else
	{
	}
	return (0);
}
