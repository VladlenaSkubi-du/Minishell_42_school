/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:40:20 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/16 17:11:57 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**After the program is finished terminal should be set to canonical input,
**otherwise terminal won't work properly.
*/

void				reset_canonical_input(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_backup_tty);
}

void				display_prompt(void)
{
	ft_putstr("$\033[1;31mminishell\033[0m> ");
}

/*
**Here we change the canonical input to non-canonical, not to react on
**combinations: ^C, ^Z, ^Q, ^S as default. After the program finished terminal
**should be set to canonical input.
*/

void				set_noncanonical_input(void)
{
	struct termios	tty;

	if (!isatty(0))
	{
		ft_putendl("Stdin is not terminal. The program is finished");
		exit(1);
	}
	tcgetattr(STDIN_FILENO, &tty);
	g_backup_tty = tty;
	tty.c_lflag &= ~(ICANON | ECHO | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}

void				save_environment(void)
{
	int				i;
	extern char		**environ;
	char			**tmp;
	unsigned int	num;

	i = 0;
	num = count_env();
	tmp = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	while (environ[i])
	{
		tmp[i] = ft_strdup(environ[i]);
		i++;
	}
	tmp[i] = NULL;
	environ = tmp;
}

/*
**If we get 1 return from the fuction readline, that means
**user put '\n' and wants to input another command.
*/

int					main(void)
{
	extern char		**environ;

	save_environment();
	set_noncanonical_input();
	while (1)
	{
		display_prompt();
		if (readline() == 1)
			continue;
	}
	reset_canonical_input();
	ft_arrdel(environ);
	return (0);
}
