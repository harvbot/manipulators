using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Reprersents Harvbot Arm Type 1.
    /// </summary>
    public sealed class HarvbotArm1 : HarvbotArmBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArm1"/> class.
        /// </summary>
        /// <param name="comNum">The COM number.</param>
        /// <param name="subType">The arm sub type.</param>
        public HarvbotArm1(string comNum, HarvbotArmSubTypes subType) : base(comNum, subType)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArm1"/> class.
        /// </summary>
        /// <param name="provider">The arm controller provider.</param>
        /// <param name="subType">The arm sub type.</param>
        public HarvbotArm1(IHarvbotArmProvider provider, HarvbotArmSubTypes subType) : base(provider, subType)
        {
        }

        /// <summary>
        /// Gets the arm type.
        /// </summary>
        public override HarvbotArmTypes ArmType
        {
            get
            {
                return HarvbotArmTypes.Type1;
            }
        }

        /// <summary>
        /// Initializes arm nodes.
        /// </summary>
        protected override void InitializeNodes()
        {
            this.nodes = new HarvbotArmNode[]
            {
                new HarvbotArmCircleNode(HarvbotArmNodeIdentifiers.Bedplate, this),
                new HarvbotArmCircleNode(HarvbotArmNodeIdentifiers.Shoulder, this),
                new HarvbotArmCircleNode(HarvbotArmNodeIdentifiers.Elbow, this),
                new HarvbotArmCircleNode(HarvbotArmNodeIdentifiers.ElbowScrew, this),
                new HarvbotArmCircleNode(HarvbotArmNodeIdentifiers.Hand, this),
                new HarvbotArmCircleNode(HarvbotArmNodeIdentifiers.HandScrew, this)
            };
        }

        /// <summary>
        /// Checks that specified sub type is valid for specified arm type.
        /// </summary>
        protected override void CheckArmSubType()
        {
            if (this.SubType != HarvbotArmSubTypes.Servo1)
            {
                throw new InvalidProgramException($"The sub type {this.SubType} is not allowed for arm type 2");
            }
        }
    }
}
