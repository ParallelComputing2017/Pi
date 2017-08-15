#!/bin/bash

for t in {1..16}
do
	time -p ./Debug/Posix pi $t
	printf "\n"
done
