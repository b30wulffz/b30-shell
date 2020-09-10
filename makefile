main:
	gcc -g main.c generics.c globals.c init.c childstatus.c prompt.c shellinput.c pwd.c cd.c echo.c ls.c pinfo.c execute.c -o main

.PHONY: main

clean:
	rm -rf *.exe *.o