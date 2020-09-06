main:
	gcc -g main.c generics.c pwd.c cd.c echo.c ls.c -o main

.PHONY: main

clean:
	rm -rf *.exe *.o