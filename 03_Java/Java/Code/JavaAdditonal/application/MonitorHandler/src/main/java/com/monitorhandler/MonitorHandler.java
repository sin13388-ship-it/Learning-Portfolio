package com.monitorhandler;

import java.util.ArrayList;
import java.util.List;

/*使用lambda 方式實作一個伺服器監控系統*/
public class MonitorHandler {
    static void main(String[] args) {

        /*字串比較要用.equals*/
        iMonitorHandler cpuHandler = event -> {
            if("CPU".equals(event.type) && event.value >90 )
                System.out.println(event.type + ",[ALERT]  CPU 超標：" + event.value + "%");
        };
        iMonitorHandler diskHandler = event -> {
            if("DISK".equals(event.type) && event.value >80 )
                System.out.println(event.type + ",[ALERT] 記憶體不足：" + event.value + "%");
        };

        EventDispatcher monitor =new EventDispatcher();

        //monitor.register(cpuHandler);
        //monitor.register(diskHandler);

        monitor.register(event -> {
            if("CPU".equals(event.type) && event.value >90 )
                System.out.println(event.type + ",[ALERT]  CPU 超標：" + event.value + "%");
        });
        monitor.register(event -> {
            if("DISK".equals(event.type) && event.value >80 )
                System.out.println(event.type + ",[ALERT] 記憶體不足：" + event.value + "%");
        });
        monitor.register(event -> {
            if (event.value > 95 && "MEM".equals(event.type)) {
                System.out.println(event.type + ",[CRITICAL] 磁碟空間嚴重不足！");
            }
        });

        monitor.dispatch(new ServerEvent("CPU", 78));
        monitor.dispatch(new ServerEvent("DISK", 68));
        monitor.dispatch(new ServerEvent("CPU", 92.3));
        monitor.dispatch(new ServerEvent("DISK", 82));
        monitor.dispatch(new ServerEvent("MEM", 98.5));
    }
}

interface iMonitorHandler{
    void handle(ServerEvent event);
}

class ServerEvent{
    String type;
    double value;
    long timeStamp;
    //Constructor
    ServerEvent(String type, double value){
        this.type=type;
        this.value=value;
        this.timeStamp=System.currentTimeMillis();
    }
}

class EventDispatcher{
    private List<iMonitorHandler> handlers= new ArrayList<>();
    public  void register(iMonitorHandler monitor){
        handlers.add(monitor); //contains 直接傳入匿名 lambda，防呆會沒有作用，除非使用具名
    }
    public void dispatch(ServerEvent e){
        for(var m : handlers ){
            m.handle(e);
        }
    }
}