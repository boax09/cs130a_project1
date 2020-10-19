

project1.out: TST.o TST_tb.o
	g++ TST.o TST_tb.o -o project1.out
TST.o : TST.cpp TST.h
	g++ TST.cpp -c
TST_tb.o: TST_tb.cpp TST.h
	g++ TST_tb.cpp -c
clean:
	rm project1.out TST.o TST_tb.o