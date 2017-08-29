CPP = g++
CFLAGS = -std=c++11 -Wall -g
LDFLAG = -g
SOURCES = main.cpp AutoReleasePool.cpp Env.cpp Expr.cpp Parser.cpp Visitor.cpp
OBJ_DIR = ./objs
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE=lxScheme

.PHONY: all make_dir clean

all: make_dir $(SOURCES) $(EXECUTABLE)
make_dir: $(OBJ_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(LDFLAG) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE)
