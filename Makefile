#SRC_DIRS scpeicfies which directories contains source files
SRC_DIRS := my_little_engine my_little_engine/common my_little_engine/events my_little_engine/objects my_little_engine/physics my_little_engine/rendering .

#File searching mask
SEARCH_FILES := $(addsuffix /*.cpp, $(SRC_DIRS))

#OBJS specifies which files to compile as part of the project
#OBJS = game_window.cpp renderer.cpp event_handler.cpp sprite.cpp the_snake.cpp snake_game.cpp
#OBJS = $(wildcard $(SEARCH_FILES))

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
the_snake : $(notdir $(patsubst %.cpp, %.o, $(wildcard $(SEARCH_FILES))))
	$(CXX) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

VPATH := $(SRC_DIRS)

%.o: %.cpp
	$(CXX) -c -MD $(addprefix -I, $(SRC_DIRS)) $<

include $(wildcard *.d)
#	$(CXX) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)