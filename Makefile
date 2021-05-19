define testScript =
	DIFF="/usr/bin/diff"
	DIFF_OPTS="--brief --report-identical-files -w"
	## Define colors
	YELLOW='\033[1;33m'
	NC='\033[0m'

	## Run tests
	for f in ./Tests/*.input; 
	do 
	  # Remove file extension
		FILENAME="${f%??????}"

		# Run tests
		echo "${YELLOW}Testing $FILENAME ${NC}";
		./qwirkle < $f > $FILENAME.gameout
		$DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout | GREP_COLOR='1;32' grep -E --color 'identical' 
		$DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout | GREP_COLOR='1;31' grep -E --color 'differ' 
		if [ -f $FILENAME.expsave ]; then
			$DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save | GREP_COLOR='1;32' grep -E --color 'identical' 
			$DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save | GREP_COLOR='1;31' grep -E --color 'differ' 
		fi
		echo "\n";
	done
endef

.default: all

all: qwirkle runtests

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o GameEngine.o Player.o qwirkle.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

runtests: ; $(value testScript)

.ONESHELL: