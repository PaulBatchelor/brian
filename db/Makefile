OBJ= jsmn.o sketches.o val.o array.o \
	 htable.o list.o main.o json.o db.o

default: briandb

CFLAGS=-Wall -g

LDFLAGS=-lsqlite3

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

briandb: $(OBJ)
	gcc $(LDFLAGS) $(CFLAGS) -o $@ $(OBJ)

clean: 
	rm -rf briandb $(OBJ)
