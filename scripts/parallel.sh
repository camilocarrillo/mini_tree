echo "start" >> time.txt
date >>time.txt

for j in `ls -1 /home/miloc/yy/scripts/xa*`
do
    echo "executing $j"
    for i in `cat $j`
    do 
	echo "starting $i in $j"
	/home/miloc/yy/scripts/execute_folder.sh $i > output.$i.txt &
	echo "finishing $i in $j"
    done
    echo "sleeping 90s"
    sleep 90
done

/home/miloc/yy/scripts/hadds.sh /home/miloc/yy/scripts/Diphoton8TeVForHLT.txt
/home/miloc/yy/scripts/harvesting.sh /home/miloc/yy/scripts//scripts/Diphoton8TeVForHLT.txt

echo "stop" >> time.txt
date >>time.txt
