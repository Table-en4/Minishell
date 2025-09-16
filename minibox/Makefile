# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 18:33:52 by raamayri          #+#    #+#              #
#    Updated: 2025/09/16 16:44:28 by raamayri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Wextra -Werror -g
MK_FLAGS = --silent
MAKEFLAGS += $(MK_FLAGS)

NAME = minibox.a
LBFT = Libft/libft.a

SRCS = srcs/build.c \
	   srcs/build_input.c \
	   srcs/build_lexing.c \
	   srcs/build_parsing.c \
	   srcs/build_parsing_syntax.c \
	   srcs/build_parsing_redirection.c \
	   srcs/build_parsing_redirection_heredoc.c \
	   srcs/build_parsing_arguments.c \
	   srcs/build_parsing_arguments_expand.c \
	   srcs/build_parsing_arguments_wildcard.c \
	   srcs/build_parsing_arguments_utils.c \
	   srcs/build_parsing_utils.c \
	   srcs/set_error.c \
	   srcs/display.c \
	   srcs/display_input.c \
	   srcs/display_lexing.c \
	   srcs/display_parsing.c \
	   srcs/display_error.c \
	   srcs/destroy.c \
	   srcs/destroy_input.c \
	   srcs/destroy_lexing.c \
	   srcs/destroy_parsing.c \
	   srcs/register.c
INCS = incs/ \
	   Libft/incs/
OBJS = $(patsubst srcs/%.c, objs/%.o, $(SRCS))
DEPS = $(patsubst objs/%.o, deps/%.d, $(OBJS))

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) $(LBFT)
	ar -rcs $@ $^
	$(info [MAKE] $@ built successfully.)

objs/%.o: srcs/%.c
	mkdir -p $(sort $(dir $@) $(dir $(patsubst objs/%.o, deps/%.d, $@)))
	cc $(CC_FLAGS) -MMD -MP -MF $(patsubst objs/%.o, deps/%.d, $@) $(addprefix -I, $(INCS)) -o $@ -c $<
	$(info [MAKE] $(addprefix $*, .c) compiled successfully.)

$(LBFT):
	$(MAKE) $(MK_FLAGS) -C $(dir $@) 1> /dev/null
	$(info [MAKE] $(dir $@) compiled successfully.)

clean:
	rm -rf $(sort $(dir $(OBJS)) $(dir $(DEPS)))
	$(MAKE) $(MK_FLAGS) -C $(dir $(LBFT)) $@ 1> /dev/null
	$(info [MAKE] $(NAME) cleaned successfully.)

fclean: clean
	rm -rf $(NAME) $(LBFT)

re: fclean all

.PHONY: all clean fclean re
