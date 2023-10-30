/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:56:38 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/30 19:15:05 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_firstp(char **av, char **env, int *fdm)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	close(fdm[0]);
	dup2(fd, 0);
	close(fd);
	dup2(fdm[1], 1);
	close(fdm[1]);
	ft_run(av[2], env);
}

void	ft_sprocess(char **av, char **env, int *fdm)
{
	int	fd;

	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(av[4], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	dup2(fdm[0], 0);
	close(fdm[0]);
	dup2(fd, 1);
	close(fd);
	ft_run(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int	a;
	int	fd[2];

	if (ac == 5)
	{
		pipe(fd);
		a = fork();
		if (a == 0)
			ft_firstp(av, env, fd);
		else
		{
			close(fd[1]);
			a = fork();
			if (a == 0)
				ft_sprocess(av, env, fd);
			else
				close(fd[0]);
			exit(0);
		}
	}
	else
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(100);
	}
}
