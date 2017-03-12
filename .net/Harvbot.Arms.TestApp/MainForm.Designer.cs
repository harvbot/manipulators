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
            this.BtnLeft = new System.Windows.Forms.Button();
            this.BtnRight = new System.Windows.Forms.Button();
            this.BtnUp = new System.Windows.Forms.Button();
            this.BtnDown = new System.Windows.Forms.Button();
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
            // BtnLeft
            // 
            this.BtnLeft.Location = new System.Drawing.Point(191, 48);
            this.BtnLeft.Name = "BtnLeft";
            this.BtnLeft.Size = new System.Drawing.Size(75, 23);
            this.BtnLeft.TabIndex = 6;
            this.BtnLeft.Text = "Left (A)";
            this.BtnLeft.UseVisualStyleBackColor = true;
            this.BtnLeft.Click += new System.EventHandler(this.BtnLeft_Click);
            // 
            // BtnRight
            // 
            this.BtnRight.Location = new System.Drawing.Point(272, 48);
            this.BtnRight.Name = "BtnRight";
            this.BtnRight.Size = new System.Drawing.Size(75, 23);
            this.BtnRight.TabIndex = 7;
            this.BtnRight.Text = "Right (D)";
            this.BtnRight.UseVisualStyleBackColor = true;
            this.BtnRight.Click += new System.EventHandler(this.BtnRight_Click);
            // 
            // BtnUp
            // 
            this.BtnUp.Location = new System.Drawing.Point(234, 19);
            this.BtnUp.Name = "BtnUp";
            this.BtnUp.Size = new System.Drawing.Size(75, 23);
            this.BtnUp.TabIndex = 8;
            this.BtnUp.Text = "Up (W)";
            this.BtnUp.UseVisualStyleBackColor = true;
            this.BtnUp.Click += new System.EventHandler(this.BtnUp_Click);
            // 
            // BtnDown
            // 
            this.BtnDown.Location = new System.Drawing.Point(234, 77);
            this.BtnDown.Name = "BtnDown";
            this.BtnDown.Size = new System.Drawing.Size(75, 23);
            this.BtnDown.TabIndex = 9;
            this.BtnDown.Text = "Down (S)";
            this.BtnDown.UseVisualStyleBackColor = true;
            this.BtnDown.Click += new System.EventHandler(this.BtnDown_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(367, 188);
            this.Controls.Add(this.BtnDown);
            this.Controls.Add(this.BtnUp);
            this.Controls.Add(this.BtnRight);
            this.Controls.Add(this.BtnLeft);
            this.Controls.Add(this.BtnStopControl);
            this.Controls.Add(this.BtnStartControl);
            this.Controls.Add(this.LblArmTypes);
            this.Controls.Add(this.CbArmTypes);
            this.Controls.Add(this.LblPorts);
            this.Controls.Add(this.CbPorts);
            this.Name = "MainForm";
            this.Text = "HarvbotArms test application";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainForm_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.MainForm_KeyUp);
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
        private System.Windows.Forms.Button BtnLeft;
        private System.Windows.Forms.Button BtnRight;
        private System.Windows.Forms.Button BtnUp;
        private System.Windows.Forms.Button BtnDown;
    }
}

