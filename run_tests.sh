#!/bin/bash
make clean; make;
for f in ./Tests/*.input; 
do 
  echo "Testing ${f%??????}";
  # ./qwirkle < $f;
  ./qwirkle < $f > ${f%??????}.gameout
  diff -w ${f%??????}.output ${f%??????}.gameout
  # if [-e ${f%??????}.expsave] diff -w -y ${f%??????}.expsave ${f%??????}.save
  echo -e "\n";
done