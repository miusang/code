package com.atom.binderdemo;
import android.util.Slog;
import android.os.ServiceManager;
import android.os.IBinder;

public class DemoClient {
    public static void main(String args[]) {
        Slog.d("binderDemoClient", "client run...");
        IBinder binder = ServiceManager.getService("DemoService");
        IDemo cs = IDemo.Stub.asInterface(binder);
        try {
            cs.test();
        } catch (Exception e) {}
    }
}
