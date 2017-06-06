using System;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm stepper node.
    /// </summary>
    public class HarvbotArmScrewNode : HarvbotArmNode
    {
        /// <summary>
        /// Stores current number of passed steps.
        /// </summary>
        private double? steps;

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmScrewNode"/> class.
        /// </summary>
        /// <param name="type">The node type.</param>
        /// <param name="arm">The owner.</param>
        public HarvbotArmScrewNode(HarvbotArmNodeIdentifiers type, HarvbotArmBase arm) : base(type, arm)
        {
        }

        /// <summary>
        /// Gets node type.
        /// </summary>
        public override HarvbotArmNodeTypes NodeType
        {
            get
            {
                return HarvbotArmNodeTypes.Screw;
            }
        }

        /// <summary>
        /// Gets the number of passed steps.
        /// </summary>
        /// <returns>The passed steps number.</returns>
        public double? GetPassedSteps()
        {
            if (!this.steps.HasValue)
            {
                var response = this.SendCommand(HarvbotArmCommands.Steps);

                if (!string.IsNullOrEmpty(response))
                {
                    this.steps = double.Parse(response);
                }

                this.steps = new double?();
            }

            return this.steps;
        }

        /// <summary>
        /// Rotates screw on specified number of steps.
        /// </summary>
        /// <param name="steps">The number of steps.</param>
        /// <returns>The new screw position.</returns>
        public double Rotate(double steps)
        {
            var response = this.SendCommand(HarvbotArmCommands.RotateOnSteps, steps);

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }

        /// <summary>
        /// Rotates screw on specified angle.
        /// </summary>
        /// <param name="degree">The rotation angle.</param>
        /// <returns>The new screw position.</returns>
        public double RotateOnAngle(double degree)
        {
            var response = this.SendCommand(HarvbotArmCommands.RotateOnAngle, degree);

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }

        /// <summary>
        /// Gets current screw angle.
        /// </summary>
        /// <returns>The angle degree.</returns>
        public double GetCurrentAngle()
        {
            var response = this.SendCommand(HarvbotArmCommands.Angle);

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper angle position taking was failed. Invalid response: {response}");
            }
        }

        /// <summary>
        /// Makes one forward revolution.
        /// </summary>
        /// <returns>The new screw position.</returns>
        public double RevolutionForward()
        {
            var response = this.SendCommand(HarvbotArmCommands.Revolution, HarvbotArmStepperDirections.Forward);

            if (!string.IsNullOrEmpty(response))
            {
                return double.Parse(response);
            }
            else
            {
                throw new InvalidOperationException($"Stepper rotation failed. Invalid response: {response}");
            }
        }

        /// <summary>
        /// Makes one backward revolution.
        /// </summary>
        /// <returns>The new screw position.</returns>
        public double RevolutionBackward()
        {
            var response = this.SendCommand(HarvbotArmCommands.Revolution, HarvbotArmStepperDirections.Backward);

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
