package com.monitorhandler;

/*使用lambda 方式實作一個伺服器監控系統*/
public class MonitorHandler {
    static void main(String[] args) {

    }


}

interface monitorHandler{
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