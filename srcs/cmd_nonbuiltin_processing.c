/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nonbuiltin_processing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:30:59 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/22 20:51:28 by sschmele         ###   ########.fr       */
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
	if ((tmp = access(cmd_full[0], X_OK)) == -1)
		return (command_error(cmd_full[0], 4));
	launch_program(cmd_full);
	return (0);
}

int					find_cmd_in_path(char *path, char **cmd_full, t_signs s)
{
	DIR				*path_dir;
	struct dirent	*entry;
	char			*ptr;

	if ((path_dir = opendir(path)) == NULL)
		return (-1);
	while ((entry = readdir(path_dir)))
	{
		if (ft_strcmp(entry->d_name, cmd_full[0]) == 0)
		{
			ptr = ft_strdup(entry->d_name);
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
	ft_putendl("LAUNCH");
}
