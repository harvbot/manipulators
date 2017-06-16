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
        /// Stores arm provider instance.
        /// </summary>
        private IHarvbotArmProvider provider;

        /// <summary>
        /// Stores value indicating that provider was injected and mustn't be disposed.
        /// </summary>
        private bool externalProvider;

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmBase"/> class.
        /// </summary>
        /// <param name="comNum">The COM number.</param>
        public HarvbotArmBase(string comNum) : this(new HarvbotArmSerialProvider(comNum))
        {
            this.externalProvider = false;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="HarvbotArmBase"/> class.
        /// </summary>
        /// <param name="provider">The arm controller provider.</param>
        public HarvbotArmBase(IHarvbotArmProvider provider)
        {
            this.externalProvider = true;
            this.provider = provider;

            this.Init();
            this.InitializeNodes();
        }

        /// <summary>
        /// Gets arm type.
        /// </summary>
        public abstract HarvbotArmTypes ArmType { get; }

        /// <summary>
        /// Gets serial port instance.
        /// </summary>
        internal IHarvbotArmProvider Provider
        {
            get
            {
                return this.provider;
            }
        }

        ~HarvbotArmBase()
        {
            this.Dispose(false);
        }

        /// <summary>
        /// Gets current arm status.
        /// </summary>
        /// <returns>The arm status.</returns>
        public HarvbotArmStatuses GetStatus()
        {
            var data = this.SendCommand(HarvbotArmCommands.Status);

            if (string.IsNullOrEmpty(data))
            {
                throw new InvalidOperationException("Invalid response data");
            }

            HarvbotArmStatuses status;
            if (!Enum.TryParse<HarvbotArmStatuses>(data, out status))
            {
                throw new InvalidOperationException($"Invalid response data {data}");
            }

            return status;
        }

        public void Init()
        {
            this.SendCommand(HarvbotArmCommands.Init, this.ArmType);
        }

        /// <summary>
        /// Moves arm to initial position.
        /// </summary>
        public void InitStart()
        {
            this.SendCommand(HarvbotArmCommands.InitStart);
        }

        /// <summary>
        /// Gets bedplate position.
        /// </summary>
        /// <returns>The bedplate position degree.</returns>
        public virtual float? GetBedplatePosition()
        {
            return this.GetCircleNodePosition(HarvbotArmNodeIdentifiers.Bedplate);
        }

        /// <summary>
        /// Moves bedplate.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual float? MoveBedplate(float degree)
        {
            return this.MoveCircleNode(HarvbotArmNodeIdentifiers.Bedplate, degree);
        }

        /// <summary>
        /// Gets shoulder position.
        /// </summary>
        /// <returns>The shoulder position degree.</returns>
        public virtual float? GetShoulderPosition()
        {
            return this.GetCircleNodePosition(HarvbotArmNodeIdentifiers.Shoulder);
        }

        /// <summary>
        /// Moves shoulder.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual float? MoveShoulder(float degree)
        {
            return this.MoveCircleNode(HarvbotArmNodeIdentifiers.Shoulder, degree);
        }

        /// <summary>
        /// Gets elbow position.
        /// </summary>
        /// <returns>The elbow position degree.</returns>
        public virtual float? GetElbowPosition()
        {
            return this.GetCircleNodePosition(HarvbotArmNodeIdentifiers.Elbow);
        }

        /// <summary>
        /// Moves elbow.
        /// </summary>
        /// <param name="degree">The degree.</param>
        public virtual float? MoveElbow(float degree)
        {
            return this.MoveCircleNode(HarvbotArmNodeIdentifiers.Elbow, degree);
        }

        /// <summary>
        /// Gets specified node position.
        /// </summary>
        /// <param name="identifier">The node identifier.</param>
        /// <returns>The node position.</returns>
        public virtual float? GetCircleNodePosition(HarvbotArmNodeIdentifiers identifier)
        {
            var node = this.nodes.FirstOrDefault(x => x.Node == identifier) as HarvbotArmCircleNode;
            if (node != null)
            {
                return node.GetPosition();
            }
            else
            {
                throw new InvalidOperationException($"The node {identifier} doesn't exist");
            }
        }

        /// <summary>
        /// Moves specified node on specified degree.
        /// </summary>
        /// <param name="identifier">The node identifier.</param>
        /// <param name="degree">The degree.</param>
        public virtual float? MoveCircleNode(HarvbotArmNodeIdentifiers identifier, float degree)
        {
            var shoulder = this.nodes.FirstOrDefault(x => x.Node == identifier) as HarvbotArmCircleNode;
            if (shoulder != null)
            {
                return shoulder.Move(degree);
            }
            else
            {
                throw new InvalidOperationException($"The node {identifier} doesn't exist");
            }
        }

        /// <summary>
        /// Gets the node instance by specified identifier.
        /// </summary>
        /// <param name="identifier">The node type.</param>
        /// <returns>The arm node.</returns>
        public virtual HarvbotArmNode GetNodeByIdentifier(HarvbotArmNodeIdentifiers identifier)
        {
            return this.nodes.FirstOrDefault(x => x.Node == identifier);
        }

        /// <summary>
        /// Gets the circle node by specified identifier.
        /// </summary>
        /// <param name="identifier">The node identifier.</param>
        /// <returns>The circle node.</returns>
        public HarvbotArmCircleNode GetCircleNodeByIdentifider(HarvbotArmNodeIdentifiers identifier)
        {
            return (HarvbotArmCircleNode)this.GetNodeByIdentifier(identifier);
        }

        /// <summary>
        /// Gets the screw node by specified identifier.
        /// </summary>
        /// <param name="identifier">The node identifier.</param>
        /// <returns>The screw node.</returns>
        public HarvbotArmScrewNode GetScrewNodeByIdentifider(HarvbotArmNodeIdentifiers identifier)
        {
            return (HarvbotArmScrewNode)this.GetNodeByIdentifier(identifier);
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
                if (!this.externalProvider)
                {
                    this.provider.Dispose();
                }

                this.isDisposed = true;
            }
        }

        /// <summary>
        /// Initializes arm nodes.
        /// </summary>
        protected abstract void InitializeNodes();

        /// <summary>
        /// Sends commands to controller.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="args">The command arguments.</param>
        /// <returns>The response.</returns>
        protected string SendCommand(HarvbotArmCommands command, params object[] args)
        {
            var response = this.Provider.SendRequest(new HarvbotArmRequest()
            {
                Command = command,
                Arguments = args
            });

            return response.Data;
        }
    }
}
