all: cards cardactions gamecontrol gameio gameutilities playerdef entry

COMPILER_PATH = g++

cards:
	$(COMPILER_PATH) -o ./tmp/Cards.o -c ./code/src/Cards.cpp -I ./code/header -O2

cardactions:
	$(COMPILER_PATH) -o ./tmp/CardActions.o -c ./code/src/CardActions.cpp -I ./code/header -O2

gamecontrol:
	$(COMPILER_PATH) -o ./tmp/GameControl.o -c ./code/src/GameControl.cpp -I ./code/header -O2

gameio:
	$(COMPILER_PATH) -o ./tmp/GameIO.o -c ./code/src/GameIO.cpp -I ./code/header -O2

gameutilities:
	$(COMPILER_PATH) -o ./tmp/GameUtilities.o -c ./code/src/GameUtilities.cpp -I ./code/header -O2

playerdef:
	$(COMPILER_PATH) -o ./tmp/PlayerDef.o -c ./code/src/PlayerDef.cpp -I ./code/header -O2

entry:
	$(COMPILER_PATH) -o ./bin/cardgame.exe -I ./code/header ./code/src/entry.cpp ./tmp/* -O2
	rm ./tmp/*
	./bin/cardgame.exe

test:
	$(COMPILER_PATH) -o ./bin/test.exe -I ./code/header ./code/src/test.cpp ./tmp/*
	./bin/test.exe
