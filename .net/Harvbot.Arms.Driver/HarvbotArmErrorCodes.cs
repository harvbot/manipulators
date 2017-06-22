using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    public enum HarvbotArmErrorCodes
    {
        Uninitialized = 101,

        InvalidArmType = 102,

        InvalidNodeIdentifier = 103,

        InvalidCommand = 104
    }
}
