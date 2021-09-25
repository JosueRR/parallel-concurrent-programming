# rule
#target: prerequisites
# commands to build

hello: hello.c
	gcc -g -Wall -Wextra hello.c -o hello -lpthread

.PHONY: asan msan tsan ubsan # google sanitizers
asan: # busca fugas de memoria y accesos inválidos de memoria
	gcc -g -Wall -Wextra -fsanitize=address hello.c -o hello -lpthread
msan: # busca memoria no incializada
	clang -g -Wall -Wextra -fsanitize=memory hello.c -o hello -lpthread
tsan: # fugas de hilos, condiciones de carrera etc
	gcc -g -Wall -Wextra -fsanitize=thread hello.c -o hello -lpthread
ubsan: # comportamiento indefinido
	clang -g -Wall -Wextra -fsanitize=undefined hello.c -o hello -lpthread

# check for memory leaks
.PHONY: memcheck
memcheck:
	valgrind --tool=memcheck --leak-check=full ./hello

# check for errores relacionados a la concurrencia, no sirve de mucho (falsos positivos)
.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind ./hello

.PHONY: clean
clean:
	rm -f hello
