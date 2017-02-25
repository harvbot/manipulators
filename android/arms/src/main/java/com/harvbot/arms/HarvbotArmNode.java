package com.harvbot.arms;

import android.text.TextUtils;

import com.hoho.android.usbserial.driver.UsbSerialPort;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

public class HarvbotArmNode
{
    private HarvbotArmBase arm;

    private HarvbotArmNodeTypes type;

    public static final int Timeout = 1000;

    public HarvbotArmNode(HarvbotArmNodeTypes type, HarvbotArmBase arm)
    {
        this.arm = arm;
        this.type = type;
    }

    public HarvbotArmNodeTypes getType()
    {
        return this.type;
    }

    public void move(int degree) throws IOException
    {
        String response = this.sendCommand("move", String.valueOf(degree));

        if (TextUtils.isEmpty(response))
        {
            throw new IllegalStateException("Invalid moving: " + String.valueOf(degree));
        }
    }

    public void sweep(int degree) throws IOException
    {
        String response = this.sendCommand("sweep", String.valueOf(degree));

        if (TextUtils.isEmpty(response))
        {
            throw new IllegalStateException("Invalid moving: " + String.valueOf(degree));
        }
    }

    public Integer getPosition() throws IOException
    {
        String response = this.sendCommand("pos");

        if (!TextUtils.isEmpty(response))
        {
            return Integer.parseInt(response);
        }

        return null;
    }

    protected String sendCommand(String command) throws IOException
    {
        return this.sendCommand(command, null);
    }

    protected String sendCommand(String command, String args) throws IOException
    {
        UsbSerialPort serailPost = this.arm.getSerialPort();
        StringBuilder request = new StringBuilder();

        request.append("harm:" + command + ":");
        request.append(String.valueOf(this.type.getNumericType()));
        if (TextUtils.isEmpty(args))
        {
            request.append(":~harm");
        }
        else
        {
            request.append(":" + args + ":~harm");
        }

        byte[] requestBytes = request.toString().getBytes("UTF-8");
        serailPost.write(requestBytes, Timeout);

        byte[] responseBytes = new byte[128];
        int read = serailPost.read(responseBytes, Timeout);

        String response = new String(responseBytes, "UTF-8");

        String[] segments = response.split(":");

        if (segments[0].equalsIgnoreCase("harm") &&
                segments[1].equalsIgnoreCase(command) &&
                segments[2].equalsIgnoreCase(String.valueOf((int)this.type.getNumericType())) &&
                segments[segments.length - 1].equalsIgnoreCase("~harm"))
        {
            throw new IllegalStateException("Invalid response: " + response);
        }

        return segments[3];
    }
}