proj2 : proj2ui.o llist.o
	g++ -o proj2 proj2ui.o llist.o

proj2ui.o : proj2ui.cpp llist.h methodPrototypes.h record.h
	g++ -c proj2ui.cpp

llist.o : llist.cpp llist.h methodPrototypes.h record.h
	g++ -c llist.cpp

clean :
	rm *.o proj2 bankDB.txt