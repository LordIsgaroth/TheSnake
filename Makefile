#SRC_DIR scpeicfies which directories contains source files
SRC_DIRS := .

#File searching mask
SEARCH_FILES := $(addsuffix /*.cpp, $(SRC_DIRS))

#OBJS specifies which files to compile as part of the project
#OBJS = game_window.cpp renderer.cpp event_handler.cpp sprite.cpp the_snake.cpp snake_game.cpp
OBJS = $(wildcard $(SEARCH_FILES))

#CC specifies which compiler we're using
CXX = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image
#-lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = the_snake

#This is the target that compiles our executable
all : $(OBJS)
	$(CXX) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)