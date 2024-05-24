/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:17:00 by aarenas-          #+#    #+#             */
/*   Updated: 2024/05/24 16:13:26 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>

typedef struct s_arg_list
{
	int					argc;
	char				**argv;
	char				**flags;
	char				**envp;
	struct s_arg_list	*next;

}	t_arg_list;

#endif