package net.hashcoding.study;

import android.content.Intent;
import android.content.IntentFilter;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class BroadcastActivity extends AppCompatActivity {

    public static final String TAG = "BroadcastActivity";

    private FirstReceiver receiver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_broadcast);

        receiver = new FirstReceiver();

        TextView dynamicBtn = (TextView) findViewById(R.id.sendDynamicBroadcast);
        TextView staticBtn = (TextView) findViewById(R.id.sendStaticBroadcast);

        dynamicBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setAction(FirstReceiver.DYNAMIC_ACTION);
                intent.putExtra(FirstReceiver.Message, "dynamic broadcast");
                sendBroadcast(intent);
            }
        });
        staticBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setAction(FirstReceiver.STATIC_ACTION);
                intent.putExtra(FirstReceiver.Message, "static broadcast");
                sendBroadcast(intent);
            }
        });

    }

    @Override
    protected void onResume() {
        super.onResume();

        Log.i(TAG, "register dynamic receiver");

        IntentFilter filter = new IntentFilter();
        filter.addAction(FirstReceiver.DYNAMIC_ACTION);
        registerReceiver(receiver, filter);
    }

    @Override
    protected void onPause() {
        super.onPause();

        Log.i(TAG, "unregister dynamic receiver");
        unregisterReceiver(receiver);
    }
}
