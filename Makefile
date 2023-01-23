
APPNAME = afdtool
 
APP = ./app
BIN = ./bin
# todos .h dentro de ./includes
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src
# Tests dir
TEST= ./tests

# Flags
FLAGS = -O3 -Wall

all: dirs modulos afdtool
# compilando src

dirs:
	mkdir -p $(OBJ)/utils

modulos:	\
	$(OBJ)/afd.o	\
	$(OBJ)/operacoes.o \
	$(OBJ)/utils/entrada_saida.o \

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

# compilando o app 
afdtool:
	gcc $(FLAGS) $(APP)/$(APPNAME).c $(OBJ)/*.o -I $(INCLUDE) -o $(APPNAME)


test_%:	
	echo $@
	gcc $(FLAGS) $(TEST)/$@.c $(OBJ)/*.o -I $(INCLUDE) -o $(TEST)/bin/$@	
	$(TEST)/bin/$@	
	rm -rf $(TEST)/bin/*

# compilar /tests
# $(TEST)/bin/%: $(TEST)/%.c
# 	echo entrou
# 	gcc $(FLAGS) $< $(OBJ)/*.o -I $(INCLUDE) -o $@
# 	./$@
# 	rm -rf $(TEST)/bin/*

# Rodar o app: 
# $ make run
run:
	./$(APPNAME)

# Remover arquivos de compilação:
# $ make clean
clean:
	rm -rf $(APPNAME) $(OBJ)/* $(TEST)/bin/*