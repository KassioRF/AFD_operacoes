
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
	@echo ::::MODULOS .src/:
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(OBJ)/utils/%.o: $(SRC)/utils/%.c $(INCLUDE)/utils/%.h
	@echo ::::MODULOS .src/utils:
	gcc $(FLAGS) -c $< -I $(INCLUDE)/utils -o $@


# compilando o app 
afdtool:
	@echo ::::APP:
	gcc $(FLAGS) $(APP)/$(APPNAME).c $(OBJ)/*.o $(OBJ)/*/*.o \
	-I $(INCLUDE) -o \
	 $(APPNAME)


test_%:	
	echo $@
	gcc $(FLAGS) $(TEST)/$@.c $(OBJ)/*.o $(OBJ)/*/*.o -I $(INCLUDE) -o $(TEST)/bin/$@	
	$(TEST)/bin/$@	
	rm -rf $(TEST)/bin/*

# Rodar o app: 
# $ make run
run:
	./$(APPNAME)

# Remover arquivos de compilação:
# $ make clean
clean:
	rm -rf $(APPNAME) $(OBJ)/* $(TEST)/bin/*