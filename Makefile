CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = main.cpp
BIN = app

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

run: $(BIN)
	LD_LIBRARY_PATH=/usr/local/lib:$$LD_LIBRARY_PATH ./$(BIN)

clean:
	rm -f $(BIN)
