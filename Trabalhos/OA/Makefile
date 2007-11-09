CONT = Controle/*
VIS = Visualizacao/*
PERS = Persistencia/*
DEPS = Main.c Tipos.h $(CONT) $(VIS) $(PERS)

programa: $(DEPS)
	gcc -o programa -O3 Main.c Controle/*.c Persistencia/*.c Visualizacao/*.c

debug: $(DEPS)
	gcc -o programa_debug -g -Wall Main.c Controle/*.c Persistencia/*.c Visualizacao/*.c
	gdb ./programa_debug