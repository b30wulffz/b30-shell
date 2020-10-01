main:
	gcc -g main.c generics.c globals.c init.c prompt.c shellinput.c pwd.c cd.c echo.c ls.c pinfo.c execute.c childproc.c cleanup.c history.c envvar.c -o main

.PHONY: main

clean:
	rm -rf *.exe *.o