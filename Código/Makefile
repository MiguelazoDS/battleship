CC = g++
CFLAGS = -I.
OBJ = BattleShip.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o output

