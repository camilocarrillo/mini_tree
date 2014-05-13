for i in `cat $1`
do 
cd $i
#cp ../template/make_up.C . 
#root -b make_up.C
cat ../scripts/index.html | sed -e "s|-folder-|$i|g" > index.html
cd ../
done



