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
            fixture.ArmSubType = HarvbotArmSubTypes.AFMotor2;
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

        [Fact]
        public void Arm2Test_Claw_Steps()
        {
            var steps = this.fixture.Arm.Claw.GetPassedSteps();
            steps.HasValue.Should().Be(true);
            steps.Value.Should().BeGreaterOrEqualTo(0);
        }

        [Fact]
        public void Arm2Test_Claw_RotateSteps()
        {
            var steps = this.fixture.Arm.Claw.GetPassedSteps();
            steps.HasValue.Should().Be(true);
            steps.Value.Should().BeGreaterOrEqualTo(0);

            var newPos = this.fixture.Arm.Claw.Rotate(100);
            newPos.Should().Be(steps.Value + 100);
        }

        [Fact]
        public void Arm2Test_Claw_RevolutionForward()
        {
            var steps = this.fixture.Arm.Claw.GetPassedSteps();
            steps.HasValue.Should().Be(true);
            steps.Value.Should().BeGreaterOrEqualTo(0);

            var newPos = this.fixture.Arm.Claw.RevolutionForward();
            newPos.Should().BeGreaterThan(steps.Value);
        }

        [Fact]
        public void Arm2Test_Claw_RevolutionBackward()
        {
            var steps = this.fixture.Arm.Claw.GetPassedSteps();
            steps.HasValue.Should().Be(true);
            steps.Value.Should().BeGreaterOrEqualTo(0);

            var newPos = this.fixture.Arm.Claw.RevolutionBackward();
            newPos.Should().BeLessOrEqualTo(steps.Value);
        }

        [Fact]
        public void Arm2Test_Claw_RotateAngle()
        {
            var angle = this.fixture.Arm.Claw.GetCurrentAngle();
            angle.Should().BeGreaterOrEqualTo(0);

            this.fixture.Arm.Claw.RotateOnAngle(45.0);

            var newAngle = this.fixture.Arm.Claw.GetCurrentAngle();
            var fullRotation = Math.Truncate((angle + 45.0) / 360);
            newAngle.Should().Be((angle + 45.0)- fullRotation * 360);
        }

        [Fact]
        public void ArmTest2_InitStart()
        {
            this.ArmTest_InitStart();
        }

        [Fact]
        public void ArmTest2_GetStatus()
        {
            this.ArmTest_GetStatus();
        }

        [Fact]
        public void ArmTest2_GetNodeStatus()
        {
            this.ArmTest_GetNodeStatus();

            this.ArmTest_GetStatus_ArmNode(this.fixture.Arm.GetScrewNodeByIdentifider(HarvbotArmNodeIdentifiers.Claw));
        }
    }
}
