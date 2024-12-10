package com.example.test2;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class LoginActivity extends Activity {
    EditText name,pwd;
    Button btnlogin,btnreg;
    MyDatabaseHelper myDatabaseHelper;
    SQLiteDatabase db;
    SharedPreferences sp1,sp2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        name = this.findViewById(R.id.account_input);            //用户名输入框
        pwd = this.findViewById(R.id.password_input);              //密码输入框
        btnlogin = this.findViewById(R.id.login);         //登录按钮
        btnreg = this.findViewById(R.id.reg);               //注册按钮
        sp1 =  this.getSharedPreferences("useinfo",this.MODE_PRIVATE);
        sp2 = this.getSharedPreferences("username",this.MODE_PRIVATE);

        name.setText(sp1.getString("usname",null));
        pwd.setText(sp1.getString("uspwd",null));
        myDatabaseHelper = new MyDatabaseHelper(this,"Userinfo",null,1);      //建数据库或者取数据库
        db = myDatabaseHelper.getReadableDatabase();
        btnlogin.setOnClickListener(new View.OnClickListener() {                //登录事件
            @Override
            public void onClick(View v) {
                String username = name.getText().toString();
                String password = pwd.getText().toString();                 //获取用户输入的用户名和密码
                //查询用户名和密码相同的数据
                Cursor cursor = db.query("logins",new String[]{"usname","uspwd"}," usname=? and uspwd=?",new String[]{username,password},null,null,null);
                int flag = cursor.getCount();                            //查询出来的记录项的条数，若没有该用户则为0条
                if(flag!=0){  //若查询出的记录不为0，则进行跳转操作
                    Intent it = new Intent(LoginActivity.this, MQTTService.class);
                    startService(it);
                    Intent intent = new Intent();
                    intent = new Intent(LoginActivity.this,MainActivity.class );//设置页面跳转

                    SharedPreferences.Editor editor = sp2.edit();
                    cursor.moveToFirst();                                   //将光标移动到position为0的位置，默认位置为-1
                    String loginname = cursor.getString(0);
                    editor.putString("Loginname",loginname);
                    editor.commit();                                        //将用户名存到SharedPreferences中
                    startActivity(intent);

                }
                else{
                    Toast.makeText(LoginActivity.this,"用户名或密码错误！",Toast.LENGTH_LONG).show();             //提示用户信息错误或没有账号
                }

            }
        });

        btnreg.setOnClickListener(new View.OnClickListener() {                  //注册事件
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent = new Intent(LoginActivity.this,RegisterActivity.class );
                startActivity(intent);
                Toast.makeText(LoginActivity.this,"前往注册！",Toast.LENGTH_SHORT).show();
            }
        });
    }
}



