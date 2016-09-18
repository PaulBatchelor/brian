ncurses.so: ncurses.c
	gcc -fPIC -shared $< -o $@ -lncurses -llua 

clean:
	rm -rf ncurses.so
