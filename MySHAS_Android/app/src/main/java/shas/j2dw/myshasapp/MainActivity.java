package shas.j2dw.myshasapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


    }

    public void SwitchToFaceRecActivity(View view) {
        Intent intent = new Intent(this, FaceUnlockActivity.class);
        startActivity(intent);
    }

    public void SwitchToCommandCenterActivity(View view) {
        Intent intent = new Intent(this, CommandCenterActivity.class);
        startActivity(intent);
    }

    public void SwitchToSensorActivity(View view) {
        Intent intent = new Intent(this, SensorActivity.class);
        startActivity(intent);
    }
}
