CXX = g++ 
CXXFLAGS = -std=gnu++0x -Os -w
#LDLIBS = -lglut -lGL -lGLU -lX11 -lm -L/usr/X11R6/lib -lopenal
LDLIBS = -framework OpenGL -framework GLUT -framework OpenAL 

build-exec = $(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^

.PHONY: all clean

all: StarTroupial
clean: ; rm -f ./*.o ./*.gch StarTroupial

%.o: %.cpp ; $(CXX) $(CXXFLAGS) $(LDLIBS) -c $<

StarTroupial: main.o objectManager.o star.o asteroid.o ring.o starship.o bullet.o explosionLight.o particle.o interactiveObject.o object.o collisionManager.o  soundManager.o glm.o; $(build-exec)
	
main.o: main.cpp objectManager.h
objectManager.o: objectManager.cpp objectManager.h
asteroid.o: asteroid.cpp asteroid.h
ring.o: ring.cpp ring.h
starship.o: starship.cpp starship.h
bullet.o: bullet.cpp bullet.h
explosionLight.o: explosionLight.cpp explosionLight.h
particle.o: particle.cpp particle.h
star.o: star.cpp star.h
interactiveObject.o: interactiveObject.cpp interactiveObject.h
object.o: object.cpp object.h
collisionManager.o: collisionManager.cpp collisionManager.h
soundManager.o: soundManager.cpp soundManager.h
glm.o: glm.cpp glm.h
