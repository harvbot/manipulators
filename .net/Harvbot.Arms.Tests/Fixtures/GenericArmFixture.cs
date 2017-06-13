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
        }

        public HarvbotArmSubTypes ArmSubType { get; set; }

        public T Arm
        {
            get
            {
                if (this.arm == null)
                {
                    this.arm = this.InitializeArm();
                }

                return this.arm;
            }
        }

        public void Dispose()
        {
            this.arm.Dispose();
        }

        public T InitializeArm()
        {
            return (T)Activator.CreateInstance(typeof(T), new object[] { TestAssemblyFixture.Provider, this.ArmSubType });
        }
    }
}
