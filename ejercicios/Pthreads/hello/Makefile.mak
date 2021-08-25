hello: hello.c
	cc -g -Wall -Wextra hello.c -o hello -pthread

.PHONY: assan msan tsan ubsan
asan:
	cc -g -Wall -Wextra hello.c -o hello -pthread

msan: