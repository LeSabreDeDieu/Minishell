/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:26:53 by gcaptari          #+#    #+#             */
/*   Updated: 2024/08/21 13:05:26 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "tokens.h"

void	free_on_children(t_minishell *minishell)
{
	free_env();
	free_token(minishell->tokens);
	free_ast(&minishell->ast);
}
