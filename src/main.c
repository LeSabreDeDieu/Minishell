/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:16:04 by sgabsi            #+#    #+#             */
/*   Updated: 2024/04/15 18:31:02 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utmp.h>

static bool	keepRunning = true;

void	intHandler(int signal)
{
	keepRunning = false;
}

int	main(int argc, char const *argv[], char *envp[])
{
	struct utmp			tmp;
	struct sigaction	act;
	char				inputString[1000];
	char				*buf;
	int					fd_user;
	int					username_size;

	username_size = 0;
	buf = NULL;
	act.sa_handler = intHandler;
	sigaction(SIGINT, &act, NULL);
	fd_user = open("/run/utmp", O_RDONLY);
	while (tmp.ut_type != 7)
		read(fd_user, &tmp, sizeof(tmp));
	while (tmp.ut_user[username_size])
		username_size++;
	write(1, tmp.ut_user, username_size);
	write(1, "$ ", 3);
	while (keepRunning)
	{
		if (buf != NULL)
		{
			buf = readline("> ");
			if (strlen(buf) != 0)
			{
				add_history(buf);
				strcpy(inputString, buf);
			}
			printf("%s", inputString);
		}
	}
	return (0);
}
