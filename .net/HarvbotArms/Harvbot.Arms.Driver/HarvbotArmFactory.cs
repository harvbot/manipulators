using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents Harvbot Arm factory.
    /// </summary>
    public static class HarvbotArmFactory
    {
        /// <summary>
        /// Gets the Harvbot Arm instance.
        /// </summary>
        /// <param name="comNum">The COM number.</param>
        /// <param name="type">The Arm type.</param>
        /// <returns>The Arm instance.</returns>
        public static HarvbotArmBase GetInstance(string comNum, HarvbotArmTypes type)
        {
            switch (type)
            {
                case HarvbotArmTypes.Type1:
                    {
                        return new HarvbotArm1(comNum);
                    }
                default:
                    {
                        throw new NotSupportedException("Specified arm type is not supported.");
                    }
            }
        }
    }
}
