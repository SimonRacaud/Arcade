##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	=	./src/

SRC_FILES = 	main.cpp						\
				exception/BaseException.cpp		\
				lib/DLLoader/DLLoader.cpp		\
				lib/DLManager/DLManager.cpp		\

SRC	=	$(addprefix $(DSRC), $(SRC_FILES))

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade

CXXFLAGS	+= -std=c++11 -W -Wall -Wextra $(INCLUDE) $(DEBUG) # -Werror
GPPFLAGS   	= -ldl

DEBUG=-g

INCLUDE = -I./includes -I./src -I./src/exception/includes

all:  $(NAME)

$(NAME): $(OBJ)
	@g++ -o $(NAME) $(OBJ) $(GPPFLAGS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	rm -f  $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean:	clean
	rm -f $(NAME)

re:	fclean all

reall:	fclean all

#tests_run:
	#@g++ -o $(NAME) $(SRC_UT) -I./ -lcriterion --coverage && ./$(NAME)

.PHONY :        clean fclean re

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LINE_RETURN	=	$(ECHO) ""
