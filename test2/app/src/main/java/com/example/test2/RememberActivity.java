package com.example.test2;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.util.ArrayList;
import java.util.List;

public class RememberActivity extends Activity {

    private static final String TAG = "RememberActivity";
    private List<Msg> msgList = new ArrayList<>();
    private RecyclerView msgRecyclerView;
    private EditText inputText;
    private Button send;
    private LinearLayoutManager layoutManager;
    private MsgAdapter adapter;
    private MqttClient client;
    String pubTopic = "aaam";
    int qos = 2;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_remember);

        msgRecyclerView = findViewById(R.id.msg_recycler_view);
        inputText = findViewById(R.id.input);
        send = findViewById(R.id.Send);
        layoutManager = new LinearLayoutManager(this);
        adapter = new MsgAdapter(msgList = getData());
        client = MyApplication.getSessionString();
        msgRecyclerView.setLayoutManager(layoutManager);
        msgRecyclerView.setAdapter(adapter);

/*       我们还需要为button建立一个监听器，我们需要将编辑框的内容发送到 RecyclerView 上：
            ①获取内容，将需要发送的消息添加到 List 当中去。
            ②调用适配器的notifyItemInserted方法，通知有新的数据加入了，赶紧将这个数据加到 RecyclerView 上面去。
            ③调用RecyclerView的scrollToPosition方法，以保证一定可以看的到最后发出的一条消息。*/
        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String content = inputText.getText().toString();
                if(!content.equals("")) {
                    msgList.add(new Msg(content,Msg.TYPE_SEND));
                    adapter.notifyItemInserted(msgList.size()-1);
                    msgRecyclerView.scrollToPosition(msgList.size()-1);
                    inputText.setText("");//清空输入框中的内容
                    MqttMessage message = new MqttMessage(content.getBytes());
                    message.setQos(qos);
                    try {
                        client.publish(pubTopic, message);
                    } catch (MqttException e) {
                        throw new RuntimeException(e);
                    }
                    System.out.println("Message published");

                }
//                自定义一问一答
//                if(msgList.size() == 2){
//                    msgList.add(new Msg("What's your name?",Msg.TYPE_RECEIVED));
//                    adapter.notifyItemInserted(msgList.size()-1);
//                    msgRecyclerView.scrollToPosition(msgList.size()-1);
//                }
//                if(msgList.size() == 4){
//                    msgList.add(new Msg("Nice to meet you,Bye!",Msg.TYPE_RECEIVED));
//                    adapter.notifyItemInserted(msgList.size()-1);
//                    msgRecyclerView.scrollToPosition(msgList.size()-1);
            //}
            }
        });
    }

    private List<Msg> getData(){
        List<Msg> list = new ArrayList<>();
        list.add(new Msg("Hello",Msg.TYPE_RECEIVED));
        return list;
    }
}
