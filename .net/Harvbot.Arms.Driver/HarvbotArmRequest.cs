using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm command request.
    /// </summary>
    public class HarvbotArmRequest
    {
        /// <summary>
        /// Gets or sets requested command.
        /// </summary>
        public HarvbotArmCommands Command { get; set; }

        /// <summary>
        /// Gets or sets the requested arm node.
        /// </summary>
        public HarvbotArmNodeIdentifiers? Node { get; set; }

        /// <summary>
        /// Gets or sets additional arguments.
        /// </summary>
        public object[] Arguments { get; set; }
    }
}
