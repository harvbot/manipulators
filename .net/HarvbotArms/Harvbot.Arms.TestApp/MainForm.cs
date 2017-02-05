using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Harvbot.Arms.Driver;

namespace HarvbotArms
{
    public partial class MainForm : Form
    {
        private bool isControlDisabled;

        private HarvbotArmBase arm;

        private Point currentMouseLocation;

        public MainForm()
        {
            InitializeComponent();

            this.isControlDisabled = true;
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            var ports = SerialPort.GetPortNames();
            foreach (var port in ports)
            {
                this.CbPorts.Items.Add(port);
            }

            this.CbArmTypes.Items.Add(HarvbotArmTypes.Type1);
        }

        private void BtnStartControl_Click(object sender, EventArgs e)
        {
            if (this.arm != null)
            {
                this.arm.Dispose();
            }

            this.arm = HarvbotArmFactory.GetInstance(this.CbPorts.SelectedText,
                (HarvbotArmTypes)this.CbArmTypes.SelectedItem);

            Cursor.Position = new Point(
                this.PnlControl.Location.X + this.PnlControl.Width / 2, 
                this.PnlControl.Location.Y + this.PnlControl.Height / 2);

            this.isControlDisabled = false;
        }

        private void BtnStopControl_Click(object sender, EventArgs e)
        {
            this.isControlDisabled = true;

            if (this.arm != null)
            {
                this.arm.Dispose();
            }
        }

        private void LblControlDescription_MouseMove(object sender, MouseEventArgs e)
        {
            if (!this.isControlDisabled)
            {
                this.arm.MoveBedplate(30);
                this.currentMouseLocation = e.Location;
            }
        }

        private void LblControlDescription_Click(object sender, EventArgs e)
        {

        }
    }
}
