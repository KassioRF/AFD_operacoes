
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

all: clean dirs modulos afdtool
	@ echo :: MAKE SUCCESS

dirs:
	@ mkdir -p $(OBJ)/utils
	@ mkdir -p $(OBJ)/afd
	@ mkdir -p $(OBJ)/operacoes

modulos:	\
	src.afd/ \
	$(OBJ)/afd/afd.o \
	$(OBJ)/afd/leitura.o \
	$(OBJ)/afd/exportar.o \
	src.operacoes/ \
	$(OBJ)/operacoes/operacoes.o \
	$(OBJ)/operacoes/reconhecer_palavra.o \
	$(OBJ)/operacoes/complemento.o \
	$(OBJ)/operacoes/minimizar.o \
	$(OBJ)/operacoes/produto.o \
	src.utils/ \
	$(OBJ)/utils/argumentos.o \

src.%:
	@ echo ::::MODULOS $@
	
# ./src
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
#	@echo ::::MODULOS .src/:
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

# ./src/utils
$(OBJ)/utils/%.o: $(SRC)/utils/%.c $(INCLUDE)/utils/%.h
#	@echo ::::MODULOS .src/utils:
	gcc $(FLAGS) -c $< -I $(INCLUDE)/utils -o $@

# ./src/afd
$(OBJ)/afd/%.o: $(SRC)/afd/%.c $(INCLUDE)/afd/%.h
#	@echo ::::MODULOS .src/afd:
	gcc $(FLAGS) -c $< -I $(INCLUDE)/afd -o $@

# ./src/operacoes
$(OBJ)/operacoes/%.o: $(SRC)/operacoes/%.c $(INCLUDE)/operacoes/operacoes.h
#	@echo ::::MODULOS .src/operacoes:
	gcc $(FLAGS) -c $< -I $(INCLUDE)/operacoes -o $@


# compilando o app 
afdtool:
	@echo ::::APP:
	gcc $(FLAGS) $(APP)/$(APPNAME).c $(OBJ)/*/*.o \
	-I $(INCLUDE) \
	-o $(APPNAME)
	

test_%:	
	echo $@
	gcc $(FLAGS) $(TEST)/$@.c $(OBJ)/*/*.o -I $(INCLUDE) -o $(TEST)/bin/$@	
	$(TEST)/bin/$@	
	@ rm -rf $(TEST)/bin/*

# Rodar o app: 
# $ make run
run:
	./$(APPNAME)

# Remover arquivos de compilação:
# $ make clean
clean:
	rm -rf $(APPNAME) $(OBJ)/* $(TEST)/bin/*