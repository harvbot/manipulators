namespace Harvbot.Arms.ItemDetection
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.ibVideo = new Emgu.CV.UI.ImageBox();
            this.BtnSelectCascade = new System.Windows.Forms.Button();
            this.ofdCascade = new System.Windows.Forms.OpenFileDialog();
            this.TbCascade = new System.Windows.Forms.TextBox();
            this.BtnStartRecognition = new System.Windows.Forms.Button();
            this.BtnStopRecognition = new System.Windows.Forms.Button();
            this.LblArmTypes = new System.Windows.Forms.Label();
            this.CbArmTypes = new System.Windows.Forms.ComboBox();
            this.LblPorts = new System.Windows.Forms.Label();
            this.CbPorts = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.CbArmSubTypes = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.ibVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // ibVideo
            // 
            this.ibVideo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ibVideo.Location = new System.Drawing.Point(214, 12);
            this.ibVideo.Name = "ibVideo";
            this.ibVideo.Size = new System.Drawing.Size(640, 480);
            this.ibVideo.TabIndex = 2;
            this.ibVideo.TabStop = false;
            // 
            // BtnSelectCascade
            // 
            this.BtnSelectCascade.Location = new System.Drawing.Point(133, 12);
            this.BtnSelectCascade.Name = "BtnSelectCascade";
            this.BtnSelectCascade.Size = new System.Drawing.Size(75, 23);
            this.BtnSelectCascade.TabIndex = 3;
            this.BtnSelectCascade.Text = "Select";
            this.BtnSelectCascade.UseVisualStyleBackColor = true;
            this.BtnSelectCascade.Click += new System.EventHandler(this.BtnSelectCascade_Click);
            // 
            // ofdCascade
            // 
            this.ofdCascade.Filter = "Cascade|*.xml";
            // 
            // TbCascade
            // 
            this.TbCascade.Location = new System.Drawing.Point(12, 14);
            this.TbCascade.Name = "TbCascade";
            this.TbCascade.Size = new System.Drawing.Size(114, 20);
            this.TbCascade.TabIndex = 4;
            this.TbCascade.Text = "haarcascade_frontalface_default.xml";
            // 
            // BtnStartRecognition
            // 
            this.BtnStartRecognition.Location = new System.Drawing.Point(12, 40);
            this.BtnStartRecognition.Name = "BtnStartRecognition";
            this.BtnStartRecognition.Size = new System.Drawing.Size(196, 23);
            this.BtnStartRecognition.TabIndex = 5;
            this.BtnStartRecognition.Text = "Start Recognition";
            this.BtnStartRecognition.UseVisualStyleBackColor = true;
            this.BtnStartRecognition.Click += new System.EventHandler(this.BtnStartRecognition_Click);
            // 
            // BtnStopRecognition
            // 
            this.BtnStopRecognition.Location = new System.Drawing.Point(12, 69);
            this.BtnStopRecognition.Name = "BtnStopRecognition";
            this.BtnStopRecognition.Size = new System.Drawing.Size(196, 23);
            this.BtnStopRecognition.TabIndex = 6;
            this.BtnStopRecognition.Text = "Stop Recognition";
            this.BtnStopRecognition.UseVisualStyleBackColor = true;
            this.BtnStopRecognition.Click += new System.EventHandler(this.BtnStopRecognition_Click);
            // 
            // LblArmTypes
            // 
            this.LblArmTypes.AutoSize = true;
            this.LblArmTypes.Location = new System.Drawing.Point(12, 154);
            this.LblArmTypes.Name = "LblArmTypes";
            this.LblArmTypes.Size = new System.Drawing.Size(83, 13);
            this.LblArmTypes.TabIndex = 10;
            this.LblArmTypes.Text = "Select arm type:";
            // 
            // CbArmTypes
            // 
            this.CbArmTypes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbArmTypes.FormattingEnabled = true;
            this.CbArmTypes.Location = new System.Drawing.Point(12, 170);
            this.CbArmTypes.Name = "CbArmTypes";
            this.CbArmTypes.Size = new System.Drawing.Size(140, 21);
            this.CbArmTypes.TabIndex = 9;
            // 
            // LblPorts
            // 
            this.LblPorts.AutoSize = true;
            this.LblPorts.Location = new System.Drawing.Point(12, 105);
            this.LblPorts.Name = "LblPorts";
            this.LblPorts.Size = new System.Drawing.Size(61, 13);
            this.LblPorts.TabIndex = 8;
            this.LblPorts.Text = "Select port:";
            // 
            // CbPorts
            // 
            this.CbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbPorts.FormattingEnabled = true;
            this.CbPorts.Location = new System.Drawing.Point(12, 121);
            this.CbPorts.Name = "CbPorts";
            this.CbPorts.Size = new System.Drawing.Size(140, 21);
            this.CbPorts.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 205);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "Select arm subtype:";
            // 
            // CbArmSubType
            // 
            this.CbArmSubTypes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbArmSubTypes.FormattingEnabled = true;
            this.CbArmSubTypes.Location = new System.Drawing.Point(12, 221);
            this.CbArmSubTypes.Name = "CbArmSubType";
            this.CbArmSubTypes.Size = new System.Drawing.Size(140, 21);
            this.CbArmSubTypes.TabIndex = 11;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(866, 504);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CbArmSubTypes);
            this.Controls.Add(this.LblArmTypes);
            this.Controls.Add(this.CbArmTypes);
            this.Controls.Add(this.LblPorts);
            this.Controls.Add(this.CbPorts);
            this.Controls.Add(this.BtnStopRecognition);
            this.Controls.Add(this.BtnStartRecognition);
            this.Controls.Add(this.TbCascade);
            this.Controls.Add(this.BtnSelectCascade);
            this.Controls.Add(this.ibVideo);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.Text = "Image recognition";
            ((System.ComponentModel.ISupportInitialize)(this.ibVideo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Emgu.CV.UI.ImageBox ibVideo;
        private System.Windows.Forms.Button BtnSelectCascade;
        private System.Windows.Forms.OpenFileDialog ofdCascade;
        private System.Windows.Forms.TextBox TbCascade;
        private System.Windows.Forms.Button BtnStartRecognition;
        private System.Windows.Forms.Button BtnStopRecognition;
        private System.Windows.Forms.Label LblArmTypes;
        private System.Windows.Forms.ComboBox CbArmTypes;
        private System.Windows.Forms.Label LblPorts;
        private System.Windows.Forms.ComboBox CbPorts;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox CbArmSubTypes;
    }
}

