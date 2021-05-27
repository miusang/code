package com.atom.binderdemo;
import android.util.Slog;
import android.os.ServiceManager;

public class DemoServer {
    public static void main(String args[]) {
        Slog.d("binderDemoServer", "server run...");
        ServiceManager.addService("DemoService", new DemoService());
        while (true) {
            try {
                Thread.sleep(10);
            } catch (Exception e) {}
        }
    }
}
