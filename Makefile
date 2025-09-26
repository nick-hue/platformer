# -------- Compiler --------
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic -MMD -MP -Iinclude

# -------- Linker (Linux + raylib) --------
LDLIBS   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# -------- Sources --------
SRCS_EDITOR := src/editor/level_editor.cpp \
               src/editor/info_screen.cpp \
			   src/common/my_button.cpp \
               src/common/grid.cpp \
               src/common/cell.cpp \
			   src/common/my_triangle.cpp \
			   src/common/item_sprite.cpp \
			   src/third_party/raygui_impl.cpp \

SRCS_GAME   := 	src/game/main.cpp \
				src/game/game.cpp \
				src/game/game_ui.cpp \
				src/game/heart.cpp \
				src/game/player.cpp \
				src/game/tile.cpp \
				src/game/texture.cpp \
				src/game/map.cpp \
				src/game/sound_manager.cpp \
				src/common/item_sprite.cpp \
				src/common/grid.cpp \
				src/common/my_triangle.cpp \
				src/common/cell.cpp \
				src/common/my_button.cpp \
				src/third_party/raygui_impl.cpp \




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

$(BIN_GAME): $(BIN_DIR) $(OBJS_GAME)
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
