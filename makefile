CXX = c++
CXXFLAGS = -Wall -Wextra -pedantic -ggdb -std=c++20 -o
OBJECT = toyc
SRC = $(shell find src/ -type f -name *.cpp)
INSTALLATION_TARGET = /usr/bin/toyc

default: $(SRC)
	@$(CXX) $(CXXFLAGS) $(OBJECT) $(SRC)

clean: $(OBJECT)
	@rm $(OBJECT)

install: $(INSTALLATION_TARGET)
	@make default
	@sudo mv $(OBJECT) $(INSTALLATION_TARGET)

uninstall: $(INSTALLATION_TARGET)
	@sudo rm $(INSTALLATION_TARGET)
