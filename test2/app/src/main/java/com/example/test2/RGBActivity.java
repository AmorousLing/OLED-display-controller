package com.example.test2;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;


public class RGBActivity extends Activity {
    private Button mgo_off;
    private Button mlight_b;
    private Button mlight_g;
    private Button mlight_r;
    String content ="cl0";
    private MqttClient client;
    String pubTopic = "aaax";
    int qos = 2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rgb);
        mgo_off=findViewById(R.id.go_off);
        mlight_b=findViewById(R.id.light_b);
        mlight_g=findViewById(R.id.light_g);
        mlight_r=findViewById(R.id.light_r);
        client = MyApplication.getSessionString();
        //发送消息
        mgo_off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content = "cl0";
                MqttMessage message = new MqttMessage(content.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mlight_b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content = "cl1";
                MqttMessage message = new MqttMessage(content.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mlight_g.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content = "cl2";
                MqttMessage message = new MqttMessage(content.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mlight_r.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content = "cl3";
                MqttMessage message = new MqttMessage(content.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
}
}




