for i in `cat $1`
do 
echo harvesting $i
cd $i
cp /home/miloc/yy/macros/make_up.C . 
root -b make_up.C
cat /home/miloc/yy/scripts/index.html | sed -e "s|-folder-|$i|g" > index.html
cd ../
done

/home/miloc/yy/scripts/higgs_hlt.sh
