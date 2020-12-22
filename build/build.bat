@ECHO off

ECHO ---------------------
ECHO [Building]
g++ -Wall -o main.exe ../test/test.cpp ../src/FTiler.cpp -I..\SFML\include -L..\SFML\lib -lsfml-window -lsfml-system -lsfml-graphics && (
	ECHO [Build Successfully Completed]
	ECHO ---------------------
	ECHO [Running]
	main.exe && ECHO [Program Finished]|| ECHO [Program Stopped]
) || (
	ECHO [Build Failed]
)
ECHO ---------------------
