
for i in `cat $1`
do 
echo "starting $i"
/home/miloc/yy/scripts/execute_folder.sh $i > output.$i.txt 
echo "finishing $i"
done
/home/miloc/yy/scripts/hadds.sh $1





