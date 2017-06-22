package net.hashcoding.study;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class FirstActivity extends AppCompatActivity {

    public static final String TAG = "FirstActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_first);

        Log.i(TAG, "onCreate()");

        TextView finish = (TextView) findViewById(R.id.tryFinish);
        finish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
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
