using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm stepper node.
    /// </summary>
    public class HarvbotArmStepperNode : HarvbotArmNode
    {
        /// <summary>
        /// Stores current number of passed steps.
        /// </summary>
        private double? steps;

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmStepperNode"/> class.
        /// </summary>
        /// <param name="type">The node type.</param>
        /// <param name="arm">The owner.</param>
        public HarvbotArmStepperNode(HarvbotArmNodeTypes type, HarvbotArmBase arm) : base(type, arm)
        {
        }

        public double? GetPassedSteps()
        {
            if (!this.steps.HasValue)
            {
                var response = this.SendCommand("steps");

                if (!string.IsNullOrEmpty(response))
                {
                    this.steps = double.Parse(response);
                }

                this.steps = new double?();
            }

            return this.steps;
        }

        public double Rotate(double steps)
        {
            var response = this.SendCommand("rotate-steps", steps.ToString());

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }

        public double RotateOnAngle(double degree)
        {
            var response = this.SendCommand("rotate-angle", degree.ToString());

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }

        public double GetCurrentAngle()
        {
            var response = this.SendCommand("angle");

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper angle position taking was failed. Invalid response: {response}");
            }
        }

        public double RevolutionForward()
        {
            var response = this.SendCommand("revolution", "forward");

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }

        public double RevolutionBackward()
        {
            var response = this.SendCommand("revolution", "backward");

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }
    }
}
