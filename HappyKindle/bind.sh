#data=$(date +%Y%m%d)
#data="20111111"
#data2="20112222"
#if [ $data -ge $data2 ]
#then
#	echo 123
#fi
userid=$1
mail=${2##*+}

if [ ! -n "$mail" ]
then
	res=0
	cat user.csv | grep -q "^$userid,"  || res=1
	if [ $res -eq 1 ]
	then
		#echo "welcome new user"
		echo 'O(∩_∩)O'
		echo '欢迎关注HappyKinle'
		echo '回复 ? 可查看使用方法,快试试吧'
		#pwd
		echo "$userid,,0" >> user.csv
	else
		#echo "welcome back"
		echo '＼( ^▽^ )／'
		echo '你终于回来啦,真的好想你呀'
	fi
	#echo $userid
	exit
fi
res=0
echo $mail | grep -q '@kindle.cn$' || res=1
if [ $res -eq 1 ]
then
	#echo "wrong email"
	echo '(..•˘_˘•..)'
	echo '添加失败了,邮箱请以@kindle.cn结尾，再试试吧'
	exit
fi
#pwd
rm temp 2> /dev/null
#echo "user:"$userid
#echo "mail:"$mail
cat user.csv | while read line
do
	echo $line | grep "^$userid," > /dev/null 
	if [ $? -eq 0 ]
	then
		#echo "1"$line | sed "s/,.*,/,$mail,/"
		echo $line | sed "s/,.*,/,$mail,/" >> temp
	else
		#echo "0"$line
		echo $line >> temp
	fi
done
mv temp user.csv
#sed -i "/^$userid,/{s/,.*,/,$mail,/}" /var/www/html/book/user.csv 2>&1
#echo "bind $mail successfully"
echo '（＾∀＾）'
echo "绑定邮箱 $mail 成功,一定记得将mail@wifewifi.com和mail@happykindle.com加入你Kindle邮箱的收信白名单,不然你就收不到我发的邮件了"
