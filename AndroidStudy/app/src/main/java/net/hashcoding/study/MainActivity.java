package net.hashcoding.study;

import android.content.Intent;
import android.content.IntentFilter;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.i(TAG, "onCreate()");
        TextView textView = (TextView) findViewById(R.id.textView);
        textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, FirstActivity.class);
                startActivity(intent);
            }
        });

        TextView showDialog = (TextView) findViewById(R.id.showDialog);
        showDialog.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new AlertDialog.Builder(MainActivity.this)
                        .setTitle("Dialog")
                        .setMessage("This is a dialog")
                        .setNegativeButton("cancel", null)
                        .setPositiveButton("ok", null)
                        .create()
                        .show();
            }
        });

        TextView sendBroadcast = (TextView) findViewById(R.id.sendBroadcast);
        sendBroadcast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, BroadcastActivity.class);
                startActivity(intent);
            }
        });

        TextView useHttpConnection = (TextView) findViewById(R.id.httpConnection);
        useHttpConnection.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, HttpConnectionActivity.class);
                startActivity(intent);
            }
        });

        TextView userOkHttp = (TextView) findViewById(R.id.ok_http);
        userOkHttp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, OKHttpActivity.class);
                startActivity(intent);
            }
        });

        TextView asyncTask = (TextView) findViewById(R.id.async_task);
        asyncTask.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, AsyncTaskImplActivity.class);
                startActivity(intent);
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        Log.i(TAG, "onDestroy()");
    }

    @Override
    protected void onStart() {
        super.onStart();

        Log.i(TAG, "onStart()");
    }

    @Override
    protected void onRestart() {
        super.onRestart();

        Log.i(TAG, "onRestart()");
    }

    @Override
    protected void onResume() {
        super.onResume();

        Log.i(TAG, "onResume()");
    }

    @Override
    protected void onPause() {
        super.onPause();

        Log.i(TAG, "onPause()");
    }

    @Override
    protected void onStop() {
        super.onStop();

        Log.i(TAG, "onStop()");
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);

        Log.i(TAG, "onNewIntent()");
    }

    @Override
    protected void onSaveInstanceState(Bundle bundle) {
        super.onSaveInstanceState(bundle);

        Log.i(TAG, "onSaveInstanceState()");
    }

    @Override
    protected void onRestoreInstanceState(Bundle bundle) {
        super.onRestoreInstanceState(bundle);

        Log.i(TAG, "onRestoreInstanceState()");
    }
}
