using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Reprersents Harvbot Arm Type 2.
    /// </summary>
    public sealed class HarvbotArm2 : HarvbotArmBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArm1"/> class.
        /// </summary>
        /// <param name="comNum">The COM number.</param>
        public HarvbotArm2(string comNum) : base(comNum)
        {
        }

        /// <summary>
        /// Gets the arm type.
        /// </summary>
        public override HarvbotArmTypes ArmType
        {
            get
            {
                return HarvbotArmTypes.Type2;
            }
        }

        public HarvbotArmStepperNode Claw
        {
            get
            {
                return (HarvbotArmStepperNode)this.nodes[3];
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
                new HarvbotArmStepperNode(HarvbotArmNodeTypes.Claw, this),
            };
        }
    }
}
