#!/bin/bash
echo "start" >> time.txt
date >>time.txt

for j in `ls -1 ~miloc/hlt/scripts/ggh_xa*`
do
    echo "executing $j"
    for i in `cat $j`
    do 
	echo "starting $i in $j"
	~miloc/hlt/scripts/execute_folder.sh $i > output.$i.txt &
	echo "finishing $i in $j"
    done
    echo "sleeping 30s"
    sleep 30s
done

~miloc/hlt/scripts/hadds.sh ~miloc/hlt/scripts/ggh_Diphoton8TeVForHLT.txt
~miloc/hlt/scripts/ggh_harvesting.sh ~miloc/hlt/scripts/ggh_Diphoton8TeVForHLT.txt
rm matrix -rf
mv ggh_matrix matrix
echo "stop" >> time.txt
date >>time.txt

