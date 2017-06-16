using System;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents arm serial provider.
    /// </summary>
    public class HarvbotArmSerialProvider : IHarvbotArmProvider
    {
        #region Fields

        /// <summary>
        /// Stores value indicating whether provider was disposed.
        /// </summary>
        private bool isDisposed;

        /// <summary>
        /// Stores serial port instance.
        /// </summary>
        private SerialPort serial;

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmSerialProvider"/> class.
        /// </summary>
        /// <param name="comNum">The COM number.</param>
        public HarvbotArmSerialProvider(string comNum)
        {
            if (string.IsNullOrEmpty(comNum))
            {
                throw new ArgumentNullException("comNum");
            }

            this.serial = new SerialPort(comNum, HarvbotArmBase.BaudRate);

            if (!this.serial.IsOpen)
            {
                this.serial.Open();
            }
        }

        /// <summary>
        /// Sends request to arm controller.
        /// </summary>
        /// <param name="request">The request.</param>
        /// <returns>The response.</returns>
        public HarvbotArmResponse SendRequest(HarvbotArmRequest request)
        {
            if (request == null)
            {
                throw new ArgumentNullException("request");
            }

            var command = ConvertCommandToString(request.Command);
            var requestData = $"harm:{command}:";

            if (request.Node.HasValue)
            {
                requestData += $"{(int)request.Node}:";
            }

            if (request.Arguments != null && request.Arguments.Length > 0)
            { 
                var args = string.Join(":", request.Arguments.Select(x => ConvertArgumentToString(x)).ToArray());
                requestData += $"{args}:";
            }

            requestData += "~harm";

            Trace.WriteLine(requestData);            
            this.serial.WriteLine(requestData);

            string response;
            do
            {
                response = this.serial.ReadLine();
            }
            while (string.IsNullOrEmpty(response));
            Trace.WriteLine(response);

            var segments = response.Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);

            if (segments[0].Equals("harm", StringComparison.InvariantCultureIgnoreCase) &&
                segments[1].Equals(command, StringComparison.InvariantCultureIgnoreCase) &&
                (request.Node.HasValue && segments[2].Equals(((int)request.Node).ToString(), StringComparison.InvariantCultureIgnoreCase) || !request.Node.HasValue) &&
                segments.Last().Equals("~harm", StringComparison.InvariantCultureIgnoreCase))
            {
                throw new InvalidOperationException($"Invalid response: {response}");
            }

            return new HarvbotArmResponse()
            {
                Command = request.Command,
                Node = request.Node,
                Data = request.Node.HasValue ? 
                    (segments.Length > 4 ? segments[3] : null) : 
                    (segments.Length > 3 ? segments[2] : null)
            };
        }

        /// <summary>
        /// Releases all resources used by current instance.
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool isDisposing)
        {
            if (!this.isDisposed)
            {
                this.serial.Dispose();
                this.isDisposed = true;
            }
        }

        private static string ConvertCommandToString(HarvbotArmCommands cmd)
        {
            switch (cmd)
            {
                case HarvbotArmCommands.Position:
                    return "pos";
                case HarvbotArmCommands.Move:
                    return "move";
                case HarvbotArmCommands.Revolution:
                    return "revolution";
                case HarvbotArmCommands.Steps:
                    return "steps";
                case HarvbotArmCommands.Angle:
                    return "angle";
                case HarvbotArmCommands.RotateOnAngle:
                    return "rotate-angle";
                case HarvbotArmCommands.RotateOnSteps:
                    return "rotate-steps";
                case HarvbotArmCommands.Init:
                    return "init";
                case HarvbotArmCommands.InitStart:
                    return "init-start";
                case HarvbotArmCommands.NodeStatus:
                    return "node-status";
                case HarvbotArmCommands.Status:
                    return "status";
                default: throw new ArgumentOutOfRangeException($"The {cmd} is not supported in Serial provider");
            }
        }

        private static string ConvertArgumentToString(object arg)
        {
            if (arg is HarvbotArmTypes)
            {
                return ((int)(HarvbotArmTypes)arg).ToString();
            }

            return arg.ToString();
        }
    }
}
