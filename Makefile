
APPNAME = afdtool
 
APP = ./app
BIN = ./bin
# todos .h dentro de ./includes
INCLUDE = ./src/include
LIB = ./lib
OBJ = ./obj
SRC = ./src


# Flags
FLAGS = -O3 -Wall

all: clean dirs modulos afdtool
	@ echo :: MAKE SUCCESS

dirs:
	@ mkdir -p $(OBJ)/utils
	@ mkdir -p $(OBJ)/afd
	@ mkdir -p $(OBJ)/operacoes

modulos:	\
	src.utils/ \
	$(OBJ)/utils/str_utils.o \
	$(OBJ)/utils/particoes.o \
	src.afd/ \
	$(OBJ)/afd/afd.o \
	$(OBJ)/afd/leitura.o \
	$(OBJ)/afd/exportar.o \
	$(OBJ)/afd/escrever.o \
	$(OBJ)/operacoes.o \
	src.operacoes/ \
	$(OBJ)/operacoes/minimizar.o \
	$(OBJ)/operacoes/reconhecer_palavra.o \
	$(OBJ)/operacoes/complemento.o \



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
$(OBJ)/operacoes/%.o: $(SRC)/operacoes/%.c $(INCLUDE)/operacoes/%.h
#	@echo ::::MODULOS .src/operacoes:
	gcc $(FLAGS) -c $< -I $(INCLUDE)/operacoes -o $@


# compilando o app 
afdtool:
	@echo ::::APP:
	gcc $(FLAGS) $(APP)/$(APPNAME).c $(OBJ)/*/*.o $(OBJ)/*.o \
	-I $(INCLUDE) \
	-o $(APPNAME)
	

# Rodar o app: 
run:
	./$(APPNAME) --dot afd.txt --output afd.dot

reconhecer:
	./$(APPNAME) --reconhecer afd.txt palavras.txt --output resultados/palavras-reconhecidas.txt

exportar:
	./$(APPNAME) --dot afd.txt --output resultados/afd.dot

complemento:
	./$(APPNAME) --complemento afd.txt --output resultados/afd-complemento.txt

minimizar:
	./$(APPNAME) --minimizacao afd.txt --output resultados/afd-minimizacao.txt

# Remover arquivos de compilação:
# $ make clean
clean:
	rm -rf $(APPNAME) $(OBJ)/*