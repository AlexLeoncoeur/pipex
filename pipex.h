/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:17:00 by aarenas-          #+#    #+#             */
/*   Updated: 2024/06/20 14:41:32 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <sys/types.h>
# include "./libft/libft.h"

typedef struct s_arg_list
{
	int					argc;
	char				**argv;
	char				**flags;
	char				**envp;
	struct s_arg_list	*next;

}	t_arg_list;

void		ft_freeanderror(t_arg_list *lst);
void		ft_puterrorstr(char *str);
void		ft_free(char **str);
t_arg_list	*ft_define_lst(int argc, char **argv, char **envp);

#endif