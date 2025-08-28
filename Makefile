CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = main.cpp
BIN = app

LEVEL_EDITOR_SRC = level_editor.cpp
LEVEL_EDITOR_BIN = level_editor

all: $(BIN) $(LEVEL_EDITOR_BIN)


$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

$(LEVEL_EDITOR_BIN): $(LEVEL_EDITOR_SRC)
	$(CXX) $(CXXFLAGS) -o $(LEVEL_EDITOR_BIN) $(LEVEL_EDITOR_SRC) $(LDFLAGS)


run: $(BIN)
	LD_LIBRARY_PATH=/usr/local/lib:$$LD_LIBRARY_PATH ./$(BIN)

run-level-editor: $(LEVEL_EDITOR_BIN)
	LD_LIBRARY_PATH=/usr/local/lib:$$LD_LIBRARY_PATH ./$(LEVEL_EDITOR_BIN)

clean:
	rm -f $(BIN) $(LEVEL_EDITOR_BIN)
