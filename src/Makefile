all: markdown-cpp

markdown-cpp: parse_markdown.o Md_file.o main.o
	g++ -o markdown-cpp parse_markdown.o Md_file.o main.o

parse_markdown.o: parse_markdown.cpp
	g++ -o parse_markdown.o -c parse_markdown.cpp -W -Wall -ansi -pedantic
	
Md_file.o: Md_file.cpp
	g++ -o Md_file.o -c Md_file.cpp -W -Wall -ansi -pedantic
	
main.o: main.cpp parse_markdown.h
	g++ -o main.o -c main.cpp -W -Wall -ansi -pedantic
	
remove: clean realclean

clean:
	rm -f *.o

rmprg:
	rm -f markdown-cpp	

realclean: clean rmprg