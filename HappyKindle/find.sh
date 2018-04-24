#echo "Search:"$1
echo "搜索:$1"
echo '下面这些都是我找到的呢'
echo '*\( ^ v ^ )/*"'
echo "-------------------"
cat list.csv | grep -i "$1" | sort -u | awk -F "," '{printf "%-20s\n NO.%-14s(%s)\n",$2,$1,$3}'| head -n 40 2>&1 
echo "-------------------"
#echo "Please choose the book you want and input @num"
echo '快选择一本你感兴趣的,回复 @书本编号 (例如 @123 ),我就把这本书推送到你的Kindle推送邮箱上(ฅ´ω`ฅ)'
echo '回复 ? 阅读使用帮助'
