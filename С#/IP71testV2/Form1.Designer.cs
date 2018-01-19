namespace IP701testV2
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
            this.StatusBox = new System.Windows.Forms.TextBox();
            this.L1_U2setB = new System.Windows.Forms.Button();
            this.L1_Loc_status_lb = new System.Windows.Forms.Label();
            this.L1_ChargeOn_B = new System.Windows.Forms.Button();
            this.L1_ChargeOff_B = new System.Windows.Forms.Button();
            this.SrcNumberC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SrcIpC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PortC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SetVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ReadVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.AddNewSource_B = new System.Windows.Forms.Button();
            this.Update_timer = new System.Windows.Forms.Timer(this.components);
            this.L1_Load_status_lb = new System.Windows.Forms.Label();
            this.L1_U2setUpDown = new System.Windows.Forms.NumericUpDown();
            this.L1_OutState = new System.Windows.Forms.TextBox();
            this.L1_Uread = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Ureadlb = new System.Windows.Forms.Label();
            this.Usetlb = new System.Windows.Forms.Label();
            this.L1 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.L1_OverHeat_lb = new System.Windows.Forms.Label();
            this.PGM_IP = new System.Windows.Forms.Label();
            this.IP = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.L1_U2setUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // StatusBox
            // 
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.Location = new System.Drawing.Point(0, 93);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(640, 26);
            this.StatusBox.TabIndex = 3;
            // 
            // L1_U2setB
            // 
            this.L1_U2setB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_U2setB.Location = new System.Drawing.Point(201, 29);
            this.L1_U2setB.Name = "L1_U2setB";
            this.L1_U2setB.Size = new System.Drawing.Size(94, 35);
            this.L1_U2setB.TabIndex = 2;
            this.L1_U2setB.Text = "Уст. U";
            this.L1_U2setB.UseVisualStyleBackColor = true;
            this.L1_U2setB.Click += new System.EventHandler(this.U2setB_Click);
            // 
            // L1_Loc_status_lb
            // 
            this.L1_Loc_status_lb.AutoSize = true;
            this.L1_Loc_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_Loc_status_lb.Location = new System.Drawing.Point(488, 70);
            this.L1_Loc_status_lb.Name = "L1_Loc_status_lb";
            this.L1_Loc_status_lb.Size = new System.Drawing.Size(152, 20);
            this.L1_Loc_status_lb.TabIndex = 1;
            this.L1_Loc_status_lb.Text = "статус блокировки";
            // 
            // L1_ChargeOn_B
            // 
            this.L1_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_ChargeOn_B.Location = new System.Drawing.Point(448, 28);
            this.L1_ChargeOn_B.Name = "L1_ChargeOn_B";
            this.L1_ChargeOn_B.Size = new System.Drawing.Size(65, 36);
            this.L1_ChargeOn_B.TabIndex = 2;
            this.L1_ChargeOn_B.Text = "ВКЛ.";
            this.L1_ChargeOn_B.UseVisualStyleBackColor = true;
            this.L1_ChargeOn_B.Click += new System.EventHandler(this.Charge_B_Click);
            // 
            // L1_ChargeOff_B
            // 
            this.L1_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_ChargeOff_B.Location = new System.Drawing.Point(519, 28);
            this.L1_ChargeOff_B.Name = "L1_ChargeOff_B";
            this.L1_ChargeOff_B.Size = new System.Drawing.Size(67, 36);
            this.L1_ChargeOff_B.TabIndex = 2;
            this.L1_ChargeOff_B.Text = "ВЫКЛ.";
            this.L1_ChargeOff_B.UseVisualStyleBackColor = true;
            this.L1_ChargeOff_B.Click += new System.EventHandler(this.L1_ChargeOff_B_Click);
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
            // AddNewSource_B
            // 
            this.AddNewSource_B.Location = new System.Drawing.Point(656, 295);
            this.AddNewSource_B.Name = "AddNewSource_B";
            this.AddNewSource_B.Size = new System.Drawing.Size(120, 22);
            this.AddNewSource_B.TabIndex = 2;
            this.AddNewSource_B.Text = "Добавить источник";
            this.AddNewSource_B.UseVisualStyleBackColor = true;
            this.AddNewSource_B.Visible = false;
            // 
            // Update_timer
            // 
            this.Update_timer.Interval = 300;
            this.Update_timer.Tick += new System.EventHandler(this.Update_timer_Tick);
            // 
            // L1_Load_status_lb
            // 
            this.L1_Load_status_lb.AutoSize = true;
            this.L1_Load_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_Load_status_lb.Location = new System.Drawing.Point(307, 70);
            this.L1_Load_status_lb.Name = "L1_Load_status_lb";
            this.L1_Load_status_lb.Size = new System.Drawing.Size(129, 20);
            this.L1_Load_status_lb.TabIndex = 1;
            this.L1_Load_status_lb.Text = "статус нагрузки";
            // 
            // L1_U2setUpDown
            // 
            this.L1_U2setUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_U2setUpDown.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.L1_U2setUpDown.Location = new System.Drawing.Point(107, 29);
            this.L1_U2setUpDown.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.L1_U2setUpDown.Name = "L1_U2setUpDown";
            this.L1_U2setUpDown.Size = new System.Drawing.Size(87, 35);
            this.L1_U2setUpDown.TabIndex = 7;
            this.L1_U2setUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.L1_U2setUpDown.ValueChanged += new System.EventHandler(this.U2setUpDown_ValueChanged);
            // 
            // L1_OutState
            // 
            this.L1_OutState.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.L1_OutState.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_OutState.Location = new System.Drawing.Point(594, 27);
            this.L1_OutState.Name = "L1_OutState";
            this.L1_OutState.Size = new System.Drawing.Size(46, 38);
            this.L1_OutState.TabIndex = 20;
            // 
            // L1_Uread
            // 
            this.L1_Uread.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_Uread.Location = new System.Drawing.Point(326, 27);
            this.L1_Uread.Name = "L1_Uread";
            this.L1_Uread.Size = new System.Drawing.Size(96, 38);
            this.L1_Uread.TabIndex = 17;
            this.L1_Uread.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(490, 3);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 18);
            this.label4.TabIndex = 13;
            this.label4.Text = "Выход";
            // 
            // Ureadlb
            // 
            this.Ureadlb.AutoSize = true;
            this.Ureadlb.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Ureadlb.Location = new System.Drawing.Point(315, 3);
            this.Ureadlb.Name = "Ureadlb";
            this.Ureadlb.Size = new System.Drawing.Size(123, 18);
            this.Ureadlb.TabIndex = 11;
            this.Ureadlb.Text = "U выходное, В";
            // 
            // Usetlb
            // 
            this.Usetlb.AutoSize = true;
            this.Usetlb.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Usetlb.Location = new System.Drawing.Point(133, 3);
            this.Usetlb.Name = "Usetlb";
            this.Usetlb.Size = new System.Drawing.Size(129, 18);
            this.Usetlb.TabIndex = 10;
            this.Usetlb.Text = "Установка U, В";
            // 
            // L1
            // 
            this.L1.AutoSize = true;
            this.L1.BackColor = System.Drawing.Color.Gold;
            this.L1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1.Location = new System.Drawing.Point(-4, 28);
            this.L1.Name = "L1";
            this.L1.Size = new System.Drawing.Size(115, 37);
            this.L1.TabIndex = 9;
            this.L1.Text = "ИП701";
            this.L1.MouseEnter += new System.EventHandler(this.L1_MouseEnter);
            this.L1.MouseLeave += new System.EventHandler(this.L1_MouseLeave);
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.Color.Gold;
            this.textBox2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox2.Location = new System.Drawing.Point(0, 26);
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(587, 42);
            this.textBox2.TabIndex = 15;
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // L1_OverHeat_lb
            // 
            this.L1_OverHeat_lb.AutoSize = true;
            this.L1_OverHeat_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1_OverHeat_lb.Location = new System.Drawing.Point(180, 70);
            this.L1_OverHeat_lb.Name = "L1_OverHeat_lb";
            this.L1_OverHeat_lb.Size = new System.Drawing.Size(14, 20);
            this.L1_OverHeat_lb.TabIndex = 1;
            this.L1_OverHeat_lb.Text = "-";
            // 
            // PGM_IP
            // 
            this.PGM_IP.AutoSize = true;
            this.PGM_IP.Location = new System.Drawing.Point(-2, 77);
            this.PGM_IP.Name = "PGM_IP";
            this.PGM_IP.Size = new System.Drawing.Size(17, 13);
            this.PGM_IP.TabIndex = 25;
            this.PGM_IP.Text = "IP";
            // 
            // IP
            // 
            this.IP.Location = new System.Drawing.Point(3, 3);
            this.IP.Name = "IP";
            this.IP.Size = new System.Drawing.Size(108, 20);
            this.IP.TabIndex = 26;
            this.IP.Text = "192.168.127.254";
            this.IP.TextChanged += new System.EventHandler(this.IP_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(642, 122);
            this.Controls.Add(this.IP);
            this.Controls.Add(this.PGM_IP);
            this.Controls.Add(this.L1_OverHeat_lb);
            this.Controls.Add(this.AddNewSource_B);
            this.Controls.Add(this.L1_Load_status_lb);
            this.Controls.Add(this.L1_Loc_status_lb);
            this.Controls.Add(this.L1_ChargeOn_B);
            this.Controls.Add(this.L1_U2setB);
            this.Controls.Add(this.L1_U2setUpDown);
            this.Controls.Add(this.L1_OutState);
            this.Controls.Add(this.L1_Uread);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.Ureadlb);
            this.Controls.Add(this.Usetlb);
            this.Controls.Add(this.L1);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.L1_ChargeOff_B);
            this.Controls.Add(this.textBox2);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "IP701testV2";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.L1_U2setUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Button L1_U2setB;
        private System.Windows.Forms.Label L1_Loc_status_lb;
        private System.Windows.Forms.Button L1_ChargeOn_B;
        private System.Windows.Forms.Button L1_ChargeOff_B;
        private System.Windows.Forms.ColumnHeader SrcNumberC;
        private System.Windows.Forms.ColumnHeader SrcIpC;
        private System.Windows.Forms.ColumnHeader PortC;
        private System.Windows.Forms.ColumnHeader SetVoltageC;
        private System.Windows.Forms.ColumnHeader ReadVoltageC;
        private System.Windows.Forms.Button AddNewSource_B;
        private System.Windows.Forms.Timer Update_timer;
        private System.Windows.Forms.Label L1_Load_status_lb;
        private System.Windows.Forms.NumericUpDown L1_U2setUpDown;
        private System.Windows.Forms.TextBox L1_OutState;
        private System.Windows.Forms.TextBox L1_Uread;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label Ureadlb;
        private System.Windows.Forms.Label Usetlb;
        private System.Windows.Forms.Label L1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label L1_OverHeat_lb;
        private System.Windows.Forms.Label PGM_IP;
        private System.Windows.Forms.TextBox IP;
    }
}

