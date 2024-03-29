# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 16:28:15 by nieyraud          #+#    #+#              #
#    Updated: 2021/03/06 09:47:00 by nieyraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################
#		COLOR		#
#####################

rose=\033[1;31m
violetfonce=\033[0;35m
violetclair=\033[1;35m
neutre=\033[0m
cyanfonce=\033[0;36m
cyanclair=\033[1;36m
vertfonce=\033[0;32m
vertclair=\033[1;32m
rouge=\033[31m
orange=\033[33m

#####################
#		SOURCES		#
#####################

NAME = a.out

include files.mk

CONTAINERS = vector.hpp map.hpp stack.hpp
CONTAINER_DIRECTORY = srcs/containers
CONTAINERS_INCLUDE = $(addprefix $(CONTAINER_DIRECTORY)/, $(CONTAINERS))
ITERATORS = list_iterator.hpp reverse_iterator.hpp Vector_iterator.hpp map_iterator.hpp
ITERATORS_DIRECTORY = srcs/iterators
ITERATORS_INCLUDE = $(addprefix $(ITERATORS_DIRECTORY)/, $(ITERATORS))
INCLUDE	= $(ITERATORS_INCLUDE) $(CONTAINERS_INCLUDE)

#############################
#		DIRCTORIES PATH		#
#############################

FPATH = ${shell find srcs -type d}
OBJ_PATH = objs
vpath %.cpp $(foreach dir, $(FPATH), $(dir))

#################################
#		FILES	VARIABLE		#
#################################

SRC		= ${SRC_FILE}
SRCS	= $(addprefix ${FPATH}, ${SRC_FILE})
OBJ		= ${addprefix ${OBJ_PATH}/, ${SRC_FILE:%.cpp=%.o}}

#########################
#			FLAGS		#
#########################

FLAGS = -Wall -Wextra -std=c++98
SAN = -g
OPT_FLAGS = -flto
INCLUDE_FLAGS = -I $(CONTAINER_DIRECTORY) -I $(ITERATORS_DIRECTORY) -I srcs/ft_utils -I srcs/main_srcs

#########################
#		LIBRARIES		#
#########################

LIBFT	= libft.a
LIB = lib/
LIBS = ${addprefix $(LIB), ${LIBFT}}

########################
#		COMMAND			#
#######################

CC= g++
DIFF = diff
MKDIR= mkdir
ECHO=echo
RM=rm

#############################
#			RULES			#
#############################

all : $(NAME)

$(NAME) : ${INCLUDE} ${OBJ} 
	@$(ECHO) "${vertclair}Creating ${NAME}"
	@$(CC) ${FLAGS} ${OPT_FLAGS} $(INCLUDE_FLAGS) ${OBJ} -o ${NAME}
	@$(ECHO) "${vertclair}[$(NAME) ready to use]$(neutre)"

${OBJ_PATH}/%.o: %.cpp ${INCLUDE}
	@$(MKDIR) -p ${OBJ_PATH}
	@$(ECHO) "${cyanfonce}Compiling ${notdir $(basename $@)}"
	@$(CC) $(FLAGS) ${OPT_FLAGS} -c -o $@ $(INCLUDE_FLAGS) $<

test:
	@cd Test && ./Run_tests.sh

debug: extend_flags re

extend_flags:
	$(eval FLAGS += $(SAN))

clean :
	@$(ECHO) "${rouge}Removing objects files"
	@$(RM) -rf ${OBJ_PATH}

fclean : clean
	@$(ECHO) "${rose}Removing ${NAME}"
	@$(RM) -f $(NAME)

re : fclean all

.PHONY : all clean fclean re test
