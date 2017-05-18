using System;
using System.Configuration;
using Harvbot.Arms.Driver;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using Xunit;
using FluentAssertions;
using HarvbotArm.Tests.Fixtures;

namespace HarvbotArm.Tests.Integration
{
    public class Arm1Test : IClassFixture<Arm1Fixture>
    {
        private Arm1Fixture fixture;

        public Arm1Test(Arm1Fixture fixture)
        {
            this.fixture = fixture;
        }

        [Theory]
        [InlineData(HarvbotArmNodeTypes.Bedplate)]
        [InlineData(HarvbotArmNodeTypes.Shoulder)]
        [InlineData(HarvbotArmNodeTypes.Elbow)]
        public void GetPosition(HarvbotArmNodeTypes nodeType)
        {
            var position = this.fixture.Arm.GetServoNodePosition(nodeType);

            position.HasValue.Should().Be(true);
            position.Value.Should().BeGreaterOrEqualTo(0);
            position.Value.Should().BeLessOrEqualTo(180);
        }
    }
}
