# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 23:23:20 by sgabsi            #+#    #+#              #
#    Updated: 2024/06/13 10:58:16 by gcaptari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

# Directories
SRC_SUBDIR	=	env utils
SRCDIR		=	./src
INCDIR		=	./include
LIBDIR		=	./lib
OBJDIR		=	obj

# Sources
#ENV
SRC_ENV_DIR 	=	$(SRCDIR)/env
SRC_ENV_FILES	=	env_factory.c \
					env.c		\
					parser.c	\
					test.c
SRC_ENV			=	$(addprefix $(SRC_ENV_DIR)/, $(SRC_ENV_FILES))

#UTILS
SRC_UTILS_DIR 	=	$(SRCDIR)/utils
SRC_UTILS_FILES	=	free.c \
					len.c
SRC_UTILS		=	$(addprefix $(SRC_UTILS_DIR)/, $(SRC_UTILS_FILES))
#READ_LINE
SRC_READ_LINE_DIR 	=	$(SRCDIR)/readline
SRC_READ_LINE_FILES	=	get_line.c
SRC_READ_LINE		=	$(addprefix $(SRC_READ_LINE_DIR)/, $(SRC_READ_LINE_FILES))

SRC				=	$(SRC_ENV) \
					$(SRC_UTILS) \
					$(SRC_READ_LINE) \
					$(SRCDIR)/minishell.c

# Objects
OBJ_SUBDIRS	=	$(SRC_SUBDIR:%=$(OBJDIR)/%)
OBJ			=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEP			=	$(OBJ:.o=.d)

# Libraries
LIBFT_DIR 	=	$(LIBDIR)/libft
LIBFT 		=	$(LIBFT_DIR)/libft.a

# Output
NAME		=	minishell

# Compiler
CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra -MMD

OPTIONS		=	-I $(INCDIR) -I $(LIBFT_DIR)/includes
LFLAGS		=	-L $(LIBFT_DIR) -lft -lreadline -lcurses

# Progress bar
COUNT		=	1
TOTAL_FILES	=	$(shell find $(SRCDIR) -type f -name "*.c" | wc -l)

# Colors
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
NC			=	\033[0m
KL			=	\033[K

#################
##  TARGETS    ##
#################

all: check

compile: pre_comp $(LIBFT) $(NAME)

check:
	@if [ -f "$(NAME)" ] && [ -z "$(shell find $(SRCDIR) -type f -name "*.c" -newer $(NAME) 2>/dev/null)" ] && [ -z "$(shell find $(SRCDIR) -type f -name "*.h" -newer $(NAME) 2>/dev/null)" ]; then \
		echo "$(YELLOW)********* Rien à faire - Tout est à jour *********$(NC)"; \
	else \
		make -s compile; \
	fi

pre_comp:
	@echo "$(YELLOW)********* Début de la compilation du programme $(NAME) *********$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(OPTIONS) $(LFLAGS) -o $@
	@echo -e "\r$(GREEN)********* Compilation terminée avec succès! *********$(NC)$(KL)"
	@echo "$(GREEN)********* L'executable $(NAME) a été créée. *********$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIONS) -c $< -o $@
	@printf "$(NC)\rCompiling files: [%-50s] %3d%% (%d/%d) %s$(KL)" \
		"$(shell printf '=%.0s' $$(seq 1 $$(($(COUNT) * 50 / $(TOTAL_FILES)))))" \
		$$(($(COUNT) * 100 / $(TOTAL_FILES))) \
		$(COUNT) \
		$(TOTAL_FILES) \
		$<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

$(LIBFT):
	@make -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJDIR)
	@rm -f norm.log
	@make -sC $(LIBFT_DIR) clean
	@echo "$(YELLOW)********* Suppression des fichiers objets *********$(NC)"

fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(RED)********* Suppression de l'executable $(NAME) *********$(NC)"

re: fclean compile

norminette:
	@echo "$(YELLOW)********* Exécution de norminette *********$(NC)"
	@norminette src/ include/ > norm.log | grep -B 1 -e "Error" || echo "Tous les fichiers ont passé le check norminette !"

.PHONY: check compile all clean fclean re norminette
-include $(DEP)
