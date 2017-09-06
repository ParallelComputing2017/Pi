#!/bin/bash

for t in {1..16}
do
	./Debug/Pi all $t
	printf "\n"
done
