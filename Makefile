# -------- Compiler --------
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic -MMD -MP -Iinclude

# -------- Linker (Linux + raylib) --------
LDLIBS   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# -------- Sources --------
SRCS_EDITOR := src/editor/level_editor.cpp \
               src/editor/grid.cpp \
               src/editor/cell.cpp \
               src/editor/debug_menu.cpp \
               src/editor/info_screen.cpp
SRCS_GAME   := src/game/main.cpp

OBJS_EDITOR := $(SRCS_EDITOR:.cpp=.o)
OBJS_GAME   := $(SRCS_GAME:.cpp=.o)

DEPS := $(OBJS_EDITOR:.o=.d) $(OBJS_GAME:.o=.d)

# -------- Binaries --------
BIN_DIR := bin
BIN_EDITOR := $(BIN_DIR)/level_editor
BIN_GAME   := $(BIN_DIR)/platformer

# -------- Rules --------
.PHONY: all clean run-editor run-game

all: $(BIN_EDITOR) $(BIN_GAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_EDITOR): $(BIN_DIR) $(OBJS_EDITOR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_EDITOR) $(LDLIBS)

$(BIN_GAME): $(BIN_DIR) $(OBJS_GAME) src/editor/grid.cpp src/editor/cell.cpp
	# If the game starts using grid/cell/debug_menu, add them above; otherwise remove them.
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_GAME) $(LDLIBS)

# Generic compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run-editor: $(BIN_EDITOR)
	./$(BIN_EDITOR)

run-game: $(BIN_GAME)
	./$(BIN_GAME)

clean:
	rm -rf $(BIN_DIR) $(OBJS_EDITOR) $(OBJS_GAME) $(DEPS)

# Auto header deps
-include $(DEPS)
