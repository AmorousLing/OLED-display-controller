package com.example.test2;

import android.app.Application;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MyApplication extends Application {

    private static MqttClient client;
    private final String host = "tcp://broker.emqx.io:1883";
    private final String ClientId = "maqttxlapp";
    @Override
    public void onCreate() {
        super.onCreate();

        // 初始化 sessionString
        try {
            client =  new MqttClient(host, ClientId, new MemoryPersistence());
        } catch (MqttException e) {
            throw new RuntimeException(e);
        }

    }
    // 访问 sessionString 的方法
    public static MqttClient getSessionString() {
        return client;
    }
    // 设置 sessionString 的方法
    public void setSessionString(MqttClient client) {
        this.client = client;
    }
}
