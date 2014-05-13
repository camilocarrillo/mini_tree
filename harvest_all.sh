for folder in `cat $1`
do
echo $folder
cd $folder
./scripts/harvesting_index.sh scripts/Diphoton8TeVForHLT.txt
cd ../
done
