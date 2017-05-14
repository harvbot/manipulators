using System;
using Harvbot.Arms.Driver;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;

namespace HarvbotArm.Tests
{
    [TestClass]
    public class Arm1Test
    {
        [TestMethod]
        public void GetPosition()
        {
            Mock<IHarvbotArmProvider> provider = new Mock<IHarvbotArmProvider>();

            provider.Setup(x => x.SendRequest(It.IsAny<HarvbotArmRequest>())).Callback((HarvbotArmRequest request) =>
            {

            }).Returns(new HarvbotArmResponse()
            {
            });
        }
    }
}
