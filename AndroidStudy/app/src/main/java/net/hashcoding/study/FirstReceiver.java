package net.hashcoding.study;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class FirstReceiver extends BroadcastReceiver {

    public static final String STATIC_ACTION = "net.hashcoding.broadcast.static";
    public static final String DYNAMIC_ACTION = "net.hashcoding.broadcast.dynamic";
    public static final String Message = "msg";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(STATIC_ACTION)) {
            String message = intent.getStringExtra(Message);
            Log.i("FirstReceiver", message);
        } else if (intent.getAction().equals(DYNAMIC_ACTION)) {
            String message = intent.getStringExtra(Message);
            Log.i("FirstReceiver", message);
        }
    }
}
