directions : README.md server client 
	cat README.md

server: server.o networking.o cras.o
	gcc -o server server.o networking.o cras.o

client: client.o networking.o
	gcc -o client client.o networking.o

client.o: client.c cras.h
	gcc -c client.c

server.o: server.c cras.h
	gcc -c server.c

cras.o : cras.c cras.h
	gcc -c cras.c

networking.o: networking.c cras.h
	gcc -c networking.c

clean:
	rm *.o
	rm server
	rm client
	rm *~
