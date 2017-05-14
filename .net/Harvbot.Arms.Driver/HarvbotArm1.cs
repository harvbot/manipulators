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
        public HarvbotArm1(string comNum) : base(comNum)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArm1"/> class.
        /// </summary>
        /// <param name="provider">The arm controller provider.</param>
        public HarvbotArm1(IHarvbotArmProvider provider) : base(provider)
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
                new HarvbotArmServoNode(HarvbotArmNodeTypes.Bedplate, this),
                new HarvbotArmServoNode(HarvbotArmNodeTypes.Shoulder, this),
                new HarvbotArmServoNode(HarvbotArmNodeTypes.Elbow, this),
                new HarvbotArmServoNode(HarvbotArmNodeTypes.ElbowScrew, this),
                new HarvbotArmServoNode(HarvbotArmNodeTypes.Hand, this),
                new HarvbotArmServoNode(HarvbotArmNodeTypes.HandScrew, this)
            };
        }
    }
}
