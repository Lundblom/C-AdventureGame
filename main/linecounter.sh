#!/bin/bash
counter=0
for f in include/*
do
	while read -r line
	do
		counter=$((counter+1))
	done < "$f"
done


for f in *.cpp
do
        while read -r line
        do
                counter=$((counter+1))
        done < "$f"
done

echo $counter
