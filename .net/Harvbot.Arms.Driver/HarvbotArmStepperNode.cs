using System;

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
                var response = this.SendCommand(HarvbotArmCommands.Steps);

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
