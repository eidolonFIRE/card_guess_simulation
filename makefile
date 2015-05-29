CC=g++

FLAGS=
_INCLUDE=

_LIB=

OBJECTS= cardGuess.o cDeck.o

EXECUTABLE=cardGuess.exe

PATH_OBJ=obj/
PATH_SRC=

INCLUDE=$(addprefix -I, $(_INCLUDE))
LIB=$(addprefix -L, $(_LIB))


vpath %.o $(PATH_OBJ)
vpath %.h $(PATH_SRC)
vpath %.cpp $(PATH_SRC)

all: pre-build main-build

pre-build:
	cls
	-mkdir obj


main-build: $(OBJECTS) $(EXECUTABLE)


%.o: %.cpp
	$(CC) $(INCLUDE) -c $< -o $(PATH_OBJ)$@


$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(addprefix $(PATH_OBJ), $(OBJECTS)) $(LIB) $(FLAGS)  


.PHONY: all


clean: 
	del obj/*
