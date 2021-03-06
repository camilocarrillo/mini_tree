echo "start" >> time.txt
date >>time.txt

for j in `ls -1 ~miloc/hlt/scripts/xa*`
do
    echo "executing $j"
    for i in `cat $j`
    do 
	echo "starting $i in $j"
	~miloc/hlt/scripts/execute_folder.sh $i > output.$i.txt &
	echo "finishing $i in $j"
    done
    echo "sleeping 80s"
    sleep 80
done

~miloc/hlt/scripts/hadds.sh ~miloc/hlt/scripts/Diphoton8TeVForHLT.txt

~miloc/hlt/scripts/harvesting.sh ~miloc/hlt/scripts/Diphoton8TeVForHLT.txt

echo "stop" >> time.txt
date >>time.txt

