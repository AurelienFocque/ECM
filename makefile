CC=g++
CFLAGS=
LIBS=-lgmp
INCLUDES=-I include/
LDFLAGS=
EXEC=main
 
all: $(EXEC)
 
$(EXEC): main.o obj/BigNum.o obj/PointEdwards.o obj/CourbeEdwards.o
	$(CC) -o $(EXEC) main.o $(LIBS)
 
main.o: main.cpp 
	$(CC) -c main.cpp $(CFLAGS) $(INCLUDES)
         
obj/BigNum.o: src/BigNum.cpp include/BigNum.h
	$(CC) -o obj/BigNum.o -c src/BigNum.cpp $(CFLAGS)$(INCLUDES)

obj/PointEdwards.o: src/PointEdwards.cpp include/PointEdwards.h
	$(CC) -o obj/PointEdwards.o -c src/PointEdwards.cpp $(CFLAGS)$(INCLUDES)
         
obj/CourbeEdwards.o: src/CourbeEdwards.cpp include/CourbeEdwards.h 
	$(CC) -o obj/CourbeEdwards.o -c src/CourbeEdwards.cpp $(CFLAGS)$(INCLUDES)
clean:
	rm *.o
 
mrproper: clean
	rm $(EXEC)
