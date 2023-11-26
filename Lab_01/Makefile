
#Compilo il file tramite questo makefile con target singolo --- METODO 1 ---
target: 
	gcc -c copy_file.c -o copy_file_v3_makefile.o
	gcc copy_file_v3_makefile.o -o copy_file_v3_makefile.exe
	

# Modificare il Makefile precedente aggiungendo il target install, in grado di
# a - creare un direttorio fratello a quello di lavoro e di nome bin
# b - spostare l'eseguibile creato in tale direttorio

install:
	mkdir bin
	mv copy_file_v3_makefile.exe bin
	
# Modificare il Makefile precedente aggiungendo il target clean, che rimuove il file oggetto nel direttorio corrente

clean:
	rm copy_file_v3_makefile.o
	
# Modificare il Makefile precedente aggiungendo il target distclean che richiama il target clean e cancella il direttorio bin fratello di quello corrente e tutto il suo contenuto

distclean:
	rm -r bin
	
# Non ho capito a cosa faccia riferimento quando dice che deve richiamare il target clean allachi
