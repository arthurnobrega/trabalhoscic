CONT = Controle/*
VIS = Visualizacao/*
DEPS = Main.c Tipos.h $(CONT) $(VIS)

programa: $(DEPS)
	gcc -o programa -O3 Main.c Controle/*.c Visualizacao/*.c

debug: $(DEPS)
	gcc -o programa_debug -g -Wall Main.c Controle/*.c Visualizacao/*.c