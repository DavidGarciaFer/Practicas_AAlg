<<<<<<< HEAD
CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = ejercicio1 main
=======
#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

<<<<<<< HEAD
$(EXE) : % : %.o ordenacion.o permutaciones.o busqueda.o
=======
$(EXE) : % : %.o ordenacion.o tiempos.o permutaciones.o busqueda.o
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
<<<<<<< HEAD
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o permutaciones.o busqueda.o

busqueda.o : busqueda.c busqueda.h
=======
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o busqueda.o

busqueda.o : busqueda.c busqueda.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

permutaciones.o : permutaciones.c permutaciones.h
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

<<<<<<< HEAD
permutaciones.o : permutaciones.c permutaciones.h
=======
 ordenacion.o : ordenacion.c ordenacion.h
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

<<<<<<< HEAD
 ordenacion.o : ordenacion.c ordenacion.h
=======
 tiempos.o : tiempos.c tiempos.h
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

<<<<<<< HEAD
# tiempos.o : tiempos.c tiempos.h
#	@echo "#---------------------------"
#	@echo "# Generando $@"
#	@echo "# Depende de $^"
#	@echo "# Ha cambiado $<"
#	$(CC) $(CFLAGS) -c $<

=======
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad
ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -limInf 1 -limSup 5 -numN 10

<<<<<<< HEAD
main_test:
	@echo Ejecutando main
	@./main
=======
ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -tamanio 1 -numP 5
>>>>>>> aaf7a05637b4f64c006e1ae38c6808082f71afad
