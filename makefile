all: cards cardactions gamecontrol gameio gameutilities entry

cards:
	g++ -o ./tmp/Cards.o -c ./code/src/Cards.cpp -I ./code/header

gameutilities:
	g++ -o ./tmp/GameUtilities.o -c ./code/src/GameUtilities.cpp -I ./code/header

test:
	g++ -o ./bin/test.exe -I ./code/header ./code/src/test.cpp ./tmp/*
	./bin/test.exe
