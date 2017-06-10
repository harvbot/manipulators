using System;
using System.Configuration;
using Harvbot.Arms.Driver;

namespace HarvbotArm.Tests.Fixtures
{
    public class GenericArmFixture<T> : IDisposable where T : HarvbotArmBase
    {
        protected T arm;

        public GenericArmFixture()
        {
            this.arm = this.InitializeArm();
        }

        public T Arm
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

        protected T InitializeArm()
        {
            return (T)Activator.CreateInstance(typeof(T), new object[] { TestAssemblyFixture.Provider });
        }
    }
}
