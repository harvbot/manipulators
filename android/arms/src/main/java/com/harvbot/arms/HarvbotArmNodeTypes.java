package com.harvbot.arms;


public enum HarvbotArmNodeTypes
{
    Bedplate (2),

    Shoulder (3),

    Elbow (4),

    ElbowScrew (5),

    Hand (6),

    HandScrew (7);

    private int mValue;

    HarvbotArmNodeTypes(int value) {
        this.mValue = value;
    }

    public int getNumericType()
    {
        return this.mValue;
    }
}
