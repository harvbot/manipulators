package com.harvbot.arms;

import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;

public class HarvbotArm1 extends HarvbotArmBase
{
    public HarvbotArm1(UsbManager usbManager, UsbDevice device)
    {
        super(usbManager, device);
    }

    @Override
    public HarvbotArmTypes getArmType()
    {
        return HarvbotArmTypes.Type1;
    }

    @Override
    protected void initializeNodes()
    {
        this.nodes = new HarvbotArmNode[]
        {
            new HarvbotArmNode(HarvbotArmNodeTypes.Bedplate, this),
            new HarvbotArmNode(HarvbotArmNodeTypes.Shoulder, this),
            new HarvbotArmNode(HarvbotArmNodeTypes.Elbow, this),
            new HarvbotArmNode(HarvbotArmNodeTypes.ElbowScrew, this),
            new HarvbotArmNode(HarvbotArmNodeTypes.Hand, this),
            new HarvbotArmNode(HarvbotArmNodeTypes.HandScrew, this)
        };
    }
}
