#!/bin/bash
MAX=0
ITERATIONS=0
LIMIT=700
FILE=problem_100
SUM=0
for i in {1..1000}
do
		export ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`
		if ../cmake-build-debug/pushswap $ARG | ./checker_Mac $ARG | grep -q KO
		then
			echo "Error!"
			echo $ARG
			break
		fi
		NUMBER="$(./push_swap $ARG | wc -l | sed 's/ //g')"
		if [ "$NUMBER" -gt "$LIMIT" ]
			then
			echo $NUMBER >> $FILE
			echo $ARG >> $FILE
		fi
		if [ "$NUMBER" -gt "$MAX" ]
			then
			MAX=$NUMBER;
		fi
		echo $i ":" $NUMBER
		let SUM+=$NUMBER;
		let ITERATIONS+=1
done
echo "AVG: $(($SUM / $ITERATIONS))"
echo "MAX: " $MAX