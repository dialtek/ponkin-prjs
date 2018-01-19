namespace _701C_src_PGM
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
            this.D11_U2setB = new System.Windows.Forms.Button();
            this.D11_Loc_status_lb = new System.Windows.Forms.Label();
            this.D11_ChargeOn_B = new System.Windows.Forms.Button();
            this.D11_ChargeOff_B = new System.Windows.Forms.Button();
            this.SrcNumberC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SrcIpC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PortC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SetVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ReadVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.AddNewSource_B = new System.Windows.Forms.Button();
            this.Update_timer = new System.Windows.Forms.Timer(this.components);
            this.D11_Load_status_lb = new System.Windows.Forms.Label();
            this.D11_U2setUpDown = new System.Windows.Forms.NumericUpDown();
            this.D12_OutState = new System.Windows.Forms.TextBox();
            this.D12_Uread = new System.Windows.Forms.TextBox();
            this.D11_OutState = new System.Windows.Forms.TextBox();
            this.D11_Uread = new System.Windows.Forms.TextBox();
            this.L2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Ureadlb = new System.Windows.Forms.Label();
            this.Usetlb = new System.Windows.Forms.Label();
            this.L1 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.D12_U2setUpDown = new System.Windows.Forms.NumericUpDown();
            this.D12_U2setB = new System.Windows.Forms.Button();
            this.D12_ChargeOff_B = new System.Windows.Forms.Button();
            this.D12_ChargeOn_B = new System.Windows.Forms.Button();
            this.D11_OverHeat_lb = new System.Windows.Forms.Label();
            this.D12_OverHeat_lb = new System.Windows.Forms.Label();
            this.D12_Loc_status_lb = new System.Windows.Forms.Label();
            this.D12_Load_status_lb = new System.Windows.Forms.Label();
            this.PGM_IP = new System.Windows.Forms.Label();
            this.D21_ChargeOff_B = new System.Windows.Forms.Button();
            this.L3 = new System.Windows.Forms.Label();
            this.D21_U2setUpDown = new System.Windows.Forms.NumericUpDown();
            this.D21_U2setB = new System.Windows.Forms.Button();
            this.D21_Uread = new System.Windows.Forms.TextBox();
            this.D21_OutState = new System.Windows.Forms.TextBox();
            this.D21_ChargeOn_B = new System.Windows.Forms.Button();
            this.D21_Loc_status_lb = new System.Windows.Forms.Label();
            this.D21_Load_status_lb = new System.Windows.Forms.Label();
            this.D21_OverHeat_lb = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.D22_Loc_status_lb = new System.Windows.Forms.Label();
            this.D22_Load_status_lb = new System.Windows.Forms.Label();
            this.D22_ChargeOff_B = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.D22_U2setUpDown = new System.Windows.Forms.NumericUpDown();
            this.D22_U2setB = new System.Windows.Forms.Button();
            this.D22_Uread = new System.Windows.Forms.TextBox();
            this.D22_OutState = new System.Windows.Forms.TextBox();
            this.D22_ChargeOn_B = new System.Windows.Forms.Button();
            this.D22_OverHeat_lb = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.D11_U2setUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.D12_U2setUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.D21_U2setUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.D22_U2setUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // StatusBox
            // 
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.Location = new System.Drawing.Point(0, 339);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(637, 26);
            this.StatusBox.TabIndex = 3;
            // 
            // D11_U2setB
            // 
            this.D11_U2setB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_U2setB.Location = new System.Drawing.Point(201, 29);
            this.D11_U2setB.Name = "D11_U2setB";
            this.D11_U2setB.Size = new System.Drawing.Size(94, 35);
            this.D11_U2setB.TabIndex = 2;
            this.D11_U2setB.Text = "Set U";
            this.D11_U2setB.UseVisualStyleBackColor = true;
            this.D11_U2setB.Click += new System.EventHandler(this.U2setB_Click);
            // 
            // D11_Loc_status_lb
            // 
            this.D11_Loc_status_lb.AutoSize = true;
            this.D11_Loc_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_Loc_status_lb.Location = new System.Drawing.Point(488, 70);
            this.D11_Loc_status_lb.Name = "D11_Loc_status_lb";
            this.D11_Loc_status_lb.Size = new System.Drawing.Size(152, 20);
            this.D11_Loc_status_lb.TabIndex = 1;
            this.D11_Loc_status_lb.Text = "статус блокировки";
            // 
            // D11_ChargeOn_B
            // 
            this.D11_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_ChargeOn_B.Location = new System.Drawing.Point(448, 28);
            this.D11_ChargeOn_B.Name = "D11_ChargeOn_B";
            this.D11_ChargeOn_B.Size = new System.Drawing.Size(65, 36);
            this.D11_ChargeOn_B.TabIndex = 2;
            this.D11_ChargeOn_B.Text = "ON";
            this.D11_ChargeOn_B.UseVisualStyleBackColor = true;
            this.D11_ChargeOn_B.Click += new System.EventHandler(this.Charge_B_Click);
            // 
            // D11_ChargeOff_B
            // 
            this.D11_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_ChargeOff_B.Location = new System.Drawing.Point(519, 28);
            this.D11_ChargeOff_B.Name = "D11_ChargeOff_B";
            this.D11_ChargeOff_B.Size = new System.Drawing.Size(67, 36);
            this.D11_ChargeOff_B.TabIndex = 2;
            this.D11_ChargeOff_B.Text = "OFF";
            this.D11_ChargeOff_B.UseVisualStyleBackColor = true;
            this.D11_ChargeOff_B.Click += new System.EventHandler(this.DisCharge_B_Click);
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
            this.AddNewSource_B.Click += new System.EventHandler(this.NewSource_B_Click);
            // 
            // Update_timer
            // 
            this.Update_timer.Interval = 300;
            this.Update_timer.Tick += new System.EventHandler(this.Update_timer_Tick);
            // 
            // D11_Load_status_lb
            // 
            this.D11_Load_status_lb.AutoSize = true;
            this.D11_Load_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_Load_status_lb.Location = new System.Drawing.Point(307, 70);
            this.D11_Load_status_lb.Name = "D11_Load_status_lb";
            this.D11_Load_status_lb.Size = new System.Drawing.Size(129, 20);
            this.D11_Load_status_lb.TabIndex = 1;
            this.D11_Load_status_lb.Text = "статус нагрузки";
            // 
            // D11_U2setUpDown
            // 
            this.D11_U2setUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_U2setUpDown.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.D11_U2setUpDown.Location = new System.Drawing.Point(107, 29);
            this.D11_U2setUpDown.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.D11_U2setUpDown.Name = "D11_U2setUpDown";
            this.D11_U2setUpDown.Size = new System.Drawing.Size(87, 35);
            this.D11_U2setUpDown.TabIndex = 7;
            this.D11_U2setUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.D11_U2setUpDown.ValueChanged += new System.EventHandler(this.U2setUpDown_ValueChanged);
            // 
            // D12_OutState
            // 
            this.D12_OutState.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.D12_OutState.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_OutState.Location = new System.Drawing.Point(594, 103);
            this.D12_OutState.Name = "D12_OutState";
            this.D12_OutState.Size = new System.Drawing.Size(46, 38);
            this.D12_OutState.TabIndex = 24;
            // 
            // D12_Uread
            // 
            this.D12_Uread.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_Uread.Location = new System.Drawing.Point(326, 103);
            this.D12_Uread.Name = "D12_Uread";
            this.D12_Uread.Size = new System.Drawing.Size(96, 38);
            this.D12_Uread.TabIndex = 21;
            this.D12_Uread.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D11_OutState
            // 
            this.D11_OutState.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.D11_OutState.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_OutState.Location = new System.Drawing.Point(594, 27);
            this.D11_OutState.Name = "D11_OutState";
            this.D11_OutState.Size = new System.Drawing.Size(46, 38);
            this.D11_OutState.TabIndex = 20;
            // 
            // D11_Uread
            // 
            this.D11_Uread.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_Uread.Location = new System.Drawing.Point(326, 27);
            this.D11_Uread.Name = "D11_Uread";
            this.D11_Uread.Size = new System.Drawing.Size(96, 38);
            this.D11_Uread.TabIndex = 17;
            this.D11_Uread.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // L2
            // 
            this.L2.AutoSize = true;
            this.L2.BackColor = System.Drawing.Color.Thistle;
            this.L2.Font = new System.Drawing.Font("Microsoft Sans Serif", 24.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L2.Location = new System.Drawing.Point(-4, 103);
            this.L2.Name = "L2";
            this.L2.Size = new System.Drawing.Size(108, 38);
            this.L2.TabIndex = 14;
            this.L2.Text = "QT1.2";
            this.L2.MouseEnter += new System.EventHandler(this.L2_MouseEnter);
            this.L2.MouseLeave += new System.EventHandler(this.L2_MouseLeave);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(487, 3);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 18);
            this.label4.TabIndex = 13;
            this.label4.Text = "Output";
            // 
            // Ureadlb
            // 
            this.Ureadlb.AutoSize = true;
            this.Ureadlb.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Ureadlb.Location = new System.Drawing.Point(340, 3);
            this.Ureadlb.Name = "Ureadlb";
            this.Ureadlb.Size = new System.Drawing.Size(70, 18);
            this.Ureadlb.TabIndex = 11;
            this.Ureadlb.Text = "U out, В";
            // 
            // Usetlb
            // 
            this.Usetlb.AutoSize = true;
            this.Usetlb.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Usetlb.Location = new System.Drawing.Point(115, 3);
            this.Usetlb.Name = "Usetlb";
            this.Usetlb.Size = new System.Drawing.Size(71, 18);
            this.Usetlb.TabIndex = 10;
            this.Usetlb.Text = "Set U, В";
            // 
            // L1
            // 
            this.L1.AutoSize = true;
            this.L1.BackColor = System.Drawing.Color.Thistle;
            this.L1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L1.Location = new System.Drawing.Point(-1, 13);
            this.L1.Name = "L1";
            this.L1.Size = new System.Drawing.Size(105, 74);
            this.L1.TabIndex = 9;
            this.L1.Text = "QT1.1\r\nQT1.3";
            this.L1.MouseEnter += new System.EventHandler(this.L1_MouseEnter);
            this.L1.MouseLeave += new System.EventHandler(this.L1_MouseLeave);
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.Color.Thistle;
            this.textBox2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox2.Location = new System.Drawing.Point(0, 26);
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(587, 42);
            this.textBox2.TabIndex = 15;
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D12_U2setUpDown
            // 
            this.D12_U2setUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_U2setUpDown.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.D12_U2setUpDown.Location = new System.Drawing.Point(107, 105);
            this.D12_U2setUpDown.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.D12_U2setUpDown.Name = "D12_U2setUpDown";
            this.D12_U2setUpDown.Size = new System.Drawing.Size(87, 35);
            this.D12_U2setUpDown.TabIndex = 7;
            this.D12_U2setUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.D12_U2setUpDown.ValueChanged += new System.EventHandler(this.U2setUpDown_ValueChanged);
            // 
            // D12_U2setB
            // 
            this.D12_U2setB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_U2setB.Location = new System.Drawing.Point(200, 105);
            this.D12_U2setB.Name = "D12_U2setB";
            this.D12_U2setB.Size = new System.Drawing.Size(94, 35);
            this.D12_U2setB.TabIndex = 2;
            this.D12_U2setB.Text = "Set U";
            this.D12_U2setB.UseVisualStyleBackColor = true;
            this.D12_U2setB.Click += new System.EventHandler(this.L2_U2setB_Click);
            // 
            // D12_ChargeOff_B
            // 
            this.D12_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_ChargeOff_B.Location = new System.Drawing.Point(519, 104);
            this.D12_ChargeOff_B.Name = "D12_ChargeOff_B";
            this.D12_ChargeOff_B.Size = new System.Drawing.Size(67, 36);
            this.D12_ChargeOff_B.TabIndex = 2;
            this.D12_ChargeOff_B.Text = "OFF";
            this.D12_ChargeOff_B.UseVisualStyleBackColor = true;
            this.D12_ChargeOff_B.Click += new System.EventHandler(this.L2_ChargeOff_B_Click);
            // 
            // D12_ChargeOn_B
            // 
            this.D12_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_ChargeOn_B.Location = new System.Drawing.Point(448, 104);
            this.D12_ChargeOn_B.Name = "D12_ChargeOn_B";
            this.D12_ChargeOn_B.Size = new System.Drawing.Size(65, 36);
            this.D12_ChargeOn_B.TabIndex = 2;
            this.D12_ChargeOn_B.Text = "ON";
            this.D12_ChargeOn_B.UseVisualStyleBackColor = true;
            this.D12_ChargeOn_B.Click += new System.EventHandler(this.L2_ChargeOn_B_Click);
            // 
            // D11_OverHeat_lb
            // 
            this.D11_OverHeat_lb.AutoSize = true;
            this.D11_OverHeat_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D11_OverHeat_lb.Location = new System.Drawing.Point(180, 70);
            this.D11_OverHeat_lb.Name = "D11_OverHeat_lb";
            this.D11_OverHeat_lb.Size = new System.Drawing.Size(14, 20);
            this.D11_OverHeat_lb.TabIndex = 1;
            this.D11_OverHeat_lb.Text = "-";
            // 
            // D12_OverHeat_lb
            // 
            this.D12_OverHeat_lb.AutoSize = true;
            this.D12_OverHeat_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_OverHeat_lb.Location = new System.Drawing.Point(180, 146);
            this.D12_OverHeat_lb.Name = "D12_OverHeat_lb";
            this.D12_OverHeat_lb.Size = new System.Drawing.Size(14, 20);
            this.D12_OverHeat_lb.TabIndex = 1;
            this.D12_OverHeat_lb.Text = "-";
            // 
            // D12_Loc_status_lb
            // 
            this.D12_Loc_status_lb.AutoSize = true;
            this.D12_Loc_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_Loc_status_lb.Location = new System.Drawing.Point(488, 146);
            this.D12_Loc_status_lb.Name = "D12_Loc_status_lb";
            this.D12_Loc_status_lb.Size = new System.Drawing.Size(152, 20);
            this.D12_Loc_status_lb.TabIndex = 1;
            this.D12_Loc_status_lb.Text = "статус блокировки";
            // 
            // D12_Load_status_lb
            // 
            this.D12_Load_status_lb.AutoSize = true;
            this.D12_Load_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D12_Load_status_lb.Location = new System.Drawing.Point(307, 146);
            this.D12_Load_status_lb.Name = "D12_Load_status_lb";
            this.D12_Load_status_lb.Size = new System.Drawing.Size(129, 20);
            this.D12_Load_status_lb.TabIndex = 1;
            this.D12_Load_status_lb.Text = "статус нагрузки";
            // 
            // PGM_IP
            // 
            this.PGM_IP.AutoSize = true;
            this.PGM_IP.Location = new System.Drawing.Point(0, 323);
            this.PGM_IP.Name = "PGM_IP";
            this.PGM_IP.Size = new System.Drawing.Size(17, 13);
            this.PGM_IP.TabIndex = 25;
            this.PGM_IP.Text = "IP";
            // 
            // D21_ChargeOff_B
            // 
            this.D21_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_ChargeOff_B.Location = new System.Drawing.Point(518, 177);
            this.D21_ChargeOff_B.Name = "D21_ChargeOff_B";
            this.D21_ChargeOff_B.Size = new System.Drawing.Size(67, 36);
            this.D21_ChargeOff_B.TabIndex = 2;
            this.D21_ChargeOff_B.Text = "OFF";
            this.D21_ChargeOff_B.UseVisualStyleBackColor = true;
            this.D21_ChargeOff_B.Click += new System.EventHandler(this.L3_ChargeOff_B_Click);
            // 
            // L3
            // 
            this.L3.AutoSize = true;
            this.L3.BackColor = System.Drawing.Color.Thistle;
            this.L3.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.L3.Location = new System.Drawing.Point(-2, 159);
            this.L3.Name = "L3";
            this.L3.Size = new System.Drawing.Size(107, 74);
            this.L3.TabIndex = 14;
            this.L3.Text = "QT2.1\r\nQT2.3";
            this.L3.MouseEnter += new System.EventHandler(this.L3_MouseEnter);
            this.L3.MouseLeave += new System.EventHandler(this.L3_MouseLeave);
            // 
            // D21_U2setUpDown
            // 
            this.D21_U2setUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_U2setUpDown.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.D21_U2setUpDown.Location = new System.Drawing.Point(106, 178);
            this.D21_U2setUpDown.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.D21_U2setUpDown.Name = "D21_U2setUpDown";
            this.D21_U2setUpDown.Size = new System.Drawing.Size(87, 35);
            this.D21_U2setUpDown.TabIndex = 7;
            this.D21_U2setUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D21_U2setB
            // 
            this.D21_U2setB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_U2setB.Location = new System.Drawing.Point(199, 178);
            this.D21_U2setB.Name = "D21_U2setB";
            this.D21_U2setB.Size = new System.Drawing.Size(94, 35);
            this.D21_U2setB.TabIndex = 2;
            this.D21_U2setB.Text = "Set U";
            this.D21_U2setB.UseVisualStyleBackColor = true;
            this.D21_U2setB.Click += new System.EventHandler(this.L3_U2setB_Click);
            // 
            // D21_Uread
            // 
            this.D21_Uread.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_Uread.Location = new System.Drawing.Point(325, 176);
            this.D21_Uread.Name = "D21_Uread";
            this.D21_Uread.Size = new System.Drawing.Size(96, 38);
            this.D21_Uread.TabIndex = 21;
            this.D21_Uread.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D21_OutState
            // 
            this.D21_OutState.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.D21_OutState.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_OutState.Location = new System.Drawing.Point(593, 176);
            this.D21_OutState.Name = "D21_OutState";
            this.D21_OutState.Size = new System.Drawing.Size(46, 38);
            this.D21_OutState.TabIndex = 24;
            // 
            // D21_ChargeOn_B
            // 
            this.D21_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_ChargeOn_B.Location = new System.Drawing.Point(447, 177);
            this.D21_ChargeOn_B.Name = "D21_ChargeOn_B";
            this.D21_ChargeOn_B.Size = new System.Drawing.Size(65, 36);
            this.D21_ChargeOn_B.TabIndex = 2;
            this.D21_ChargeOn_B.Text = "ON";
            this.D21_ChargeOn_B.UseVisualStyleBackColor = true;
            this.D21_ChargeOn_B.Click += new System.EventHandler(this.L3_ChargeOn_B_Click);
            // 
            // D21_Loc_status_lb
            // 
            this.D21_Loc_status_lb.AutoSize = true;
            this.D21_Loc_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_Loc_status_lb.Location = new System.Drawing.Point(487, 219);
            this.D21_Loc_status_lb.Name = "D21_Loc_status_lb";
            this.D21_Loc_status_lb.Size = new System.Drawing.Size(152, 20);
            this.D21_Loc_status_lb.TabIndex = 1;
            this.D21_Loc_status_lb.Text = "статус блокировки";
            // 
            // D21_Load_status_lb
            // 
            this.D21_Load_status_lb.AutoSize = true;
            this.D21_Load_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_Load_status_lb.Location = new System.Drawing.Point(306, 219);
            this.D21_Load_status_lb.Name = "D21_Load_status_lb";
            this.D21_Load_status_lb.Size = new System.Drawing.Size(129, 20);
            this.D21_Load_status_lb.TabIndex = 1;
            this.D21_Load_status_lb.Text = "статус нагрузки";
            // 
            // D21_OverHeat_lb
            // 
            this.D21_OverHeat_lb.AutoSize = true;
            this.D21_OverHeat_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D21_OverHeat_lb.Location = new System.Drawing.Point(179, 219);
            this.D21_OverHeat_lb.Name = "D21_OverHeat_lb";
            this.D21_OverHeat_lb.Size = new System.Drawing.Size(14, 20);
            this.D21_OverHeat_lb.TabIndex = 1;
            this.D21_OverHeat_lb.Text = "-";
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.Color.Thistle;
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox1.Location = new System.Drawing.Point(0, 101);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(587, 42);
            this.textBox1.TabIndex = 15;
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.Color.Thistle;
            this.textBox3.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox3.Location = new System.Drawing.Point(0, 175);
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.Size = new System.Drawing.Size(587, 42);
            this.textBox3.TabIndex = 15;
            this.textBox3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox4
            // 
            this.textBox4.BackColor = System.Drawing.Color.Thistle;
            this.textBox4.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox4.Location = new System.Drawing.Point(1, 249);
            this.textBox4.Name = "textBox4";
            this.textBox4.ReadOnly = true;
            this.textBox4.Size = new System.Drawing.Size(587, 42);
            this.textBox4.TabIndex = 15;
            this.textBox4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D22_Loc_status_lb
            // 
            this.D22_Loc_status_lb.AutoSize = true;
            this.D22_Loc_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_Loc_status_lb.Location = new System.Drawing.Point(488, 293);
            this.D22_Loc_status_lb.Name = "D22_Loc_status_lb";
            this.D22_Loc_status_lb.Size = new System.Drawing.Size(152, 20);
            this.D22_Loc_status_lb.TabIndex = 1;
            this.D22_Loc_status_lb.Text = "статус блокировки";
            // 
            // D22_Load_status_lb
            // 
            this.D22_Load_status_lb.AutoSize = true;
            this.D22_Load_status_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_Load_status_lb.Location = new System.Drawing.Point(307, 293);
            this.D22_Load_status_lb.Name = "D22_Load_status_lb";
            this.D22_Load_status_lb.Size = new System.Drawing.Size(129, 20);
            this.D22_Load_status_lb.TabIndex = 1;
            this.D22_Load_status_lb.Text = "статус нагрузки";
            // 
            // D22_ChargeOff_B
            // 
            this.D22_ChargeOff_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_ChargeOff_B.Location = new System.Drawing.Point(519, 251);
            this.D22_ChargeOff_B.Name = "D22_ChargeOff_B";
            this.D22_ChargeOff_B.Size = new System.Drawing.Size(67, 36);
            this.D22_ChargeOff_B.TabIndex = 2;
            this.D22_ChargeOff_B.Text = "OFF";
            this.D22_ChargeOff_B.UseVisualStyleBackColor = true;
            this.D22_ChargeOff_B.Click += new System.EventHandler(this.D22_ChargeOff_B_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Thistle;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 24.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(-3, 250);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(108, 38);
            this.label3.TabIndex = 14;
            this.label3.Text = "QT2.2";
            this.label3.MouseEnter += new System.EventHandler(this.L3_MouseEnter);
            this.label3.MouseLeave += new System.EventHandler(this.L3_MouseLeave);
            // 
            // D22_U2setUpDown
            // 
            this.D22_U2setUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_U2setUpDown.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.D22_U2setUpDown.Location = new System.Drawing.Point(107, 252);
            this.D22_U2setUpDown.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.D22_U2setUpDown.Name = "D22_U2setUpDown";
            this.D22_U2setUpDown.Size = new System.Drawing.Size(87, 35);
            this.D22_U2setUpDown.TabIndex = 7;
            this.D22_U2setUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D22_U2setB
            // 
            this.D22_U2setB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_U2setB.Location = new System.Drawing.Point(200, 252);
            this.D22_U2setB.Name = "D22_U2setB";
            this.D22_U2setB.Size = new System.Drawing.Size(94, 35);
            this.D22_U2setB.TabIndex = 2;
            this.D22_U2setB.Text = "Set U";
            this.D22_U2setB.UseVisualStyleBackColor = true;
            this.D22_U2setB.Click += new System.EventHandler(this.D22_U2setB_Click);
            // 
            // D22_Uread
            // 
            this.D22_Uread.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_Uread.Location = new System.Drawing.Point(326, 250);
            this.D22_Uread.Name = "D22_Uread";
            this.D22_Uread.Size = new System.Drawing.Size(96, 38);
            this.D22_Uread.TabIndex = 21;
            this.D22_Uread.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // D22_OutState
            // 
            this.D22_OutState.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.D22_OutState.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_OutState.Location = new System.Drawing.Point(594, 250);
            this.D22_OutState.Name = "D22_OutState";
            this.D22_OutState.Size = new System.Drawing.Size(46, 38);
            this.D22_OutState.TabIndex = 24;
            // 
            // D22_ChargeOn_B
            // 
            this.D22_ChargeOn_B.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_ChargeOn_B.Location = new System.Drawing.Point(448, 251);
            this.D22_ChargeOn_B.Name = "D22_ChargeOn_B";
            this.D22_ChargeOn_B.Size = new System.Drawing.Size(65, 36);
            this.D22_ChargeOn_B.TabIndex = 2;
            this.D22_ChargeOn_B.Text = "ON";
            this.D22_ChargeOn_B.UseVisualStyleBackColor = true;
            this.D22_ChargeOn_B.Click += new System.EventHandler(this.D22_ChargeOn_B_Click);
            // 
            // D22_OverHeat_lb
            // 
            this.D22_OverHeat_lb.AutoSize = true;
            this.D22_OverHeat_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.D22_OverHeat_lb.Location = new System.Drawing.Point(180, 293);
            this.D22_OverHeat_lb.Name = "D22_OverHeat_lb";
            this.D22_OverHeat_lb.Size = new System.Drawing.Size(14, 20);
            this.D22_OverHeat_lb.TabIndex = 1;
            this.D22_OverHeat_lb.Text = "-";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(642, 367);
            this.Controls.Add(this.PGM_IP);
            this.Controls.Add(this.D22_OverHeat_lb);
            this.Controls.Add(this.D21_OverHeat_lb);
            this.Controls.Add(this.D12_OverHeat_lb);
            this.Controls.Add(this.D11_OverHeat_lb);
            this.Controls.Add(this.AddNewSource_B);
            this.Controls.Add(this.D11_Load_status_lb);
            this.Controls.Add(this.D11_Loc_status_lb);
            this.Controls.Add(this.D22_ChargeOn_B);
            this.Controls.Add(this.D21_ChargeOn_B);
            this.Controls.Add(this.D12_ChargeOn_B);
            this.Controls.Add(this.D22_OutState);
            this.Controls.Add(this.D11_ChargeOn_B);
            this.Controls.Add(this.D21_OutState);
            this.Controls.Add(this.D22_Uread);
            this.Controls.Add(this.D12_OutState);
            this.Controls.Add(this.D21_Uread);
            this.Controls.Add(this.D22_U2setB);
            this.Controls.Add(this.D12_Uread);
            this.Controls.Add(this.D21_U2setB);
            this.Controls.Add(this.D12_U2setB);
            this.Controls.Add(this.D22_U2setUpDown);
            this.Controls.Add(this.D11_U2setB);
            this.Controls.Add(this.D21_U2setUpDown);
            this.Controls.Add(this.D12_U2setUpDown);
            this.Controls.Add(this.D11_U2setUpDown);
            this.Controls.Add(this.D11_OutState);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.D11_Uread);
            this.Controls.Add(this.L3);
            this.Controls.Add(this.L2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.Ureadlb);
            this.Controls.Add(this.Usetlb);
            this.Controls.Add(this.D22_ChargeOff_B);
            this.Controls.Add(this.L1);
            this.Controls.Add(this.D21_ChargeOff_B);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.D12_ChargeOff_B);
            this.Controls.Add(this.D22_Load_status_lb);
            this.Controls.Add(this.D11_ChargeOff_B);
            this.Controls.Add(this.D21_Load_status_lb);
            this.Controls.Add(this.D22_Loc_status_lb);
            this.Controls.Add(this.D12_Load_status_lb);
            this.Controls.Add(this.D21_Loc_status_lb);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.D12_Loc_status_lb);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.textBox2);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "HILAC triplets";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed_1);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.D11_U2setUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.D12_U2setUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.D21_U2setUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.D22_U2setUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Button D11_U2setB;
        private System.Windows.Forms.Label D11_Loc_status_lb;
        private System.Windows.Forms.Button D11_ChargeOn_B;
        private System.Windows.Forms.Button D11_ChargeOff_B;
        private System.Windows.Forms.ColumnHeader SrcNumberC;
        private System.Windows.Forms.ColumnHeader SrcIpC;
        private System.Windows.Forms.ColumnHeader PortC;
        private System.Windows.Forms.ColumnHeader SetVoltageC;
        private System.Windows.Forms.ColumnHeader ReadVoltageC;
        private System.Windows.Forms.Button AddNewSource_B;
        private System.Windows.Forms.Timer Update_timer;
        private System.Windows.Forms.Label D11_Load_status_lb;
        private System.Windows.Forms.NumericUpDown D11_U2setUpDown;
        private System.Windows.Forms.TextBox D12_OutState;
        private System.Windows.Forms.TextBox D12_Uread;
        private System.Windows.Forms.TextBox D11_OutState;
        private System.Windows.Forms.TextBox D11_Uread;
        private System.Windows.Forms.Label L2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label Ureadlb;
        private System.Windows.Forms.Label Usetlb;
        private System.Windows.Forms.Label L1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.NumericUpDown D12_U2setUpDown;
        private System.Windows.Forms.Button D12_U2setB;
        private System.Windows.Forms.Button D12_ChargeOff_B;
        private System.Windows.Forms.Button D12_ChargeOn_B;
        private System.Windows.Forms.Label D11_OverHeat_lb;
        private System.Windows.Forms.Label D12_OverHeat_lb;
        private System.Windows.Forms.Label D12_Loc_status_lb;
        private System.Windows.Forms.Label D12_Load_status_lb;
        private System.Windows.Forms.Label PGM_IP;
        private System.Windows.Forms.Button D21_ChargeOff_B;
        private System.Windows.Forms.Label L3;
        private System.Windows.Forms.NumericUpDown D21_U2setUpDown;
        private System.Windows.Forms.Button D21_U2setB;
        private System.Windows.Forms.TextBox D21_Uread;
        private System.Windows.Forms.TextBox D21_OutState;
        private System.Windows.Forms.Button D21_ChargeOn_B;
        private System.Windows.Forms.Label D21_Loc_status_lb;
        private System.Windows.Forms.Label D21_Load_status_lb;
        private System.Windows.Forms.Label D21_OverHeat_lb;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label D22_Loc_status_lb;
        private System.Windows.Forms.Label D22_Load_status_lb;
        private System.Windows.Forms.Button D22_ChargeOff_B;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown D22_U2setUpDown;
        private System.Windows.Forms.Button D22_U2setB;
        private System.Windows.Forms.TextBox D22_Uread;
        private System.Windows.Forms.TextBox D22_OutState;
        private System.Windows.Forms.Button D22_ChargeOn_B;
        private System.Windows.Forms.Label D22_OverHeat_lb;
    }
}

