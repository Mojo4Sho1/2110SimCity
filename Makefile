++ = g++
++FLAGS = -w -Wall

default: SimCity clean

SimCity: main.o Cell.o City.o Residential.o Commercial.o Industrial.o PowerPlant.o PowerLine.o Combo.o Worker.o Good.o
	$(++) $(++FLAGS) main.o Cell.o City.o Residential.o Commercial.o Industrial.o PowerPlant.o PowerLine.o Combo.o Worker.o Good.o -o SimCity

main.o: main.cpp
	$(++) $(++FLAGS) -c main.cpp

Cell.o: Cell.cpp Cell.h
	$(++) $(++FLAGS) -c Cell.cpp

City.o: City.cpp *.h
	$(++) $(++FLAGS) -c City.cpp

Residential.o: Residential.cpp Residential.h
	$(++) $(++FLAGS) -c Residential.cpp

Commercial.o: Commercial.cpp Commercial.h
	$(++) $(++FLAGS) -c Commercial.cpp

Industrial.o: Industrial.cpp Industrial.h
	$(++) $(++FLAGS) -c Industrial.cpp

PowerPlant.o: PowerPlant.cpp PowerPlant.h
	$(++) $(++FLAGS) -c PowerPlant.cpp

PowerLine.o: PowerLine.cpp PowerLine.h
	$(++) $(++FLAGS) -c PowerLine.cpp

Combo.o: Combo.cpp Combo.h
	$(++) $(++FLAGS) -c Combo.cpp

Worker.o: Worker.cpp Worker.h
	$(++) $(++FLAGS) -c Worker.cpp

Good.o: Good.cpp Good.h
	$(++) $(++FLAGS) -c Good.cpp

clean:
	rm -f *.o