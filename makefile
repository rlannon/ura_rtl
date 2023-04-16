SRC_DIR=./src
INCLUDE_DIR=./include
messaging_base=./messaging
messaging_include_path=$(messaging_base)/include
messaging_library=$(messaging_base)/messaging.a
OBJ_DIR=./bin
SRC_FILES=$(wildcard $(SRC_DIR)/*.cxx)
OBJ_FILES=$(patsubst %.cxx, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
cc=clang++
cppversion=c++20
flags=-std=$(cppversion) -g -I $(INCLUDE_DIR) -I $(messaging_include_path)
link_flags=-lpthread $(flags)
target=ura.a
test_exe=ura_test.out

default: $(target)
library: $(target)
messaging: $(messaging_library)
test: $(test_exe)

$(test_exe): $(target) $(messaging_library)
	@echo Creating test executable...
	$(cc) $(link_flags) main.cxx $(target) $(messaging_library) -o $(test_exe)
	@echo Done.

$(target): $(OBJ_FILES)
	@echo Creating library file...
	ar r $@ $^
	@echo Done.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(cc) $(flags) -c -o $@ $<

$(messaging_library):
	cd $(messaging_base) && make

clean:
	rm -f bin/*.o
	rm -f ./$(target)
	rm -f ./$(test_exe)

.PHONY: $(target) clean
