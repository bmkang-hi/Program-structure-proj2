Proj1 : project1.o recordMethods.o 
	gcc -o Proj1 project1.o recordMethods.o
	
project1.o : project1.c record.h projPrototypes.h
	gcc -c project1.c

recordMethods.o : 	recordMethods.c record.h 
	gcc -c recordMethods.c

clean :
	rm *.o Proj1 bankDB.txt
