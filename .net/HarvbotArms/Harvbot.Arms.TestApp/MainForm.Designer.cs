namespace HarvbotArms
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
            this.CbPorts = new System.Windows.Forms.ComboBox();
            this.LblPorts = new System.Windows.Forms.Label();
            this.LblArmTypes = new System.Windows.Forms.Label();
            this.CbArmTypes = new System.Windows.Forms.ComboBox();
            this.BtnStartControl = new System.Windows.Forms.Button();
            this.BtnStopControl = new System.Windows.Forms.Button();
            this.PnlControl = new System.Windows.Forms.Panel();
            this.LblControlDescription = new System.Windows.Forms.Label();
            this.PnlControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // CbPorts
            // 
            this.CbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbPorts.FormattingEnabled = true;
            this.CbPorts.Location = new System.Drawing.Point(12, 25);
            this.CbPorts.Name = "CbPorts";
            this.CbPorts.Size = new System.Drawing.Size(140, 21);
            this.CbPorts.TabIndex = 0;
            // 
            // LblPorts
            // 
            this.LblPorts.AutoSize = true;
            this.LblPorts.Location = new System.Drawing.Point(12, 9);
            this.LblPorts.Name = "LblPorts";
            this.LblPorts.Size = new System.Drawing.Size(61, 13);
            this.LblPorts.TabIndex = 1;
            this.LblPorts.Text = "Select port:";
            // 
            // LblArmTypes
            // 
            this.LblArmTypes.AutoSize = true;
            this.LblArmTypes.Location = new System.Drawing.Point(12, 58);
            this.LblArmTypes.Name = "LblArmTypes";
            this.LblArmTypes.Size = new System.Drawing.Size(83, 13);
            this.LblArmTypes.TabIndex = 3;
            this.LblArmTypes.Text = "Select arm type:";
            // 
            // CbArmTypes
            // 
            this.CbArmTypes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbArmTypes.FormattingEnabled = true;
            this.CbArmTypes.Location = new System.Drawing.Point(12, 74);
            this.CbArmTypes.Name = "CbArmTypes";
            this.CbArmTypes.Size = new System.Drawing.Size(140, 21);
            this.CbArmTypes.TabIndex = 2;
            // 
            // BtnStartControl
            // 
            this.BtnStartControl.Location = new System.Drawing.Point(12, 113);
            this.BtnStartControl.Name = "BtnStartControl";
            this.BtnStartControl.Size = new System.Drawing.Size(140, 23);
            this.BtnStartControl.TabIndex = 4;
            this.BtnStartControl.Text = "Start control";
            this.BtnStartControl.UseVisualStyleBackColor = true;
            this.BtnStartControl.Click += new System.EventHandler(this.BtnStartControl_Click);
            // 
            // BtnStopControl
            // 
            this.BtnStopControl.Location = new System.Drawing.Point(12, 142);
            this.BtnStopControl.Name = "BtnStopControl";
            this.BtnStopControl.Size = new System.Drawing.Size(140, 23);
            this.BtnStopControl.TabIndex = 5;
            this.BtnStopControl.Text = "Stop control";
            this.BtnStopControl.UseVisualStyleBackColor = true;
            this.BtnStopControl.Click += new System.EventHandler(this.BtnStopControl_Click);
            // 
            // PnlControl
            // 
            this.PnlControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PnlControl.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PnlControl.Controls.Add(this.LblControlDescription);
            this.PnlControl.Location = new System.Drawing.Point(158, 12);
            this.PnlControl.Name = "PnlControl";
            this.PnlControl.Size = new System.Drawing.Size(408, 413);
            this.PnlControl.TabIndex = 6;
            // 
            // LblControlDescription
            // 
            this.LblControlDescription.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LblControlDescription.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblControlDescription.Location = new System.Drawing.Point(0, 0);
            this.LblControlDescription.Name = "LblControlDescription";
            this.LblControlDescription.Size = new System.Drawing.Size(406, 411);
            this.LblControlDescription.TabIndex = 0;
            this.LblControlDescription.Text = "Move mouse under this area to control Harvbot Arm";
            this.LblControlDescription.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.LblControlDescription.MouseMove += new System.Windows.Forms.MouseEventHandler(this.LblControlDescription_MouseMove);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(578, 437);
            this.Controls.Add(this.PnlControl);
            this.Controls.Add(this.BtnStopControl);
            this.Controls.Add(this.BtnStartControl);
            this.Controls.Add(this.LblArmTypes);
            this.Controls.Add(this.CbArmTypes);
            this.Controls.Add(this.LblPorts);
            this.Controls.Add(this.CbPorts);
            this.Name = "MainForm";
            this.Text = "HarvbotArms test application";
            this.PnlControl.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox CbPorts;
        private System.Windows.Forms.Label LblPorts;
        private System.Windows.Forms.Label LblArmTypes;
        private System.Windows.Forms.ComboBox CbArmTypes;
        private System.Windows.Forms.Button BtnStartControl;
        private System.Windows.Forms.Button BtnStopControl;
        private System.Windows.Forms.Panel PnlControl;
        private System.Windows.Forms.Label LblControlDescription;
    }
}

