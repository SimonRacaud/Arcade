##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	=	./src/

### COMPILE
CXXFLAGS	+= -std=c++11 -W -Wall -Wextra $(INCLUDE) $(DEBUG) # -Werror
DEBUG		= -g
INCLUDE 	= -I./includes -I./src -I./src/exception/includes
NAME		= arcade lib/arcade_nibbler.so lib/arcade_libsfml.so

### DEFAULT
DEF_SRC	= 	$(DSRC)exception/BaseException.cpp		\
			$(DSRC)utility/trim.cpp					\

### CORE
CORE_SRC_FILES = 	main.cpp						\
					lib/DLLoader/DLLoader.cpp		\
					lib/DLManager/DLManager.cpp		\

CORE_SRC			= $(DEF_SRC) $(addprefix $(DSRC), $(CORE_SRC_FILES))
CORE_OBJ			= $(CORE_SRC:.cpp=.o)
core: OBJ 			= $(CORE_OBJ)
core: NAME		= arcade
core: LDFLAGS   += -ldl
core: $(CORE_OBJ) build

### GAMES
NIBBLER_SRC	=	$(DEF_SRC) $(DSRC)lib/game/nibbler.cpp
NIBBLER_OBJ	=	$(NIBBLER_SRC:.cpp=.o)
nibbler: OBJ = $(NIBBLER_OBJ)
nibbler: NAME	=	lib/arcade_nibbler.so
nibbler: LDFLAGS 	+= -fpic
nibbler: CXXFLAGS 	+= -shared
nibbler: $(NIBBLER_OBJ) build

### GRAPHICALS
SFML_SRC 	= 	$(DSRC)lib/SFML.cpp $(DEF_SRC)
SFML_OBJ	= 	$(SFML_SRC:.cpp=.o)
sfml: OBJ	=	$(SFML_OBJ)
sfml: NAME	=	lib/arcade_libsfml.so
sfml: LDFLAGS 	+= -shared -lsfml-graphics -lsfml-window -lsfml-system
sfml: CXXFLAGS 	+= -fPIC
sfml: $(SFML_OBJ) build

all:  core games graphicals

games: nibbler
graphicals: sfml

### BUILD
%.o: %.cpp
	@g++ -c $(CXXFLAGS) -o $@ $<

build: $(OBJ)
	@g++ -o $(NAME) $(OBJ) $(LDFLAGS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

###

clean:
	@rm -f `find ./src -name '*.o' -print`
	rm -f *.gcda
	rm -f *.gcno

fclean:	clean
	rm -f $(NAME)

re:	fclean all

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
