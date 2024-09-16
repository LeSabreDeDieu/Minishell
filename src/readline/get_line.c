/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/06 04:51:39 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assemble(const char **display)
{
	char	*display_final;
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (display[i] != NULL)
		len += ft_strlen(display[i++]);
	display_final = ft_calloc(sizeof(char), len + 1);
	if (display_final == NULL)
		return (NULL);
	i = 0;
	while (display[i] != NULL)
		ft_strlcat(display_final, display[i++], len + 1);
	return (display_final);
}

char *create_diplaye(void){
	char	*prompt[12];
	char	*cwd;
	t_env	*data;
	char	*final;

	data = get_env("USER");
	if (data && data->value)
		prompt[0] = data->value;
	else
		prompt[0] = "";
	prompt[1] = "@";
	cwd = getcwd(NULL, 0);
	if (cwd)
		prompt[2] = cwd;
	else
		prompt[2] = "";
	prompt[3] = ">";
	prompt[4] = NULL;
	final = assemble(prompt);
	free(cwd);
	return (final);
}


char	*rl_gets(void)
{
	char	*line;
	t_env	*pwd;
	t_env	*home;
	char	*test;

	test = create_diplaye();
	line = readline(test);
	free(test);
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);

	return (line);
}
