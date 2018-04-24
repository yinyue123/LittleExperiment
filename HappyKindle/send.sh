user=$1
name=${2##*@}
line=$(cat list.csv | head -n $name | tail -n 1)
text=${line%%,*}
user='^'$user','
mail=$(cat user.csv | grep $user | awk -F "," '{print $2}')
exist=$(echo $mail | wc -c)
if [[ $exist -eq 1 ]]
then
	#echo "Please bind your kindle email and we will send the book to your device.Reply +email and we will bind it"
	echo '（⊙.⊙）'
	echo '推送失败,你还没绑定你的Kindle邮箱呢,快回复 +邮箱 绑定你的邮箱吧(例如+happy@kindle.cn),回复 ? 可获取更多帮助'
	exit
else
	#echo "An email has been send to $mail ,Please check you device"
	echo '｡:.ﾟヽ(｡◕‿◕｡)ﾉﾟ.:｡+ﾟ'
	echo "我已经把这本书发送到邮箱$mail,快打开你的Kindle看看吧"
fi
position=${line##*,}
position2=$(echo $position | sed "s/ /\\ /g")
book=${position2##*/}
###########
#url=$(php urlencode.php $position2)
#echo "http://wifewifi.com/book/"$url
###########
#echo $book
#echo $mail
#echo $position2
python mail.py "$book" "$mail" "$position2" 2>&1
