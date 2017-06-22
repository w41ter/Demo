package net.hashcoding.study;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.IOException;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class OKHttpActivity extends AppCompatActivity {

    private OkHttpClient client;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_okhttp);

        client = new OkHttpClient();

        TextView makeRequest = (TextView) findViewById(R.id.makeConnect);
        makeRequest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                request();
            }
        });
    }

    private void request() {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                Request request = new Request.Builder()
                    .url("https://www.baidu.com")
                    .build();

                try {
                    Response response = client.newCall(request).execute();
                    if (response.isSuccessful())
                        Log.i("OKHttpActivity", response.body().toString());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        thread.start();
    }
}
