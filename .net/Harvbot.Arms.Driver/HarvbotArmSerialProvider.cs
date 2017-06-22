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

            var requestData = ConvertCommandToString(request.Command);

            if (request.Node.HasValue)
            {
                requestData += $" {ConvertNodeToString(request.Node.Value)}";
            }

            if (request.Arguments != null && request.Arguments.Length > 0)
            { 
                var args = string.Join(":", request.Arguments.Select(x => ConvertArgumentToString(x)).ToArray());

                if (request.Node.HasValue)
                {
                    requestData += $"{args}";
                }
                else
                {
                    requestData += $" {args}";
                }
            }

            Trace.WriteLine(requestData);            
            this.serial.WriteLine(requestData);

            string response;
            do
            {
                response = this.serial.ReadLine();
            }
            while (string.IsNullOrEmpty(response));
            Trace.WriteLine(response);

            response = response.Trim();

            var segments = response.Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);

            if (segments.Length > 0)
            {
                if (segments[0].Equals("error", StringComparison.InvariantCultureIgnoreCase))
                {
                    if (segments.Length == 2)
                    {
                        HarvbotArmErrorCodes errorCode = (HarvbotArmErrorCodes)int.Parse(segments[1].Trim());
                        throw new InvalidOperationException($"Error: {errorCode}");
                    }
                }
                else if (segments[0].Equals("ok", StringComparison.InvariantCultureIgnoreCase))
                {
                    var responseNodeType = string.Empty;
                    var responseValue = string.Empty;
                    if (segments.Length > 1)
                    {
                        if (request.Node.HasValue)
                        {
                            responseNodeType = segments[1].Substring(0, 2);
                            responseValue = segments[1].Substring(2);
                        }
                        else
                        {
                            responseValue = segments[1];
                        }
                    }
                    
                    return new HarvbotArmResponse()
                    {
                        Command = request.Command,
                        Node = request.Node,
                        Data = responseValue
                    };
                }
            }

            throw new InvalidOperationException($"Invalid response: {response}");
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
                    return "HNP";
                case HarvbotArmCommands.Move:
                    return "HNM";
                case HarvbotArmCommands.Revolution:
                    return "HRE";
                case HarvbotArmCommands.Steps:
                    return "HSS";
                case HarvbotArmCommands.Angle:
                    return "HSA";
                case HarvbotArmCommands.RotateOnAngle:
                    return "HRA";
                case HarvbotArmCommands.RotateOnSteps:
                    return "HSR";
                case HarvbotArmCommands.Init:
                    return "HIN";
                case HarvbotArmCommands.InitStart:
                    return "HIS";
                case HarvbotArmCommands.NodeStatus:
                    return "HNS";
                case HarvbotArmCommands.Status:
                    return "HAS";
                default: throw new ArgumentOutOfRangeException($"The {cmd} is not supported in Serial provider");
            }
        }

        private static string ConvertNodeToString(HarvbotArmNodeIdentifiers node)
        {
            switch (node)
            {
                case HarvbotArmNodeIdentifiers.Bedplate:
                    return "BP";
                case HarvbotArmNodeIdentifiers.Shoulder:
                    return "SH";
                case HarvbotArmNodeIdentifiers.Elbow:
                    return "EL";
                case HarvbotArmNodeIdentifiers.ElbowScrew:
                    return "ES";
                case HarvbotArmNodeIdentifiers.Hand:
                    return "HA";
                case HarvbotArmNodeIdentifiers.HandScrew:
                    return "HS";
                case HarvbotArmNodeIdentifiers.Claw:
                    return "CL";
                default: throw new ArgumentOutOfRangeException($"The {node} node type is not supported in Serial provider");
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
