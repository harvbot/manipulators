using System;
using System.Linq;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents Harvbot Arm node.
    /// </summary>
    public class HarvbotArmNode
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
        public HarvbotArmNode(HarvbotArmNodeTypes type, HarvbotArmBase arm)
        {
            this.Arm = arm;
            this.Type = type;
            this.pos = null;
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

        /// <summary>
        /// Sends commands to controller.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="args">The command arguments.</param>
        /// <returns>The response.</returns>
        protected string SendCommand(string command, string args = null)
        {
            if (string.IsNullOrEmpty(args))
            {
                this.Arm.SerialPort.WriteLine($"harm:{command}:{(int)this.Type}:~harm");
            }
            else
            {
                this.Arm.SerialPort.WriteLine($"harm:{command}:{(int)this.Type}:{args}:~harm");
            }

            var response = this.Arm.SerialPort.ReadLine();

            var segments = response.Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);

            if (segments[0].Equals("harm", StringComparison.InvariantCultureIgnoreCase) &&
                segments[1].Equals(command, StringComparison.InvariantCultureIgnoreCase) &&
                segments[2].Equals(((int)this.Type).ToString(), StringComparison.InvariantCultureIgnoreCase) &&
                segments.Last().Equals("~harm", StringComparison.InvariantCultureIgnoreCase))
            {
                throw new InvalidOperationException($"Invalid response: {response}");
            }

            return segments[3];
        }
    }
}
