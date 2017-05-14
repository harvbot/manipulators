using System;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm provider.
    /// </summary>
    public interface IHarvbotArmProvider: IDisposable
    {
        /// <summary>
        /// Sends request to arm controller.
        /// </summary>
        /// <param name="request">The request.</param>
        /// <returns>The response.</returns>
        HarvbotArmResponse SendRequest(HarvbotArmRequest request);
    }
}
