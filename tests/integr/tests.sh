#!/usr/bin/env bash

# This script is used to run the integration tests for the
path="./build/exe/wrapper"

# Set up the binaries. Used to run this code to rebuild project every time I ran the tests
# You may uncomment this code to enable this feature
#mkdir -p "build"
#cd "build"
#cmake .. > /dev/null
#make > /dev/null
#cd ..

# Run all the tests

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
