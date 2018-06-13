# -nostdinc
#  -Werror
make:
	g++ -ggdb -std=c++11 -O0 -D__DEBUG=1 -DLINUX src/ss_main.cpp -o bin/ss -Iinc -L./lib/linux -lSDL2 -lSDL2main -ldl -lpthread

run: make
	./bin/ss

debug: make
	gdb ./bin/ss

valgrind: make
	valgrind --suppressions=sup --tool=memcheck --show-reachable=yes --num-callers=20 --track-fds=yes --leak-check=full -v ./bin/game 2> temp

edit:
	nvim src/* makefile
