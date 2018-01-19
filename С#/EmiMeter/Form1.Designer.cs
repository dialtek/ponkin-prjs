namespace EmiMeterSln
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.RefreshTimer = new System.Windows.Forms.Timer(this.components);
            this.PCBtemper = new System.Windows.Forms.Label();
            this.ScreenShotB = new System.Windows.Forms.Button();
            this.StatusBox = new System.Windows.Forms.TextBox();
            this.Save2fileB = new System.Windows.Forms.Button();
            this.IP_adr_textbox = new System.Windows.Forms.TextBox();
            this.Port_texbox = new System.Windows.Forms.MaskedTextBox();
            this.AutoReadPeriod = new System.Windows.Forms.NumericUpDown();
            this.IntensShowB = new System.Windows.Forms.Button();
            this.XprofileShowB = new System.Windows.Forms.Button();
            this.YprofileShowB = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.Tint_UpDown = new System.Windows.Forms.NumericUpDown();
            this.L1 = new System.Windows.Forms.Label();
            this.ZeroSetB = new System.Windows.Forms.Button();
            this.ADCscaleComboBox = new System.Windows.Forms.ComboBox();
            this.Full_Q = new System.Windows.Forms.Label();
            this.GraphB_Box = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.BeamQ = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SumQlb = new System.Windows.Forms.Label();
            this.SumIlb = new System.Windows.Forms.Label();
            this.CommentTb = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.TargetI = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.CommentLb = new System.Windows.Forms.Label();
            this.TrigModeRb = new System.Windows.Forms.RadioButton();
            this.ModegroupBox = new System.Windows.Forms.GroupBox();
            this.ContModeRb = new System.Windows.Forms.RadioButton();
            this.Modelb = new System.Windows.Forms.Label();
            this.Testlb = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.AutoReadPeriod)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Tint_UpDown)).BeginInit();
            this.GraphB_Box.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.ModegroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // RefreshTimer
            // 
            this.RefreshTimer.Interval = 200;
            this.RefreshTimer.Tick += new System.EventHandler(this.RefreshTimer_Tick);
            // 
            // PCBtemper
            // 
            this.PCBtemper.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.PCBtemper.AutoSize = true;
            this.PCBtemper.BackColor = System.Drawing.Color.Transparent;
            this.PCBtemper.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PCBtemper.Location = new System.Drawing.Point(5, 152);
            this.PCBtemper.Name = "PCBtemper";
            this.PCBtemper.Size = new System.Drawing.Size(0, 24);
            this.PCBtemper.TabIndex = 6;
            // 
            // ScreenShotB
            // 
            this.ScreenShotB.Location = new System.Drawing.Point(316, 215);
            this.ScreenShotB.Name = "ScreenShotB";
            this.ScreenShotB.Size = new System.Drawing.Size(78, 32);
            this.ScreenShotB.TabIndex = 8;
            this.ScreenShotB.Text = "Print screen";
            this.ScreenShotB.UseVisualStyleBackColor = true;
            this.ScreenShotB.Click += new System.EventHandler(this.ScreenShotB_Click);
            // 
            // StatusBox
            // 
            this.StatusBox.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.Location = new System.Drawing.Point(0, 250);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(666, 20);
            this.StatusBox.TabIndex = 0;
            this.StatusBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Save2fileB
            // 
            this.Save2fileB.Location = new System.Drawing.Point(232, 215);
            this.Save2fileB.Name = "Save2fileB";
            this.Save2fileB.Size = new System.Drawing.Size(78, 32);
            this.Save2fileB.TabIndex = 8;
            this.Save2fileB.Text = "Save to file";
            this.Save2fileB.UseVisualStyleBackColor = true;
            this.Save2fileB.Click += new System.EventHandler(this.Save2fileB_Click);
            // 
            // IP_adr_textbox
            // 
            this.IP_adr_textbox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.IP_adr_textbox.Location = new System.Drawing.Point(549, 72);
            this.IP_adr_textbox.Name = "IP_adr_textbox";
            this.IP_adr_textbox.Size = new System.Drawing.Size(93, 20);
            this.IP_adr_textbox.TabIndex = 9;
            this.IP_adr_textbox.Text = "192.168.127.254";
            this.IP_adr_textbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Port_texbox
            // 
            this.Port_texbox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Port_texbox.Location = new System.Drawing.Point(550, 98);
            this.Port_texbox.Name = "Port_texbox";
            this.Port_texbox.Size = new System.Drawing.Size(52, 20);
            this.Port_texbox.TabIndex = 10;
            this.Port_texbox.Text = "4001";
            this.Port_texbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AutoReadPeriod
            // 
            this.AutoReadPeriod.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.AutoReadPeriod.Location = new System.Drawing.Point(13, 88);
            this.AutoReadPeriod.Maximum = new decimal(new int[] {
            60000,
            0,
            0,
            0});
            this.AutoReadPeriod.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.AutoReadPeriod.Name = "AutoReadPeriod";
            this.AutoReadPeriod.Size = new System.Drawing.Size(74, 20);
            this.AutoReadPeriod.TabIndex = 11;
            this.AutoReadPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.AutoReadPeriod.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.AutoReadPeriod.ValueChanged += new System.EventHandler(this.AutoReadPeriod_ValueChanged);
            // 
            // IntensShowB
            // 
            this.IntensShowB.Location = new System.Drawing.Point(174, 19);
            this.IntensShowB.Name = "IntensShowB";
            this.IntensShowB.Size = new System.Drawing.Size(78, 31);
            this.IntensShowB.TabIndex = 13;
            this.IntensShowB.Text = "Intensity";
            this.IntensShowB.UseVisualStyleBackColor = true;
            this.IntensShowB.Click += new System.EventHandler(this.IntensShowB_Click);
            // 
            // XprofileShowB
            // 
            this.XprofileShowB.Location = new System.Drawing.Point(6, 19);
            this.XprofileShowB.Name = "XprofileShowB";
            this.XprofileShowB.Size = new System.Drawing.Size(78, 31);
            this.XprofileShowB.TabIndex = 13;
            this.XprofileShowB.Text = "X-profile";
            this.XprofileShowB.UseVisualStyleBackColor = true;
            this.XprofileShowB.Click += new System.EventHandler(this.XprofileShowB_Click);
            // 
            // YprofileShowB
            // 
            this.YprofileShowB.Location = new System.Drawing.Point(90, 19);
            this.YprofileShowB.Name = "YprofileShowB";
            this.YprofileShowB.Size = new System.Drawing.Size(78, 31);
            this.YprofileShowB.TabIndex = 13;
            this.YprofileShowB.Text = "Y-profile";
            this.YprofileShowB.UseVisualStyleBackColor = true;
            this.YprofileShowB.Click += new System.EventHandler(this.YprofileShowB_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(86, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(18, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "us";
            // 
            // Tint_UpDown
            // 
            this.Tint_UpDown.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.Tint_UpDown.Location = new System.Drawing.Point(9, 19);
            this.Tint_UpDown.Maximum = new decimal(new int[] {
            65000,
            0,
            0,
            0});
            this.Tint_UpDown.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.Tint_UpDown.Name = "Tint_UpDown";
            this.Tint_UpDown.Size = new System.Drawing.Size(75, 20);
            this.Tint_UpDown.TabIndex = 11;
            this.Tint_UpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Tint_UpDown.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.Tint_UpDown.ValueChanged += new System.EventHandler(this.Tint_UpDown_ValueChanged);
            // 
            // L1
            // 
            this.L1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.L1.AutoSize = true;
            this.L1.Location = new System.Drawing.Point(551, 126);
            this.L1.Name = "L1";
            this.L1.Size = new System.Drawing.Size(19, 13);
            this.L1.TabIndex = 12;
            this.L1.Text = "L1";
            // 
            // ZeroSetB
            // 
            this.ZeroSetB.Location = new System.Drawing.Point(278, 19);
            this.ZeroSetB.Name = "ZeroSetB";
            this.ZeroSetB.Size = new System.Drawing.Size(78, 31);
            this.ZeroSetB.TabIndex = 13;
            this.ZeroSetB.Text = "Set \"zero\"";
            this.ZeroSetB.UseVisualStyleBackColor = true;
            this.ZeroSetB.Click += new System.EventHandler(this.ZeroSetB_Click);
            // 
            // ADCscaleComboBox
            // 
            this.ADCscaleComboBox.FormattingEnabled = true;
            this.ADCscaleComboBox.Items.AddRange(new object[] {
            "3 pC",
            "6 pC",
            "12 pC"});
            this.ADCscaleComboBox.Location = new System.Drawing.Point(10, 19);
            this.ADCscaleComboBox.Name = "ADCscaleComboBox";
            this.ADCscaleComboBox.Size = new System.Drawing.Size(74, 21);
            this.ADCscaleComboBox.TabIndex = 14;
            this.ADCscaleComboBox.Text = "12 pC";
            this.ADCscaleComboBox.SelectedIndexChanged += new System.EventHandler(this.ADCscaleComboBox_SelectedIndexChanged);
            // 
            // Full_Q
            // 
            this.Full_Q.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Full_Q.AutoSize = true;
            this.Full_Q.Location = new System.Drawing.Point(551, 150);
            this.Full_Q.Name = "Full_Q";
            this.Full_Q.Size = new System.Drawing.Size(37, 13);
            this.Full_Q.TabIndex = 12;
            this.Full_Q.Text = "Full_Q";
            // 
            // GraphB_Box
            // 
            this.GraphB_Box.Controls.Add(this.YprofileShowB);
            this.GraphB_Box.Controls.Add(this.IntensShowB);
            this.GraphB_Box.Controls.Add(this.XprofileShowB);
            this.GraphB_Box.Controls.Add(this.ZeroSetB);
            this.GraphB_Box.Location = new System.Drawing.Point(142, 67);
            this.GraphB_Box.Name = "GraphB_Box";
            this.GraphB_Box.Size = new System.Drawing.Size(362, 58);
            this.GraphB_Box.TabIndex = 16;
            this.GraphB_Box.TabStop = false;
            this.GraphB_Box.Text = "Graphs";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(93, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(20, 13);
            this.label3.TabIndex = 12;
            this.label3.Text = "ms";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.Tint_UpDown);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(142, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(110, 49);
            this.groupBox2.TabIndex = 17;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Integration time";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.ADCscaleComboBox);
            this.groupBox3.Location = new System.Drawing.Point(269, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(97, 49);
            this.groupBox3.TabIndex = 17;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Scale";
            // 
            // BeamQ
            // 
            this.BeamQ.AutoSize = true;
            this.BeamQ.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.BeamQ.Location = new System.Drawing.Point(321, 178);
            this.BeamQ.Name = "BeamQ";
            this.BeamQ.Size = new System.Drawing.Size(94, 24);
            this.BeamQ.TabIndex = 12;
            this.BeamQ.Text = "TargetQ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(206, 178);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 24);
            this.label2.TabIndex = 12;
            this.label2.Text = "Target Q:";
            // 
            // SumQlb
            // 
            this.SumQlb.AutoSize = true;
            this.SumQlb.Font = new System.Drawing.Font("Consolas", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SumQlb.Location = new System.Drawing.Point(0, 177);
            this.SumQlb.Name = "SumQlb";
            this.SumQlb.Size = new System.Drawing.Size(64, 28);
            this.SumQlb.TabIndex = 12;
            this.SumQlb.Text = "SumQ";
            // 
            // SumIlb
            // 
            this.SumIlb.AutoSize = true;
            this.SumIlb.Font = new System.Drawing.Font("Consolas", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SumIlb.Location = new System.Drawing.Point(0, 139);
            this.SumIlb.Name = "SumIlb";
            this.SumIlb.Size = new System.Drawing.Size(64, 28);
            this.SumIlb.TabIndex = 12;
            this.SumIlb.Text = "SumI";
            // 
            // CommentTb
            // 
            this.CommentTb.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CommentTb.Location = new System.Drawing.Point(78, 220);
            this.CommentTb.Name = "CommentTb";
            this.CommentTb.Size = new System.Drawing.Size(144, 22);
            this.CommentTb.TabIndex = 18;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.Location = new System.Drawing.Point(206, 141);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(118, 24);
            this.label8.TabIndex = 12;
            this.label8.Text = "Target I:";
            // 
            // TargetI
            // 
            this.TargetI.AutoSize = true;
            this.TargetI.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TargetI.Location = new System.Drawing.Point(321, 141);
            this.TargetI.Name = "TargetI";
            this.TargetI.Size = new System.Drawing.Size(94, 24);
            this.TargetI.TabIndex = 12;
            this.TargetI.Text = "TargetI";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label9.Location = new System.Drawing.Point(471, 141);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(46, 24);
            this.label9.TabIndex = 12;
            this.label9.Text = "[А]";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(471, 175);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 24);
            this.label4.TabIndex = 12;
            this.label4.Text = "[C]";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Image = global::EmiMeterSln.Properties.Resources.LHEP_emblema_small;
            this.pictureBox1.Location = new System.Drawing.Point(403, 7);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(101, 54);
            this.pictureBox1.TabIndex = 19;
            this.pictureBox1.TabStop = false;
            // 
            // CommentLb
            // 
            this.CommentLb.AutoSize = true;
            this.CommentLb.Location = new System.Drawing.Point(15, 225);
            this.CommentLb.Name = "CommentLb";
            this.CommentLb.Size = new System.Drawing.Size(51, 13);
            this.CommentLb.TabIndex = 20;
            this.CommentLb.Text = "Comment";
            // 
            // TrigModeRb
            // 
            this.TrigModeRb.AutoSize = true;
            this.TrigModeRb.Location = new System.Drawing.Point(17, 23);
            this.TrigModeRb.Name = "TrigModeRb";
            this.TrigModeRb.Size = new System.Drawing.Size(70, 17);
            this.TrigModeRb.TabIndex = 21;
            this.TrigModeRb.Text = "Triggered";
            this.TrigModeRb.UseVisualStyleBackColor = true;
            this.TrigModeRb.CheckedChanged += new System.EventHandler(this.TrigModeRb_CheckedChanged);
            // 
            // ModegroupBox
            // 
            this.ModegroupBox.Controls.Add(this.label3);
            this.ModegroupBox.Controls.Add(this.ContModeRb);
            this.ModegroupBox.Controls.Add(this.AutoReadPeriod);
            this.ModegroupBox.Controls.Add(this.TrigModeRb);
            this.ModegroupBox.Location = new System.Drawing.Point(5, 12);
            this.ModegroupBox.Name = "ModegroupBox";
            this.ModegroupBox.Size = new System.Drawing.Size(118, 113);
            this.ModegroupBox.TabIndex = 17;
            this.ModegroupBox.TabStop = false;
            this.ModegroupBox.Text = "Reading mode";
            // 
            // ContModeRb
            // 
            this.ContModeRb.AutoSize = true;
            this.ContModeRb.Checked = true;
            this.ContModeRb.Location = new System.Drawing.Point(17, 60);
            this.ContModeRb.Name = "ContModeRb";
            this.ContModeRb.Size = new System.Drawing.Size(78, 17);
            this.ContModeRb.TabIndex = 21;
            this.ContModeRb.TabStop = true;
            this.ContModeRb.Text = "Continuous";
            this.ContModeRb.UseVisualStyleBackColor = true;
            this.ContModeRb.CheckedChanged += new System.EventHandler(this.ContModeRb_CheckedChanged);
            // 
            // Modelb
            // 
            this.Modelb.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Modelb.AutoSize = true;
            this.Modelb.Location = new System.Drawing.Point(551, 174);
            this.Modelb.Name = "Modelb";
            this.Modelb.Size = new System.Drawing.Size(34, 13);
            this.Modelb.TabIndex = 12;
            this.Modelb.Text = "Mode";
            // 
            // Testlb
            // 
            this.Testlb.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Testlb.AutoSize = true;
            this.Testlb.Location = new System.Drawing.Point(417, 225);
            this.Testlb.Name = "Testlb";
            this.Testlb.Size = new System.Drawing.Size(49, 13);
            this.Testlb.TabIndex = 12;
            this.Testlb.Text = "test label";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Wheat;
            this.ClientSize = new System.Drawing.Size(666, 270);
            this.Controls.Add(this.CommentLb);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.CommentTb);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.ModegroupBox);
            this.Controls.Add(this.GraphB_Box);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.SumQlb);
            this.Controls.Add(this.TargetI);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.SumIlb);
            this.Controls.Add(this.BeamQ);
            this.Controls.Add(this.Testlb);
            this.Controls.Add(this.Modelb);
            this.Controls.Add(this.Full_Q);
            this.Controls.Add(this.L1);
            this.Controls.Add(this.Port_texbox);
            this.Controls.Add(this.IP_adr_textbox);
            this.Controls.Add(this.Save2fileB);
            this.Controls.Add(this.ScreenShotB);
            this.Controls.Add(this.PCBtemper);
            this.Controls.Add(this.StatusBox);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(300, 100);
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Text = "Ion collector current visualisation";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.AutoReadPeriod)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Tint_UpDown)).EndInit();
            this.GraphB_Box.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ModegroupBox.ResumeLayout(false);
            this.ModegroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer RefreshTimer;
        private System.Windows.Forms.Label PCBtemper;
        private System.Windows.Forms.Button ScreenShotB;
        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Button Save2fileB;
        private System.Windows.Forms.TextBox IP_adr_textbox;
        private System.Windows.Forms.MaskedTextBox Port_texbox;
        private System.Windows.Forms.NumericUpDown AutoReadPeriod;
        private System.Windows.Forms.Button IntensShowB;
        private System.Windows.Forms.Button XprofileShowB;
        private System.Windows.Forms.Button YprofileShowB;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown Tint_UpDown;
        private System.Windows.Forms.Label L1;
        private System.Windows.Forms.Button ZeroSetB;
        private System.Windows.Forms.ComboBox ADCscaleComboBox;
        private System.Windows.Forms.Label Full_Q;
        private System.Windows.Forms.GroupBox GraphB_Box;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label BeamQ;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label SumQlb;
        private System.Windows.Forms.Label SumIlb;
        private System.Windows.Forms.TextBox CommentTb;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label TargetI;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label CommentLb;
        private System.Windows.Forms.RadioButton TrigModeRb;
        private System.Windows.Forms.GroupBox ModegroupBox;
        private System.Windows.Forms.RadioButton ContModeRb;
        private System.Windows.Forms.Label Modelb;
        private System.Windows.Forms.Label Testlb;
    }
}

