namespace AntiCryo
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.IPadress = new System.Windows.Forms.TextBox();
            this.TCPconnectionGroupBox = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.LocalPort = new System.Windows.Forms.TextBox();
            this.TCPdisconnectB = new System.Windows.Forms.Button();
            this.TCPconnectB = new System.Windows.Forms.Button();
            this.StatusBox = new System.Windows.Forms.TextBox();
            this.TCPrdTimer = new System.Windows.Forms.Timer(this.components);
            this.TemperChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.CurrentTemper = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.XaxHoursUpDown = new System.Windows.Forms.NumericUpDown();
            this.XaxMinUpDown = new System.Windows.Forms.NumericUpDown();
            this.XaxSecUpDown = new System.Windows.Forms.NumericUpDown();
            this.AxTimeGroupBox = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.YaxMinUpDown = new System.Windows.Forms.NumericUpDown();
            this.YaxMaxUpDown = new System.Windows.Forms.NumericUpDown();
            this.YaxMaxManualUpDown = new System.Windows.Forms.NumericUpDown();
            this.YaxMinManualUpDown = new System.Windows.Forms.NumericUpDown();
            this.AutoscaleCheckBox = new System.Windows.Forms.CheckBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.ScreenShotB = new System.Windows.Forms.Button();
            this.TCPconnectionGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TemperChart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxHoursUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxMinUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxSecUpDown)).BeginInit();
            this.AxTimeGroupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMinUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMaxUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMaxManualUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMinManualUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // IPadress
            // 
            this.IPadress.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPadress.Location = new System.Drawing.Point(7, 35);
            this.IPadress.Name = "IPadress";
            this.IPadress.Size = new System.Drawing.Size(124, 26);
            this.IPadress.TabIndex = 0;
            this.IPadress.Text = "10.10.10.10";
            // 
            // TCPconnectionGroupBox
            // 
            this.TCPconnectionGroupBox.Controls.Add(this.label2);
            this.TCPconnectionGroupBox.Controls.Add(this.label1);
            this.TCPconnectionGroupBox.Controls.Add(this.IPadress);
            this.TCPconnectionGroupBox.Controls.Add(this.LocalPort);
            this.TCPconnectionGroupBox.Controls.Add(this.TCPdisconnectB);
            this.TCPconnectionGroupBox.Controls.Add(this.TCPconnectB);
            this.TCPconnectionGroupBox.Location = new System.Drawing.Point(3, -1);
            this.TCPconnectionGroupBox.Name = "TCPconnectionGroupBox";
            this.TCPconnectionGroupBox.Size = new System.Drawing.Size(275, 98);
            this.TCPconnectionGroupBox.TabIndex = 2;
            this.TCPconnectionGroupBox.TabStop = false;
            this.TCPconnectionGroupBox.Text = "Настройки TCP/ IP";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(70, 70);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Порт";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(116, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(20, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "IP ";
            // 
            // LocalPort
            // 
            this.LocalPort.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LocalPort.Location = new System.Drawing.Point(7, 65);
            this.LocalPort.Name = "LocalPort";
            this.LocalPort.Size = new System.Drawing.Size(63, 26);
            this.LocalPort.TabIndex = 0;
            this.LocalPort.Text = "4001";
            // 
            // TCPdisconnectB
            // 
            this.TCPdisconnectB.Image = global::AntiCryo.Properties.Resources.ic_cancel_black_18dp;
            this.TCPdisconnectB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.TCPdisconnectB.Location = new System.Drawing.Point(137, 62);
            this.TCPdisconnectB.Name = "TCPdisconnectB";
            this.TCPdisconnectB.Size = new System.Drawing.Size(126, 32);
            this.TCPdisconnectB.TabIndex = 1;
            this.TCPdisconnectB.Text = "Отключиться";
            this.TCPdisconnectB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.TCPdisconnectB.UseVisualStyleBackColor = true;
            this.TCPdisconnectB.Click += new System.EventHandler(this.TCPdisconnectB_Click);
            // 
            // TCPconnectB
            // 
            this.TCPconnectB.Image = global::AntiCryo.Properties.Resources.ic_settings_input_hdmi_black_18dp;
            this.TCPconnectB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.TCPconnectB.Location = new System.Drawing.Point(137, 31);
            this.TCPconnectB.Name = "TCPconnectB";
            this.TCPconnectB.Size = new System.Drawing.Size(126, 30);
            this.TCPconnectB.TabIndex = 1;
            this.TCPconnectB.Text = "Подключиться";
            this.TCPconnectB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.TCPconnectB.UseVisualStyleBackColor = true;
            this.TCPconnectB.Click += new System.EventHandler(this.TCPconnectB_Click);
            // 
            // StatusBox
            // 
            this.StatusBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.StatusBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.Location = new System.Drawing.Point(1, 485);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(767, 19);
            this.StatusBox.TabIndex = 0;
            // 
            // TCPrdTimer
            // 
            this.TCPrdTimer.Interval = 50;
            this.TCPrdTimer.Tick += new System.EventHandler(this.TCPrdTimer_Tick);
            // 
            // TemperChart
            // 
            this.TemperChart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TemperChart.BackColor = System.Drawing.Color.Transparent;
            this.TemperChart.BorderlineColor = System.Drawing.Color.Black;
            chartArea1.AxisX.InterlacedColor = System.Drawing.Color.Black;
            chartArea1.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Seconds;
            chartArea1.AxisX.IsLabelAutoFit = false;
            chartArea1.AxisX.LineColor = System.Drawing.Color.DimGray;
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisX.MajorGrid.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Seconds;
            chartArea1.AxisX.MajorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.NotSet;
            chartArea1.AxisX.MinorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisX.ScrollBar.BackColor = System.Drawing.Color.Black;
            chartArea1.AxisX.ScrollBar.ButtonColor = System.Drawing.Color.Black;
            chartArea1.AxisX.ScrollBar.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            chartArea1.AxisX.TitleFont = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            chartArea1.AxisY.MajorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisY.MinorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea1.BackColor = System.Drawing.Color.AliceBlue;
            chartArea1.BorderColor = System.Drawing.Color.Silver;
            chartArea1.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea1.CursorX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Seconds;
            chartArea1.InnerPlotPosition.Auto = false;
            chartArea1.InnerPlotPosition.Height = 89.58112F;
            chartArea1.InnerPlotPosition.Width = 88.86673F;
            chartArea1.InnerPlotPosition.X = 6.66519F;
            chartArea1.InnerPlotPosition.Y = 2.79255F;
            chartArea1.Name = "ChartArea1";
            chartArea1.Position.Auto = false;
            chartArea1.Position.Height = 94F;
            chartArea1.Position.Width = 94F;
            chartArea1.Position.X = 3F;
            chartArea1.Position.Y = 3F;
            this.TemperChart.ChartAreas.Add(chartArea1);
            legend1.BorderWidth = 0;
            legend1.Enabled = false;
            legend1.Name = "Legend1";
            legend1.TableStyle = System.Windows.Forms.DataVisualization.Charting.LegendTableStyle.Wide;
            this.TemperChart.Legends.Add(legend1);
            this.TemperChart.Location = new System.Drawing.Point(1, 105);
            this.TemperChart.Name = "TemperChart";
            this.TemperChart.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            series1.BackImageAlignment = System.Windows.Forms.DataVisualization.Charting.ChartImageAlignmentStyle.Top;
            series1.BackImageTransparentColor = System.Drawing.Color.Transparent;
            series1.BorderColor = System.Drawing.Color.Transparent;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Color = System.Drawing.Color.MediumBlue;
            series1.CustomProperties = "LineTension=0.5";
            series1.EmptyPointStyle.BorderColor = System.Drawing.Color.Red;
            series1.EmptyPointStyle.Color = System.Drawing.Color.Black;
            series1.Legend = "Legend1";
            series1.MarkerBorderColor = System.Drawing.Color.LightBlue;
            series1.Name = "Температура";
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.DateTime;
            this.TemperChart.Series.Add(series1);
            this.TemperChart.Size = new System.Drawing.Size(767, 378);
            this.TemperChart.TabIndex = 5;
            // 
            // CurrentTemper
            // 
            this.CurrentTemper.AutoSize = true;
            this.CurrentTemper.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CurrentTemper.Location = new System.Drawing.Point(5, 34);
            this.CurrentTemper.Name = "CurrentTemper";
            this.CurrentTemper.Size = new System.Drawing.Size(0, 33);
            this.CurrentTemper.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(20, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 20);
            this.label3.TabIndex = 4;
            this.label3.Text = "часы";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(85, 15);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(42, 20);
            this.label4.TabIndex = 4;
            this.label4.Text = "мин.";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(148, 15);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(38, 20);
            this.label5.TabIndex = 4;
            this.label5.Text = "сек.";
            // 
            // XaxHoursUpDown
            // 
            this.XaxHoursUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.XaxHoursUpDown.Location = new System.Drawing.Point(15, 37);
            this.XaxHoursUpDown.Maximum = new decimal(new int[] {
            23,
            0,
            0,
            0});
            this.XaxHoursUpDown.Name = "XaxHoursUpDown";
            this.XaxHoursUpDown.Size = new System.Drawing.Size(57, 26);
            this.XaxHoursUpDown.TabIndex = 6;
            this.XaxHoursUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.XaxHoursUpDown.ValueChanged += new System.EventHandler(this.XaxHoursUpDown_ValueChanged);
            // 
            // XaxMinUpDown
            // 
            this.XaxMinUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.XaxMinUpDown.Location = new System.Drawing.Point(78, 37);
            this.XaxMinUpDown.Maximum = new decimal(new int[] {
            59,
            0,
            0,
            0});
            this.XaxMinUpDown.Name = "XaxMinUpDown";
            this.XaxMinUpDown.Size = new System.Drawing.Size(57, 26);
            this.XaxMinUpDown.TabIndex = 6;
            this.XaxMinUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.XaxMinUpDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.XaxMinUpDown.ValueChanged += new System.EventHandler(this.XaxMinUpDown_ValueChanged);
            // 
            // XaxSecUpDown
            // 
            this.XaxSecUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.XaxSecUpDown.Location = new System.Drawing.Point(141, 37);
            this.XaxSecUpDown.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.XaxSecUpDown.Minimum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.XaxSecUpDown.Name = "XaxSecUpDown";
            this.XaxSecUpDown.Size = new System.Drawing.Size(57, 26);
            this.XaxSecUpDown.TabIndex = 6;
            this.XaxSecUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.XaxSecUpDown.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.XaxSecUpDown.ValueChanged += new System.EventHandler(this.XaxSecUpDown_ValueChanged);
            // 
            // AxTimeGroupBox
            // 
            this.AxTimeGroupBox.Controls.Add(this.XaxHoursUpDown);
            this.AxTimeGroupBox.Controls.Add(this.XaxSecUpDown);
            this.AxTimeGroupBox.Controls.Add(this.label3);
            this.AxTimeGroupBox.Controls.Add(this.XaxMinUpDown);
            this.AxTimeGroupBox.Controls.Add(this.label4);
            this.AxTimeGroupBox.Controls.Add(this.label5);
            this.AxTimeGroupBox.Location = new System.Drawing.Point(292, -1);
            this.AxTimeGroupBox.Name = "AxTimeGroupBox";
            this.AxTimeGroupBox.Size = new System.Drawing.Size(206, 67);
            this.AxTimeGroupBox.TabIndex = 7;
            this.AxTimeGroupBox.TabStop = false;
            this.AxTimeGroupBox.Text = "Интервал просмотра графика";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.CurrentTemper);
            this.groupBox1.Location = new System.Drawing.Point(508, -1);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(145, 98);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Текущая Т";
            // 
            // YaxMinUpDown
            // 
            this.YaxMinUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMinUpDown.Location = new System.Drawing.Point(685, 93);
            this.YaxMinUpDown.Maximum = new decimal(new int[] {
            59,
            0,
            0,
            0});
            this.YaxMinUpDown.Name = "YaxMinUpDown";
            this.YaxMinUpDown.Size = new System.Drawing.Size(57, 26);
            this.YaxMinUpDown.TabIndex = 6;
            this.YaxMinUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxMinUpDown.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.YaxMinUpDown.ValueChanged += new System.EventHandler(this.YaxMinUpDown_ValueChanged);
            // 
            // YaxMaxUpDown
            // 
            this.YaxMaxUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMaxUpDown.Location = new System.Drawing.Point(685, 61);
            this.YaxMaxUpDown.Maximum = new decimal(new int[] {
            23,
            0,
            0,
            0});
            this.YaxMaxUpDown.Name = "YaxMaxUpDown";
            this.YaxMaxUpDown.Size = new System.Drawing.Size(57, 26);
            this.YaxMaxUpDown.TabIndex = 6;
            this.YaxMaxUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxMaxUpDown.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.YaxMaxUpDown.ValueChanged += new System.EventHandler(this.YaxMaxUpDown_ValueChanged);
            // 
            // YaxMaxManualUpDown
            // 
            this.YaxMaxManualUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMaxManualUpDown.Location = new System.Drawing.Point(3, 96);
            this.YaxMaxManualUpDown.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.YaxMaxManualUpDown.Name = "YaxMaxManualUpDown";
            this.YaxMaxManualUpDown.Size = new System.Drawing.Size(43, 21);
            this.YaxMaxManualUpDown.TabIndex = 6;
            this.YaxMaxManualUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxMaxManualUpDown.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // YaxMinManualUpDown
            // 
            this.YaxMinManualUpDown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.YaxMinManualUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMinManualUpDown.Location = new System.Drawing.Point(3, 463);
            this.YaxMinManualUpDown.Minimum = new decimal(new int[] {
            40,
            0,
            0,
            -2147483648});
            this.YaxMinManualUpDown.Name = "YaxMinManualUpDown";
            this.YaxMinManualUpDown.Size = new System.Drawing.Size(45, 21);
            this.YaxMinManualUpDown.TabIndex = 6;
            this.YaxMinManualUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxMinManualUpDown.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // AutoscaleCheckBox
            // 
            this.AutoscaleCheckBox.AutoSize = true;
            this.AutoscaleCheckBox.Location = new System.Drawing.Point(52, 99);
            this.AutoscaleCheckBox.Name = "AutoscaleCheckBox";
            this.AutoscaleCheckBox.Size = new System.Drawing.Size(92, 17);
            this.AutoscaleCheckBox.TabIndex = 9;
            this.AutoscaleCheckBox.Text = "Автошкала Т";
            this.AutoscaleCheckBox.UseVisualStyleBackColor = true;
            this.AutoscaleCheckBox.CheckedChanged += new System.EventHandler(this.AutoscaleCheckBox_CheckedChanged);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::AntiCryo.Properties.Resources.LHEP_emblema_small;
            this.pictureBox1.Location = new System.Drawing.Point(668, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 58);
            this.pictureBox1.TabIndex = 8;
            this.pictureBox1.TabStop = false;
            // 
            // ScreenShotB
            // 
            this.ScreenShotB.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ScreenShotB.Image = global::AntiCryo.Properties.Resources.ic_photo_camera_black_18dp;
            this.ScreenShotB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.ScreenShotB.Location = new System.Drawing.Point(344, 72);
            this.ScreenShotB.Name = "ScreenShotB";
            this.ScreenShotB.Size = new System.Drawing.Size(103, 30);
            this.ScreenShotB.TabIndex = 1;
            this.ScreenShotB.Text = "Скриншот";
            this.ScreenShotB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.ScreenShotB.UseVisualStyleBackColor = true;
            this.ScreenShotB.Click += new System.EventHandler(this.ScreenShotB_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(768, 505);
            this.Controls.Add(this.AutoscaleCheckBox);
            this.Controls.Add(this.YaxMinManualUpDown);
            this.Controls.Add(this.YaxMaxManualUpDown);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.YaxMaxUpDown);
            this.Controls.Add(this.ScreenShotB);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.AxTimeGroupBox);
            this.Controls.Add(this.YaxMinUpDown);
            this.Controls.Add(this.TCPconnectionGroupBox);
            this.Controls.Add(this.TemperChart);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.TCPconnectionGroupBox.ResumeLayout(false);
            this.TCPconnectionGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TemperChart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxHoursUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxMinUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxSecUpDown)).EndInit();
            this.AxTimeGroupBox.ResumeLayout(false);
            this.AxTimeGroupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMinUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMaxUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMaxManualUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxMinManualUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox IPadress;
        private System.Windows.Forms.Button TCPconnectB;
        private System.Windows.Forms.GroupBox TCPconnectionGroupBox;
        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox LocalPort;
        private System.Windows.Forms.Button TCPdisconnectB;
        private System.Windows.Forms.Timer TCPrdTimer;
        private System.Windows.Forms.DataVisualization.Charting.Chart TemperChart;
        private System.Windows.Forms.Label CurrentTemper;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown XaxHoursUpDown;
        private System.Windows.Forms.NumericUpDown XaxMinUpDown;
        private System.Windows.Forms.NumericUpDown XaxSecUpDown;
        private System.Windows.Forms.GroupBox AxTimeGroupBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.NumericUpDown YaxMinUpDown;
        private System.Windows.Forms.NumericUpDown YaxMaxUpDown;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.NumericUpDown YaxMaxManualUpDown;
        private System.Windows.Forms.NumericUpDown YaxMinManualUpDown;
        private System.Windows.Forms.CheckBox AutoscaleCheckBox;
        private System.Windows.Forms.Button ScreenShotB;
    }
}

