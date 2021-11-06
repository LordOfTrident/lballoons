# Compiler related
C = gcc
C_VER = c99
C_FLAGS = \
	-O3\
	-std=${C_VER}\
	-I./src\
	-I./\
	-o ./bin/app\
	-lncurses\
	-g

compile: src/main.c
	@mkdir -p ./bin
	@echo Created ./bin/

	@echo Compiling...
	@${C} src/main.c ${C_FLAGS}
	@echo Compiled successfully

clean:
	@echo Cleaning...
	@rm ./bin/app
	@echo Cleaned succesfully...

all:
	@echo compile - Compiles the source
	@echo clean - Removes built files
