# ---- Compiler & Flags ----
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic -MMD -MP
# Add debug symbols by running: make CXXFLAGS+='-g'

# ---- Linker Flags & Libs (Linux + raylib) ----
LDFLAGS  :=
LDLIBS   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# ---- Sources ----
SRCS_COMMON := grid.cpp cell.cpp debug_menu.cpp
SRCS_EDITOR := level_editor.cpp
SRCS_MAIN   := main.cpp

# ---- Executables ----
BIN_EDITOR := level_editor
BIN_MAIN   := main

# ---- Objects / Deps ----
OBJS_COMMON := $(SRCS_COMMON:.cpp=.o)
OBJS_EDITOR := $(SRCS_EDITOR:.cpp=.o)
OBJS_MAIN   := $(SRCS_MAIN:.cpp=.o)

DEPS := $(OBJS_COMMON:.o=.d) $(OBJS_EDITOR:.o=.d) $(OBJS_MAIN:.o=.d)

# ---- Default target ----
all: $(BIN_EDITOR) $(BIN_MAIN)

# ---- Build rules ----
$(BIN_EDITOR): $(OBJS_EDITOR) $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(BIN_MAIN): $(OBJS_MAIN) $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Generic .cpp -> .o rule (handles all sources)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- Convenience targets ----
run-level-editor: $(BIN_EDITOR)
	./$(BIN_EDITOR)

run-main: $(BIN_MAIN)
	./$(BIN_MAIN)

clean:
	rm -f $(BIN_EDITOR) $(BIN_MAIN) *.o *.d

.PHONY: all clean run-level-editor run-main

# Include auto-generated dependency files
-include $(DEPS)
