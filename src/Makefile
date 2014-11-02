SRC= Md_file.cpp parse_markdown.cpp main.cpp
OBJ= $(SRC:.c=.o)

all: markdown-cpp

markdown-cpp: $(OBJ)
	g++ -o $@ $^

%.o: %.cpp
	g++ -o $@ -c $^ -W -Wall -ansi -pedantic
	
remove: clean realclean

clean:
	rm -f *.o

rmprg:
	rm -f markdown-cpp	

realclean: clean rmprg