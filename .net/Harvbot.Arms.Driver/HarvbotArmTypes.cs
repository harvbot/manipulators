using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    public enum HarvbotArmTypes
    {
        /// <summary>
        /// 6-asix arm with 6 nodes.
        /// </summary>
        Type1,

        /// <summary>
        /// 4 nodes arm: beadplate, shoulder, elbow, claw
        /// </summary>
        Type2,

        /// <summary>
        /// 4 nodes arm: beadplate, shoulder, elbow, claw and laser rangefinder + camera.
        /// </summary>
        Type3
    }
}
