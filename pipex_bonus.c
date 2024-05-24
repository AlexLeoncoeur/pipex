/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:39:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/05/24 16:53:56 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
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

static char	*ft_pathfinder(char *argv, char **envp, char **flags)
{
	char	**d_paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	d_paths = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5), ':');
	flags = ft_split(argv, ' ');
	d_paths[0] = ft_strjoin(d_paths[0], "/");
	//el d_path correspondiente hay que guardarlo en un tmp para despues poder liberarlo y en el access de la linea 45 no hago join de d_path sino de tmp
	i = 0;
	printf("%s\n", d_paths[i]);
	printf("%s\n", flags[0]);
	while (access(ft_strjoin(d_paths[i], flags[0]), X_OK | F_OK) <= 0 && d_paths[i]) //hay que hacer un split modificado para que termine todos los d_paths con / y que eso se anada a flags[0]
		i++;
	path = ft_strjoin(d_paths[i], flags[0]);
	return (path);
}

void	do_cmd(int *pipefd, t_arg_list *lst)
{
	char	*path;
	int		i;

	i = 2;
	while (i < lst->argc - 2)
	{
		close(pipefd[1]);
		if (i > 2)
			dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		if (fork() == 0)
		{
			path = ft_pathfinder(lst->argv[i], lst->envp, lst->flags);
			if (execve(path, lst->flags, lst->envp) < 0)
				exit(1);
			exit(0);
		}
		wait(0);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		fd;
	char	**flags;

	flags = NULL;
	//if (access(argv[0], R_OK | F_OK) == -1)
		//return (perror(argv[0]), NULL);
	if (pipe(pipefd) == -1)
	{
	}
	fd = open(argv[1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	do_cmd(pipefd, ft_define_lst(argc, argv, flags, envp));
	fd = open(argv[argc - 1], O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	execve(ft_pathfinder(argv[argc - 2], envp, flags), flags, envp);
	return (0);
}
