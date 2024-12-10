package com.example.test2;
import android.annotation.SuppressLint;
import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.widget.Button;
import android.widget.Toast;
import androidx.annotation.Nullable;
import org.eclipse.paho.client.mqttv3.*;
import java.util.concurrent.ScheduledExecutorService;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public  class MQTTService extends Service {
    //声明控件
    private ScheduledExecutorService reconnectScheduler;
    private Handler handler;
    private MqttClient client;
    private final String host = "tcp://broker.emqx.io:1883";
    private final String userName = "xl";
    private final String passWord = "xl";
    private final String ClientId = "maqttxlapp";
    private final String mqtt_sub_topic = "espxl";//订阅话题
    private final String mqtt_pub_topic = "espsub";//发布话题
    private MqttConnectOptions mqttConnectOptions;
    private Button mlink;
    @Override
    public void onCreate() {
        super.onCreate();
        Mqtt_init();
        Mqtt_connect();
        handler = new Handler(Looper.myLooper()) {//用于处理
            @SuppressLint("SetTextI18n")
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case 1: //开机校验更新回传
                        break;
                    case 2:  // 反馈回传
                        break;
                    case 3:  //MQTT 收到消息回传
                        System.out.println(msg.obj.toString());   // 显示MQTT数据
                        break;
                    case 31:   //连接成功
                        //Toast.makeText(getApplicationContext(), "连接成功！", Toast.LENGTH_SHORT).show();
                        try {
                            client.subscribe(mqtt_sub_topic, 1);//订阅
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                        break;
                    case 30:  //连接失败
                        Toast.makeText(getApplicationContext(), "连接失败！", Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        break;
                }
            }
        };
    }

    @Nullable


    public void Mqtt_init() {
        try {

            client = MyApplication.getSessionString();
            //MQTT的连接设置
            mqttConnectOptions = new MqttConnectOptions();
            //在重启和连接时记住状态
            mqttConnectOptions.setCleanSession(true);
            mqttConnectOptions.setUserName(userName);
            mqttConnectOptions.setPassword(passWord.toCharArray());
            mqttConnectOptions.setConnectionTimeout(10);
            // 设置会话心跳时间 单位为秒 服务器会每隔1.5*30秒的时间向客户端发送个消息判断客户端是否在线
            //由于自身网络延时很难确定，建议设大一点，防止断开连接后无法重连
            mqttConnectOptions.setKeepAliveInterval(30);
            //自动重连
            mqttConnectOptions.setAutomaticReconnect(true);

            //设置回调
            client.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    //连接丢失后，一般在这里面进行重连
                    System.out.println("connectionLost----------");
                    Mqtt_connect();
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    //publish后会执行到这里
                    System.out.println("deliveryComplete---------"
                            + token.isComplete());
                    Toast.makeText(getApplicationContext(), "已发送！", Toast.LENGTH_SHORT).show();

                }

                @Override
                public void messageArrived(String topicName, MqttMessage message)
                        throws Exception {
                    //subscribe后得到的消息会执行到这里面
                    System.out.println("messageArrived----------");
                }

            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // MQTT连接函数
    public void Mqtt_connect() {
        //Toast.makeText(LinkActivity.this, "Button Clicked!", Toast.LENGTH_SHORT).show();
        new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    if (!client.isConnected())  //如果还未连接
                    {
                        client.connect(mqttConnectOptions);
                        Message msg = new Message();
                        msg.what = 31;
                        handler.sendMessage(msg);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    e.getMessage();
                    Message msg = new Message();
                    msg.what = 30;
                    handler.sendMessage(msg);
                }

            }
        }).start();
    }
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
    public void onDestroy() {
        super.onDestroy();
        try {
            client.disconnect();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
