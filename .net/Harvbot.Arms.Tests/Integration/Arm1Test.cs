using System;
using System.Configuration;
using FluentAssertions;
using Harvbot.Arms.Driver;
using HarvbotArm.Tests.Fixtures;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using Xunit;

namespace HarvbotArm.Tests.Integration
{
    public class Arm1Test : BaseArmTest<HarvbotArm1>, IClassFixture<GenericArmFixture<HarvbotArm1>>
    {
        public Arm1Test(GenericArmFixture<HarvbotArm1> fixture) 
            : base(fixture)
        {
            fixture.ArmSubType = HarvbotArmSubTypes.Servo1;
        }

        [Theory]
        [InlineData(HarvbotArmNodeIdentifiers.Bedplate)]
        [InlineData(HarvbotArmNodeIdentifiers.Shoulder)]
        [InlineData(HarvbotArmNodeIdentifiers.Elbow)]
        public void Arm1Test_GetPosition(HarvbotArmNodeIdentifiers nodeType)
        {
            this.ArmTest_GetPosition(nodeType);
        }

        [Fact]
        public void Arm1Test_SetPosition_Bedplate()
        {
            this.ArmTest_SetPosition_Bedplate();
        }

        [Fact]
        public void Arm1Test_SetPosition_Shoulder()
        {
            this.ArmTest_SetPosition_Shoulder();
        }

        [Fact]
        public void Arm1Test_SetPosition_Elbow()
        {
            this.ArmTest_SetPosition_Elbow();
        }
    }
}
