class Demo extends Thread
{
	public void run()
	{
		for(int x=0; x<60; x++)
			System.out.println("demo run---"+x);
	}
}

class ThreadDemo
{
	public static void main(String[] args)
	{
		Demo d = new Demo();
		d.start();//启动线程
		//d.run();//执行函数
		for(int x=0; x<60; x++)
			System.out.println("hello world --"+x);
	}
}
