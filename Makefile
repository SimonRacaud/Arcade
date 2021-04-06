##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	=	./src/

### COMPILE
CXXFLAGS	+= -W -Wall -Wextra $(INCLUDE) $(DEBUG) # -Werror
DEBUG		= -g
INCLUDE 	= -I./includes -I./src -I./src/exception/includes
NAME		= arcade lib/arcade_nibbler.so lib/arcade_sfml.so lib/arcade_ncurses.so lib/arcade_sdl2.so lib/arcade_solarfox.so
LDFLAGS 	= $(INCLUDE) $(DEBUG)

### DEFAULT
DEF_SRC	= 	$(DSRC)exception/BaseException.cpp		\
			$(DSRC)utility/trim.cpp					\
			$(DSRC)utility/Vector.cpp				\
			$(DSRC)Timer/Timer.cpp					\

### DEFAUL_GAME_CLASSES
GAME_DSRC = $(DSRC)Game
DEF_GAME_SRC	= 	$(GAME_DSRC)/AbstractGameModule/AbstractGameModule.cpp	\
					$(GAME_DSRC)/GameMap/GameMap.cpp						\
					$(GAME_DSRC)/GameObject/GameObject.cpp					\
					$(GAME_DSRC)/Projectile/Projectile.cpp					\

###
all:  core games graphicals

games: nibbler solarfox
graphicals: sfml SDL2 ncurses

### CORE
CORE_SRC_FILES = 	main.cpp						\
					lib/DLLoader/DLLoader.cpp		\
					lib/DLManager/DLManager.cpp		\
					CoreConfig/CoreConfig.cpp		\
					Core/Core.cpp					\
					MainMenu/MainMenu.cpp			\

CORE_SRC			= $(addprefix $(DSRC), $(CORE_SRC_FILES))
CORE_OBJ			= $(CORE_SRC:.cpp=.o)
core: OBJ 			= $(CORE_OBJ)
core: NAME		= arcade
core: LDFLAGS   += -ldl
core: $(CORE_OBJ)

### GAMES
NIBBLER_SRC	=	$(DSRC)Game/Nibbler/NibblerGameModule.cpp		\
				$(DSRC)Game/Nibbler/Player/NibblerPlayer.cpp	\
				$(DSRC)Game/Nibbler/entrypoint.cpp				\

NIBBLER_OBJ	=	$(NIBBLER_SRC:.cpp=.o)
nibbler: OBJ = $(NIBBLER_OBJ) $(DEF_GAME_SRC)
nibbler: NAME	=	lib/arcade_nibbler.so
nibbler: LDFLAGS 	+= -shared -fPIC
nibbler: CXXFLAGS 	+= -fPIC
nibbler: $(NIBBLER_OBJ)

SOLARFOX_SRC	=	$(DSRC)Game/SolarFox/SolarFoxGameModule.cpp				\
					$(DSRC)Game/SolarFox/Player/SolarFoxPlayer.cpp			\
					$(DSRC)Game/SolarFox/Enemy/SolarFoxEnemy.cpp			\
					$(DSRC)Game/SolarFox/Projectile/SolarFoxProjectile.cpp	\
					$(DSRC)Game/SolarFox/entrypoint.cpp						\

SOLARFOX_OBJ	=	$(SOLARFOX_SRC:.cpp=.o)
solarfox: OBJ = $(SOLARFOX_OBJ) $(DEF_GAME_SRC)
solarfox: NAME	=	lib/arcade_solarfox.so
solarfox: LDFLAGS 	+= -shared -fPIC
solarfox: CXXFLAGS 	+= -fPIC
solarfox: $(SOLARFOX_OBJ)

### GRAPHICALS
SFML_SRC 	= 	$(DSRC)lib/SFML/SFML.cpp
SFML_OBJ	= 	$(SFML_SRC:.cpp=.o)
sfml: OBJ	=	$(SFML_OBJ)
sfml: NAME	=	lib/arcade_sfml.so
sfml: LDFLAGS 	+= -shared -lsfml-graphics -lsfml-window -lsfml-system -fPIC
sfml: CXXFLAGS 	+= -fPIC
sfml: $(SFML_OBJ)

NCURSES_SRC 	= 	$(DSRC)lib/Ncurses/Ncurses.cpp
NCURSES_OBJ	= 	$(NCURSES_SRC:.cpp=.o)
ncurses: OBJ	=	$(NCURSES_OBJ)
ncurses: NAME	=	lib/arcade_ncurses.so
ncurses: LDFLAGS 	+= -shared -lncurses -fPIC
ncurses: CXXFLAGS 	+= -fPIC
ncurses: $(NCURSES_OBJ)

SDL2_SRC	=	$(DSRC)lib/SDL2/SDL2.cpp
SDL2_OBJ	=	$(SDL2_SRC:.cpp=.o)
SDL2: OBJ	=	$(SDL2_OBJ)
SDL2: NAME	=	lib/arcade_sdl2.so
SDL2: LDFLAGS	+= -shared -lSDL2 -lSDL2_ttf -fPIC
SDL2: CXXFLAGS	+=	-fPIC
SDL2: $(SDL2_OBJ)

### BUILD
%.o: %.cpp
	g++ -c $(CXXFLAGS) -o $@ $<

core nibbler sfml SDL2 ncurses solarfox: $(OBJ)
	@g++ -o $(NAME) $(OBJ) $(DEF_SRC) $(LDFLAGS) && \
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
