#Makefiles encargado de compilar tanto el módulo gráfico como el quienesquien.

#Macros
INCLUDE = include
LIB = lib


all: make doc

#Ejecutamos los dos makefiles
make: graficos/Makefile quienesquien/Makefile
	#Compilamos el módulo gráfico
	make -C graficos  $(LIB)/libgraficos.a 
	#Compilamos el quienesquien
	make  -C quienesquien 

#Documentacion en doxygen
doc:
	doxygen quienesquien/doc/Doxyfile

#Borramos todos los código objeto y bibliotecas generados tanto por el módulo gráfico como por el quienesquien
clean: graficos/Makefile quienesquien/Makefile
	make clean -C quienesquien
	make clean -C graficos
