all: compile link run

compile:
	g++ -c game.cpp game_tile.cpp game_world.cpp character.cpp main.cpp -I"C:\libraries\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ game.o game_tile.o game_world.o character.o main.o -o Sverrin -L"C:\libraries\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

run:
	./Sverrin

clean:
	rm -f Sverrin *.o