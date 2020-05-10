CXX=g++-10
CXX_FLAGS=-Wall -Wextra -Wshadow -Wpedantic -O3 -std=c++2a
CXX_LIBS=

EXEC_NAME=TSP
OBJECTS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
REBUILDABLES=$(EXEC_NAME) $(OBJECTS)

.PHONY: all build $(EXEC_NAME) clean

all: $(EXEC_NAME)

clean:
	@echo "Deleting " $(REBUILDABLES)
	@rm -f $(REBUILDABLES)

$(EXEC_NAME): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXX_LIBS) $(CXX_FLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXX_LIBS) $(CXX_FLAGS)

