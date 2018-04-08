public class Test extends Thread
{
    private volatile boolean stop=false;
    public void stopMe()
    {
        stop=true;
    }
    @Override
    public void run()
    {
        int i=0;
        while(!stop)
        {
            i++;
        }
        System.out.println("Stop thread");
    }
    public static void main(String[] args)throws InterruptedException
    {
        System.out.println(Runtime.getRuntime().maxMemory());
        Test t=new Test();
        t.start();
        Thread.sleep(1000);
        t.stopMe();
        Thread.sleep(1000);
    }
}