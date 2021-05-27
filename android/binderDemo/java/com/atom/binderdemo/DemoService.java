package com.atom.binderdemo;
import android.os.RemoteException;
import android.util.Slog;

public class DemoService extends IDemo.Stub {
    private int count = 0;
    public void test() throws RemoteException {
        Slog.d("binderDemoService", "test " + count);
        count++;
    }
}
