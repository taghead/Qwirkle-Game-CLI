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
  $DIFF $DIFF_OPTS $FILENAME.output $FILENAME.gameout
  if [[ -f $FILENAME.expsave ]]; then
    $DIFF $DIFF_OPTS $FILENAME.expsave $FILENAME.save
  fi
  echo -e "\n";
done