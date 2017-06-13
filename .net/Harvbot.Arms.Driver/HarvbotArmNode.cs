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
        public HarvbotArmNode(HarvbotArmNodeIdentifiers type, HarvbotArmBase arm)
        {
            this.Arm = arm;
            this.Node = type;
        }

        /// <summary>
        /// Gets the node owner.
        /// </summary>
        public HarvbotArmBase Arm { get; private set; }

        /// <summary>
        /// Gets the node identifier.
        /// </summary>
        public HarvbotArmNodeIdentifiers Node { get; private set; }

        /// <summary>
        /// Gets node type.
        /// </summary>
        public abstract HarvbotArmNodeTypes NodeType { get; }

        /// <summary>
        /// Gets current arm status.
        /// </summary>
        /// <returns>The arm status.</returns>
        public HarvbotArmStatuses GetStatus()
        {
            var data = this.SendCommand(HarvbotArmCommands.NodeStatus);

            if (string.IsNullOrEmpty(data))
            {
                throw new InvalidOperationException("Invalid response data");
            }

            HarvbotArmStatuses status;
            if (!Enum.TryParse<HarvbotArmStatuses>(data, out status))
            {
                throw new InvalidOperationException($"Invalid response data {data}");
            }

            return status;
        }

        /// <summary>
        /// Sends commands to controller.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="args">The command arguments.</param>
        /// <returns>The response.</returns>
        protected string SendCommand(HarvbotArmCommands command, params object[] args)
        {
            var response = this.Arm.Provider.SendRequest(new HarvbotArmRequest()
            {
                Command = command,
                Node = this.Node,
                Arguments =  args
            });

            return response.Data;
        }
    }
}
