/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:27:14 by aarenas-          #+#    #+#             */
/*   Updated: 2024/06/20 14:55:32 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_here_doc(int *pipefd, char **argv)
{
	char	*str;
	int		child;

	child = fork();
	if (child == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			str = get_next_line(0);
			if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0)
				exit(0);
			ft_putstr_fd(str, pipefd[1]);
			free(str);
			str = NULL;
		}
	}
	if (waitpid(-1, NULL, 0) == -1)
	{
		perror("Error");
		exit(1);
	}
}

int	ft_check_heredoc(char **argv)
{
	int		fd;
	int		pipefd[2];

	if (ft_strncmp("here_doc\0", argv[1], 9) == 0)
	{
		fd = pipe(pipefd);
		if (fd == -1)
			perror("Error");
		ft_here_doc(pipefd, argv);
		close(pipefd[1]);
		return (pipefd[0]);
	}
	else
	{
		if (access(argv[1], R_OK) == -1)
			return (perror("Error"), -1);
		fd = open(argv[1], O_RDONLY, 0777);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}

int	ft_openfile(char **argv, int argc)
{
	int	fd;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	return (fd);
}
