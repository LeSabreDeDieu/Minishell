/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:43:37 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/20 13:43:47 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "env.h"

int env_command(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	print_env();
	return (0);
}