#!/usr/bin/env bash

# This script is used to run the integration tests for the
path="./build/exe/wrapper"

# Set up the binaries
mkdir -p "build"
cd "build"
cmake .. > /dev/null
make > /dev/null
cd ..

# Run all the tests

output=$($path <"tests/integr/inputs/01.in")
if [[ $? != 0 ]]; then
  echo "FAILED"
else
  expected="Meow!"

  if [[ $output == "$expected" ]]; then
    echo "OK"
  else
    echo "FAILED"
  fi
fi

output=$($path < "tests/integr/inputs/02.in")
if [[ $? != 0 ]]; then
  echo "FAILED"
else
  expected=$'Woof!\nMeow!'

  if [[ $output == "$expected" ]]; then
    echo "OK"
  else
    echo "FAILED"
  fi
fi

output=$($path < "tests/integr/inputs/03.in")
if [[ $? != 0 ]]; then
  echo "FAILED"
else
  expected=$'Goodbye!'

  if [[ $output == "$expected" ]]; then
    echo "OK"
  else
    echo "FAILED"
  fi
fi

# Check with the valgrind

if valgrind --log-file="/dev/null" --leak-check=full --error-exitcode=1 $path < "tests/integr/inputs/02.in" > /dev/null;
 then
  echo "OK"
else
  echo "FAILED"
fi
