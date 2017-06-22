package net.hashcoding.study;

import android.accounts.NetworkErrorException;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * Created by MaoChuan on 2017/6/22.
 */

public class NetUitls {

    public static String post(String url_, Map<String, String> params) {
        HttpURLConnection conn = null;
        try {
            URL url = new URL(url_);
            conn = (HttpURLConnection) url.openConnection();

            conn.setRequestMethod("POST");
            conn.setReadTimeout(5000);
            conn.setConnectTimeout(10000);
            conn.setDoOutput(true);

            OutputStream os = conn.getOutputStream();
            for (Map.Entry<String, String> entry : params.entrySet()) {
                os.write(renderLine(entry.getKey(), entry.getValue()).getBytes());
            }
            os.flush();
            os.close();

            int responseCode = conn.getResponseCode();
            if (responseCode == 200) {
                InputStream is = conn.getInputStream();
                return readStringFromInputStream(is);
            } else {
                throw new NetworkErrorException("response status is " + String.valueOf(responseCode));
            }
        } catch (IOException | NetworkErrorException e) {
            e.printStackTrace();
        } finally {
            if (conn != null)
                conn.disconnect();
        }
        return null;
    }

    private static String renderLine(String requestHeader, String body) {
        return requestHeader +
            ':' +
            ' ' +
            body +
            '\r' +
            '\n';
    }

    public static String get(String url_) {
        HttpURLConnection conn = null;
        try {
            URL url = new URL(url_);
            conn = (HttpURLConnection) url.openConnection();

            conn.setRequestMethod("GET");
            conn.setReadTimeout(5000);
            conn.setConnectTimeout(10000);

            int responseCode = conn.getResponseCode();
            if (responseCode == 200) {
                InputStream is = conn.getInputStream();
                return readStringFromInputStream(is);
            } else {
                throw new NetworkErrorException("response status is " + String.valueOf(responseCode));
            }
        } catch (IOException | NetworkErrorException e) {
            e.printStackTrace();
        } finally {
            if (conn != null)
                conn.disconnect();
        }
        return null;
    }

    private static String readStringFromInputStream(InputStream is) throws IOException {
        ByteArrayOutputStream os = new ByteArrayOutputStream();
        byte[] bytes = new byte[1024];
        int length = -1;
        while ((length = is.read(bytes)) != -1) {
            os.write(bytes, 0, length);
        }
        is.close();
        String result = os.toString();
        os.close();
        return result;
    }

}
