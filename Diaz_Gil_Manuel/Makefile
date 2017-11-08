BASE_DIR = APELLIDO1_APELLIDO2_NOMBRE
TAR_NAME = practicas-da

####################### FIN CONFIGURACION ###########################

# Cuidado con la configuración del editor de texto. Los comandos de los objetivos deben de ir precedidos por tabuladores, NO ESPACIOS (error: falta separador).


CC = g++ # C++ compiler
CFLAGS = -O2 -fPIC -ffloat-store # -m64 -Wall -Wextra # -g 
LDFLAGS = -shared # linking flags 

EXE = simulador/simulador
GUION_P0 = guion-p0
GUION_P1 = guion-p1
GUION_P2 = guion-p2
GUION_P3 = guion-p3
GUION_P4 = guion-p4

BIN_SIMULADOR = ../$(BASE_DIR)/simulador/simulador
BIN_P1 = ../$(BASE_DIR)/p1/lib*.so
BIN_P2 = ../$(BASE_DIR)/p2/lib*.so
BIN_P3 = ../$(BASE_DIR)/p3/lib*.so
BIN_P4 = ../$(BASE_DIR)/p4/lib*.so 

FILES_TO_PACK_SIMULADOR = ../$(BASE_DIR)/simulador/Asedio.h ../$(BASE_DIR)/simulador/Defense.h ../$(BASE_DIR)/simulador/Makefile ../$(BASE_DIR)/simulador/Vector3.h ../$(BASE_DIR)/simulador/ObjectsManager.h $(BIN_SIMULADOR)

FILES_TO_PACK_VISOR = ../$(BASE_DIR)/visor/bin/*

FILES_TO_PACK_OTHERS = ../$(BASE_DIR)/Makefile

FILES_TO_PACK_P0 = ../$(BASE_DIR)/autor.tex ../$(BASE_DIR)/p0/guion-p0.pdf

FILES_TO_PACK_P1 = ../$(BASE_DIR)/p1/DefenseStrategy.example.cpp ../$(BASE_DIR)/p1/e*.tex ../$(BASE_DIR)/p1/p1.tex ../$(BASE_DIR)/p1/guion-p1.pdf ../$(BASE_DIR)/p1/Makefile ../$(BASE_DIR)/p1/ppm.h $(BIN_P1)

FILES_TO_PACK_P2 = ../$(BASE_DIR)/p2/DefensesSelection.example.cpp ../$(BASE_DIR)/p2/e*.tex ../$(BASE_DIR)/p2/p2.tex ../$(BASE_DIR)/p2/guion-p2.pdf ../$(BASE_DIR)/p2/Makefile $(BIN_P2)

FILES_TO_PACK_P3 = ../$(BASE_DIR)/p3/cronometro.h ../$(BASE_DIR)/p3/data.txt ../$(BASE_DIR)/p3/DefenseStrategy.example.cpp ../$(BASE_DIR)/p3/e*.tex ../$(BASE_DIR)/p3/p3.tex ../$(BASE_DIR)/p3/guion-p3.pdf ../$(BASE_DIR)/p3/Makefile ../$(BASE_DIR)/p3/graphic.plot $(BIN_P3)

FILES_TO_PACK_P4 = ../$(BASE_DIR)/p4/PathFind.example.cpp ../$(BASE_DIR)/p4/e*.tex ../$(BASE_DIR)/p4/p4.tex ../$(BASE_DIR)/p4/guion-p4.pdf ../$(BASE_DIR)/p4/Makefile ../$(BASE_DIR)/p4/ppm.h $(BIN_P4)

# solutions

FILES_TO_PACK_P1_SOL = ../$(BASE_DIR)/p1/DefenseStrategy.cpp

FILES_TO_PACK_P2_SOL = 

FILES_TO_PACK_P3_SOL = ../$(BASE_DIR)/p3/DefenseStrategy.cpp

FILES_TO_PACK_P4_SOL = ../$(BASE_DIR)/p4/PathFind.cpp

#sources

SOURCES_SIMULADOR = ../$(BASE_DIR)/simulador/Makefile ../$(BASE_DIR)/simulador/*.cpp ../$(BASE_DIR)/simulador/*.h

SOURCES_VISOR = 

SOURCES_OTHERS = $(FILES_TO_PACK_OTHERS) ../$(BASE_DIR)/update.sh ../$(BASE_DIR)/sendupdate.sh 

SOURCES_P0 = $(FILES_TO_PACK_P0) ../$(BASE_DIR)/p0/guion-p0.tex

SOURCES_P1 = $(FILES_TO_PACK_P1) $(FILES_TO_PACK_P1_SOL) ../$(BASE_DIR)/p1/guion-p1.tex ../$(BASE_DIR)/competicion/p1/competicion.sh ../$(BASE_DIR)/competicion/p1/resultados.xls ../$(BASE_DIR)/competicion/p1/copias.sh

SOURCES_P2 = $(FILES_TO_PACK_P2) $(FILES_TO_PACK_P2_SOL) ../$(BASE_DIR)/p2/guion-p2.tex ../$(BASE_DIR)/p2/DefensesSelection.cpp ../$(BASE_DIR)/competicion/p2/competicion.sh ../$(BASE_DIR)/competicion/p2/resultados.xls ../$(BASE_DIR)/competicion/p2/copias.sh

SOURCES_P3 = $(FILES_TO_PACK_P3) $(FILES_TO_PACK_P3_SOL) ../$(BASE_DIR)/p3/guion-p3.tex

SOURCES_P4 = $(FILES_TO_PACK_P4) $(FILES_TO_PACK_P4_SOL) ../$(BASE_DIR)/p4/guion-p4.tex

# ============================ RULES ===========================================

.PHONY: all
all: p0 p1 p2 p3 p4 $(EXE)

$(EXE): simulador/CodingManager.cpp simulador/ppm.cpp simulador/Defense.cpp simulador/Game.cpp simulador/Unit.cpp simulador/Map.cpp simulador/Asedio.h simulador/ObjectsManager.h simulador/CodingManager.h simulador/ppm.h simulador/Defense.h simulador/ezOptionParser.h  simulador/Unit.h simulador/Game.h simulador/Vector3.h simulador/Map.h

	cd simulador; make; cd ..

# ==== P0 ====

p0/$(GUION_P0).pdf: p0/$(GUION_P0).tex
	cd p0; latex $(GUION_P0).tex && pdflatex $(GUION_P0).tex; cd ..

p0: p0/$(GUION_P0).pdf

# ==== P1 ====

p1/$(GUION_P1).pdf: p1/$(GUION_P1).tex
	cd p1; latex $(GUION_P1).tex && pdflatex $(GUION_P1).tex; cd ..

p1/libDefenseStrategy.default.so:
	cd p1; $(CC) $(CFLAGS) ${LDFLAGS} -DGREEDY_DEFENSE_STRATEGY -o libDefenseStrategy.default.so DefenseStrategy.cpp && cp libDefenseStrategy.default.so libDefenseStrategy.so; cd ..

p1/libDefenseStrategy.random.so:
	cd p1; $(CC) $(CFLAGS) ${LDFLAGS} -DRANDOM_DEFENSE_STRATEGY -o libDefenseStrategy.random.so DefenseStrategy.cpp; cd ..

p1/libDefenseStrategy.null.so:
	cd p1; $(CC) $(CFLAGS) ${LDFLAGS} -DNULL_DEFENSE_STRATEGY -o libDefenseStrategy.null.so DefenseStrategy.cpp; cd ..

p1: p1/$(GUION_P1).pdf p1/libDefenseStrategy.default.so p1/libDefenseStrategy.random.so p1/libDefenseStrategy.null.so

# ==== P2 ====

p2/$(GUION_P2).pdf: p2/$(GUION_P2).tex
	cd p2; latex $(GUION_P2).tex && pdflatex $(GUION_P2).tex; cd ..

p2/libDefensesSelection.default.so: 
	cd p2; $(CC) $(CFLAGS) ${LDFLAGS} -o libDefensesSelection.default.so DefensesSelection.cpp && cp libDefensesSelection.default.so libDefensesSelection.so; cd ..

p2: p2/$(GUION_P2).pdf p2/libDefensesSelection.default.so

# ==== P3 ====

p3/$(GUION_P3).pdf: p3/$(GUION_P3).tex
	cd p3; latex $(GUION_P3).tex && pdflatex $(GUION_P3).tex; cd ..

p3/libDefenseStrategy3.null.so:
	cd p3; $(CC) $(CFLAGS) ${LDFLAGS} -o libDefenseStrategy3.null.so DefenseStrategy.cpp && cp libDefenseStrategy3.null.so libDefenseStrategy3.so ; cd ..

p3: p3/$(GUION_P3).pdf p3/libDefenseStrategy3.null.so

# ==== P4 ====

p4/$(GUION_P4).pdf: p4/$(GUION_P4).tex
	cd p4; latex $(GUION_P4).tex && pdflatex $(GUION_P4).tex; cd ..

p4/libAttackStrategy.default.so:
	cd p4; $(CC) $(CFLAGS) ${LDFLAGS} -o libAttackStrategy.default.so PathFind.cpp && cp libAttackStrategy.default.so libAttackStrategy.so; cd ..

p4: p4/$(GUION_P4).pdf p4/libAttackStrategy.default.so

# ==== General ====
 
publish:
	rm $(TAR_NAME).tar.gz; tar -czvf $(TAR_NAME).tar.gz $(FILES_TO_PACK_SIMULADOR) $(FILES_TO_PACK_VISOR) $(FILES_TO_PACK_P0) $(FILES_TO_PACK_P1) $(FILES_TO_PACK_P2) $(FILES_TO_PACK_P3) $(FILES_TO_PACK_P4) $(FILES_TO_PACK_OTHERS)

bin:
	rm $(TAR_NAME)-bin.tar.gz; tar -czvf $(TAR_NAME)-bin.tar.gz $(BIN_SIMULADOR) $(BIN_P1) $(BIN_P2) $(BIN_P3) $(BIN_P4)

solutions:
	rm $(TAR_NAME)-soluciones.tar.gz; tar -czvf $(TAR_NAME)-soluciones.tar.gz $(FILES_TO_PACK_P1_SOL) $(FILES_TO_PACK_P2_SOL) $(FILES_TO_PACK_P3_SOL) $(FILES_TO_PACK_P4_SOL)

sources:
	rm $(TAR_NAME)-sources.tar.gz; tar -czvf $(TAR_NAME)-sources.tar.gz $(SOURCES_SIMULADOR) $(SOURCES_VISOR) $(SOURCES_OTHERS) $(SOURCES_P0) $(SOURCES_P1) $(SOURCES_P2) $(SOURCES_P3) $(SOURCES_P4)

update:
	rm update.sh*
	wget http://agsh.net/asedio/update.sh
	chmod u+x update.sh
	./update.sh

sendupdate:
	./sendupdate.sh

to64:
	sed -i.bak 's/asedio_player.x86$$/asedio_player.x86_64/g' simulador/Makefile ; sed -i.bak 's/asedio_player.x86$$/asedio_player.x86_64/g' p1/Makefile ; sed -i.bak 's/asedio_player.x86$$/asedio_player.x86_64/g' p2/Makefile ; sed -i.bak 's/asedio_player.x86$$/asedio_player.x86_64/g' p3/Makefile ; sed -i.bak 's/asedio_player.x86$$/asedio_player.x86_64/g' p4/Makefile

to32:
	sed -i.bak 's/asedio_player.x86_64$$/asedio_player.x86/g' simulador/Makefile ; sed -i.bak 's/asedio_player.x86_64$$/asedio_player.x86/g' p1/Makefile ; sed -i.bak 's/asedio_player.x86_64$$/asedio_player.x86/g' p2/Makefile ; sed -i.bak 's/asedio_player.x86_64$$/asedio_player.x86/g' p3/Makefile ; sed -i.bak 's/asedio_player.x86_64$$/asedio_player.x86/g' p4/Makefile


clean:
	rm p*/*.so simulador/simulador


