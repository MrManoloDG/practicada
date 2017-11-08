LEVEL = 3204

####################### FIN CONFIGURACION ###########################

# Cuidado con la configuración del editor de texto. Los comandos de los objetivos deben de ir precedidos por tabuladores, NO ESPACIOS (error: falta separador). 

CC = g++ # C++ compiler
#CFLAGS = -Wall -Wextra -O2 -g # C flags
#CFLAGS = -Wall -O2 -g # C flags
#CFLAGS = -O0 -g # C flags
CFLAGS = -ggdb -ffloat-store # C flags
LDFLAGS =  # linking flags
RM = rm -f # rm command
DEF_LIB_PATH1 = ../p1
DEF_LIB_BASE_NAME1 = DefenseStrategy
DEF_LIB_PATH2 = ../p2
DEF_LIB_BASE_NAME2 = DefensesSelection
DEF_LIB_PATH3 = ../p3
DEF_LIB_BASE_NAME3 = DefenseStrategy3
DEF_LIB_PATH4 = ../p4
DEF_LIB_BASE_NAME4 = AttackStrategy
EXE = simulador # target lib
VIEWER = ../visor/bin/lin/asedio_player.x86_64
VIEWERFLAGS = # -logfile log.txt
REPLAYFILE = replay.txt
 
SRCS = $(shell echo *.cpp) # source files
OBJS = $(SRCS:.cpp=.o)
 
.PHONY: all
all: ${EXE}
 
#$(EXE): $(OBJS) #$(DEF_LIB)
$(EXE): $(OBJS)
	$(CC) -L'$(DEF_LIB_PATH1)' -Wl,-rpath='$$ORIGIN/../p1' -L'$(DEF_LIB_PATH2)' -Wl,-rpath='$$ORIGIN/../p2' -L'$(DEF_LIB_PATH3)' -Wl,-rpath='$$ORIGIN/../p3' -L'$(DEF_LIB_PATH4)' -Wl,-rpath='$$ORIGIN/../p4' ${LDFLAGS} -o $@ $^ -l$(DEF_LIB_BASE_NAME1) -l$(DEF_LIB_BASE_NAME2) -l$(DEF_LIB_BASE_NAME3) -l$(DEF_LIB_BASE_NAME4)
 
$(SRCS:.cpp=.d):%.d:%.cpp
	$(CC) $(CFLAGS) -MM $< > $@
 
include $(SRCS:.cpp=.d)
 
test: $(EXE)
	./$< -l $(LEVEL) -v -p paths

savereplay: $(EXE)
	./$< -l $(LEVEL) -v -replay $(REPLAYFILE)

loadreplay: $(REPLAYFILE)
	${VIEWER} -replay $(REPLAYFILE) $(VIEWERFLAGS)
	
convertimages: 
	for i in *.ppm ; do \
		convert $$i -scale 400x400 $$i.png ; \
	done

convertpaths: 
	for i in paths/*.ppm ; do \
		convert $$i -scale 400x400 $$i.png ; \
	done

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.d) \
	${RM} *.ppm* *.aux *.log *.pdf *.tar.gz *.png
	${RM} paths/*.ppm*

