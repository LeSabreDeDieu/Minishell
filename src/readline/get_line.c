#include "minishell.h"

static char **get_line(void)
{
	static char *line_read = (char *)NULL;

	return (&line_read);
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *rl_gets(void)
{
	char **line_read = get_line();
  /* If the buffer has already been allocated, return the memory
     to the free pool. */
  if (*line_read)
    {
      free (*line_read);
      *line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  *line_read = readline ("$");

  /* If the line has any text in it, save it on the history. */
  if (*line_read && **line_read)
    add_history (*line_read);

  return (*line_read);
}