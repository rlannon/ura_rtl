SRC_DIR=./src
INCLUDE_DIR=./include
OBJ_DIR=./bin
SRC_FILES=$(wildcard $(SRC_DIR)/*.cxx)
OBJ_FILES=$(patsubst %.cxx, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
cc=clang++
cppversion=c++2a
flags=-std=$(cppversion) -g -I $(INCLUDE_DIR)
link_flags=-lpthread $(flags)
target=ura.a
test_exe=ura_test.out

default: $(target)
library: $(target)
test: $(test_exe)

$(test_exe): $(target)
	@echo Creating test executable...
	$(cc) $(link_flags) main.cxx $(target) -o $(test_exe)
	@echo Done.

$(target): $(OBJ_FILES)
	@echo Creating library file...
	ar r $@ $^
	@echo Done.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(cc) $(flags) -c -o $@ $<

clean:
	rm -f bin/*.o
	rm -f ./$(target)
	rm -f ./$(test_exe)

.PHONY: $(target) clean
