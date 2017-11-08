APELLIDO1_APELLIDO2_NOMBRE = APELLIDO1_APELLIDO2_NOMBRE
LEVEL = 3324

####################### FIN CONFIGURACION ###########################

# Cuidado con la configuración del editor de texto. Los comandos de los objetivos deben de ir precedidos por tabuladores, NO ESPACIOS (error: falta separador). 

FILES_TO_PACK_P1 = ../p1/DefenseStrategy.cpp ../p1/*.tex ../p1/p1.pdf ../autor.tex ../p1/Makefile ../p1/ppm.h ../p1/.conf
FILES_TO_PACK_P2 = ../p2/DefensesSelection.cpp ../p2/*.tex ../p2/p2.pdf ../p2/Makefile ../p2/.conf
FILES_TO_PACK_P3 = ../p3/DefenseStrategy.cpp ../p3/*.tex ../p3/p3.pdf ../p3/Makefile ../p3/cronometro.h ../p3/.conf
FILES_TO_PACK_P4 = ../p4/PathFind.cpp ../p4/*.tex ../p4/p4.pdf ../p4/Makefile ../p4/ppm.h ../p4/.conf
CC = g++ # C++ compiler
CFLAGS = -fPIC -O2 -ffloat-store # -Wall -Wextra -g 
LDFLAGS = -shared # linking flags
RM = rm -f # rm command
TARGET_LIB = libAttackStrategy.so # target lib
SIMPATH = ../simulador/
EXE = $(SIMPATH)simulador
VIEWER = ../visor/bin/lin/asedio_player.x86_64
VIEWERFLAGS = # -logfile log.txt
REPLAYFILE = replay.txt

SRCS = PathFind.cpp # source files
OBJS = $(SRCS:.cpp=.o)
 
.PHONY: all
all: ${TARGET_LIB}
 
$(TARGET_LIB): $(SRCS)
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^

test: $(EXE)
	./$< -l $(LEVEL) -v

savereplay: $(EXE)
	./$< -l $(LEVEL) -v -replay $(REPLAYFILE)

loadreplay: $(REPLAYFILE)
	${VIEWER} -replay $(REPLAYFILE) $(VIEWERFLAGS)

testpaths: $(EXE)
	./$< -l $(LEVEL) -v -p paths

convertimages: 
	for i in *.ppm ; do \
		convert $$i -scale 400x400 $$i.png ; \
	done

convertpaths: 
	for i in paths/*.ppm ; do \
		convert $$i -scale 400x400 $$i.png ; \
	done
 
doc:
	pdflatex p4.tex
pack:
	tar -czvf $(APELLIDO1_APELLIDO2_NOMBRE)-p4.tar.gz $(FILES_TO_PACK_P1) $(FILES_TO_PACK_P2) $(FILES_TO_PACK_P3) $(FILES_TO_PACK_P4)
 
.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.d) \
	${RM} *.ppm* *.aux *.log p*.pdf *.tar.gz *.png
	${RM} paths/*.ppm*

