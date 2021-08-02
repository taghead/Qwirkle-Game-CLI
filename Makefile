define testScript =
	DIFF="/usr/bin/diff"
	DIFF_OPTS="--brief --report-identical-files -w"

	## Define colors
	YELLOW='\033[1;33m'
	GREEN='\033[1;32m'
	RED='\033[1;31m'
	NC='\033[0m'

	## Counters

	FAILED=0
	PASSED=0

	## Run tests
	for f in ./tests/*.input; 
	do 
	  # Remove file extension
		FILENAME="${f%??????}"

		# Run tests
		echo "${YELLOW}Testing $FILENAME ${NC}";
		./qwirkle < $FILENAME.input > $FILENAME.gameout
		if $DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout | \
													GREP_COLOR='1;32' grep -E --color 'identical' ; then
				PASSED=$((PASSED=PASSED+1))
		else
				FAILED=$((FAILED=FAILED+1))
		fi
		$DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout | \
																		GREP_COLOR='1;31' grep -E --color 'differ'
		if [ -f $FILENAME.expsave ]; then
			if	$DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save | \
													GREP_COLOR='1;32' grep -E --color 'identical' ; then
					PASSED=$((PASSED=PASSED+1))
			else
					FAILED=$((FAILED=FAILED+1))
			fi
			$DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save | \
																		GREP_COLOR='1;31' grep -E --color 'differ'
		fi
		echo "\n";
	done
	echo "${GREEN}\n \nTESTS PASSED: $PASSED ${RED}\nTESTS FAILED: $FAILED${NC}";
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