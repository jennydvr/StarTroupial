# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c file under linux.
#   check the location of the X libraries on your implementation.
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.c is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files

#LDLIBS = -lglut -lGL -lGLU -lX11  -lm -L/usr/X11R6/lib
LDLIBS = -framework OpenGL -framework GLUT

StarTroupial: main.o objectManager.o star.o ring.o starship.o glm.o
	g++ -o StarTroupial main.o objectManager.o star.o ring.o starship.o glm.o $(LDLIBS) -w
	rm *.o

objectManager.o: objectManager.cpp objectManager.h star.h ring.h starship.h glm.h
	g++ -c objectManager.cpp -w

star.o: star.cpp star.h glm.h
	g++ -c star.cpp -w

ring.o: ring.cpp ring.h glm.h
	g++ -c ring.cpp -w

starship.o: starship.cpp starship.h glm.h
	g++ -c starship.cpp -w

glm.o: glm.cpp glm.h
	g++ -c glm.cpp -w

clean:
	rm StarTroupial