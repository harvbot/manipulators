using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            var bedplate = this.nodes.FirstOrDefault(x => x.Type == HarvbotArmNodeTypes.Bedplate);
            if (bedplate != null)
            {
                return bedplate.GetPosition();
            }

            return new int?();
        }

        /// <summary>
        /// Moves bedplate.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual void MoveBedplate(int degree)
        {
            var bedplate = this.nodes.FirstOrDefault(x => x.Type == HarvbotArmNodeTypes.Bedplate);
            if (bedplate != null)
            {
                bedplate.Move(degree);
            }
        }

        /// <summary>
        /// Gets shoulder position.
        /// </summary>
        /// <returns>The shoulder position degree.</returns>
        public virtual int? GetShoulderPosition()
        {
            var shoulder = this.nodes.FirstOrDefault(x => x.Type == HarvbotArmNodeTypes.Shoulder);
            if (shoulder != null)
            {
                return shoulder.GetPosition();
            }

            return new int?();
        }

        /// <summary>
        /// Moves shoulder.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual void MoveShoulder(int degree)
        {
            var shoulder = this.nodes.FirstOrDefault(x => x.Type == HarvbotArmNodeTypes.Shoulder);
            if (shoulder != null)
            {
                shoulder.Move(degree);
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
