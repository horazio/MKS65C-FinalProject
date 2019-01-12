forking: client fserver

select: sclient sserver

sserver: select_server.o networking.o
	gcc -o server select_server.o networking.o

fserver: forking_server.o networking.o cras.o
	gcc -o server forking_server.o networking.o cras.o

sclient: select_client.o networking.o
	gcc -o client select_client.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

select_client.o: select_client.c cras.h
	gcc -c select_client.c

client.o: client.c cras.h
	gcc -c client.c

select_server.o: select_server.c cras.h
	gcc -c select_server.c

forking_server.o: forking_server.c cras.h
	gcc -c forking_server.c

cras.o : cras.c cras.h
	gcc -c cras.c

networking.o: networking.c cras.h
	gcc -c networking.c

clean:
	rm *.o
	rm server
	rm client
	rm *~
