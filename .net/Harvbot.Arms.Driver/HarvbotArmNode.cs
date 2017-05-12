using System;
using System.Diagnostics;
using System.Linq;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm base node.
    /// </summary>
    public abstract class HarvbotArmNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmNode"/> class.
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
        /// Sends commands to controller.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="args">The command arguments.</param>
        /// <returns>The response.</returns>
        protected string SendCommand(string command, string args = null)
        {
            var request = string.Empty;
            if (string.IsNullOrEmpty(args))
            {
                request = $"harm:{command}:{(int)this.Type}:~harm";
            }
            else
            {
                request = $"harm:{command}:{(int)this.Type}:{args}:~harm";
            }

            Trace.WriteLine(request);
            this.Arm.SerialPort.WriteLine(request);

            var response = this.Arm.SerialPort.ReadLine();
            Trace.WriteLine(response);

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
