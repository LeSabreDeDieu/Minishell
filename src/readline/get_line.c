/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 16:01:10 by sgabsi           ###   ########.fr       */
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

char	*get_cwd_prompt(t_minishell *shell_data)
{
	char	*cwd;
	char	*tmp;
	char	*result;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		tmp = ft_strjoin("/home/", shell_data->data.username);
		result = ft_str_replace(cwd, tmp, "~");
		if (result == NULL)
			result = cwd;
		free(tmp);
	}
	else
		result = "";
	return (result);
}

char	*create_display(t_minishell *shell_data)
{
	char	*prompt[12];
	char	*final;
	char 	*tmp;

	prompt[0] =	CYAN_RL;
	prompt[1] = shell_data->data.username;
	prompt[2] = RESET_RL;
	prompt[3] = "@";
	prompt[4] = GREEN_RL;
	prompt[5] = get_cwd_prompt(shell_data);
	prompt[6] = RESET_RL;
	prompt[7] = "> ";
	prompt[8] = NULL;
	final = assemble(prompt);
	free(prompt[5]);
	return (final);
}


char	*rl_gets(char *prompt)
{
	char	*line;

	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	if (*line)
		add_history_file(line);
	return (line);
}
