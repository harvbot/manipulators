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
    public class Arm2Test : BaseArmTest<HarvbotArm2>, IClassFixture<GenericArmFixture<HarvbotArm2>>
    {
        public Arm2Test(GenericArmFixture<HarvbotArm2> fixture) 
            : base(fixture)
        {
        }

        [Theory]
        [InlineData(HarvbotArmNodeIdentifiers.Bedplate)]
        [InlineData(HarvbotArmNodeIdentifiers.Shoulder)]
        [InlineData(HarvbotArmNodeIdentifiers.Elbow)]
        public void Arm2Test_GetPosition(HarvbotArmNodeIdentifiers nodeType)
        {
            this.ArmTest_GetPosition(nodeType);
        }

        [Fact]
        public void Arm2Test_SetPosition_Bedplate()
        {
            this.ArmTest_SetPosition_Bedplate();
        }

        [Fact]
        public void Arm2Test_SetPosition_Shoulder()
        {
            this.ArmTest_SetPosition_Shoulder();
        }

        [Fact]
        public void Arm2Test_SetPosition_Elbow()
        {
            this.ArmTest_SetPosition_Elbow();
        }
    }
}
