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

StarTroupial: main.o objectManager.o star.o asteroid.o ring.o starship.o bullet.o particle.o interactiveObject.o object.o collisionManager.o glm.o
	g++ -o StarTroupial main.o objectManager.o star.o asteroid.o ring.o starship.o bullet.o particle.o interactiveObject.o object.o collisionManager.o glm.o $(LDLIBS) -w
	rm *.o

objectManager.o: objectManager.cpp objectManager.h star.h asteroid.h ring.h starship.h
	g++-mp-4.6 -c objectManager.cpp -w

asteroid.o: asteroid.cpp asteroid.h particle.h interactiveObject.h
	g++ -c asteroid.cpp -w

ring.o: ring.cpp ring.h interactiveObject.h
	g++ -c ring.cpp -w

starship.o: starship.cpp starship.h bullet.h
	g++ -c starship.cpp -w

bullet.o: bullet.cpp bullet.h interactiveObject.h
	g++ -c bullet.cpp -w

particle.o: particle.cpp particle.h object.h
	g++ -c particle.cpp -w

star.o: star.cpp star.h object.h
	g++ -c star.cpp -w

interactiveObject.o: interactiveObject.cpp interactiveObject.h object.h
	g++ -c interactiveObject.cpp -w

object.o: object.cpp object.h collisionManager.h
	g++ -c object.cpp -w

collisionManager.o: collisionManager.cpp collisionManager.h glm.h
	g++ -c collisionManager.cpp -w

glm.o: glm.cpp glm.h
	g++ -c glm.cpp -w

clean:
	rm StarTroupial