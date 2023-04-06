##
# Project Title
#
# @file
# @version 0.1



# end

.PHONY: target build clean

target:
	mkdir build

build: target
	gcc -o build/main main.c -Wall -lpthread

clean:
	rm -rf build
