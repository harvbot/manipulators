using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    public enum HarvbotArmSubTypes
    {
        /// <summary>
        /// Represetns Type1 arm based on servo engines.
        /// </summary>
        Servo1,

        /// <summary>
        /// Represents Type2 arm based on servo for bedplate and Adafruit motor shield for claw.
        /// </summary>
        AFMotor2
    }
}
