main:
	gcc -g main.c generics.c pwd.c cd.c echo.c ls.c pinfo.c execute.c -o main

.PHONY: main

clean:
	rm -rf *.exe *.o