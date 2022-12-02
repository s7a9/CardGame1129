all: cards cardactions gamecontrol gameio gameutilities playerdef entry clean

cards:
	g++ -o ./tmp/Cards.o -c ./code/src/Cards.cpp -I ./code/header

cardactions:
	g++ -o ./tmp/CardActions.o -c ./code/src/CardActions.cpp -I ./code/header

gamecontrol:
	g++ -o ./tmp/GameControl.o -c ./code/src/GameControl.cpp -I ./code/header

gameio:
	g++ -o ./tmp/GameIO.o -c ./code/src/GameIO.cpp -I ./code/header

gameutilities:
	g++ -o ./tmp/GameUtilities.o -c ./code/src/GameUtilities.cpp -I ./code/header

playerdef:
	g++ -o ./tmp/PlayerDef.o -c ./code/src/PlayerDef.cpp -I ./code/header

entry:
	g++ -o ./bin/cardgame.exe -I ./code/header ./code/src/entry.cpp ./tmp/*
	./bin/cardgame.exe

test:
	g++ -o ./bin/test.exe -I ./code/header ./code/src/test.cpp ./tmp/*
	./bin/test.exe
