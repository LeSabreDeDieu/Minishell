/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:25:09 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 16:00:53 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RESET			"\033[0m"

# define BLACK			"\033[0;30m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"

# define BOLD_BLACK		"\033[1;30m"
# define BOLD_RED		"\033[1;31m"
# define BOLD_GREEN		"\033[1;32m"
# define BOLD_YELLOW	"\033[1;33m"
# define BOLD_BLUE 		"\033[1;34m"
# define BOLD_MAGENTA	"\033[1;35m"
# define BOLD_CYAN		"\033[1;36m"
# define BOLD_WHITE		"\033[1;37m"

# define BG_BLACK		"\033[40m"
# define BG_RED			"\033[41m"
# define BG_GREEN		"\033[42m"
# define BG_YELLOW		"\033[43m"
# define BG_BLUE		"\033[44m"
# define BG_MAGENTA		"\033[45m"
# define BG_CYAN		"\033[46m"
# define BG_WHITE		"\033[47m"
# define BG_RESET		"\033[49m"

# define BG_BLACK_INV	"\033[40;7m"
# define BOLD			"\033[1m"
# define UNDERLINE		"\033[4m"

// Color speciale pour readline

# define RESET_RL			"\001\033[0m\002"

# define BLACK_RL			"\001\033[0;30m\002"
# define RED_RL				"\001\033[0;31m\002"
# define GREEN_RL			"\001\033[0;32m\002"
# define YELLOW_RL			"\001\033[0;33m\002"
# define BLUE_RL			"\001\033[0;34m\002"
# define MAGENTA_RL			"\001\033[0;35m\002"
# define CYAN_RL			"\001\033[0;36m\002"
# define WHITE_RL			"\001\033[0;37m\002"

# define BOLD_BLACK_RL		"\001\033[1;30m\002"
# define BOLD_RED_RL		"\001\033[1;31m\002"
# define BOLD_GREEN_RL		"\001\033[1;32m\002"
# define BOLD_YELLOW_RL		"\001\033[1;33m\002"
# define BOLD_BLUE_RL		"\001\033[1;34m\002"
# define BOLD_MAGENTA_RL	"\001\033[1;35m\002"
# define BOLD_CYAN_RL		"\001\033[1;36m\002"
# define BOLD_WHITE_RL		"\001\033[1;37m\002"

# define BG_BLACK_RL		"\001\033[40m\002"
# define BG_RED_RL			"\001\033[41m\002"
# define BG_GREEN_RL		"\001\033[42m\002"
# define BG_YELLOW_RL		"\001\033[43m\002"
# define BG_BLUE_RL			"\001\033[44m\002"
# define BG_MAGENTA_RL		"\001\033[45m\002"
# define BG_CYAN_RL			"\001\033[46m\002"
# define BG_WHITE_RL		"\001\033[47m\002"
# define BG_RESET_RL		"\001\033[49m\002"

# define BG_BLACK_INV_RL	"\001\033[40;7m\002"
# define BOLD_RL			"\001\033[1m\002"
# define UNDERLINE_RL		"\001\033[4m\002"

#endif
