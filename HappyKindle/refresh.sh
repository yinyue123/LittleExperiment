find /var/book/* | while read line
do
	name=${line##*/}
	postion=$(echo $line | sed "s/ /\\ /g")
	size=$(du -sh "$postion" | awk '{print $1}')
	echo -e "$name,$size,$postion"  >> temp
done
rm list.csv
i=0
sort -u temp | while read line
do
	((i++));
	echo $i,$line>>list.csv
done
rm temp
echo "refresh successfully"	
