CXX = g++ 
CXXFLAGS = -Os -w

#LDLIBS = -lglut -lGL -lGLU -lX11 -lm -L/usr/X11R6/lib
LDLIBS = -framework OpenGL -framework GLUT

ifeq ($(MUSIC), m)
#	LDLIBS = -lglut -lGL -lGLU -lX11 -lm -L/usr/X11R6/lib -lopenal
	LDLIBS = -framework OpenGL -framework GLUT -framework OpenAL
endif

build-exec = $(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^

.PHONY: all clean

all: playGame

clean: ; rm -f ./*.o ./*.gch playGame

%.o: %.cpp ; $(CXX) $(CXXFLAGS) $(LDLIBS) -c $<

playGame: main.o objectManager.o skyroof.o grassfloor.o star.o asteroid.o building.o ring.o starship.o bullet.o explosionLight.o particle.o interactiveObject.o object.o collisionManager.o shadowManager.o textureManager.o soundManager.o glm.o Texture.o; $(build-exec)
	
main.o: main.cpp objectManager.h
objectManager.o: objectManager.cpp objectManager.h
asteroid.o: asteroid.cpp asteroid.h
ring.o: ring.cpp ring.h
building.o: building.cpp building.h
starship.o: starship.cpp starship.h
bullet.o: bullet.cpp bullet.h
explosionLight.o: explosionLight.cpp explosionLight.h
particle.o: particle.cpp particle.h
star.o: star.cpp star.h
grassfloor.o: grassfloor.cpp grassfloor.h
skyroof.o: skyroof.cpp skyroof.h
interactiveObject.o: interactiveObject.cpp interactiveObject.h
object.o: object.cpp object.h
collisionManager.o: collisionManager.cpp collisionManager.h
textureManager.o: textureManager.cpp textureManager.h
shadowManager.o: shadowManager.cpp shadowManager.h
soundManager.o: soundManager.cpp soundManager.h config.h
glm.o: glm.cpp glm.h
Texture.o: Texture.cpp Texture.h
