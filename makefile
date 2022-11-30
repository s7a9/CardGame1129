all: cards cardactions gamecontrol gameio gameutilities entry

gameutilities:
	g++ -o ./tmp/GameUtilities.o -c ./code/src/GameUtilities.cpp -I ./code/header

test:
	g++ -o ./bin/test.exe -I ./code/header ./code/src/test.cpp ./tmp/*
	./bin/test.exe
