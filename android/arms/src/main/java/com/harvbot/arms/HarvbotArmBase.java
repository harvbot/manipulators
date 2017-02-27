package com.harvbot.arms;

import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.text.TextUtils;

import com.hoho.android.usbserial.driver.CdcAcmSerialDriver;
import com.hoho.android.usbserial.driver.Ch34xSerialDriver;
import com.hoho.android.usbserial.driver.Cp21xxSerialDriver;
import com.hoho.android.usbserial.driver.FtdiSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialPort;

import java.io.IOException;
import java.util.Timer;

public abstract class HarvbotArmBase
{
    public static final int BaudRate = 9600;

    protected HarvbotArmNode[] nodes;

    private boolean isDisposed;

    private UsbSerialDriver serial;

    private UsbSerialPort serialPort;

    private UsbDeviceConnection usbDeviceConnection;

    private UsbManager usbManager;

    public HarvbotArmBase(UsbManager usbManager, UsbDevice device) throws IOException {
        this.usbManager = usbManager;

        this.usbDeviceConnection = usbManager.openDevice(device);
        this.serial =  new CdcAcmSerialDriver(device);
        this.serialPort = this.serial.getPorts().get(0);

        this.initializeNodes();
    }

    public abstract HarvbotArmTypes getArmType();

    public UsbSerialPort getSerialPort()
    {
        return  this.serialPort;
    }

    public void open() throws IOException
    {
        this.serialPort.open(this.usbDeviceConnection);
        this.serialPort.setDTR(true);
    }

    public void close() throws IOException
    {
        this.serialPort.close();
    }

    public Integer getBedplatePosition() throws IOException
    {
        HarvbotArmNode bedplate = this.getNodeByType(HarvbotArmNodeTypes.Bedplate);
        if (bedplate != null)
        {
            return bedplate.getPosition();
        }

        return null;
    }

    public void moveBedplate(int degree) throws IOException
    {
        HarvbotArmNode bedplate = this.getNodeByType(HarvbotArmNodeTypes.Bedplate);
        if (bedplate != null)
        {
            bedplate.move(degree);
        }
    }

    public Integer getShoulderPosition() throws IOException
    {
        HarvbotArmNode shoulder = this.getNodeByType(HarvbotArmNodeTypes.Shoulder);
        if (shoulder != null)
        {
            return shoulder.getPosition();
        }

        return null;
    }

    public void moveShoulder(int degree) throws IOException
    {
        HarvbotArmNode shoulder = this.getNodeByType(HarvbotArmNodeTypes.Shoulder);
        if (shoulder != null)
        {
            shoulder.move(degree);
        }
    }

    public HarvbotArmNode getNodeByType(HarvbotArmNodeTypes type)
    {
        for(int i=0;i<this.nodes.length;i++)
        {
            if(this.nodes[i].getType() == type)
            {
                return this.nodes[i];
            }
        }

        return null;
    }

    protected abstract void initializeNodes();
}
