using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
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

        private Timer timer;

        private Keys pressedKey;

        public MainForm()
        {
            InitializeComponent();

            this.isControlDisabled = true;

            this.timer = new Timer();
            this.timer.Interval = 300;
            this.timer.Enabled = false;
            this.timer.Tick += Timer_Tick;
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            if (this.isControlDisabled)
            {
                return;
            }

            switch (this.pressedKey)
            {
                case Keys.A:
                    {
                        this.MoveLeft();
                        break;
                    }
                case Keys.D:
                    {
                        this.MoveRight();
                        break;
                    }
                case Keys.W:
                    {
                        this.MoveUp();
                        break;
                    }
                case Keys.S:
                    {
                        this.MoveDown();
                        break;
                    }
                default: break;
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            var ports = SerialPort.GetPortNames();
            foreach (var port in ports)
            {
                this.CbPorts.Items.Add(port);
            }

            if (ports.Length > 0)
            {
                this.CbPorts.SelectedIndex = 0;
            }

            this.CbArmTypes.Items.Add(HarvbotArmTypes.Type1);
            this.CbArmTypes.Items.Add(HarvbotArmTypes.Type2);
            this.CbArmTypes.SelectedIndex = 0;
        }

        private void BtnStartControl_Click(object sender, EventArgs e)
        {
            if (this.arm != null)
            {
                this.arm.Dispose();
            }

            if (this.CbPorts.SelectedItem != null && this.CbArmTypes.SelectedItem != null)
            {
                this.arm = HarvbotArmFactory.GetInstance(this.CbPorts.SelectedItem.ToString(),
                    (HarvbotArmTypes)this.CbArmTypes.SelectedItem);

                this.isControlDisabled = false;
            }
        }

        private void BtnStopControl_Click(object sender, EventArgs e)
        {
            this.isControlDisabled = true;

            if (this.arm != null)
            {
                this.arm.Dispose();
            }
        }

        private void BtnLeft_Click(object sender, EventArgs e)
        {
            this.MoveLeft();
        }

        private void BtnRight_Click(object sender, EventArgs e)
        {
            this.MoveRight();
        }

        private void BtnUp_Click(object sender, EventArgs e)
        {
            this.MoveUp();
        }

        private void BtnDown_Click(object sender, EventArgs e)
        {
            this.MoveDown();
        }

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.A || e.KeyCode == Keys.D || e.KeyCode == Keys.W || e.KeyCode == Keys.S)
            {
                this.pressedKey = e.KeyCode;
                this.timer.Enabled = true;
            }
        }

        private void MainForm_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.A || e.KeyCode == Keys.D || e.KeyCode == Keys.W || e.KeyCode == Keys.S)
            {
                this.pressedKey = Keys.None;
                this.timer.Enabled = false;
            }
        }

        private void BtnOpenClaw_Click(object sender, EventArgs e)
        {
            this.OpenClaw();
        }

        private void BtnCloseClaw_Click(object sender, EventArgs e)
        {
            this.CloseClaw();
        }

        private void CbArmTypes_SelectedIndexChanged(object sender, EventArgs e)
        {
            var armType = (HarvbotArmTypes)this.CbArmTypes.SelectedItem;
            this.BtnCloseClaw.Enabled = this.BtnOpenClaw.Enabled = armType != HarvbotArmTypes.Type1;
        }

        private void MoveLeft()
        {
            var pos = this.arm.GetBedplatePosition().GetValueOrDefault(0) - 1;
            this.arm.MoveBedplate(pos);
        }

        private void MoveRight()
        {
            var pos = this.arm.GetBedplatePosition().GetValueOrDefault(0) + 1;
            this.arm.MoveBedplate(pos);
        }

        private void MoveUp()
        {
            var pos = this.arm.GetShoulderPosition().GetValueOrDefault(0) + 1;
            this.arm.MoveShoulder(pos);
        }

        private void MoveDown()
        {
            var pos = this.arm.GetShoulderPosition().GetValueOrDefault(0) - 1;
            this.arm.MoveShoulder(pos);
        }

        private void OpenClaw()
        {
            ((HarvbotArm2)this.arm).Claw.RevolutionForward();
        }

        private void CloseClaw()
        {
            ((HarvbotArm2)this.arm).Claw.RevolutionBackward();
        }
    }
}
