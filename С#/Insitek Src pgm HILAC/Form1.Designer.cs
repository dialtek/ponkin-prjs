namespace Insitek_src
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
            this.IPV60_U2setB = new System.Windows.Forms.Button();
            this.IPV60_ChargeOn_B = new System.Windows.Forms.Button();
            this.IPV60_ChargeOff_B = new System.Windows.Forms.Button();
            this.SrcNumberC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SrcIpC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PortC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SetVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ReadVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ReadCurrentC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.OutStateC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Update_timer = new System.Windows.Forms.Timer(this.components);
            this.IPV60_VoltUpDown = new System.Windows.Forms.NumericUpDown();
            this.ErrorLabel = new System.Windows.Forms.Label();
            this.Uread_1 = new System.Windows.Forms.TextBox();
            this.Uread_2 = new System.Windows.Forms.TextBox();
            this.Iread_1 = new System.Windows.Forms.TextBox();
            this.Iread_2 = new System.Windows.Forms.TextBox();
            this.OutState_1 = new System.Windows.Forms.TextBox();
            this.OutState_2 = new System.Windows.Forms.TextBox();
            this.IPV30 = new System.Windows.Forms.Label();
            this.IPV120 = new System.Windows.Forms.Label();
            this.Usetlb = new System.Windows.Forms.Label();
            this.Ureadlb = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.IPV120_VoltUpDown = new System.Windows.Forms.NumericUpDown();
            this.IPV120_UsetB = new System.Windows.Forms.Button();
            this.IPV120_ChargeOn_B = new System.Windows.Forms.Button();
            this.IPV120_ChargeOff_B = new System.Windows.Forms.Button();
            this.PGM_IP = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.IPV60_VoltUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.IPV120_VoltUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // IPV60_U2setB
            // 
            this.IPV60_U2setB.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV60_U2setB.Location = new System.Drawing.Point(237, 31);
            this.IPV60_U2setB.Name = "IPV60_U2setB";
            this.IPV60_U2setB.Size = new System.Drawing.Size(79, 38);
            this.IPV60_U2setB.TabIndex = 2;
            this.IPV60_U2setB.Text = "Set U";
            this.IPV60_U2setB.UseVisualStyleBackColor = true;
            this.IPV60_U2setB.Click += new System.EventHandler(this.U2setB_Click);
            // 
            // IPV60_ChargeOn_B
            // 
            this.IPV60_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV60_ChargeOn_B.Location = new System.Drawing.Point(548, 34);
            this.IPV60_ChargeOn_B.Name = "IPV60_ChargeOn_B";
            this.IPV60_ChargeOn_B.Size = new System.Drawing.Size(66, 32);
            this.IPV60_ChargeOn_B.TabIndex = 2;
            this.IPV60_ChargeOn_B.Text = "ON";
            this.IPV60_ChargeOn_B.UseVisualStyleBackColor = true;
            this.IPV60_ChargeOn_B.Click += new System.EventHandler(this.Charge_B_Click);
            // 
            // IPV60_ChargeOff_B
            // 
            this.IPV60_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV60_ChargeOff_B.Location = new System.Drawing.Point(617, 34);
            this.IPV60_ChargeOff_B.Name = "IPV60_ChargeOff_B";
            this.IPV60_ChargeOff_B.Size = new System.Drawing.Size(75, 32);
            this.IPV60_ChargeOff_B.TabIndex = 2;
            this.IPV60_ChargeOff_B.Text = "OFF";
            this.IPV60_ChargeOff_B.UseVisualStyleBackColor = true;
            this.IPV60_ChargeOff_B.Click += new System.EventHandler(this.DisCharge_B_Click);
            // 
            // SrcNumberC
            // 
            this.SrcNumberC.Text = "№ источника";
            this.SrcNumberC.Width = 120;
            // 
            // SrcIpC
            // 
            this.SrcIpC.Text = "IP адрес";
            this.SrcIpC.Width = 124;
            // 
            // PortC
            // 
            this.PortC.Text = "Порт";
            // 
            // SetVoltageC
            // 
            this.SetVoltageC.Text = "Заданное U, В";
            this.SetVoltageC.Width = 133;
            // 
            // ReadVoltageC
            // 
            this.ReadVoltageC.Text = "Реальное U, В";
            this.ReadVoltageC.Width = 123;
            // 
            // Update_timer
            // 
            this.Update_timer.Tick += new System.EventHandler(this.Update_timer_Tick);
            // 
            // IPV60_VoltUpDown
            // 
            this.IPV60_VoltUpDown.DecimalPlaces = 1;
            this.IPV60_VoltUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV60_VoltUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.IPV60_VoltUpDown.Location = new System.Drawing.Point(118, 31);
            this.IPV60_VoltUpDown.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.IPV60_VoltUpDown.Name = "IPV60_VoltUpDown";
            this.IPV60_VoltUpDown.Size = new System.Drawing.Size(109, 38);
            this.IPV60_VoltUpDown.TabIndex = 4;
            this.IPV60_VoltUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ErrorLabel
            // 
            this.ErrorLabel.AutoSize = true;
            this.ErrorLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.ErrorLabel.Location = new System.Drawing.Point(4, 35);
            this.ErrorLabel.Name = "ErrorLabel";
            this.ErrorLabel.Size = new System.Drawing.Size(0, 16);
            this.ErrorLabel.TabIndex = 1;
            this.ErrorLabel.Visible = false;
            // 
            // Uread_1
            // 
            this.Uread_1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Uread_1.Location = new System.Drawing.Point(337, 31);
            this.Uread_1.Name = "Uread_1";
            this.Uread_1.Size = new System.Drawing.Size(100, 38);
            this.Uread_1.TabIndex = 7;
            this.Uread_1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Uread_2
            // 
            this.Uread_2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Uread_2.Location = new System.Drawing.Point(337, 108);
            this.Uread_2.Name = "Uread_2";
            this.Uread_2.Size = new System.Drawing.Size(100, 38);
            this.Uread_2.TabIndex = 7;
            this.Uread_2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Iread_1
            // 
            this.Iread_1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Iread_1.Location = new System.Drawing.Point(448, 31);
            this.Iread_1.Name = "Iread_1";
            this.Iread_1.Size = new System.Drawing.Size(82, 38);
            this.Iread_1.TabIndex = 7;
            this.Iread_1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Iread_2
            // 
            this.Iread_2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Iread_2.Location = new System.Drawing.Point(448, 108);
            this.Iread_2.Name = "Iread_2";
            this.Iread_2.Size = new System.Drawing.Size(82, 38);
            this.Iread_2.TabIndex = 7;
            this.Iread_2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // OutState_1
            // 
            this.OutState_1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.OutState_1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OutState_1.Location = new System.Drawing.Point(699, 31);
            this.OutState_1.Name = "OutState_1";
            this.OutState_1.Size = new System.Drawing.Size(44, 38);
            this.OutState_1.TabIndex = 7;
            // 
            // OutState_2
            // 
            this.OutState_2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.OutState_2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OutState_2.Location = new System.Drawing.Point(699, 108);
            this.OutState_2.Name = "OutState_2";
            this.OutState_2.Size = new System.Drawing.Size(44, 38);
            this.OutState_2.TabIndex = 7;
            // 
            // IPV30
            // 
            this.IPV30.AutoSize = true;
            this.IPV30.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.IPV30.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV30.Location = new System.Drawing.Point(10, 31);
            this.IPV30.Name = "IPV30";
            this.IPV30.Size = new System.Drawing.Size(105, 39);
            this.IPV30.TabIndex = 1;
            this.IPV30.Text = "60 кВ";
            this.IPV30.MouseEnter += new System.EventHandler(this.IPV30_MouseEnter);
            this.IPV30.MouseLeave += new System.EventHandler(this.IPV30_MouseLeave);
            // 
            // IPV120
            // 
            this.IPV120.AutoSize = true;
            this.IPV120.BackColor = System.Drawing.Color.Wheat;
            this.IPV120.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV120.Location = new System.Drawing.Point(-6, 108);
            this.IPV120.Name = "IPV120";
            this.IPV120.Size = new System.Drawing.Size(124, 39);
            this.IPV120.TabIndex = 1;
            this.IPV120.Text = "120 кВ";
            this.IPV120.MouseEnter += new System.EventHandler(this.IPV120_MouseEnter);
            this.IPV120.MouseLeave += new System.EventHandler(this.IPV120_MouseLeave);
            // 
            // Usetlb
            // 
            this.Usetlb.AutoSize = true;
            this.Usetlb.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Usetlb.Location = new System.Drawing.Point(151, 4);
            this.Usetlb.Name = "Usetlb";
            this.Usetlb.Size = new System.Drawing.Size(99, 18);
            this.Usetlb.TabIndex = 1;
            this.Usetlb.Text = "Settings, кВ";
            // 
            // Ureadlb
            // 
            this.Ureadlb.AutoSize = true;
            this.Ureadlb.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Ureadlb.Location = new System.Drawing.Point(345, 4);
            this.Ureadlb.Name = "Ureadlb";
            this.Ureadlb.Size = new System.Drawing.Size(84, 18);
            this.Ureadlb.TabIndex = 1;
            this.Ureadlb.Text = "U out., кВ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(452, 4);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(78, 18);
            this.label3.TabIndex = 1;
            this.label3.Text = "I out., мА";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(585, 2);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 18);
            this.label4.TabIndex = 1;
            this.label4.Text = "Output";
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox1.Location = new System.Drawing.Point(-55, 29);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(805, 42);
            this.textBox1.TabIndex = 3;
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.Color.Wheat;
            this.textBox2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox2.Location = new System.Drawing.Point(-54, 106);
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(804, 42);
            this.textBox2.TabIndex = 3;
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // IPV120_VoltUpDown
            // 
            this.IPV120_VoltUpDown.DecimalPlaces = 1;
            this.IPV120_VoltUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV120_VoltUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.IPV120_VoltUpDown.Location = new System.Drawing.Point(118, 108);
            this.IPV120_VoltUpDown.Maximum = new decimal(new int[] {
            120,
            0,
            0,
            0});
            this.IPV120_VoltUpDown.Name = "IPV120_VoltUpDown";
            this.IPV120_VoltUpDown.Size = new System.Drawing.Size(109, 38);
            this.IPV120_VoltUpDown.TabIndex = 4;
            this.IPV120_VoltUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // IPV120_UsetB
            // 
            this.IPV120_UsetB.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV120_UsetB.Location = new System.Drawing.Point(237, 108);
            this.IPV120_UsetB.Name = "IPV120_UsetB";
            this.IPV120_UsetB.Size = new System.Drawing.Size(79, 38);
            this.IPV120_UsetB.TabIndex = 2;
            this.IPV120_UsetB.Text = "Set U";
            this.IPV120_UsetB.UseVisualStyleBackColor = true;
            this.IPV120_UsetB.Click += new System.EventHandler(this.IPV120_UsetB_Click);
            // 
            // IPV120_ChargeOn_B
            // 
            this.IPV120_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV120_ChargeOn_B.Location = new System.Drawing.Point(548, 111);
            this.IPV120_ChargeOn_B.Name = "IPV120_ChargeOn_B";
            this.IPV120_ChargeOn_B.Size = new System.Drawing.Size(66, 32);
            this.IPV120_ChargeOn_B.TabIndex = 2;
            this.IPV120_ChargeOn_B.Text = "ON";
            this.IPV120_ChargeOn_B.UseVisualStyleBackColor = true;
            this.IPV120_ChargeOn_B.Click += new System.EventHandler(this.IPV120_ChargeOn_B_Click);
            // 
            // IPV120_ChargeOff_B
            // 
            this.IPV120_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPV120_ChargeOff_B.Location = new System.Drawing.Point(617, 111);
            this.IPV120_ChargeOff_B.Name = "IPV120_ChargeOff_B";
            this.IPV120_ChargeOff_B.Size = new System.Drawing.Size(75, 32);
            this.IPV120_ChargeOff_B.TabIndex = 2;
            this.IPV120_ChargeOff_B.Text = "OFF";
            this.IPV120_ChargeOff_B.UseVisualStyleBackColor = true;
            this.IPV120_ChargeOff_B.Click += new System.EventHandler(this.IPV120_ChargeOff_B_Click);
            // 
            // PGM_IP
            // 
            this.PGM_IP.AutoSize = true;
            this.PGM_IP.Location = new System.Drawing.Point(621, 151);
            this.PGM_IP.Name = "PGM_IP";
            this.PGM_IP.Size = new System.Drawing.Size(47, 13);
            this.PGM_IP.TabIndex = 8;
            this.PGM_IP.Text = "PGM IP:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 167);
            this.Controls.Add(this.PGM_IP);
            this.Controls.Add(this.IPV120_ChargeOff_B);
            this.Controls.Add(this.IPV60_ChargeOff_B);
            this.Controls.Add(this.IPV120_ChargeOn_B);
            this.Controls.Add(this.IPV120_UsetB);
            this.Controls.Add(this.IPV60_ChargeOn_B);
            this.Controls.Add(this.IPV60_U2setB);
            this.Controls.Add(this.IPV120_VoltUpDown);
            this.Controls.Add(this.IPV60_VoltUpDown);
            this.Controls.Add(this.OutState_2);
            this.Controls.Add(this.Iread_2);
            this.Controls.Add(this.Uread_2);
            this.Controls.Add(this.OutState_1);
            this.Controls.Add(this.Iread_1);
            this.Controls.Add(this.Uread_1);
            this.Controls.Add(this.ErrorLabel);
            this.Controls.Add(this.IPV120);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.Ureadlb);
            this.Controls.Add(this.Usetlb);
            this.Controls.Add(this.IPV30);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "Управление источниками INSITEK - Томск";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.IPV60_VoltUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.IPV120_VoltUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button IPV60_U2setB;
        private System.Windows.Forms.Button IPV60_ChargeOn_B;
        private System.Windows.Forms.Button IPV60_ChargeOff_B;
        private System.Windows.Forms.ColumnHeader SrcNumberC;
        private System.Windows.Forms.ColumnHeader SrcIpC;
        private System.Windows.Forms.ColumnHeader PortC;
        private System.Windows.Forms.ColumnHeader SetVoltageC;
        private System.Windows.Forms.ColumnHeader ReadVoltageC;
        private System.Windows.Forms.ColumnHeader ReadCurrentC;
        private System.Windows.Forms.ColumnHeader OutStateC;
        private System.Windows.Forms.Timer Update_timer;
        private System.Windows.Forms.NumericUpDown IPV60_VoltUpDown;
        private System.Windows.Forms.Label ErrorLabel;
        private System.Windows.Forms.TextBox Uread_1;
        private System.Windows.Forms.TextBox Uread_2;
        private System.Windows.Forms.TextBox Iread_1;
        private System.Windows.Forms.TextBox Iread_2;
        private System.Windows.Forms.TextBox OutState_1;
        private System.Windows.Forms.TextBox OutState_2;
        private System.Windows.Forms.Label IPV30;
        private System.Windows.Forms.Label IPV120;
        private System.Windows.Forms.Label Usetlb;
        private System.Windows.Forms.Label Ureadlb;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.NumericUpDown IPV120_VoltUpDown;
        private System.Windows.Forms.Button IPV120_UsetB;
        private System.Windows.Forms.Button IPV120_ChargeOn_B;
        private System.Windows.Forms.Button IPV120_ChargeOff_B;
        private System.Windows.Forms.Label PGM_IP;
    }
}

