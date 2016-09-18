sqlite.so: sqlite.c
	gcc -fPIC -shared $< -o $@ -lsqlite3 -llua 

clean:
	rm -rf sqlite.so
