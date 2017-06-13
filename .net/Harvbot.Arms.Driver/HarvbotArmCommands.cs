using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    public enum HarvbotArmCommands
    {
        Status,

        Init,

        InitStart,

        Position,

        Move,

        Steps,

        Angle,

        RotateOnSteps,

        RotateOnAngle,

        Revolution,

        NodeStatus
    }
}
