namespace PSP_405_control
{
    partial class Form1
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
            this.VDK_FI_OutputBoN = new System.Windows.Forms.Button();
            this.CurrTime = new System.Windows.Forms.Label();
            this.DataUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.VoltageUpDown = new System.Windows.Forms.NumericUpDown();
            this.VoltageLimitUpDown = new System.Windows.Forms.NumericUpDown();
            this.CurrentLimitUpDown = new System.Windows.Forms.NumericUpDown();
            this.Statusbox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.SetParameters = new System.Windows.Forms.Button();
            this.VDK_FI_currBox = new System.Windows.Forms.TextBox();
            this.VDK_FI_voltBox = new System.Windows.Forms.TextBox();
            this.IColumn = new System.Windows.Forms.Label();
            this.UColumn = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.VDK_FI_OutputBoff = new System.Windows.Forms.Button();
            this.OutStatusLb = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.VoltageUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.VoltageLimitUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentLimitUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // VDK_FI_OutputBoN
            // 
            this.VDK_FI_OutputBoN.BackColor = System.Drawing.Color.Silver;
            this.VDK_FI_OutputBoN.Font = new System.Drawing.Font("Verdana", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_OutputBoN.ForeColor = System.Drawing.SystemColors.WindowText;
            this.VDK_FI_OutputBoN.Location = new System.Drawing.Point(296, 44);
            this.VDK_FI_OutputBoN.Name = "VDK_FI_OutputBoN";
            this.VDK_FI_OutputBoN.Size = new System.Drawing.Size(136, 46);
            this.VDK_FI_OutputBoN.TabIndex = 0;
            this.VDK_FI_OutputBoN.Text = "Вкл.";
            this.VDK_FI_OutputBoN.UseVisualStyleBackColor = false;
            this.VDK_FI_OutputBoN.Click += new System.EventHandler(this.VDK_FI_OutputB_Click);
            // 
            // CurrTime
            // 
            this.CurrTime.AutoSize = true;
            this.CurrTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.CurrTime.Location = new System.Drawing.Point(323, 223);
            this.CurrTime.Name = "CurrTime";
            this.CurrTime.Size = new System.Drawing.Size(88, 15);
            this.CurrTime.TabIndex = 2;
            this.CurrTime.Text = "Time and Data";
            // 
            // DataUpdateTimer
            // 
            this.DataUpdateTimer.Tick += new System.EventHandler(this.DataUpdateTimer_Tick);
            // 
            // VoltageUpDown
            // 
            this.VoltageUpDown.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VoltageUpDown.ForeColor = System.Drawing.Color.DimGray;
            this.VoltageUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.VoltageUpDown.Location = new System.Drawing.Point(470, 161);
            this.VoltageUpDown.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.VoltageUpDown.Name = "VoltageUpDown";
            this.VoltageUpDown.Size = new System.Drawing.Size(138, 45);
            this.VoltageUpDown.TabIndex = 7;
            this.VoltageUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VoltageUpDown.ValueChanged += new System.EventHandler(this.VoltageUpDown_ValueChanged);
            // 
            // VoltageLimitUpDown
            // 
            this.VoltageLimitUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F);
            this.VoltageLimitUpDown.ForeColor = System.Drawing.Color.Red;
            this.VoltageLimitUpDown.Location = new System.Drawing.Point(474, 46);
            this.VoltageLimitUpDown.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.VoltageLimitUpDown.Name = "VoltageLimitUpDown";
            this.VoltageLimitUpDown.Size = new System.Drawing.Size(136, 44);
            this.VoltageLimitUpDown.TabIndex = 7;
            this.VoltageLimitUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VoltageLimitUpDown.ValueChanged += new System.EventHandler(this.VoltageLimitUpDown_ValueChanged);
            // 
            // CurrentLimitUpDown
            // 
            this.CurrentLimitUpDown.BackColor = System.Drawing.SystemColors.Window;
            this.CurrentLimitUpDown.DecimalPlaces = 2;
            this.CurrentLimitUpDown.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CurrentLimitUpDown.ForeColor = System.Drawing.Color.DimGray;
            this.CurrentLimitUpDown.Increment = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.CurrentLimitUpDown.Location = new System.Drawing.Point(8, 107);
            this.CurrentLimitUpDown.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.CurrentLimitUpDown.Name = "CurrentLimitUpDown";
            this.CurrentLimitUpDown.Size = new System.Drawing.Size(120, 45);
            this.CurrentLimitUpDown.TabIndex = 7;
            this.CurrentLimitUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.CurrentLimitUpDown.ValueChanged += new System.EventHandler(this.CurrentLimitUpDown_ValueChanged);
            // 
            // Statusbox
            // 
            this.Statusbox.BackColor = System.Drawing.SystemColors.Window;
            this.Statusbox.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Statusbox.Location = new System.Drawing.Point(8, 231);
            this.Statusbox.Multiline = true;
            this.Statusbox.Name = "Statusbox";
            this.Statusbox.ReadOnly = true;
            this.Statusbox.Size = new System.Drawing.Size(261, 24);
            this.Statusbox.TabIndex = 10;
            this.Statusbox.Text = "Источник выключен\r\n ";
            this.Statusbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.ForeColor = System.Drawing.Color.Red;
            this.label6.Location = new System.Drawing.Point(469, 25);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(139, 18);
            this.label6.TabIndex = 9;
            this.label6.Text = " Ограничение  U, B";
            // 
            // SetParameters
            // 
            this.SetParameters.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SetParameters.Location = new System.Drawing.Point(8, 170);
            this.SetParameters.Name = "SetParameters";
            this.SetParameters.Size = new System.Drawing.Size(261, 44);
            this.SetParameters.TabIndex = 0;
            this.SetParameters.Text = "УСТАНОВИТЬ";
            this.SetParameters.UseVisualStyleBackColor = true;
            this.SetParameters.Click += new System.EventHandler(this.SetParameters_Click);
            // 
            // VDK_FI_currBox
            // 
            this.VDK_FI_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.VDK_FI_currBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_FI_currBox.Location = new System.Drawing.Point(8, 45);
            this.VDK_FI_currBox.Name = "VDK_FI_currBox";
            this.VDK_FI_currBox.Size = new System.Drawing.Size(120, 45);
            this.VDK_FI_currBox.TabIndex = 18;
            this.VDK_FI_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // VDK_FI_voltBox
            // 
            this.VDK_FI_voltBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.VDK_FI_voltBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_FI_voltBox.Location = new System.Drawing.Point(152, 45);
            this.VDK_FI_voltBox.Name = "VDK_FI_voltBox";
            this.VDK_FI_voltBox.Size = new System.Drawing.Size(120, 45);
            this.VDK_FI_voltBox.TabIndex = 18;
            this.VDK_FI_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // IColumn
            // 
            this.IColumn.AutoSize = true;
            this.IColumn.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IColumn.Location = new System.Drawing.Point(32, 9);
            this.IColumn.Name = "IColumn";
            this.IColumn.Size = new System.Drawing.Size(69, 29);
            this.IColumn.TabIndex = 6;
            this.IColumn.Text = "I [A]";
            // 
            // UColumn
            // 
            this.UColumn.AutoSize = true;
            this.UColumn.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.UColumn.Location = new System.Drawing.Point(171, 9);
            this.UColumn.Name = "UColumn";
            this.UColumn.Size = new System.Drawing.Size(77, 29);
            this.UColumn.TabIndex = 6;
            this.UColumn.Text = "U [B]";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(313, 8);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(92, 29);
            this.label5.TabIndex = 6;
            this.label5.Text = "Выход";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(484, 140);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 18);
            this.label1.TabIndex = 9;
            this.label1.Text = "Рабочее U, B";
            // 
            // VDK_FI_OutputBoff
            // 
            this.VDK_FI_OutputBoff.BackColor = System.Drawing.Color.Silver;
            this.VDK_FI_OutputBoff.Font = new System.Drawing.Font("Verdana", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_OutputBoff.ForeColor = System.Drawing.SystemColors.WindowText;
            this.VDK_FI_OutputBoff.Location = new System.Drawing.Point(296, 106);
            this.VDK_FI_OutputBoff.Name = "VDK_FI_OutputBoff";
            this.VDK_FI_OutputBoff.Size = new System.Drawing.Size(136, 46);
            this.VDK_FI_OutputBoff.TabIndex = 0;
            this.VDK_FI_OutputBoff.Text = "Выкл";
            this.VDK_FI_OutputBoff.UseVisualStyleBackColor = false;
            this.VDK_FI_OutputBoff.Click += new System.EventHandler(this.VDK_FI_OutputBoff_Click);
            // 
            // OutStatusLb
            // 
            this.OutStatusLb.AutoSize = true;
            this.OutStatusLb.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.OutStatusLb.Font = new System.Drawing.Font("Consolas", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OutStatusLb.Location = new System.Drawing.Point(279, 177);
            this.OutStatusLb.Name = "OutStatusLb";
            this.OutStatusLb.Size = new System.Drawing.Size(25, 28);
            this.OutStatusLb.TabIndex = 2;
            this.OutStatusLb.Text = "-";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Verdana", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonShadow;
            this.label2.Location = new System.Drawing.Point(144, 117);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(125, 25);
            this.label2.TabIndex = 6;
            this.label2.Text = "Уст. ток, A";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(626, 258);
            this.Controls.Add(this.VoltageUpDown);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.VoltageLimitUpDown);
            this.Controls.Add(this.CurrentLimitUpDown);
            this.Controls.Add(this.SetParameters);
            this.Controls.Add(this.VDK_FI_OutputBoff);
            this.Controls.Add(this.VDK_FI_OutputBoN);
            this.Controls.Add(this.OutStatusLb);
            this.Controls.Add(this.CurrTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.UColumn);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.IColumn);
            this.Controls.Add(this.VDK_FI_voltBox);
            this.Controls.Add(this.VDK_FI_currBox);
            this.Controls.Add(this.Statusbox);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "БЛОК НАГРЕВА ВИСМУТА";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseClick);
            ((System.ComponentModel.ISupportInitialize)(this.VoltageUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.VoltageLimitUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentLimitUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.Button VDK_FI_OutputBoN;
        private System.Windows.Forms.Label CurrTime;
        private System.Windows.Forms.Timer DataUpdateTimer;
        private System.Windows.Forms.NumericUpDown VoltageUpDown;
        private System.Windows.Forms.NumericUpDown CurrentLimitUpDown;
        private System.Windows.Forms.NumericUpDown VoltageLimitUpDown;
        private System.Windows.Forms.TextBox Statusbox;
        private System.Windows.Forms.TextBox VDK_FI_currBox;
        private System.Windows.Forms.TextBox VDK_FI_voltBox;
        private System.Windows.Forms.Label IColumn;
        private System.Windows.Forms.Label UColumn;
        private System.Windows.Forms.Label label5;
        public System.Windows.Forms.Button SetParameters;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label1;
        public System.Windows.Forms.Button VDK_FI_OutputBoff;
        private System.Windows.Forms.Label OutStatusLb;
        private System.Windows.Forms.Label label2;
    }
}

