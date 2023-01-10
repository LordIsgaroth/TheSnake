#SRC_DIRS scpeicfies which directories contains source files
SRC_DIRS := snake_game my_little_engine my_little_engine/core my_little_engine/common my_little_engine/events my_little_engine/objects my_little_engine/physics my_little_engine/rendering .

#File searching mask
SEARCH_FILES := $(addsuffix /*.cpp, $(SRC_DIRS))

#CXX specifies which C++ compiler we're using
CXX = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#Source files
SRCS := $(notdir $(wildcard $(SEARCH_FILES)))
#SRCS := $(notdir $(patsubst %.cpp, %.o, $(wildcard $(SEARCH_FILES))))

#Header files and directories
INCS := $(wildcard *.hpp $(foreach fd, $(SRC_DIRS), $(fd)/*.hpp))
INC_DIRS := -I./ $(addprefix -I, $(SRC_DIRS))

#Object files and directory
OBJ_DIR := ./objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:cpp=o))

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = the_snake

#This is the target that compiles our executable
the_snake : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LINKER_FLAGS)
#	$(CXX) $^ $(COMPILER_FLAGS)  $@ $(OBJS)

VPATH := $(SRC_DIRS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) -o $@ $(COMPILER_FLAGS) -c $< $(INC_DIRS)
#	 $(CXX) -c $(addprefix -I, $(SRC_DIRS)) $<

include $(wildcard *.d)
#	$(CXX) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)