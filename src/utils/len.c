/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:21:55 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/01 18:21:55 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

size_t len_env(void)
{
	t_env  *current;
    size_t len;

    current = get_env_factory()->env;
    len = 0;
    while (current)
    {
        ++len;
        current = current->next;
    }
    return (len);
}