using System;
using System.IO.Ports;
using System.Linq;

namespace Harvbot.Arms.Driver
{
    /// <summary>
    /// Represents Harvbot Arm base driver.
    /// </summary>
    public abstract class HarvbotArmBase : IDisposable
    {
        #region Constants

        /// <summary>
        /// Laser rangefinder baud rate.
        /// </summary>
        public const int BaudRate = 9600;

        #endregion

        #region Fields

        /// <summary>
        /// Stores arm nodes.
        /// </summary>
        protected HarvbotArmNode[] nodes;

        /// <summary>
        /// Stores value indicating whether driver was disposed.
        /// </summary>
        private bool isDisposed;

        /// <summary>
        /// Stores serial port instance.
        /// </summary>
        private SerialPort serial;

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmBase"/> class.
        /// </summary>
        /// <param name="comNum">The COM number.</param>
        public HarvbotArmBase(string comNum)
        {
            if (string.IsNullOrEmpty(comNum))
            {
                throw new ArgumentNullException("comNum");
            }

            this.serial = new SerialPort(comNum, HarvbotArmBase.BaudRate);
            this.serial.DtrEnable = true;
            if (!this.serial.IsOpen)
            {
                this.serial.Open();
            }

            this.InitializeNodes();
        }

        /// <summary>
        /// Gets arm type.
        /// </summary>
        public abstract HarvbotArmTypes ArmType { get; }

        /// <summary>
        /// Gets serial port instance.
        /// </summary>
        internal SerialPort SerialPort
        {
            get
            {
                return this.serial;
            }
        }

        ~HarvbotArmBase()
        {
            this.Dispose(false);
        }

        /// <summary>
        /// Opens rangefinder to start measurement.
        /// </summary>
        public void Open()
        {
            this.serial.Open();
        }

        /// <summary>
        /// Closes rangefinder.
        /// </summary>
        public void Close()
        {
            this.serial.Close();
        }

        /// <summary>
        /// Gets bedplate position.
        /// </summary>
        /// <returns>The bedplate position degree.</returns>
        public virtual int? GetBedplatePosition()
        {
            return this.GetServoNodePosition(HarvbotArmNodeTypes.Bedplate);
        }

        /// <summary>
        /// Moves bedplate.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual int? MoveBedplate(int degree)
        {
            return this.MoveServoNode(HarvbotArmNodeTypes.Bedplate, degree);
        }

        /// <summary>
        /// Gets shoulder position.
        /// </summary>
        /// <returns>The shoulder position degree.</returns>
        public virtual int? GetShoulderPosition()
        {
            return this.GetServoNodePosition(HarvbotArmNodeTypes.Shoulder);
        }

        /// <summary>
        /// Moves shoulder.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual int? MoveShoulder(int degree)
        {
            return this.MoveServoNode(HarvbotArmNodeTypes.Shoulder, degree);
        }

        /// <summary>
        /// Gets elbow position.
        /// </summary>
        /// <returns>The elbow position degree.</returns>
        public virtual int? GetElbowPosition()
        {
            return this.GetServoNodePosition(HarvbotArmNodeTypes.Elbow);
        }

        /// <summary>
        /// Moves elbow.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual int? MoveElbow(int degree)
        {
            return this.MoveServoNode(HarvbotArmNodeTypes.Elbow, degree);
        }

        /// <summary>
        /// Gets specified node position.
        /// </summary>
        /// <param name="nodeType">The node type.</param>
        /// <returns>The node position.</returns>
        public virtual int? GetServoNodePosition(HarvbotArmNodeTypes nodeType)
        {
            var node = this.nodes.FirstOrDefault(x => x.Type == nodeType) as HarvbotArmServoNode;
            if (node != null)
            {
                return node.GetPosition();
            }
            else
            {
                throw new InvalidOperationException($"The node {nodeType} doesn't exist");
            }
        }

        /// <summary>
        /// Moves specified node on specified degree.
        /// </summary>
        /// <param name="nodeType">The node type.</param>
        /// <param name="degree">The degree.</param>
        public virtual int? MoveServoNode(HarvbotArmNodeTypes nodeType, int degree)
        {
            var shoulder = this.nodes.FirstOrDefault(x => x.Type == nodeType) as HarvbotArmServoNode;
            if (shoulder != null)
            {
                return shoulder.Move(degree);
            }
            else
            {
                throw new InvalidOperationException($"The node {nodeType} doesn't exist");
            }
        }

        /// <summary>
        /// Sweeps specified node on specified degree.
        /// </summary>
        /// <param name="nodeType">The node type.</param>
        /// <param name="degree">The degree.</param>
        public virtual int? SweepServoNode(HarvbotArmNodeTypes nodeType, int degree)
        {
            var shoulder = this.nodes.FirstOrDefault(x => x.Type == nodeType) as HarvbotArmServoNode;
            if (shoulder != null)
            {
                return shoulder.Sweep(degree);
            }
            else
            {
                throw new InvalidOperationException($"The node {nodeType} doesn't exist");
            }
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

        /// <summary>
        /// Initializes arm nodes.
        /// </summary>
        protected abstract void InitializeNodes();
    }
}
