# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 18:33:52 by raamayri          #+#    #+#              #
#    Updated: 2025/09/07 19:42:04 by raamayri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Wextra -Werror -g3 -MMD -MP
MK_FLAGS = --silent
MAKEFLAGS += $(MK_FLAGS)

NAME = minibox.a
LBFT = Libft/libft.a

SRCS = srcs/build.c \
	   srcs/build_input.c \
	   srcs/build_lexing.c \
	   srcs/build_parsing.c \
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

.PHONY: all debug clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LBFT)
	ar -rcs $@ $^
	$(info [MAKE] $@ built successfully.)

objs/%.o: srcs/%.c
	mkdir -p $(sort $(dir $@) $(dir $(patsubst objs/%.o, deps/%.d, $@)))
	cc $(CC_FLAGS) -MF $(patsubst objs/%.o, deps/%.d, $@) $(addprefix -I, $(INCS)) -o $@ -c $<
	$(info [MAKE] $(addprefix $*, .c) compiled successfully.)

$(LBFT):
	$(MAKE) $(MK_FLAGS) -C $(dir $@) 1> /dev/null
	$(info [MAKE] $(dir $@) compiled successfully.)

debug: srcs/debug.c $(NAME) $(LBFT)
	cc -Wall -Wextra -Werror -g3 $(addprefix -I, $(INCS)) $< $(NAME) $(LBFT) -o debug
	$(info [MAKE] debug built successfully.)

clean:
	rm -rf $(sort $(dir $(OBJS)) $(dir $(DEPS)))
	$(MAKE) $(MK_FLAGS) -C $(dir $(LBFT)) $@ 1> /dev/null
	$(info [MAKE] $(NAME) cleaned successfully.)

fclean: clean
	rm -rf $(NAME) $(LBFT) debug

re: fclean all

-include $(DEPS)
