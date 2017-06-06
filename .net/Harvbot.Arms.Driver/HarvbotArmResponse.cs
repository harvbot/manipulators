namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represnets the arm command response.
    /// </summary>
    public class HarvbotArmResponse
    {
        /// <summary>
        /// Gets or sets response command.
        /// </summary>
        public HarvbotArmCommands Command { get; set; }

        /// <summary>
        /// Gets or sets the response arm node.
        /// </summary>
        public HarvbotArmNodeIdentifiers Node { get; set; }

        /// <summary>
        /// Gets or sets the response additional data.
        /// </summary>
        public string Data { get; set; }
    }
}
