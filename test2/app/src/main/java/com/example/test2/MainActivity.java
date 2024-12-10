package com.example.test2;
import android.app.Activity;
import android.content.Intent;
import android.view.View;

import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends Activity {
    //声明控件
    private Button mChange;
    private Button mRGB;
    private Button mLink;
    private Button mRemember;
    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //找到控件
        mChange=findViewById(R.id.change);
        //实现跳转
        mChange.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                Intent intent = null;
                intent = new Intent(MainActivity.this,ChangeActivity.class );
                startActivity(intent);

        }
        });

        //找到控件
        mRGB=findViewById(R.id.RGB);
        //实现跳转
        mRGB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                Intent intent = null;
                intent = new Intent(MainActivity.this,RGBActivity.class );
                startActivity(intent);
            }
        });
        //找到控件
        mLink=findViewById(R.id.connect);
        //实现跳转
        mLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                Intent intent = null;
                intent = new Intent(MainActivity.this, LoginActivity.class );
                startActivity(intent);
            }
        });
        mRemember=findViewById(R.id.remember);
        //实现跳转
        mRemember.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                Intent intent = null;
                intent = new Intent(MainActivity.this,RememberActivity.class );
                startActivity(intent);
            }
        });

    }
}
