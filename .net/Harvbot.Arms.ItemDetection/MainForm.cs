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
        private const int Threshold = 1;

        private VideoCapture capture;

        private Mat frame;

        private CascadeClassifier recognizer;

        private HarvbotArmBase arm;

        private Thread manipulatorThread;

        private Rectangle prevRecognizedRect;

        private int recognitionCount;

        private ConcurrentQueue<int> commandsQueue;

        public MainForm()
        {
            InitializeComponent();

            CvInvoke.UseOpenCL = false;
            this.capture = new VideoCapture(1);
            this.capture.ImageGrabbed += this.ProcessFrame;
            this.frame = new Mat();

            this.prevRecognizedRect = Rectangle.Empty;

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
                                    this.recognitionCount++;
                                    var rect = detectionResult.First();

                                    imageFrame.Draw(rect, new Bgr(Color.Red), 2);

                                    if (this.prevRecognizedRect == Rectangle.Empty)
                                    {
                                        this.prevRecognizedRect = rect;
                                    }

                                    Rectangle intersect = rect;

                                    intersect.Intersect(this.prevRecognizedRect);

                                    var area1 = rect.Width * rect.Height;
                                    var area2 = intersect.Width * intersect.Height;

                                    if (Math.Abs(area1 - area2) < area1 * 0.1 && this.recognitionCount > 4)
                                    {
                                        var deltaX = (imageFrame.Width - rect.Width) / 2 - rect.X;

                                        var cX = deltaX * 180 / imageFrame.Width;

                                        cX = cX / 4;

                                        this.recognitionCount = 0;

                                        Trace.WriteLine($"Send bedplate move command: {cX}");

                                        this.commandsQueue.Enqueue(cX);
                                    }

                                    this.prevRecognizedRect = rect;
                                }
                                else
                                {
                                    this.recognitionCount = 0;
                                }

                                this.ibVideo.Image = imageFrame;
                            }
                        }
                    }
                }
                else
                {
                    this.recognitionCount = 0;
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
                            var pos = this.arm.GetBedplatePosition();
                            this.arm.MoveBedplate(pos.GetValueOrDefault(90) + degree);
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
