/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:49:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/05 13:25:51 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_factory	*get_ast_factory(void)
{
	static t_ast_factory	factory;

	if (!factory.instanced)
	{
		factory.instanced = true;
		factory.ast = NULL;
	}
	return (&factory);
}
