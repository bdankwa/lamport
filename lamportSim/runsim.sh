#!/bin/bash
numIter=1000000
byztProb=(10 1000 10000)
eventProb=(1 2 3 4 5)

p0='process_0'
p1='process_1'
p2='process_2'
p3='process_3'

for i in "${byztProb[@]}" 
do
	for j in "${eventProb[@]}" 
	do
		echo "Running simulation with" $numIter "iterations, with event prob" "$j" "and bzt prob" "$i".
		./lmptSim $numIter "$j" "$i" 
		mv $p0 $p0"_"$i"_"$j
	done
done
