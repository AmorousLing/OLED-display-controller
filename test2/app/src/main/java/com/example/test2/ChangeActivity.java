package com.example.test2;
import android.app.Activity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class ChangeActivity extends Activity {
    private Button moverview;
    private Button mtemperature;
    private Button mweather;
    private Button mhumidity;
    private Button mmessage;
    private String content1 ="pg0";
    private MqttClient client;
    String pubTopic = "aaax";
    int qos = 2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change);
        moverview=findViewById(R.id.overview);
        mweather=findViewById(R.id.weather);
        mtemperature=findViewById(R.id.temperature);
        mhumidity=findViewById(R.id.humidity);
        mmessage=findViewById(R.id.message);
        client = MyApplication.getSessionString();
        //发送消息
        moverview.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content1 = "pg0";
                MqttMessage message = new MqttMessage(content1.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mweather.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content1 = "pg1";
                MqttMessage message = new MqttMessage(content1.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mtemperature.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content1 = "pg2";
                MqttMessage message = new MqttMessage(content1.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mhumidity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content1 = "pg3";
                MqttMessage message = new MqttMessage(content1.getBytes());
                message.setQos(qos);
                try {

                    client.publish(pubTopic, message);
                } catch (MqttException e) {
                    throw new RuntimeException(e);
                }
                System.out.println("Message published");
            }
        });
        mmessage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                content1 = "pg4";
                MqttMessage message = new MqttMessage(content1.getBytes());
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
