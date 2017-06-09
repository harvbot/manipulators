using System;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm servo node.
    /// </summary>
    public class HarvbotArmCircleNode : HarvbotArmNode
    {
        /// <summary>
        /// Stores current node position.
        /// </summary>
        private float? pos;

        /// <summary>
        /// Represents Harvbot Arm node.
        /// </summary>
        /// <param name="type">The node type.</param>
        /// <param name="arm">The owner.</param>
        public HarvbotArmCircleNode(HarvbotArmNodeIdentifiers type, HarvbotArmBase arm) : base(type, arm)
        {
            this.pos = null;
        }

        /// <summary>
        /// Gets node type.
        /// </summary>
        public override HarvbotArmNodeTypes NodeType
        {
            get
            {
                return HarvbotArmNodeTypes.Circle;
            }
        }

        /// <summary>
        /// Moves node to specified position.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public float? Move(float degree)
        {
            var response = this.SendCommand(HarvbotArmCommands.Move, degree.ToString());

            if (string.IsNullOrEmpty(response))
            {
                throw new InvalidOperationException($"Invalid moving: {degree}");
            }

            this.pos = float.Parse(response);

            return this.pos;
        }

        /// <summary>
        /// Gets current node position.
        /// </summary>
        /// <returns>The current node position degree.</returns>
        public float? GetPosition()
        {
            if (!this.pos.HasValue)
            {
                var response = this.SendCommand(HarvbotArmCommands.Position);

                if (!string.IsNullOrEmpty(response))
                {
                    this.pos = float.Parse(response);
                }
            }

            return this.pos;
        }
    }
}
