using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Harvbot.Arms.Driver;

namespace HarvbotArm.Tests.Fixtures
{
    public class TestAssemblyFixture : IDisposable
    {
        private static object rootSync = new object();

        private static IHarvbotArmProvider provider;

        public static IHarvbotArmProvider Provider
        {
            get
            {
                if (provider == null)
                {
                    lock (rootSync)
                    {
                        if (provider == null)
                        {
                            provider = new HarvbotArmSerialProvider(ConfigurationManager.AppSettings["usb-serial"]);
                        }
                    }
                }

                return provider;
            }
        }

        public void Dispose()
        {
            if (provider != null)
            {
                provider.Dispose();
            }
        }
    }
}
