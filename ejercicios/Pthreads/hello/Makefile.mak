# rule
#target: prerequisites
#	commands to build target

hello: hello.c
	cc -g -Wall -Wextra hello.c -o hello -pthread


.PHONY: asan msan tsan ubsan
asan:
	cc -g -Wall -Wextra -fsanitize=address hello.c -o hello -pthread

msan:
	clang -g -Wall -Wextra -fsanitize=memory hello.c -o hello -pthread

tsan:
	cc -g -Wall -Wextra -fsanitize=thread hello.c -o hello -pthread

ubsan:
	cc -g -Wall -Wextra -fsanitize=undefined hello.c -o hello -pthread

.PHONY: memcheck
memcheck:
	valgrind --tool=memcheck --leak-check=full ./hello

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind ./hello

.PHONY: clean
clean:
	rm -f hello hello_*

