CXX = g++
CXXFLAGS = -std=c++14 -MMD
OBJECTS = main.o addtext.o game.o player.o board.o box.o piece.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
