user=$1
name=${2##*@}
#echo $line
cat list.csv | while read line
do
	text=${line%%,*}
	if [[ "$name" -eq "$text" ]]
	then
		user='^'$user','
		mail=$(cat user.csv | grep $user | awk -F "," '{print $2}')
		exist=$(echo $mail | wc -c)
		if [[ $exist -eq 1 ]]
		then
			echo "Please bind your kindle email and we will send the book to your device.Reply +email and we will bind it"
		else
			echo "An email has been send to $mail,Please check you device"
		fi
		postion=${line##*,}
		#echo $postion
		postion2=$(echo $postion | sed "s/ /\\ /g")
		url=$(php urlencode.php $postion2)
		echo "http://wifewifi.com/book/"$url
	fi
done
#temp=$(cat list.csv | awk -F ',' 'NR==${{line}}{print $4}')
#temp=$(cat list.csv | head $line)
#echo $temp

