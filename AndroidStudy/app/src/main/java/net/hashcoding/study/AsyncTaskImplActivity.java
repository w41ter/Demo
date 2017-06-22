package net.hashcoding.study;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class AsyncTaskImplActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_async_task_impl);

        TextView connect = (TextView) findViewById(R.id.connect);
        connect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connectTo();
            }
        });
    }

    private void connectTo() {
        final AsyncTaskImpl<String, Integer, String> task = new AsyncTaskImpl<String, Integer, String>() {
            @Override
            protected void onPreExecute() {
                String tag = "AsyncTaskImpl" + String.valueOf(android.os.Process.myTid());
                Log.i(tag, "onPreExecute");
            }

            @Override
            protected String doInBackground(String... params) {
                String tag = "AsyncTaskImpl" + String.valueOf(android.os.Process.myTid());
                Log.i(tag, "doInBackground");
                updateProgress(0);
                String s = NetUitls.get("http://www.baidu.com");
                updateProgress(100);
                return s;
            }

            @Override
            protected void onProgressUpdate(Integer values) {
                String tag = "AsyncTaskImpl" + String.valueOf(android.os.Process.myTid());
                Log.i(tag, "onProgressUpdate");
            }

            @Override
            protected void onPostExecute(String s) {
                String tag = "AsyncTaskImpl" + String.valueOf(android.os.Process.myTid());
                Log.i(tag, "onPostExecute");
                Log.i(tag, s);
            }
        };
        task.execute();
    }
}
