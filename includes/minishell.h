/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/04 18:00:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>     //DELETE
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"

# define BUF_SIZE   1024

/*
**The list of builtins we have to implement: echo, cd, setenv, unsetenv, env, exit
*/

void        cmd_exit(void);

#endif
