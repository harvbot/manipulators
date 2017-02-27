package com.harvbot.armapp;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

import com.harvbot.app.R;
import com.harvbot.arms.HarvbotArm1;
import com.harvbot.arms.HarvbotArmBase;

import java.io.IOException;
import java.util.Iterator;

public class MainActivity extends AppCompatActivity {

    private UsbManager usbManager;

    private UsbDevice armDevice;

    private HarvbotArmBase arm;

    private float prevX;
    private float prevY;

    private static final String ACTION_USB_PERMISSION =
            "com.harvbot.armapp.USB_PERMISSION";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.usbManager = (UsbManager)this.getSystemService(Context.USB_SERVICE);

        this.findArmDevice();

        final TextView pnlControl = (TextView) findViewById(R.id.pnlControl);
        pnlControl.setOnTouchListener( new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(arm==null)
                {
                    return false;
                }

                int deltaX = (int)(event.getX() * 180 / pnlControl.getWidth());
                int deltaY = (int)(event.getY() * 180 / pnlControl.getHeight());

                if (deltaX < 0)
                {
                    try {
                        arm.moveBedplate(0);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                else if (deltaX > 180)
                {
                    try {
                        arm.moveBedplate(180);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                else
                {
                    try {
                        arm.moveBedplate(deltaX);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }

                if (deltaY < 0)
                {
                    try {
                        arm.moveShoulder(0);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                else if (deltaY > 180)
                {
                    try {
                        arm.moveShoulder(180);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                else
                {
                    try {
                        arm.moveShoulder(deltaY);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }

                return false;
            }
        });
    }

    private void findArmDevice()
    {
        Iterator<UsbDevice> deviceIterator = usbManager.getDeviceList().values().iterator();

        while (deviceIterator.hasNext())
        {
            UsbDevice device = deviceIterator.next();

            if(device.getVendorId()==9025 && device.getProductId()==32822)
            {
                this.armDevice = device;
                break;
            }
        }

        if(this.armDevice != null) {
            PendingIntent mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
            IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
            this.registerReceiver(mUsbReceiver, filter);

            usbManager.requestPermission(this.armDevice, mPermissionIntent);
        }
    }

    private final BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {

        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (ACTION_USB_PERMISSION.equals(action)) {
                synchronized (this) {
                    UsbDevice device = (UsbDevice)intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);

                    if (intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
                        if(device != null)
                        {
                            //call method to set up device communication
                            try
                            {
                                arm = new HarvbotArm1(usbManager, device);
                                arm.open();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                    else {
                        Log.d("TAG", "permission denied for the device " + device);
                    }
                }
            }
        }
    };
}
