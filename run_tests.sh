#!/bin/bash

## Use latest compilation
make clean; make;

## Define diff and options
DIFF="/usr/bin/diff"
DIFF_OPTS="--brief --report-identical-files -w"

## Define colors
YELLOW='\033[1;33m'
NC='\033[0m'

## Check for colordiff
if [[ -f /usr/bin/colordiff ]]; then
  DIFF="/usr/bin/colordiff"
fi

## Run tests
for f in ./Tests/*.input; 
do 
  # Remove file extension
  FILENAME="${f%??????}"

  # Run tests
  echo -e "${YELLOW}Testing $FILENAME ${NC}";
  ./qwirkle < $f > $FILENAME.gameout
  $DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout | GREP_COLOR='1;32' grep -E --color 'identical' 
  $DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout | GREP_COLOR='1;31' grep -E --color 'differ' 
  if [[ -f $FILENAME.expsave ]]; then
    $DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save | GREP_COLOR='1;32' grep -E --color 'identical' 
    $DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save | GREP_COLOR='1;31' grep -E --color 'differ' 
  fi
  echo -e "\n";
done