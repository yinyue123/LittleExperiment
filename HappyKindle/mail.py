#coding:utf-8
import sys
import smtplib
import traceback
from email.mime.text import MIMEText  # 引入smtplib和MIMEText

from email.mime.multipart import MIMEMultipart 
from email.mime.application import MIMEApplication 

#name mail position
#1    2    3

host = '127.0.0.1'  # 设置发件服务器地址
port = 25  # 设置发件服务器端口号。注意，这里有SSL和非SSL两种形式
sender = 'mail@wifewifi.com'  # 设置发件邮箱，一定要自己注册的邮箱
receiver = sys.argv[2] # 设置邮件接收人，可以是扣扣邮箱

#msg = MIMEText(body, 'html') # 设置正文为符合邮件格式的HTML内容
msg = MIMEMultipart()
msg['subject'] = sys.argv[1] # 设置邮件标题
msg['from'] = sender  # 设置发送人
msg['to'] = receiver  # 设置接收人

#part = MIMEText("乔装打扮，不择手段",'plain','gbk')
part = MIMEText("test",'plain','utf-8') 
msg.attach(part)

part = MIMEApplication(open(sys.argv[3],'rb').read()) 
part.add_header('Content-Disposition', 'attachment', filename=('utf-8','',sys.argv[1]))
msg.attach(part) 

try:
	s = smtplib.SMTP(host, port)  # 注意！如果是使用SSL端口，这里就要改为SMTP_SSL
	s.ehlo();
	s.sendmail(sender, receiver, msg.as_string())  # 发送邮件！
	print 'Done'
except smtplib.SMTPException:
	print 'Error'
	print traceback.format_exc()
