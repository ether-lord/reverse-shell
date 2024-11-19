BUILD_DIR=build

all: main

main: build_dir main.c
	gcc main.c -o $(BUILD_DIR)/server

build_dir:
	ls build || mkdir $(BUILD_DIR)
