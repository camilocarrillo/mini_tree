for folder in `cat $1`
do
echo starting $folder
cd $folder
rm macros scripts
cd ../
echo finishing $folder
done

#./scripts/parallel.sh
#./scripts/clean.sh
#cat template/READING_DIPHOTON_TREE.C | sed -e 's/hlt_bit=hlt_bit/hlt_bit=(bit194||bit195||bit205)/g' > template/READING_DIPHOTON_TREE.C_buff; mv template/READING_DIPHOTON_TREE.C_buff template/READING_DIPHOTON_TREE.C
#rm macros -rf
#rm scripts -rf 
#rm macros scripts -rf 
#rm scripts_minitree -rf
#ln -s ../macros_minitrees/ macros
#ln -s /home/miloc/yy/scripts_minitree/ scripts


