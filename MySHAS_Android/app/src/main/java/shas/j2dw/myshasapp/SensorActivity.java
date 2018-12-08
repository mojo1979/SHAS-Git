package shas.j2dw.myshasapp;

import android.content.Intent;
import android.os.CountDownTimer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class SensorActivity extends AppCompatActivity {
    private TextView mTextView;
    private TextView mT0R0C0;
    private TextView mT0R0C1;
    private TextView mT0R0C2;
    private TextView mT0R1C0;
    private TextView mT0R1C1;
    private TextView mT0R1C2;
    private TextView mT0R2C0;
    private TextView mT0R2C1;
    private TextView mT0R2C2;
    private TextView mT0R3C0;
    private TextView mT0R3C1;
    private TextView mT0R3C2;
    private TextView mT1R0C0;
    private TextView mT1R0C1;
    private TextView mT1R0C2;
    private TextView mT1R1C0;
    private TextView mT1R1C1;
    private TextView mT1R1C2;
    private TextView mT1R2C0;
    private TextView mT1R2C1;
    private TextView mT1R2C2;
    private TextView mT1R3C0;
    private TextView mT1R3C1;
    private TextView mT1R3C2;
    private TextView mT2R0C0;
    private TextView mT2R0C1;
    private TextView mT2R0C2;
    private TextView mT2R1C0;
    private TextView mT2R1C1;
    private TextView mT2R1C2;
    private TextView mT2R2C0;
    private TextView mT2R2C1;
    private TextView mT2R2C2;
    private TextView mT2R3C0;
    private TextView mT2R3C1;
    private TextView mT2R3C2;
    private TextView mT3R0C0;
    private TextView mT3R0C1;
    private TextView mT3R0C2;
    private TextView mT3R1C0;
    private TextView mT3R1C1;
    private TextView mT3R1C2;
    private TextView mT3R2C0;
    private TextView mT3R2C1;
    private TextView mT3R2C2;
    private TextView mT3R3C0;
    private TextView mT3R3C1;
    private TextView mT3R3C2;
    private RequestQueue mQueue;

    CountDownTimer updateData = new CountDownTimer(500, 1000) {
        public void onTick(long millisUntilFinished) {
        }
        public void onFinish() {
            Log.i("SCROLLS ", "UPDATE CONTENT HERE ");
            updateSensorData();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensors);
        //mTextView = findViewById(R.id.jsonResults);
        mT0R0C0 = findViewById(R.id.T0R0C0);
        mT0R0C1 = findViewById(R.id.T0R0C1);
        mT0R0C2 = findViewById(R.id.T0R0C2);
        mT0R1C0 = findViewById(R.id.T0R1C0);
        mT0R1C1 = findViewById(R.id.T0R1C1);
        mT0R1C2 = findViewById(R.id.T0R1C2);
        mT0R2C0 = findViewById(R.id.T0R2C0);
        mT0R2C1 = findViewById(R.id.T0R2C1);
        mT0R2C2 = findViewById(R.id.T0R2C2);
        mT0R3C0 = findViewById(R.id.T0R3C0);
        mT0R3C1 = findViewById(R.id.T0R3C1);
        mT0R3C2 = findViewById(R.id.T0R3C2);
        mT1R0C0 = findViewById(R.id.T1R0C0);
        mT1R0C1 = findViewById(R.id.T1R0C1);
        mT1R0C2 = findViewById(R.id.T1R0C2);
        mT1R1C0 = findViewById(R.id.T1R1C0);
        mT1R1C1 = findViewById(R.id.T1R1C1);
        mT1R1C2 = findViewById(R.id.T1R1C2);
        mT1R2C0 = findViewById(R.id.T1R2C0);
        mT1R2C1 = findViewById(R.id.T1R2C1);
        mT1R2C2 = findViewById(R.id.T1R2C2);
        mT1R3C0 = findViewById(R.id.T1R3C0);
        mT1R3C1 = findViewById(R.id.T1R3C1);
        mT1R3C2 = findViewById(R.id.T1R3C2);
        mT2R0C0 = findViewById(R.id.T2R0C0);
        mT2R0C1 = findViewById(R.id.T2R0C1);
        mT2R0C2 = findViewById(R.id.T2R0C2);
        mT2R1C0 = findViewById(R.id.T2R1C0);
        mT2R1C1 = findViewById(R.id.T2R1C1);
        mT2R1C2 = findViewById(R.id.T2R1C2);
        mT2R2C0 = findViewById(R.id.T2R2C0);
        mT2R2C1 = findViewById(R.id.T2R2C1);
        mT2R2C2 = findViewById(R.id.T2R2C2);
        mT2R3C0 = findViewById(R.id.T2R3C0);
        mT2R3C1 = findViewById(R.id.T2R3C1);
        mT2R3C2 = findViewById(R.id.T2R3C2);
        mT3R0C0 = findViewById(R.id.T3R0C0);
        mT3R0C1 = findViewById(R.id.T3R0C1);
        mT3R0C2 = findViewById(R.id.T3R0C2);
        mT3R1C0 = findViewById(R.id.T3R1C0);
        mT3R1C1 = findViewById(R.id.T3R1C1);
        mT3R1C2 = findViewById(R.id.T3R1C2);
        mT3R2C0 = findViewById(R.id.T3R2C0);
        mT3R2C1 = findViewById(R.id.T3R2C1);
        mT3R2C2 = findViewById(R.id.T3R2C2);
        mT3R3C0 = findViewById(R.id.T3R3C0);
        mT3R3C1 = findViewById(R.id.T3R3C1);
        mT3R3C2 = findViewById(R.id.T3R3C2);

        mQueue = Volley.newRequestQueue(this);
        updateData.start();
    }

    private void updateSensorData () {
        String url = "https://myshas.online/controller?session=Fhsoux6fV9VM&key=XGD45T9FF1337&update=sensors";

        JsonObjectRequest jsonObjectRequest = new JsonObjectRequest
                (Request.Method.GET, url, null, new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            JSONArray SensorData = response.getJSONArray("ACVals");
                            JSONObject FACSensObj = SensorData.getJSONObject(0);
                            JSONObject LACSensObj = SensorData.getJSONObject(1);
                            JSONObject BEACSensObj = SensorData.getJSONObject(2);
                            JSONObject BACSensObj = SensorData.getJSONObject(3);
                            JSONArray FACSensorData = FACSensObj.getJSONArray("Sensors");
                            JSONArray LACSensorData = LACSensObj.getJSONArray("Sensors");
                            JSONArray BEACSensorData = BEACSensObj.getJSONArray("Sensors");
                            JSONArray BACSensorData = BACSensObj.getJSONArray("Sensors");

                            mT0R0C0.setText(String.valueOf(FACSensorData.getJSONObject(0).getInt("SensId")));
                            mT0R0C1.setText(String.valueOf(FACSensorData.getJSONObject(0).getInt("SensType")));
                            mT0R0C2.setText(String.valueOf(FACSensorData.getJSONObject(0).getInt("SensVal")));
                            mT0R1C0.setText(String.valueOf(FACSensorData.getJSONObject(1).getInt("SensId")));
                            mT0R1C1.setText(String.valueOf(FACSensorData.getJSONObject(1).getInt("SensType")));
                            mT0R1C2.setText(String.valueOf(FACSensorData.getJSONObject(1).getInt("SensVal")));
                            mT0R2C0.setText(String.valueOf(FACSensorData.getJSONObject(2).getInt("SensId")));
                            mT0R2C1.setText(String.valueOf(FACSensorData.getJSONObject(2).getInt("SensType")));
                            mT0R2C2.setText(String.valueOf(FACSensorData.getJSONObject(2).getInt("SensVal")));
                            mT0R3C0.setText(String.valueOf(FACSensorData.getJSONObject(3).getInt("SensId")));
                            mT0R3C1.setText(String.valueOf(FACSensorData.getJSONObject(3).getInt("SensType")));
                            mT0R3C2.setText(String.valueOf(FACSensorData.getJSONObject(3).getInt("SensVal")));
                            mT1R0C0.setText(String.valueOf(LACSensorData.getJSONObject(0).getInt("SensId")));
                            mT1R0C1.setText(String.valueOf(LACSensorData.getJSONObject(0).getInt("SensType")));
                            mT1R0C2.setText(String.valueOf(LACSensorData.getJSONObject(0).getInt("SensVal")));
                            mT1R1C0.setText(String.valueOf(LACSensorData.getJSONObject(1).getInt("SensId")));
                            mT1R1C1.setText(String.valueOf(LACSensorData.getJSONObject(1).getInt("SensType")));
                            mT1R1C2.setText(String.valueOf(LACSensorData.getJSONObject(1).getInt("SensVal")));
                            mT1R2C0.setText(String.valueOf(LACSensorData.getJSONObject(2).getInt("SensId")));
                            mT1R2C1.setText(String.valueOf(LACSensorData.getJSONObject(2).getInt("SensType")));
                            mT1R2C2.setText(String.valueOf(LACSensorData.getJSONObject(2).getInt("SensVal")));
                            mT1R3C0.setText(String.valueOf(LACSensorData.getJSONObject(3).getInt("SensId")));
                            mT1R3C1.setText(String.valueOf(LACSensorData.getJSONObject(3).getInt("SensType")));
                            mT1R3C2.setText(String.valueOf(LACSensorData.getJSONObject(3).getInt("SensVal")));
                            mT2R0C0.setText(String.valueOf(BEACSensorData.getJSONObject(0).getInt("SensId")));
                            mT2R0C1.setText(String.valueOf(BEACSensorData.getJSONObject(0).getInt("SensType")));
                            mT2R0C2.setText(String.valueOf(BEACSensorData.getJSONObject(0).getInt("SensVal")));
                            mT2R1C0.setText(String.valueOf(BEACSensorData.getJSONObject(1).getInt("SensId")));
                            mT2R1C1.setText(String.valueOf(BEACSensorData.getJSONObject(1).getInt("SensType")));
                            mT2R1C2.setText(String.valueOf(BEACSensorData.getJSONObject(1).getInt("SensVal")));
                            mT2R2C0.setText(String.valueOf(BEACSensorData.getJSONObject(2).getInt("SensId")));
                            mT2R2C1.setText(String.valueOf(BEACSensorData.getJSONObject(2).getInt("SensType")));
                            mT2R2C2.setText(String.valueOf(BEACSensorData.getJSONObject(2).getInt("SensVal")));
                            mT2R3C0.setText(String.valueOf(BEACSensorData.getJSONObject(3).getInt("SensId")));
                            mT2R3C1.setText(String.valueOf(BEACSensorData.getJSONObject(3).getInt("SensType")));
                            mT2R3C2.setText(String.valueOf(BEACSensorData.getJSONObject(3).getInt("SensVal")));
                            mT3R0C0.setText(String.valueOf(BACSensorData.getJSONObject(0).getInt("SensId")));
                            mT3R0C1.setText(String.valueOf(BACSensorData.getJSONObject(0).getInt("SensType")));
                            mT3R0C2.setText(String.valueOf(BACSensorData.getJSONObject(0).getInt("SensVal")));
                            mT3R1C0.setText(String.valueOf(BACSensorData.getJSONObject(1).getInt("SensId")));
                            mT3R1C1.setText(String.valueOf(BACSensorData.getJSONObject(1).getInt("SensType")));
                            mT3R1C2.setText(String.valueOf(BACSensorData.getJSONObject(1).getInt("SensVal")));
                            mT3R2C0.setText(String.valueOf(BACSensorData.getJSONObject(2).getInt("SensId")));
                            mT3R2C1.setText(String.valueOf(BACSensorData.getJSONObject(2).getInt("SensType")));
                            mT3R2C2.setText(String.valueOf(BACSensorData.getJSONObject(2).getInt("SensVal")));
                            mT3R3C0.setText(String.valueOf(BACSensorData.getJSONObject(3).getInt("SensId")));
                            mT3R3C1.setText(String.valueOf(BACSensorData.getJSONObject(3).getInt("SensType")));
                            mT3R3C2.setText(String.valueOf(BACSensorData.getJSONObject(3).getInt("SensVal")));

                        } catch (JSONException e) {
                            e.printStackTrace();
                        }

                        //mTextView.setText("Response: " + response.toString());
                        refreshAllContent();
                    }
                }, new Response.ErrorListener() {

                    @Override
                    public void onErrorResponse(VolleyError error) {
                        // TODO: Handle error

                    }
                });
        mQueue.add(jsonObjectRequest);

    }

    public void refreshAllContent() {
        updateData.start();
    }

    public void SwitchToMainActivity(View view) {
        updateData.cancel();
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}
