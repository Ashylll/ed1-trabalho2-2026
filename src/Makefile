PROJ_NAME= ted
ALUNO= Ashley
LIBS= -lm
OBJETOS= main.o circulo.o retangulo.o linha.o texto.o forma.o arvore.o svg.o sorting.o leitura_geo.o processa_qry.o

CC=gcc
CFLAGS= -std=c99 -fstack-protector-all -ggdb -O0 -Werror=implicit-function-declaration -I. -I./unity -DUNITY_INCLUDE_DOUBLE
LDFLAGS= -O0
VG = valgrind --log-file="valgrind_log" --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Dependências dos objetos
main.o: main.c arvore.h svg.h sorting.h leitura_geo.h processa_qry.h
circulo.o: circulo.c circulo.h
retangulo.o: retangulo.c retangulo.h
linha.o: linha.c linha.h
texto.o: texto.c texto.h
forma.o: forma.c forma.h circulo.h retangulo.h linha.h texto.h
svg.o: svg.c svg.h arvore.h
sorting.o: sorting.c sorting.h forma.h arvore.h
leitura_geo: leitura_geo.c leitura_geo.h forma.h circulo.h retangulo.h linha.h texto.h arvore.h
processa_qry.o: processa_qry.c processa_qry.h forma.h retangulo.h arvore.h sorting.h processa_qry.h


TESTES = teste_circulo teste_retangulo teste_linha teste_texto teste_forma teste_arvore teste_sorting teste_leitura_geo teste_processa_qry

# Regra para compilar e rodar todos os testes 
tstall: $(TESTES)
	@echo "Executando todos os testes unitários..."
	@for t in $(TESTES); do ./$$t; done

teste_circulo: circulo.o unity.o t_circulo.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_retangulo: retangulo.o unity.o t_retangulo.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_linha: linha.o unity.o t_linha.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_texto: texto.o unity.o t_texto.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_forma: forma.o circulo.o retangulo.o linha.o texto.o unity.o t_forma.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_arvore: arvore.o svg.o circulo.o retangulo.o linha.o texto.o forma.o sorting.o leitura_geo.o unity.o t_arvore.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_svg: svg.o circulo.o retangulo.o linha.o texto.o forma.o arvore.o sorting.o unity.o t_svg.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_sorting: sorting.o retangulo.o circulo.o texto.o linha.o forma.o svg.o arvore.o leitura_geo.o unity.o t_sorting.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS) 	

teste_leitura_geo: leitura_geo.o svg.o circulo.o retangulo.o linha.o texto.o forma.o arvore.o sorting.o unity.o t_leitura_geo.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_processa_qry: processa_qry.o leitura_geo.o svg.o circulo.o retangulo.o linha.o texto.o forma.o arvore.o sorting.o unity.o t_processa_qry.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^ $(LIBS)


.PHONY: clean run memcheck tstall

clean:
	rm -rf *.o $(PROJ_NAME) $(TESTES) valgrind_log

run: $(PROJ_NAME)
	./$(PROJ_NAME)

memtest:
	$(VG) ./$(T)
	
memcheck: $(PROJ_NAME)
	$(VG) ./$(PROJ_NAME)