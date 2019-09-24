/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nonbuiltin_processing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:30:59 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/24 19:42:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_cmd_name(char **cmd_full)
{
	int				tmp;
	struct stat		info;

	if ((tmp = stat(cmd_full[0], &info)) == -1)
		return (command_error(cmd_full[0], 1));
	else
	{
		if (tmp == 0 && S_ISDIR(info.st_mode))
			return (command_error(cmd_full[0], 2));
		else if (tmp == 0 && !S_ISREG(info.st_mode))
			return (command_error(cmd_full[0], 3));
	}
	launch_program(cmd_full);
	return (0);
}

int					find_cmd_in_path(char *path, char **cmd_full)
{
	DIR				*path_dir;
	struct dirent	*entry;
	char			*ptr;

	if ((path_dir = opendir(path)) == NULL)
	{
		closedir(path_dir);
		return (-1);
	}
	while ((entry = readdir(path_dir)))
	{
		if (ft_strcmp(entry->d_name, cmd_full[0]) == 0)
		{
			ptr = ft_strjoin(path, "/");
			ptr = ft_strrejoin(ptr, cmd_full[0]);
			free(cmd_full[0]);
			cmd_full[0] = ptr;
			launch_program(cmd_full);
			closedir(path_dir);
			return (0);
		}
	}
	closedir(path_dir);
	return (1);
}

void				launch_program(char **cmd_full)
{
	pid_t			process;
	extern char		**environ;

	if ((access(cmd_full[0], X_OK)) == -1)
	{
		command_error(cmd_full[0], 4);
		return ;
	}
	signal(SIGINT, handle_signal);
	process = fork();
	if (process == 0)
	{
		if (execve(cmd_full[0], cmd_full, environ) < 0)
			alarm_exit(cmd_full, 1);
	}
	else if (process > 0)
		waitpid(process, NULL, 0);
	else
		alarm_exit(cmd_full, 0);
}

void				alarm_exit(char **cmd_full, int fl)
{
	extern char		**environ;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_full[0], 2);
	if (fl == 0)
		ft_putendl_fd(": Can't be forked", 2);
	else
		ft_putendl_fd(": Can't be executed", 2);
	ft_arrdel(environ);
	exit(1);
}

void				handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		return ;
	}
}
