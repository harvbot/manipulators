﻿using System;
using System.Configuration;
using FluentAssertions;
using Harvbot.Arms.Driver;
using HarvbotArm.Tests.Fixtures;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using Xunit;

namespace HarvbotArm.Tests.Integration
{
    public abstract class BaseArmTest<T> : IClassFixture<GenericArmFixture<T>> where T: HarvbotArmBase
    {
        protected GenericArmFixture<T> fixture;

        public BaseArmTest(GenericArmFixture<T> fixture)
        {
            this.fixture = fixture;
        }

        protected void ArmTest_GetPosition(HarvbotArmNodeIdentifiers identifieer)
        {
            var position = this.fixture.Arm.GetCircleNodePosition(identifieer);

            position.HasValue.Should().Be(true);
            position.Value.Should().BeGreaterOrEqualTo(0);
            position.Value.Should().BeLessOrEqualTo(180);
        }

        protected void ArmTest_SetPosition_Bedplate()
        {
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Bedplate), 90.0f, 90.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Bedplate), 90.5f, 90.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Bedplate), 320.0f, 180.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Bedplate), -1.0f, 0.0f);
        }

        protected void ArmTest_SetPosition_Shoulder()
        {
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Shoulder), 90.0f, 90.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Shoulder), 90.5f, 90.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Shoulder), 320.0f, 180.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Shoulder), -1.0f, 5.0f);
        }

        protected void ArmTest_SetPosition_Elbow()
        {
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Elbow), 90.0f, 90.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Elbow), 90.5f, 90.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Elbow), 320.0f, 180.0f);
            ArmTest_SetCirclePosition_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Elbow), -1.0f, 20.0f);
        }

        protected void ArmTest_GetNodeStatus()
        {
            ArmTest_GetStatus_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Bedplate));
            ArmTest_GetStatus_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Shoulder));
            ArmTest_GetStatus_ArmNode(this.fixture.Arm.GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers.Elbow));
        }

        protected void ArmTest_SetCirclePosition_ArmNode(HarvbotArmCircleNode node, float target, float expected)
        {
            float? position = null;
            position = node.Move(target);
            position.HasValue.Should().Be(true);
            position.Value.Should().Be(expected);
        }

        protected void ArmTest_GetStatus_ArmNode(HarvbotArmNode node)
        {
            var status = node.GetStatus();
            status.Should().Be(HarvbotArmStatuses.Ready);
        }

        protected void ArmTest_InitStart()
        {
            this.fixture.Arm.InitStart();
        }

        protected void ArmTest_GetStatus()
        {
            var status = this.fixture.Arm.GetStatus();
            status.Should().Be(HarvbotArmStatuses.Ready);
        }
    }
}
