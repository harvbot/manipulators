using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents Harvbot Arm node.
    /// </summary>
    public class HarvbotArmNode
    {
        /// <summary>
        /// Represents Harvbot Arm node.
        /// </summary>
        /// <param name="type">The node type.</param>
        /// <param name="arm">The owner.</param>
        public HarvbotArmNode(HarvbotArmNodeTypes type, HarvbotArmBase arm)
        {
            this.Arm = arm;
            this.Type = type;
        }

        /// <summary>
        /// Gets the node owner.
        /// </summary>
        public HarvbotArmBase Arm { get; private set; }

        /// <summary>
        /// Gets the node type.
        /// </summary>
        public HarvbotArmNodeTypes Type { get; private set; }

        /// <summary>
        /// Moves node to specified position.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public void Move(int degree)
        {
            this.Arm.SerialPort.WriteLine($"harm:move:{(int)this.Type}:{degree}:~harm");
        }

        /// <summary>
        /// Gets current node position.
        /// </summary>
        /// <returns>The current node position degree.</returns>
        public int? GetPosition()
        {
            this.Arm.SerialPort.WriteLine($"harm:pos:{(int)this.Type}:~harm");

            var response = this.Arm.SerialPort.ReadLine();

            var parts = response.Split(':');

            if (parts != null && parts.Length == 4)
            {
                return int.Parse(parts[2]);
            }

            return new int?();
        }
    }
}
