package com.harvbot.arms;

import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;

import static com.harvbot.arms.HarvbotArmTypes.*;

public class HarvbotArmFactory
{
    public static HarvbotArmBase getInstance(HarvbotArmTypes armType, UsbManager usbManager, UsbDevice device)
    {
        switch(armType)
        {
            case Type1:
                return new HarvbotArm1(usbManager, device);
            default:
                throw new IllegalArgumentException("Invalid Harvbot Arm type");
        }
    }
}
