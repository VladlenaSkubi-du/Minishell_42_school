/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/24 14:03:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "ft_printf.h"

/*
**@t_signs is used in the file special-signs.c because of the norm
*/

typedef struct			s_signs
{
	size_t				i;
	size_t				j;
	int					w;
	int					old;
	int					pwd;
	size_t				len;
	size_t				len1;
	int					fl;
	char				*tmp;
	char				*main;
}						t_signs;

/*
**Where: MAX - length of the command line while readline processing: how many
**bytes I expect to get from user not ot make a lot of reallocs and not to
**lose memory unused;
**PROMPT: the length of prompt-string for readline processing;
**Beginning "FLAG" - used in readline:
**Beginning "ECHO" - used in echo-cmd-processing
*/

# define MAX			100
# define PROMPT			11
# define FL_NL			0x1
# define FL_SCMD		0x2
# define FL_ESC			0x4
# define FL_OSQBRK		0x8
# define ECHO_N			0x10
# define ECHO_E			0x20
# define ECHO_EE		0x40
# define E_OQUT			0x80
# define E_OTYS			0x100
# define E_OTYD			0x200

struct termios			g_backup_tty;

/*
**File main.c
*/

void					set_noncanonical_input(void);
void					reset_canonical_input(void);
void					display_prompt(void);
void					save_environment(void);

/*
**File readline.c
*/

int						readline();
char					*del_symbol(char *cmd, size_t *all);
void					esc_leftright(char c, size_t *all);
char					*printable_parce(char c, char *cmd, size_t *all);
int						nl_signals(char c, char *cmd, size_t *all);

/*
**File cmd_readline_changes.c
*/

char					*str_add_symbol(char *arr, char add, size_t *all);
char					*str_del_symbol(char *arr, size_t *all);
char					*help_str_change(char *cmd, char *swap,
							int point, char add);
void					help_nl_signal(size_t *all);

/*
**The list of helpers for the commands that are to be implemented.
**File special_signs.c
*/

int						special_signs_check(char *cmd);
char					*special_tilda_processing(char *cmd, int *len);
char					*special_dollar_processing_1(char *cmd,
							int *len, int i);
char					*special_dollar_processing_2(char *cmd, int *len,
							t_signs s, int len_f);
char					*cmd_line_modification(char *cmd, int *len,
							t_signs s, int len_full);

/*
**File commands_check.c
*/

char					*check_command(char *cmd, int len);
void					builtin_minishell(char *cmd, int i, int len);
void					search_command(char *cmd);
void					prepare_for_check(char *cmd, t_signs s);
int						command_error(char *cmd, int fl);

/*
**The list of builtins we have to implement: echo, cd, setenv, unsetenv, env,
**exit.
*/

/*
**File cmd_echo.c
*/

void					cmd_echo(char *cmd, int len, int flag);
int						cmd_echo_flags(char *cmd, int len, int *flag, int i);
void					cmd_echo_output(char *cmd, int len, int *flag, int i);
int						cmd_echo_escape(char *cmd, int i);
int						cmd_echo_quatations(char c, int *flag);

/*
**File cmd_exit_cd_env.c
*/

void					cmd_env(int flag);
void					cmd_exit(char *cmd);
void					cmd_cd(char *cmd, int flag);
void					change_dir(char *cmd, t_signs s);
void					change_environ(char *cmd, t_signs s);

/*
**File cmd_setenv_unset.c
*/

void					cmd_setenv(char *cmd, int j);
void					cmd_setenv_environ_1(char *name, t_signs s, char **ptr);
char					*cmd_setenv_environ_2(char *name, int i, char *env);
void					cmd_unsetenv(char *cmd, int flag);
void					cmd_unsetenv_environ(char *name, t_signs s);

/*
**Dealing with the commands which are not builtin we had to implement.
**File cmd_nonbuiltin processing.c
*/

int						check_cmd_name(char **cmd_full);
int						find_cmd_in_path(char *path,
							char **cmd_full);
void					launch_program(char **cmd_full);
void					alarm_exit(char **cmd_full, int fl);

/*
**Other functions used - the file other_functions_1.c
*/

void					*ft_xmalloc(size_t size);
void					*ft_realloc(void *subj, size_t len_subj,
							size_t len, size_t len_needed);
void					get_terminal_width(size_t *term);
void					init_all(size_t *all);
int						count_env(void);

/*
**Other functions used - the file other_functions_2.c
*/

void					ft_bzero_int(int *arr, int len);
int						signs_indication(char c);
void					ft_arrdel(char **arr);
short					quatations_indication(char c, short flag);
void					many_commands(char *cmd);

#endif
