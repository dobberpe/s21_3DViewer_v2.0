UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	GFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lgtest 
endif

run:
	g++ -Wall -Wextra -Werror -g --std=c++17 main.cpp -o app
	./app
	rm -rf app *.dSYM

test:
	g++ -Wall -Wextra -Werror -g --std=c++17 tests/test_run.cpp tests/test_parser.cpp tests/test_scale.cpp tests/test_move.cpp  tests/test_rotate.cpp tests/test_worker.cpp  -o test_run $(GFLAGS)
	./test_run
	rm -rf test_run *.dSYM