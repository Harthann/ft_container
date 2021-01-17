# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 16:28:15 by nieyraud          #+#    #+#              #
#    Updated: 2021/01/17 09:32:15 by nieyraud         ###   ########.fr        #
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

SRC_FILE = main.cpp list_test.cpp test_vector.cpp

INCLUDE	=	srcs/list/List.hpp srcs/list/List_node.hpp srcs/list/List_iterator.hpp \
			srcs/stack/Stack.hpp \
			srcs/queue/Queue.hpp \
			srcs/vector/Vector.hpp srcs/vector/Vector_iterator.hpp \
			srcs/map/Map.hpp \
			srcs/iterators/base_iterator.hpp

#############################
#		DIRCTORIES PATH		#
#############################

PATH = ${shell find srcs -type d}
OBJ_PATH = objs
vpath %.cpp $(foreach dir, $(PATH), $(dir))

#################################
#		FILES	VARIABLE		#
#################################

SRC		= ${SRC_FILE}
SRCS	= $(addprefix ${PATH}, ${SRC_FILE})
OBJ		= ${addprefix ${OBJ_PATH}/, ${SRC_FILE:%.cpp=%.o}}

#########################
#			FLAGS		#
#########################

FLAGS = -Wall -Wextra --std=c++98
SAN = -g3 -fsanitize=address
OPT_FLAGS = -flto
INCLUDE_FLAGS = -I srcs/list \
				-I srcs/queue \
				-I srcs/map \
				-I srcs/vector \
				-I srcs/stack \
				-I srcs/allocator \
				-I srcs/iterators

#########################
#		LIBRARIES		#
#########################

LIBFT	= libft.a
LIB = lib/
LIBS = ${addprefix $(LIB), ${LIBFT}}

########################
#		COMMAND			#
#######################

CC= /usr/bin/clang++
MKDIR= /bin/mkdir
ECHO=echo
RM=/bin/rm

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
	@$(CC) $(FLAGS) -c -o $@ $(INCLUDE_FLAGS) $<

sanitize: ${LIBS} ${OBJ} ${INCLUDE} 
	@$(ECHO) "${vertclair}Creating ${NAME}"
	@$(CC) ${FLAGS} ${OPT_FLAGS} ${SAN} -I. ${OBJ} -o ${NAME}
	@$(ECHO) "${vertclair}[$(NAME) ready to use]"

clean :
	@$(ECHO) "${rouge}Removing objects files"
	@$(RM) -rf ${OBJ_PATH}

run : all
	@./${NAME}

fclean : clean
	@$(ECHO) "${rose}Removing ${NAME}"
	@$(RM) -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
