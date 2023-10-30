/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:56:30 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/30 18:48:00 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_getpath(char **env)
{
	int		n;
	char	**ret;

	n = 0;
	ret = NULL;
	while (env && env[n])
	{
		if (ft_strncmp(env[n], "PATH=", 5) == 0)
		{
			ret = ft_split(ft_strchr(env[n], '/'), ':');
			return (ret);
		}
		n++;
	}
	return (ret);
}

char	*ft_retpath(char *command, char **env)
{
	char	**pathlist;
	char	*temppath;
	char	*testpath;

	pathlist = ft_getpath(env);
	while (pathlist && *pathlist)
	{
		temppath = ft_strjoin(*pathlist, "/");
		testpath = ft_strjoin(temppath, command);
		free(temppath);
		if (!(access(testpath, X_OK)))
			return (testpath);
		else
			free(testpath);
		pathlist++;
	}
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": There is no such command", 2);
	exit(EXIT_FAILURE);
}

void	ft_run(char *command, char **env)
{
	char	**cmdlist;
	char	*path;

	cmdlist = ft_split(command, ' ');
	if (ft_strchr(cmdlist[0], '/'))
	{
		path = cmdlist[0];
		if (access(path, X_OK) == -1)
		{
			ft_putstr_fd(cmdlist[0], 2);
			ft_putendl_fd(": There is no such command", 2);
			free(cmdlist);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
		path = ft_retpath(cmdlist[0], env);
	execve(path, cmdlist, env);
	free(cmdlist);
}
