using System;
using System.Configuration;
using Harvbot.Arms.Driver;

namespace HarvbotArm.Tests.Fixtures
{
    public class Arm1Fixture : IDisposable
    {
        private HarvbotArm1 arm;

        public Arm1Fixture()
        {
            this.arm = new HarvbotArm1(ConfigurationManager.AppSettings["usb-serial"]);
        }

        public HarvbotArm1 Arm
        {
            get
            {
                return this.arm;
            }
        }

        public void Dispose()
        {
            this.arm.Dispose();
        }
    }
}
