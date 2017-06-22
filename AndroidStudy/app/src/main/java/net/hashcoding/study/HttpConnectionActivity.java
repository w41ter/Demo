package net.hashcoding.study;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class HttpConnectionActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_http_connection);

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
                String result = NetUitls.get("http://www.baidu.com");
                Log.i("HttpConnectionActivity", result);
            }
        });
        thread.start();
    }
}
