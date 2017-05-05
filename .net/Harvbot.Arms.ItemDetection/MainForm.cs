using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.Cuda;
using Emgu.CV.Structure;
using Harvbot.Arms.Driver;

namespace Harvbot.Arms.ItemDetection
{
    public partial class MainForm : Form
    {
        private const int Threshold = 8;

        private VideoCapture capture;

        private Mat frame;

        private CascadeClassifier recognizer;

        private HarvbotArmBase arm;

        private Thread manipulatorThread;

        private ConcurrentQueue<int> commandsQueue;

        public MainForm()
        {
            InitializeComponent();

            CvInvoke.UseOpenCL = false;
            this.capture = new VideoCapture();
            this.capture.ImageGrabbed += this.ProcessFrame;
            this.frame = new Mat();

            this.manipulatorThread = new Thread(new ThreadStart(this.ProcessManipulatorCommand));
            this.commandsQueue = new ConcurrentQueue<int>();
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
            this.CbArmTypes.SelectedIndex = 0;

            this.ibVideo.Image = this.capture.QueryFrame();
            this.capture.Start();

            this.manipulatorThread.Start();
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);

            if (this.manipulatorThread != null)
            {
                this.manipulatorThread.Abort();
            }

            if (this.capture != null)
            {
                this.capture.Dispose();
            }

            if (this.recognizer != null)
            {
                this.recognizer.Dispose();
            }
        }

        private void ProcessFrame(object sender, EventArgs arg)
        {
            if (this.capture != null && this.capture.Ptr != IntPtr.Zero)
            {
                this.capture.Retrieve(this.frame, 0);

                if (this.recognizer != null)
                {
                    lock (this)
                    {
                        if (this.recognizer != null)
                        {
                            using (var imageFrame = this.frame.ToImage<Bgr, byte>())
                            using (var grayframe = imageFrame.Convert<Gray, byte>())
                            {
                                //Detect the faces  from the gray scale image and store the locations as rectangle
                                //The first dimensional is the channel
                                //The second dimension is the index of the rectangle in the specific channel                     
                                var detectionResult = this.recognizer.DetectMultiScale(
                                    grayframe,
                                    1.1,
                                    10,
                                    new Size(20, 20));

                                if (detectionResult != null && detectionResult.Length > 0)
                                {
                                    var rect = detectionResult.First();
                                    imageFrame.Draw(rect, new Bgr(Color.Red), 2);

                                    var deltaX = (imageFrame.Width - rect.Width) / 2 - rect.X;

                                    var cX = deltaX * 180 / imageFrame.Width;

                                    this.commandsQueue.Enqueue(cX);
                                }

                                this.ibVideo.Image = imageFrame;
                            }
                        }
                    }
                }
                else
                {
                    this.ibVideo.Image = this.frame;
                }
            }
        }

        private void ProcessManipulatorCommand()
        {
            try
            {
                while (true)
                {
                    if (this.arm != null)
                    {
                        int degree = 0;
                        int value = 0;

                        // Clean up queue.
                        while (this.commandsQueue.TryDequeue(out value))
                        {
                            // And take the latest version.
                            degree = value;
                        }

                        if (this.arm != null && Math.Abs(degree) > Threshold)
                        {
                            this.arm.MoveBedplate(90 + degree);
                        }

                        Thread.Sleep(200);
                    }
                    else
                    {
                        Thread.Sleep(1000);
                    }
                }
            }
            catch (ThreadAbortException)
            {
            }
        }

        private void BtnSelectCascade_Click(object sender, EventArgs e)
        {
            if (this.ofdCascade.ShowDialog() == DialogResult.OK)
            {
                this.TbCascade.Text = this.ofdCascade.FileName;
            }
        }

        private void BtnStartRecognition_Click(object sender, EventArgs e)
        {
            if (File.Exists(this.TbCascade.Text))
            {
                lock (this)
                {
                    if (this.recognizer != null)
                    {
                        this.recognizer.Dispose();
                    }

                    this.recognizer = new CascadeClassifier(this.TbCascade.Text);

                    if (this.arm != null)
                    {
                        this.arm.Dispose();
                    }

                    if (this.CbPorts.SelectedItem != null && this.CbArmTypes.SelectedItem != null)
                    {
                        this.arm = HarvbotArmFactory.GetInstance(this.CbPorts.SelectedItem.ToString(),
                            (HarvbotArmTypes)this.CbArmTypes.SelectedItem);
                    }
                }
            }
            else
            {
                MessageBox.Show("Selected file doesn't exist");
            }
        }

        private void BtnStopRecognition_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                if (this.arm != null)
                {
                    this.arm.Dispose();
                }

                if (this.recognizer != null)
                {
                    this.recognizer.Dispose();
                }
            }
        }
    }
}
