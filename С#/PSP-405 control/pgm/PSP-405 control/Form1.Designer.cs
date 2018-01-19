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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.VDK_FI_OutputB = new System.Windows.Forms.Button();
            this.CurrTime = new System.Windows.Forms.Label();
            this.DataUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.S1_name = new System.Windows.Forms.Label();
            this.S2_name = new System.Windows.Forms.Label();
            this.S3_name = new System.Windows.Forms.Label();
            this.S4_name = new System.Windows.Forms.Label();
            this.S5_name = new System.Windows.Forms.Label();
            this.S6_name = new System.Windows.Forms.Label();
            this.SourceId = new System.Windows.Forms.Label();
            this.V_ = new System.Windows.Forms.Label();
            this.VoltageUpDown = new System.Windows.Forms.NumericUpDown();
            this.VsetGroupBox = new System.Windows.Forms.GroupBox();
            this.CfgGroupBox = new System.Windows.Forms.GroupBox();
            this.SetCfg = new System.Windows.Forms.Button();
            this.LoadCfg = new System.Windows.Forms.Button();
            this.SaveCfg = new System.Windows.Forms.Button();
            this.VoltageLimitUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.CurrentLimitUpDown = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.Statusbox = new System.Windows.Forms.TextBox();
            this.AllControlsGroupBox = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.SetParameters = new System.Windows.Forms.Button();
            this.VDK_FI_currBox = new System.Windows.Forms.TextBox();
            this.GDK_FI_currBox = new System.Windows.Forms.TextBox();
            this.VDK_1_currBox = new System.Windows.Forms.TextBox();
            this.GDK_1_currBox = new System.Windows.Forms.TextBox();
            this.VDK_6_currBox = new System.Windows.Forms.TextBox();
            this.GDK_6_currBox = new System.Windows.Forms.TextBox();
            this.VDK_FI_voltBox = new System.Windows.Forms.TextBox();
            this.GDK_FI_voltBox = new System.Windows.Forms.TextBox();
            this.VDK_1_voltBox = new System.Windows.Forms.TextBox();
            this.GDK_1_voltBox = new System.Windows.Forms.TextBox();
            this.VDK_6_voltBox = new System.Windows.Forms.TextBox();
            this.GDK_6_voltBox = new System.Windows.Forms.TextBox();
            this.IColumn = new System.Windows.Forms.Label();
            this.UColumn = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.GDK_FI_OutputB = new System.Windows.Forms.Button();
            this.VDK_1_OutputB = new System.Windows.Forms.Button();
            this.GDK_1_OutputB = new System.Windows.Forms.Button();
            this.VDK_6_OutputB = new System.Windows.Forms.Button();
            this.GDK_6_OutputB = new System.Windows.Forms.Button();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.VoltageUpDown)).BeginInit();
            this.VsetGroupBox.SuspendLayout();
            this.CfgGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VoltageLimitUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentLimitUpDown)).BeginInit();
            this.AllControlsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // VDK_FI_OutputB
            // 
            this.VDK_FI_OutputB.BackColor = System.Drawing.Color.Silver;
            this.VDK_FI_OutputB.Font = new System.Drawing.Font("Verdana", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_OutputB.ForeColor = System.Drawing.SystemColors.WindowText;
            this.VDK_FI_OutputB.Location = new System.Drawing.Point(395, 37);
            this.VDK_FI_OutputB.Name = "VDK_FI_OutputB";
            this.VDK_FI_OutputB.Size = new System.Drawing.Size(106, 46);
            this.VDK_FI_OutputB.TabIndex = 0;
            this.VDK_FI_OutputB.Text = "─";
            this.VDK_FI_OutputB.UseVisualStyleBackColor = false;
            this.VDK_FI_OutputB.Click += new System.EventHandler(this.VDK_FI_OutputB_Click);
            // 
            // CurrTime
            // 
            this.CurrTime.AutoSize = true;
            this.CurrTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CurrTime.Location = new System.Drawing.Point(406, 490);
            this.CurrTime.Name = "CurrTime";
            this.CurrTime.Size = new System.Drawing.Size(104, 18);
            this.CurrTime.TabIndex = 2;
            this.CurrTime.Text = "Time and Data";
            // 
            // DataUpdateTimer
            // 
            this.DataUpdateTimer.Tick += new System.EventHandler(this.DataUpdateTimer_Tick);
            // 
            // S1_name
            // 
            this.S1_name.AutoSize = true;
            this.S1_name.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.S1_name.ForeColor = System.Drawing.Color.DimGray;
            this.S1_name.Location = new System.Drawing.Point(6, 45);
            this.S1_name.Name = "S1_name";
            this.S1_name.Size = new System.Drawing.Size(177, 32);
            this.S1_name.TabIndex = 12;
            this.S1_name.Text = "ВДК-ФИ     ";
            this.S1_name.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.S1_name.Click += new System.EventHandler(this.S1_name_Click);
            this.S1_name.MouseEnter += new System.EventHandler(this.S1_name_MouseEnter);
            this.S1_name.MouseLeave += new System.EventHandler(this.S1_name_MouseLeave);
            // 
            // S2_name
            // 
            this.S2_name.AutoSize = true;
            this.S2_name.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.S2_name.ForeColor = System.Drawing.Color.DimGray;
            this.S2_name.Location = new System.Drawing.Point(6, 91);
            this.S2_name.Name = "S2_name";
            this.S2_name.Size = new System.Drawing.Size(183, 32);
            this.S2_name.TabIndex = 12;
            this.S2_name.Text = "ГДК-ФИ      ";
            this.S2_name.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.S2_name.Click += new System.EventHandler(this.S2_name_Click);
            this.S2_name.MouseEnter += new System.EventHandler(this.S2_name_MouseEnter);
            this.S2_name.MouseLeave += new System.EventHandler(this.S2_name_MouseLeave);
            // 
            // S3_name
            // 
            this.S3_name.AutoSize = true;
            this.S3_name.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.S3_name.ForeColor = System.Drawing.Color.DimGray;
            this.S3_name.Location = new System.Drawing.Point(6, 137);
            this.S3_name.Name = "S3_name";
            this.S3_name.Size = new System.Drawing.Size(192, 32);
            this.S3_name.TabIndex = 12;
            this.S3_name.Text = "ВДК-1         ";
            this.S3_name.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.S3_name.Click += new System.EventHandler(this.S3_name_Click);
            this.S3_name.MouseEnter += new System.EventHandler(this.S3_name_MouseEnter);
            this.S3_name.MouseLeave += new System.EventHandler(this.S3_name_MouseLeave);
            // 
            // S4_name
            // 
            this.S4_name.AutoSize = true;
            this.S4_name.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.S4_name.ForeColor = System.Drawing.Color.DimGray;
            this.S4_name.Location = new System.Drawing.Point(6, 183);
            this.S4_name.Name = "S4_name";
            this.S4_name.Size = new System.Drawing.Size(188, 32);
            this.S4_name.TabIndex = 12;
            this.S4_name.Text = "ГДК-1         ";
            this.S4_name.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.S4_name.Click += new System.EventHandler(this.S4_name_Click);
            this.S4_name.MouseEnter += new System.EventHandler(this.S4_name_MouseEnter);
            this.S4_name.MouseLeave += new System.EventHandler(this.S4_name_MouseLeave);
            // 
            // S5_name
            // 
            this.S5_name.AutoSize = true;
            this.S5_name.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.S5_name.ForeColor = System.Drawing.Color.DimGray;
            this.S5_name.Location = new System.Drawing.Point(6, 230);
            this.S5_name.Name = "S5_name";
            this.S5_name.Size = new System.Drawing.Size(312, 32);
            this.S5_name.TabIndex = 12;
            this.S5_name.Text = "ВДК-6                     ";
            this.S5_name.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.S5_name.Click += new System.EventHandler(this.S5_name_Click);
            this.S5_name.MouseEnter += new System.EventHandler(this.S5_name_MouseEnter);
            this.S5_name.MouseLeave += new System.EventHandler(this.S5_name_MouseLeave);
            // 
            // S6_name
            // 
            this.S6_name.AutoSize = true;
            this.S6_name.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.S6_name.ForeColor = System.Drawing.Color.DimGray;
            this.S6_name.Location = new System.Drawing.Point(6, 274);
            this.S6_name.Name = "S6_name";
            this.S6_name.Size = new System.Drawing.Size(338, 32);
            this.S6_name.TabIndex = 12;
            this.S6_name.Text = "ГДК-6                        ";
            this.S6_name.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.S6_name.Click += new System.EventHandler(this.S6_name_Click);
            this.S6_name.MouseEnter += new System.EventHandler(this.S6_name_MouseEnter);
            this.S6_name.MouseLeave += new System.EventHandler(this.S6_name_MouseLeave);
            // 
            // SourceId
            // 
            this.SourceId.AutoSize = true;
            this.SourceId.Font = new System.Drawing.Font("Verdana", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SourceId.ForeColor = System.Drawing.Color.DimGray;
            this.SourceId.Location = new System.Drawing.Point(53, 14);
            this.SourceId.Name = "SourceId";
            this.SourceId.Size = new System.Drawing.Size(0, 59);
            this.SourceId.TabIndex = 5;
            // 
            // V_
            // 
            this.V_.AutoSize = true;
            this.V_.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.V_.Location = new System.Drawing.Point(120, 40);
            this.V_.Name = "V_";
            this.V_.Size = new System.Drawing.Size(34, 32);
            this.V_.TabIndex = 6;
            this.V_.Text = "B";
            // 
            // VoltageUpDown
            // 
            this.VoltageUpDown.Font = new System.Drawing.Font("Verdana", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VoltageUpDown.Location = new System.Drawing.Point(8, 36);
            this.VoltageUpDown.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.VoltageUpDown.Name = "VoltageUpDown";
            this.VoltageUpDown.Size = new System.Drawing.Size(114, 40);
            this.VoltageUpDown.TabIndex = 7;
            this.VoltageUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VoltageUpDown.ValueChanged += new System.EventHandler(this.VoltageUpDown_ValueChanged);
            // 
            // VsetGroupBox
            // 
            this.VsetGroupBox.Controls.Add(this.VoltageUpDown);
            this.VsetGroupBox.Controls.Add(this.V_);
            this.VsetGroupBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VsetGroupBox.Location = new System.Drawing.Point(344, 192);
            this.VsetGroupBox.Name = "VsetGroupBox";
            this.VsetGroupBox.Size = new System.Drawing.Size(34, 28);
            this.VsetGroupBox.TabIndex = 8;
            this.VsetGroupBox.TabStop = false;
            this.VsetGroupBox.Text = "Запас U";
            // 
            // CfgGroupBox
            // 
            this.CfgGroupBox.Controls.Add(this.SetCfg);
            this.CfgGroupBox.Controls.Add(this.LoadCfg);
            this.CfgGroupBox.Controls.Add(this.SaveCfg);
            this.CfgGroupBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CfgGroupBox.Location = new System.Drawing.Point(398, 336);
            this.CfgGroupBox.Name = "CfgGroupBox";
            this.CfgGroupBox.Size = new System.Drawing.Size(108, 142);
            this.CfgGroupBox.TabIndex = 9;
            this.CfgGroupBox.TabStop = false;
            this.CfgGroupBox.Text = "Конфигурация";
            // 
            // SetCfg
            // 
            this.SetCfg.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SetCfg.Location = new System.Drawing.Point(6, 60);
            this.SetCfg.Name = "SetCfg";
            this.SetCfg.Size = new System.Drawing.Size(90, 35);
            this.SetCfg.TabIndex = 0;
            this.SetCfg.Text = "Применить";
            this.SetCfg.UseVisualStyleBackColor = true;
            this.SetCfg.Click += new System.EventHandler(this.SetCfg_Click);
            // 
            // LoadCfg
            // 
            this.LoadCfg.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LoadCfg.Location = new System.Drawing.Point(6, 19);
            this.LoadCfg.Name = "LoadCfg";
            this.LoadCfg.Size = new System.Drawing.Size(90, 35);
            this.LoadCfg.TabIndex = 0;
            this.LoadCfg.Text = "Загрузить";
            this.LoadCfg.UseVisualStyleBackColor = true;
            this.LoadCfg.Click += new System.EventHandler(this.LoadCfg_Click);
            // 
            // SaveCfg
            // 
            this.SaveCfg.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SaveCfg.Location = new System.Drawing.Point(6, 101);
            this.SaveCfg.Name = "SaveCfg";
            this.SaveCfg.Size = new System.Drawing.Size(90, 35);
            this.SaveCfg.TabIndex = 0;
            this.SaveCfg.Text = "Сохранить";
            this.SaveCfg.UseVisualStyleBackColor = true;
            this.SaveCfg.Click += new System.EventHandler(this.SaveCfg_Click);
            // 
            // VoltageLimitUpDown
            // 
            this.VoltageLimitUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 33.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VoltageLimitUpDown.ForeColor = System.Drawing.Color.Red;
            this.VoltageLimitUpDown.Location = new System.Drawing.Point(211, 101);
            this.VoltageLimitUpDown.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.VoltageLimitUpDown.Name = "VoltageLimitUpDown";
            this.VoltageLimitUpDown.Size = new System.Drawing.Size(120, 58);
            this.VoltageLimitUpDown.TabIndex = 7;
            this.VoltageLimitUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VoltageLimitUpDown.ValueChanged += new System.EventHandler(this.VoltageLimitUpDown_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.ForeColor = System.Drawing.Color.DimGray;
            this.label2.Location = new System.Drawing.Point(324, 103);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 55);
            this.label2.TabIndex = 6;
            this.label2.Text = "B";
            // 
            // CurrentLimitUpDown
            // 
            this.CurrentLimitUpDown.BackColor = System.Drawing.SystemColors.Window;
            this.CurrentLimitUpDown.DecimalPlaces = 2;
            this.CurrentLimitUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 33.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CurrentLimitUpDown.ForeColor = System.Drawing.Color.DimGray;
            this.CurrentLimitUpDown.Increment = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.CurrentLimitUpDown.Location = new System.Drawing.Point(8, 101);
            this.CurrentLimitUpDown.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.CurrentLimitUpDown.Name = "CurrentLimitUpDown";
            this.CurrentLimitUpDown.Size = new System.Drawing.Size(136, 58);
            this.CurrentLimitUpDown.TabIndex = 7;
            this.CurrentLimitUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.CurrentLimitUpDown.ValueChanged += new System.EventHandler(this.CurrentLimitUpDown_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.ForeColor = System.Drawing.Color.DimGray;
            this.label4.Location = new System.Drawing.Point(139, 103);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 55);
            this.label4.TabIndex = 6;
            this.label4.Text = "А";
            // 
            // Statusbox
            // 
            this.Statusbox.BackColor = System.Drawing.SystemColors.Window;
            this.Statusbox.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Statusbox.Location = new System.Drawing.Point(1, 567);
            this.Statusbox.Multiline = true;
            this.Statusbox.Name = "Statusbox";
            this.Statusbox.ReadOnly = true;
            this.Statusbox.Size = new System.Drawing.Size(388, 43);
            this.Statusbox.TabIndex = 10;
            this.Statusbox.Text = "Проверьте питание источников: \r\nВДК-ФИ ГДК-ФИ ВДК-1 ГДК-1 ВДК-6 ГДК-6\r\n ";
            this.Statusbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AllControlsGroupBox
            // 
            this.AllControlsGroupBox.Controls.Add(this.label6);
            this.AllControlsGroupBox.Controls.Add(this.VoltageLimitUpDown);
            this.AllControlsGroupBox.Controls.Add(this.CurrentLimitUpDown);
            this.AllControlsGroupBox.Controls.Add(this.SetParameters);
            this.AllControlsGroupBox.Controls.Add(this.label4);
            this.AllControlsGroupBox.Controls.Add(this.VsetGroupBox);
            this.AllControlsGroupBox.Controls.Add(this.label2);
            this.AllControlsGroupBox.Controls.Add(this.SourceId);
            this.AllControlsGroupBox.Location = new System.Drawing.Point(5, 337);
            this.AllControlsGroupBox.Name = "AllControlsGroupBox";
            this.AllControlsGroupBox.Size = new System.Drawing.Size(384, 225);
            this.AllControlsGroupBox.TabIndex = 15;
            this.AllControlsGroupBox.TabStop = false;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Red;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.ForeColor = System.Drawing.Color.Yellow;
            this.label6.Location = new System.Drawing.Point(214, 161);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(114, 18);
            this.label6.TabIndex = 9;
            this.label6.Text = " Ограничение   ";
            // 
            // SetParameters
            // 
            this.SetParameters.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SetParameters.Location = new System.Drawing.Point(6, 175);
            this.SetParameters.Name = "SetParameters";
            this.SetParameters.Size = new System.Drawing.Size(177, 44);
            this.SetParameters.TabIndex = 0;
            this.SetParameters.Text = "УСТАНОВИТЬ";
            this.SetParameters.UseVisualStyleBackColor = true;
            this.SetParameters.Click += new System.EventHandler(this.SetParameters_Click);
            // 
            // VDK_FI_currBox
            // 
            this.VDK_FI_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.VDK_FI_currBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_FI_currBox.Location = new System.Drawing.Point(151, 37);
            this.VDK_FI_currBox.Name = "VDK_FI_currBox";
            this.VDK_FI_currBox.Size = new System.Drawing.Size(120, 46);
            this.VDK_FI_currBox.TabIndex = 18;
            this.VDK_FI_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VDK_FI_currBox.TextChanged += new System.EventHandler(this.VDK_FI_currBox_TextChanged);
            // 
            // GDK_FI_currBox
            // 
            this.GDK_FI_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.GDK_FI_currBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GDK_FI_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.GDK_FI_currBox.Location = new System.Drawing.Point(151, 83);
            this.GDK_FI_currBox.Name = "GDK_FI_currBox";
            this.GDK_FI_currBox.Size = new System.Drawing.Size(120, 46);
            this.GDK_FI_currBox.TabIndex = 18;
            this.GDK_FI_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.GDK_FI_currBox.TextChanged += new System.EventHandler(this.GDK_FI_currBox_TextChanged);
            // 
            // VDK_1_currBox
            // 
            this.VDK_1_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.VDK_1_currBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_1_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_1_currBox.Location = new System.Drawing.Point(151, 129);
            this.VDK_1_currBox.Name = "VDK_1_currBox";
            this.VDK_1_currBox.Size = new System.Drawing.Size(120, 46);
            this.VDK_1_currBox.TabIndex = 18;
            this.VDK_1_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VDK_1_currBox.TextChanged += new System.EventHandler(this.VDK_1_currBox_TextChanged);
            // 
            // GDK_1_currBox
            // 
            this.GDK_1_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.GDK_1_currBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GDK_1_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.GDK_1_currBox.Location = new System.Drawing.Point(151, 175);
            this.GDK_1_currBox.Name = "GDK_1_currBox";
            this.GDK_1_currBox.Size = new System.Drawing.Size(120, 46);
            this.GDK_1_currBox.TabIndex = 18;
            this.GDK_1_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.GDK_1_currBox.TextChanged += new System.EventHandler(this.GDK_1_currBox_TextChanged);
            // 
            // VDK_6_currBox
            // 
            this.VDK_6_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.VDK_6_currBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_6_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_6_currBox.Location = new System.Drawing.Point(151, 221);
            this.VDK_6_currBox.Name = "VDK_6_currBox";
            this.VDK_6_currBox.Size = new System.Drawing.Size(120, 46);
            this.VDK_6_currBox.TabIndex = 18;
            this.VDK_6_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VDK_6_currBox.TextChanged += new System.EventHandler(this.VDK_6_currBox_TextChanged);
            // 
            // GDK_6_currBox
            // 
            this.GDK_6_currBox.BackColor = System.Drawing.Color.LemonChiffon;
            this.GDK_6_currBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GDK_6_currBox.ForeColor = System.Drawing.Color.DimGray;
            this.GDK_6_currBox.Location = new System.Drawing.Point(151, 267);
            this.GDK_6_currBox.Name = "GDK_6_currBox";
            this.GDK_6_currBox.Size = new System.Drawing.Size(120, 46);
            this.GDK_6_currBox.TabIndex = 18;
            this.GDK_6_currBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.GDK_6_currBox.TextChanged += new System.EventHandler(this.GDK_6_currBox_TextChanged);
            // 
            // VDK_FI_voltBox
            // 
            this.VDK_FI_voltBox.BackColor = System.Drawing.Color.Honeydew;
            this.VDK_FI_voltBox.Font = new System.Drawing.Font("Verdana", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_FI_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_FI_voltBox.Location = new System.Drawing.Point(271, 37);
            this.VDK_FI_voltBox.Name = "VDK_FI_voltBox";
            this.VDK_FI_voltBox.Size = new System.Drawing.Size(120, 46);
            this.VDK_FI_voltBox.TabIndex = 18;
            this.VDK_FI_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // GDK_FI_voltBox
            // 
            this.GDK_FI_voltBox.BackColor = System.Drawing.Color.Honeydew;
            this.GDK_FI_voltBox.Font = new System.Drawing.Font("Verdana", 24F);
            this.GDK_FI_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.GDK_FI_voltBox.Location = new System.Drawing.Point(271, 83);
            this.GDK_FI_voltBox.Name = "GDK_FI_voltBox";
            this.GDK_FI_voltBox.Size = new System.Drawing.Size(120, 46);
            this.GDK_FI_voltBox.TabIndex = 18;
            this.GDK_FI_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // VDK_1_voltBox
            // 
            this.VDK_1_voltBox.BackColor = System.Drawing.Color.Honeydew;
            this.VDK_1_voltBox.Font = new System.Drawing.Font("Verdana", 24F);
            this.VDK_1_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_1_voltBox.Location = new System.Drawing.Point(271, 129);
            this.VDK_1_voltBox.Name = "VDK_1_voltBox";
            this.VDK_1_voltBox.Size = new System.Drawing.Size(120, 46);
            this.VDK_1_voltBox.TabIndex = 18;
            this.VDK_1_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // GDK_1_voltBox
            // 
            this.GDK_1_voltBox.BackColor = System.Drawing.Color.Honeydew;
            this.GDK_1_voltBox.Font = new System.Drawing.Font("Verdana", 24F);
            this.GDK_1_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.GDK_1_voltBox.Location = new System.Drawing.Point(271, 175);
            this.GDK_1_voltBox.Name = "GDK_1_voltBox";
            this.GDK_1_voltBox.Size = new System.Drawing.Size(120, 46);
            this.GDK_1_voltBox.TabIndex = 18;
            this.GDK_1_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // VDK_6_voltBox
            // 
            this.VDK_6_voltBox.BackColor = System.Drawing.Color.Honeydew;
            this.VDK_6_voltBox.Font = new System.Drawing.Font("Verdana", 24F);
            this.VDK_6_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.VDK_6_voltBox.Location = new System.Drawing.Point(271, 221);
            this.VDK_6_voltBox.Name = "VDK_6_voltBox";
            this.VDK_6_voltBox.Size = new System.Drawing.Size(120, 46);
            this.VDK_6_voltBox.TabIndex = 18;
            this.VDK_6_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // GDK_6_voltBox
            // 
            this.GDK_6_voltBox.BackColor = System.Drawing.Color.Honeydew;
            this.GDK_6_voltBox.Font = new System.Drawing.Font("Verdana", 24F);
            this.GDK_6_voltBox.ForeColor = System.Drawing.Color.DimGray;
            this.GDK_6_voltBox.Location = new System.Drawing.Point(271, 267);
            this.GDK_6_voltBox.Name = "GDK_6_voltBox";
            this.GDK_6_voltBox.Size = new System.Drawing.Size(120, 46);
            this.GDK_6_voltBox.TabIndex = 18;
            this.GDK_6_voltBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // IColumn
            // 
            this.IColumn.AutoSize = true;
            this.IColumn.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IColumn.Location = new System.Drawing.Point(174, 2);
            this.IColumn.Name = "IColumn";
            this.IColumn.Size = new System.Drawing.Size(79, 29);
            this.IColumn.TabIndex = 6;
            this.IColumn.Text = "I [A]";
            // 
            // UColumn
            // 
            this.UColumn.AutoSize = true;
            this.UColumn.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.UColumn.Location = new System.Drawing.Point(289, 2);
            this.UColumn.Name = "UColumn";
            this.UColumn.Size = new System.Drawing.Size(77, 29);
            this.UColumn.TabIndex = 6;
            this.UColumn.Text = "U [B]";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(386, 3);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(126, 29);
            this.label5.TabIndex = 6;
            this.label5.Text = "Нагрузка";
            // 
            // GDK_FI_OutputB
            // 
            this.GDK_FI_OutputB.BackColor = System.Drawing.Color.Silver;
            this.GDK_FI_OutputB.Font = new System.Drawing.Font("Verdana", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GDK_FI_OutputB.ForeColor = System.Drawing.SystemColors.WindowText;
            this.GDK_FI_OutputB.Location = new System.Drawing.Point(395, 83);
            this.GDK_FI_OutputB.Name = "GDK_FI_OutputB";
            this.GDK_FI_OutputB.Size = new System.Drawing.Size(106, 46);
            this.GDK_FI_OutputB.TabIndex = 0;
            this.GDK_FI_OutputB.Text = "─";
            this.GDK_FI_OutputB.UseVisualStyleBackColor = false;
            this.GDK_FI_OutputB.Click += new System.EventHandler(this.GDK_FI_OutputB_Click);
            // 
            // VDK_1_OutputB
            // 
            this.VDK_1_OutputB.BackColor = System.Drawing.Color.Silver;
            this.VDK_1_OutputB.Font = new System.Drawing.Font("Verdana", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_1_OutputB.ForeColor = System.Drawing.SystemColors.WindowText;
            this.VDK_1_OutputB.Location = new System.Drawing.Point(395, 129);
            this.VDK_1_OutputB.Name = "VDK_1_OutputB";
            this.VDK_1_OutputB.Size = new System.Drawing.Size(106, 46);
            this.VDK_1_OutputB.TabIndex = 0;
            this.VDK_1_OutputB.Text = "─";
            this.VDK_1_OutputB.UseVisualStyleBackColor = false;
            this.VDK_1_OutputB.Click += new System.EventHandler(this.VDK_1_OutputB_Click);
            // 
            // GDK_1_OutputB
            // 
            this.GDK_1_OutputB.BackColor = System.Drawing.Color.Silver;
            this.GDK_1_OutputB.Font = new System.Drawing.Font("Verdana", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GDK_1_OutputB.ForeColor = System.Drawing.SystemColors.WindowText;
            this.GDK_1_OutputB.Location = new System.Drawing.Point(395, 175);
            this.GDK_1_OutputB.Name = "GDK_1_OutputB";
            this.GDK_1_OutputB.Size = new System.Drawing.Size(106, 46);
            this.GDK_1_OutputB.TabIndex = 0;
            this.GDK_1_OutputB.Text = "─";
            this.GDK_1_OutputB.UseVisualStyleBackColor = false;
            this.GDK_1_OutputB.Click += new System.EventHandler(this.GDK_1_OutputB_Click);
            // 
            // VDK_6_OutputB
            // 
            this.VDK_6_OutputB.BackColor = System.Drawing.Color.Silver;
            this.VDK_6_OutputB.Font = new System.Drawing.Font("Verdana", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.VDK_6_OutputB.ForeColor = System.Drawing.SystemColors.WindowText;
            this.VDK_6_OutputB.Location = new System.Drawing.Point(395, 221);
            this.VDK_6_OutputB.Name = "VDK_6_OutputB";
            this.VDK_6_OutputB.Size = new System.Drawing.Size(106, 46);
            this.VDK_6_OutputB.TabIndex = 0;
            this.VDK_6_OutputB.Text = "─";
            this.VDK_6_OutputB.UseVisualStyleBackColor = false;
            this.VDK_6_OutputB.Click += new System.EventHandler(this.VDK_6_OutputB_Click);
            // 
            // GDK_6_OutputB
            // 
            this.GDK_6_OutputB.BackColor = System.Drawing.Color.Silver;
            this.GDK_6_OutputB.Font = new System.Drawing.Font("Verdana", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GDK_6_OutputB.ForeColor = System.Drawing.SystemColors.WindowText;
            this.GDK_6_OutputB.Location = new System.Drawing.Point(395, 267);
            this.GDK_6_OutputB.Name = "GDK_6_OutputB";
            this.GDK_6_OutputB.Size = new System.Drawing.Size(106, 46);
            this.GDK_6_OutputB.TabIndex = 0;
            this.GDK_6_OutputB.Text = "─";
            this.GDK_6_OutputB.UseVisualStyleBackColor = false;
            this.GDK_6_OutputB.Click += new System.EventHandler(this.GDK_6_OutputB_Click);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(399, 553);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(100, 61);
            this.pictureBox3.TabIndex = 20;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 50);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Location = new System.Drawing.Point(0, 0);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(100, 50);
            this.pictureBox2.TabIndex = 19;
            this.pictureBox2.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(513, 611);
            this.Controls.Add(this.AllControlsGroupBox);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.GDK_6_OutputB);
            this.Controls.Add(this.GDK_1_OutputB);
            this.Controls.Add(this.VDK_6_OutputB);
            this.Controls.Add(this.VDK_1_OutputB);
            this.Controls.Add(this.GDK_FI_OutputB);
            this.Controls.Add(this.VDK_FI_OutputB);
            this.Controls.Add(this.CurrTime);
            this.Controls.Add(this.GDK_6_voltBox);
            this.Controls.Add(this.GDK_6_currBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.UColumn);
            this.Controls.Add(this.IColumn);
            this.Controls.Add(this.VDK_6_voltBox);
            this.Controls.Add(this.VDK_6_currBox);
            this.Controls.Add(this.GDK_1_voltBox);
            this.Controls.Add(this.GDK_1_currBox);
            this.Controls.Add(this.VDK_1_voltBox);
            this.Controls.Add(this.VDK_1_currBox);
            this.Controls.Add(this.GDK_FI_voltBox);
            this.Controls.Add(this.GDK_FI_currBox);
            this.Controls.Add(this.VDK_FI_voltBox);
            this.Controls.Add(this.VDK_FI_currBox);
            this.Controls.Add(this.Statusbox);
            this.Controls.Add(this.CfgGroupBox);
            this.Controls.Add(this.S1_name);
            this.Controls.Add(this.S2_name);
            this.Controls.Add(this.S3_name);
            this.Controls.Add(this.S4_name);
            this.Controls.Add(this.S5_name);
            this.Controls.Add(this.S6_name);
            this.Controls.Add(this.pictureBox2);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "УПРАВЛЕНИЕ ПИТАНИЕМ КОРРЕКТОРОВ ПУЧКА ЛУ-20";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseClick);
            ((System.ComponentModel.ISupportInitialize)(this.VoltageUpDown)).EndInit();
            this.VsetGroupBox.ResumeLayout(false);
            this.VsetGroupBox.PerformLayout();
            this.CfgGroupBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.VoltageLimitUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentLimitUpDown)).EndInit();
            this.AllControlsGroupBox.ResumeLayout(false);
            this.AllControlsGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.Button VDK_FI_OutputB;
        private System.Windows.Forms.Label CurrTime;
        private System.Windows.Forms.Timer DataUpdateTimer;
        private System.Windows.Forms.Label S1_name;
        private System.Windows.Forms.Label S2_name;
        private System.Windows.Forms.Label S3_name;
        private System.Windows.Forms.Label S4_name;
        private System.Windows.Forms.Label S5_name;
        private System.Windows.Forms.Label S6_name;
        private System.Windows.Forms.Label SourceId;
        private System.Windows.Forms.Label V_;
        private System.Windows.Forms.NumericUpDown VoltageUpDown;
        private System.Windows.Forms.GroupBox VsetGroupBox;
        private System.Windows.Forms.GroupBox CfgGroupBox;
        public System.Windows.Forms.Button LoadCfg;
        public System.Windows.Forms.Button SaveCfg;
        public System.Windows.Forms.Button SetCfg;
        private System.Windows.Forms.NumericUpDown CurrentLimitUpDown;
        private System.Windows.Forms.NumericUpDown VoltageLimitUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox Statusbox;
        private System.Windows.Forms.GroupBox AllControlsGroupBox;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.TextBox VDK_FI_currBox;
        private System.Windows.Forms.TextBox GDK_FI_currBox;
        private System.Windows.Forms.TextBox VDK_1_currBox;
        private System.Windows.Forms.TextBox GDK_1_currBox;
        private System.Windows.Forms.TextBox VDK_6_currBox;
        private System.Windows.Forms.TextBox GDK_6_currBox;
        private System.Windows.Forms.TextBox VDK_FI_voltBox;
        private System.Windows.Forms.TextBox GDK_FI_voltBox;
        private System.Windows.Forms.TextBox VDK_1_voltBox;
        private System.Windows.Forms.TextBox GDK_1_voltBox;
        private System.Windows.Forms.TextBox VDK_6_voltBox;
        private System.Windows.Forms.TextBox GDK_6_voltBox;
        private System.Windows.Forms.Label IColumn;
        private System.Windows.Forms.Label UColumn;
        private System.Windows.Forms.Label label5;
        public System.Windows.Forms.Button SetParameters;
        public System.Windows.Forms.Button GDK_FI_OutputB;
        public System.Windows.Forms.Button VDK_1_OutputB;
        public System.Windows.Forms.Button GDK_1_OutputB;
        public System.Windows.Forms.Button VDK_6_OutputB;
        public System.Windows.Forms.Button GDK_6_OutputB;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Label label6;
    }
}

