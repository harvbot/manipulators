using System;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm servo node.
    /// </summary>
    public class HarvbotArmServoNode : HarvbotArmNode
    {
        /// <summary>
        /// Stores current node position.
        /// </summary>
        private int? pos;

        /// <summary>
        /// Represents Harvbot Arm node.
        /// </summary>
        /// <param name="type">The node type.</param>
        /// <param name="arm">The owner.</param>
        public HarvbotArmServoNode(HarvbotArmNodeTypes type, HarvbotArmBase arm) : base(type, arm)
        {
            this.pos = null;
        }

        /// <summary>
        /// Moves node to specified position.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public int? Move(int degree)
        {
            var response = this.SendCommand("move", degree.ToString());

            if (string.IsNullOrEmpty(response))
            {
                throw new InvalidOperationException($"Invalid moving: {degree}");
            }

            this.pos = int.Parse(response);

            return pos;
        }

        /// <summary>
        /// Sweep node to specified position.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public int? Sweep(int degree)
        {
            var response = this.SendCommand("sweep", degree.ToString());

            if (string.IsNullOrEmpty(response))
            {
                throw new InvalidOperationException($"Invalid moving: {degree}");
            }

            this.pos = int.Parse(response);

            return pos;
        }

        /// <summary>
        /// Gets current node position.
        /// </summary>
        /// <returns>The current node position degree.</returns>
        public int? GetPosition()
        {
            if (!this.pos.HasValue)
            {
                var response = this.SendCommand("pos");

                if (!string.IsNullOrEmpty(response))
                {
                    this.pos = int.Parse(response);
                }

                this.pos = new int?();
            }

            return this.pos;
        }
    }
}
