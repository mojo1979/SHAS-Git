package shas.j2dw.myshasapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import com.android.volley.*;
import com.android.volley.toolbox.*;
import android.widget.EditText;
import android.widget.TextView;

public class CommandCenterActivity extends AppCompatActivity {

    private EditText comFAC;
    private EditText comLAC;
    private EditText comBEAC;
    private EditText comBAC;
    private RequestQueue mQueue;
    private TextView urlStringOut;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_command_center);
        comFAC = findViewById(R.id.commandFAC);
        comLAC = findViewById(R.id.commandLAC);
        comBEAC = findViewById(R.id.commandBEAC);
        comBAC = findViewById(R.id.commandBAC);
        urlStringOut = findViewById(R.id.urlStringDisp);

        mQueue = Volley.newRequestQueue(this);
    }

    public void SendCommands (View view) {
        String faccom = comFAC.getText().toString();
        String laccom = comLAC.getText().toString();
        String beaccom = comBEAC.getText().toString();
        String baccom = comBAC.getText().toString();

        String url = "https://myshas.online/api?key=XGD45T9FF1337&update=actuators";

        if (faccom != null && !faccom.isEmpty()){
            url += "&faccomm=" + faccom;
            comFAC.setHint(faccom);
            comFAC.setText("");
        }
        if (laccom != null && !laccom.isEmpty()){
            url += "&laccomm=" + laccom;
            comLAC.setHint(laccom);
            comLAC.setText("");
        }
        if (beaccom != null && !beaccom.isEmpty()){
            url += "&beaccomm=" + beaccom;
            comBEAC.setHint(beaccom);
            comBEAC.setText("");
        }
        if (baccom != null && !baccom.isEmpty()){
            url += "&baccomm=" + baccom;
            comBAC.setHint(baccom);
            comBAC.setText("");
        }

        //urlStringOut.setText(url);
        StringRequest sendCommandRequest = new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                //Do something later ;)
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                error.printStackTrace();
            }
        });

        mQueue.add(sendCommandRequest);
    }

    public void SwitchToMainActivity(View view) {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}
