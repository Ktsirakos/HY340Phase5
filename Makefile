all: al exe run

exe: al
	./al test.alpha

compiler: VM.c
	gcc -g VM.c

run: binary.abc compiler
	./a.out

al: parser.o lex.yy.o
	gcc -g -o al lex.yy.o parser.o


lex.yy.o: lex.yy.c
	gcc -c -g lex.yy.c

lex.yy.c: in.l
	flex in.l


parser.o: parser.c
	gcc -c -g parser.c

parser.c: parser.y
	bison -v --yacc --defines --output=parser.c parser.y


clean:
	rm lex.yy.*
	rm parser.c
	rm parser.h
	rm parser.o
	rm al


debug:lex.yy.c
	gcc -g lex.yy.c

save:
	./save.sh
