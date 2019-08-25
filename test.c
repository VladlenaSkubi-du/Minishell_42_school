#include "libft/includes/libft.h"
#include <stdio.h>

static void     *ft_realloc(void *subj, int len_subj, int len_needed)
{
    void	*ptr;

    if (!(ptr = malloc(len_needed)))
	{
		write(2, "No space left\n", 15);
		exit(1);
	}
    ft_memcpy(ptr, subj, len_subj);
    ft_bzero(ptr + len_subj, len_needed - len_subj);
    free(subj);
    return (ptr);
}

int main(void)
{
    char    *s;
    int     i = 0;

    s = (char*)malloc(6);
    while (i < 5)
        s[i++] = 's';
    s[5] = '\0';
    ft_putendl(s);
    s = ft_realloc(s, 6, 12);
    s[5] = ' ';
    s[6] = 'a';
    ft_nputstr(s, 12);
    return (0);
}