package net.hashcoding.study;

import android.os.Handler;

import java.util.LinkedList;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by MaoChuan on 2017/6/22.
 */

public abstract class AsyncTaskImpl<Params, Progress, Result> {

    private static final int CORE_PROCESS;
    private static final int MAXIMUM_PROCESS;
    private static final int KEEP_ALIVE;
    private static final BlockingQueue<Runnable> BLOCKING_QUEUE;
    private static final ThreadPoolExecutor EXECUTOR;

    static {
        CORE_PROCESS = Runtime.getRuntime().availableProcessors() + 1;
        MAXIMUM_PROCESS = CORE_PROCESS * 2 - 1;
        KEEP_ALIVE = 1;
        BLOCKING_QUEUE = new LinkedBlockingQueue<>(128);
        EXECUTOR = new ThreadPoolExecutor(CORE_PROCESS, MAXIMUM_PROCESS,
            KEEP_ALIVE, TimeUnit.SECONDS, BLOCKING_QUEUE);
    }

    private final Handler handler;
    private final Runnable worker;
    private Params [] params;

    public AsyncTaskImpl() {
        worker = new Runnable() {
            @Override
            public void run() {
                Result result = doInBackground(params);
                postResult(result);
            }
        };

        handler = new Handler();
    }

    public void execute(Params ...params) {
        executeOnExecutor(EXECUTOR, params);
    }

    public void updateProgress(final Progress progress) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                onProgressUpdate(progress);
            }
        });
    }

    private void postResult(final Result result) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                onPostExecute(result);
            }
        });
    }

    private void executeOnExecutor(ThreadPoolExecutor executor, Params ...params) {
        onPreExecute();
        this.params = params;
        executor.execute(worker);
    }

    protected abstract void onPreExecute();
    protected abstract Result doInBackground(Params ...params);
    protected abstract void onProgressUpdate(Progress values);
    protected abstract void onPostExecute(Result result);
    protected void onCancel() {
        // Ignore
    }
}
