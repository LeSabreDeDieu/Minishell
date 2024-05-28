# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:44:09 by sgabsi            #+#    #+#              #
#    Updated: 2024/05/17 11:08:26 by sgabsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

# Directories
SRC_SUBDIRS			=	ft_is ft_lst ft_mem ft_put ft_str ft_to gnl printf
SRCDIR				=	./srcs
INCDIR				=	./includes
OBJDIR				=	objs

# Sources
# ft_is
SRCS_IS_DIR			=	ft_is
SRCS_IS_LIST		=	ft_isalnum.c		\
						ft_isalpha.c		\
						ft_isascii.c		\
						ft_isdigit.c		\
						ft_isprint.c
SRCS_IS				=	$(addprefix $(SRCS_IS_DIR)/, $(SRCS_IS_LIST))

#ft_lst
SRCS_LST_DIR		=	ft_lst
SRCS_LST_LIST		=	ft_lstadd_back.c	\
						ft_lstadd_front.c	\
						ft_lstclear.c		\
						ft_lstdelone.c		\
						ft_lstiter.c		\
						ft_lstlast.c		\
						ft_lstmap.c			\
						ft_lstnew.c			\
						ft_lstsize.c
SRCS_LST			=	$(addprefix $(SRCS_LST_DIR)/, $(SRCS_LST_LIST))

#ft_mem
SRCS_MEM_DIR		=	ft_mem
SRCS_MEM_LIST		=	ft_bzero.c			\
						ft_calloc.c			\
						ft_memchr.c			\
						ft_memcmp.c			\
						ft_memcpy.c			\
						ft_memmove.c		\
						ft_memset.c
SRCS_MEM			=	$(addprefix $(SRCS_MEM_DIR)/, $(SRCS_MEM_LIST))

#ft_put
SRCS_PUT_DIR		=	ft_put
SRCS_PUT_LIST		=	ft_putchar_fd.c 	\
						ft_putendl_fd.c 	\
						ft_putnbr_fd.c 		\
						ft_putstr_fd.c
SRCS_PUT			=	$(addprefix $(SRCS_PUT_DIR)/, $(SRCS_PUT_LIST))

#ft_str
SRCS_STR_DIR		=	ft_str
SRCS_STR_LIST		=	ft_split.c			\
						ft_strchr.c			\
						ft_strdup.c			\
						ft_striteri.c		\
						ft_strjoin.c		\
						ft_strlcat.c		\
						ft_strlcpy.c		\
						ft_strlen.c			\
						ft_strmapi.c		\
						ft_strncmp.c		\
						ft_strnstr.c		\
						ft_strrchr.c		\
						ft_strtrim.c		\
						ft_substr.c
SRCS_STR			=	$(addprefix $(SRCS_STR_DIR)/, $(SRCS_STR_LIST))

#ft_to
SRCS_TO_DIR			=	ft_to
SRCS_TO_LIST		=	ft_atoi.c				\
						ft_itoa.c				\
						ft_tolower.c			\
						ft_toupper.c
SRCS_TO				=	$(addprefix $(SRCS_TO_DIR)/, $(SRCS_TO_LIST))

#ft_gnl
SRCS_GNL_DIR		=	gnl
SRCS_GNL_LIST		=	get_next_line.c			\
						get_next_line_utils.c
SRCS_GNL			=	$(addprefix $(SRCS_GNL_DIR)/, $(SRCS_GNL_LIST))

#ft_printf
SRCS_PRINTF_DIR		=	printf
SRCS_PRINTF_LIST	=	ft_print_hex.c 			\
						ft_print_ptr.c			\
						ft_print_unsigned.c		\
						ft_printf_utils.c		\
						ft_printf.c
SRCS_PRINTF			=	$(addprefix $(SRCS_PRINTF_DIR)/, $(SRCS_PRINTF_LIST))

SRC_LIST			= 	$(SRCS_IS)				\
						$(SRCS_LST)				\
						$(SRCS_MEM)				\
						$(SRCS_PUT)				\
						$(SRCS_STR)				\
						$(SRCS_TO)				\
						$(SRCS_GNL)				\
						$(SRCS_PRINTF)
SRCS				=	$(addprefix $(SRCDIR)/, $(SRC_LIST))

# Objects
OBJ_SUBDIRS	=	$(SRC_SUBDIRS:%=$(OBJDIR)/%)
OBJ			=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Output
NAME		=	libft.a
NAMESO		=	libft.so

# Compiler
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra #en-O3 -ffreestanding -nostdlib
OPTIONS		=	-I $(INCDIR)

#Progress bar
COUNT		=	1
TOTAL_FILES	=	$(shell find . -type f -name "*.c" | wc -l)

# Colors
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
NC			=	\033[0m
KL			=	\033[K

#################
##  TARGETS    ##
#################

all: pre_comp $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ) $(BOBJ)

pre_comp :
	@echo "$(YELLOW)********* Début de la compilation de la librairie Libft *********$(NC)"

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo -e "\r$(GREEN)********* Compilation terminée avec succès! *********$(NC)$(KL)"
	@echo "$(GREEN)********* La librairie $(NAME) a été créée. *********$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIONS) -o $@ -c $<
	@printf "\rCompiling files: [%-50s] %3d%% (%d/%d) %s$(KL)" \
		"$(shell printf '=%.0s' $$(seq 1 $$(($(COUNT) * 50 / $(TOTAL_FILES)))))" \
		$$(($(COUNT) * 100 / $(TOTAL_FILES))) \
		$(COUNT) \
		$(TOTAL_FILES) \
		$<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

clean:
	@/bin/rm -rf $(OBJDIR)
	@echo "$(YELLOW)********* Suppression des fichiers objets *********$(NC)"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(NAMESO) a.out
	@echo "$(RED)********* Suppression de la librairie $(NAME) *********$(NC)"
	
re: fclean all

.PHONY: all clean fclean re
