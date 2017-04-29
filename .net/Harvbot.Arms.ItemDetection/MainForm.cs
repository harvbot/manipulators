using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.Structure;

namespace Harvbot.Arms.ItemDetection
{
    public partial class MainForm : Form
    {
        private VideoCapture capture;

        private Mat frame;

        private CascadeClassifier recognizer;

        public MainForm()
        {
            InitializeComponent();

            CvInvoke.UseOpenCL = false;
            this.capture = new VideoCapture();
            this.capture.ImageGrabbed += ProcessFrame;
            this.frame = new Mat();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.ibVideo.Image = this.capture.QueryFrame();
            this.capture.Start();
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
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
                            using (var imageFrame = this.frame.ToImage<Bgr, Byte>())
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
                                    foreach (var rect in detectionResult)
                                    {
                                        imageFrame.Draw(rect, new Bgr(Color.Red), 2);
                                    }

                                    this.ibVideo.Image = imageFrame;
                                }
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
                if (this.recognizer != null)
                {
                    this.recognizer.Dispose();
                }
            }
        }
    }
}
