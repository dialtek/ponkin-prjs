namespace KZ_vitok
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.IPadress = new System.Windows.Forms.TextBox();
            this.TCPconnectionGroupBox = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.LocalPort = new System.Windows.Forms.TextBox();
            this.StatusBox = new System.Windows.Forms.TextBox();
            this.TemperChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.MagnFieldLb = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.XaxHoursUpDown = new System.Windows.Forms.NumericUpDown();
            this.XaxMinUpDown = new System.Windows.Forms.NumericUpDown();
            this.XaxSecUpDown = new System.Windows.Forms.NumericUpDown();
            this.AxTimeGroupBox = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.CurrentLb = new System.Windows.Forms.Label();
            this.YaxMinUpDown = new System.Windows.Forms.NumericUpDown();
            this.YaxMaxUpDown = new System.Windows.Forms.NumericUpDown();
            this.YaxMaxManualUpDown = new System.Windows.Forms.NumericUpDown();
            this.YaxMinManualUpDown = new System.Windows.Forms.NumericUpDown();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.ScreenShotB = new System.Windows.Forms.Button();
            this.GraphUpdTimer = new System.Windows.Forms.Timer(this.components);
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.ZeroSetB = new System.Windows.Forms.Button();
            this.YaxIntUpDown = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.YaxMinLb = new System.Windows.Forms.Label();
            this.YaxMaxLb = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.XaxIntUpDown = new System.Windows.Forms.NumericUpDown();
            this.ManualZero = new System.Windows.Forms.TextBox();
            this.ManualZeroSet = new System.Windows.Forms.CheckBox();
            this.ZeroSetGroupBox = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
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
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxIntUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxIntUpDown)).BeginInit();
            this.ZeroSetGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // IPadress
            // 
            this.IPadress.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.IPadress.Location = new System.Drawing.Point(7, 26);
            this.IPadress.Name = "IPadress";
            this.IPadress.Size = new System.Drawing.Size(124, 26);
            this.IPadress.TabIndex = 0;
            this.IPadress.Text = "159.93.126.32";
            // 
            // TCPconnectionGroupBox
            // 
            this.TCPconnectionGroupBox.Controls.Add(this.label2);
            this.TCPconnectionGroupBox.Controls.Add(this.label1);
            this.TCPconnectionGroupBox.Controls.Add(this.IPadress);
            this.TCPconnectionGroupBox.Controls.Add(this.LocalPort);
            this.TCPconnectionGroupBox.Location = new System.Drawing.Point(3, 2);
            this.TCPconnectionGroupBox.Name = "TCPconnectionGroupBox";
            this.TCPconnectionGroupBox.Size = new System.Drawing.Size(142, 93);
            this.TCPconnectionGroupBox.TabIndex = 2;
            this.TCPconnectionGroupBox.TabStop = false;
            this.TCPconnectionGroupBox.Text = "Настройки TCP/ IP";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(70, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Порт";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(116, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(20, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "IP ";
            // 
            // LocalPort
            // 
            this.LocalPort.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LocalPort.Location = new System.Drawing.Point(7, 56);
            this.LocalPort.Name = "LocalPort";
            this.LocalPort.Size = new System.Drawing.Size(63, 26);
            this.LocalPort.TabIndex = 0;
            this.LocalPort.Text = "4001";
            // 
            // StatusBox
            // 
            this.StatusBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.StatusBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.ForeColor = System.Drawing.Color.Red;
            this.StatusBox.Location = new System.Drawing.Point(1, 485);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(761, 19);
            this.StatusBox.TabIndex = 0;
            this.StatusBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // TemperChart
            // 
            this.TemperChart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TemperChart.BackColor = System.Drawing.Color.Transparent;
            this.TemperChart.BorderlineColor = System.Drawing.Color.Black;
            chartArea3.AxisX.InterlacedColor = System.Drawing.Color.Black;
            chartArea3.AxisX.Interval = 10D;
            chartArea3.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Seconds;
            chartArea3.AxisX.LabelAutoFitMaxFontSize = 16;
            chartArea3.AxisX.LineColor = System.Drawing.Color.DimGray;
            chartArea3.AxisX.MajorGrid.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Seconds;
            chartArea3.AxisX.MajorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(46)))), ((int)(((byte)(44)))));
            chartArea3.AxisX.MinorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea3.AxisX.ScrollBar.BackColor = System.Drawing.Color.Black;
            chartArea3.AxisX.ScrollBar.ButtonColor = System.Drawing.Color.Black;
            chartArea3.AxisX.ScrollBar.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            chartArea3.AxisX.TitleFont = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            chartArea3.AxisY.InterlacedColor = System.Drawing.Color.White;
            chartArea3.AxisY.Interval = 100D;
            chartArea3.AxisY.LabelAutoFitMaxFontSize = 16;
            chartArea3.AxisY.LabelAutoFitStyle = ((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles)((((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.IncreaseFont | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.DecreaseFont) 
            | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.StaggeredLabels) 
            | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.WordWrap)));
            chartArea3.AxisY.MajorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(46)))), ((int)(((byte)(44)))));
            chartArea3.AxisY.MinorGrid.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea3.AxisY.MinorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(46)))), ((int)(((byte)(44)))));
            chartArea3.AxisY.Title = "ТОК КЗ ВИТКА, А";
            chartArea3.AxisY.TitleFont = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            chartArea3.AxisY2.LabelAutoFitMaxFontSize = 16;
            chartArea3.BackColor = System.Drawing.Color.Black;
            chartArea3.BorderColor = System.Drawing.Color.Silver;
            chartArea3.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea3.CursorX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Seconds;
            chartArea3.InnerPlotPosition.Auto = false;
            chartArea3.InnerPlotPosition.Height = 89.58112F;
            chartArea3.InnerPlotPosition.Width = 88.86673F;
            chartArea3.InnerPlotPosition.X = 6.66519F;
            chartArea3.InnerPlotPosition.Y = 2.79255F;
            chartArea3.Name = "ChartArea1";
            chartArea3.Position.Auto = false;
            chartArea3.Position.Height = 94F;
            chartArea3.Position.Width = 94F;
            chartArea3.Position.X = 3F;
            chartArea3.Position.Y = 3F;
            this.TemperChart.ChartAreas.Add(chartArea3);
            legend3.BorderWidth = 0;
            legend3.Enabled = false;
            legend3.Name = "Legend1";
            legend3.TableStyle = System.Windows.Forms.DataVisualization.Charting.LegendTableStyle.Wide;
            this.TemperChart.Legends.Add(legend3);
            this.TemperChart.Location = new System.Drawing.Point(3, 120);
            this.TemperChart.Name = "TemperChart";
            this.TemperChart.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            series3.BackImageAlignment = System.Windows.Forms.DataVisualization.Charting.ChartImageAlignmentStyle.Top;
            series3.BackImageTransparentColor = System.Drawing.Color.Transparent;
            series3.BorderColor = System.Drawing.Color.Transparent;
            series3.BorderWidth = 2;
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series3.Color = System.Drawing.Color.GreenYellow;
            series3.CustomProperties = "LineTension=0.5";
            series3.EmptyPointStyle.BorderColor = System.Drawing.Color.Red;
            series3.EmptyPointStyle.Color = System.Drawing.Color.Black;
            series3.Legend = "Legend1";
            series3.MarkerBorderColor = System.Drawing.Color.GreenYellow;
            series3.MarkerBorderWidth = 2;
            series3.MarkerSize = 1;
            series3.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Circle;
            series3.Name = "Температура";
            series3.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.DateTime;
            series3.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Int32;
            this.TemperChart.Series.Add(series3);
            this.TemperChart.Size = new System.Drawing.Size(765, 373);
            this.TemperChart.TabIndex = 5;
            // 
            // MagnFieldLb
            // 
            this.MagnFieldLb.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MagnFieldLb.AutoSize = true;
            this.MagnFieldLb.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.MagnFieldLb.Location = new System.Drawing.Point(4, 18);
            this.MagnFieldLb.Name = "MagnFieldLb";
            this.MagnFieldLb.Size = new System.Drawing.Size(0, 33);
            this.MagnFieldLb.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(10, 14);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 20);
            this.label3.TabIndex = 4;
            this.label3.Text = "часы";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(138, 14);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(38, 20);
            this.label5.TabIndex = 4;
            this.label5.Text = "сек.";
            // 
            // XaxHoursUpDown
            // 
            this.XaxHoursUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.XaxHoursUpDown.Location = new System.Drawing.Point(5, 36);
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
            this.XaxMinUpDown.Location = new System.Drawing.Point(68, 36);
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
            this.XaxSecUpDown.Location = new System.Drawing.Point(131, 36);
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
            this.AxTimeGroupBox.Controls.Add(this.label4);
            this.AxTimeGroupBox.Controls.Add(this.label3);
            this.AxTimeGroupBox.Controls.Add(this.XaxMinUpDown);
            this.AxTimeGroupBox.Controls.Add(this.label5);
            this.AxTimeGroupBox.Location = new System.Drawing.Point(268, 2);
            this.AxTimeGroupBox.Name = "AxTimeGroupBox";
            this.AxTimeGroupBox.Size = new System.Drawing.Size(197, 67);
            this.AxTimeGroupBox.TabIndex = 7;
            this.AxTimeGroupBox.TabStop = false;
            this.AxTimeGroupBox.Text = "Интервал просмотра графика";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(72, 14);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(42, 20);
            this.label4.TabIndex = 4;
            this.label4.Text = "мин.";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.CurrentLb);
            this.groupBox1.Location = new System.Drawing.Point(474, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(179, 56);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "ТОК КЗ ВИТКА";
            // 
            // label6
            // 
            this.label6.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.ForeColor = System.Drawing.Color.Navy;
            this.label6.Location = new System.Drawing.Point(134, 13);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 39);
            this.label6.TabIndex = 4;
            this.label6.Text = "A";
            // 
            // CurrentLb
            // 
            this.CurrentLb.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CurrentLb.AutoSize = true;
            this.CurrentLb.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CurrentLb.ForeColor = System.Drawing.Color.Navy;
            this.CurrentLb.Location = new System.Drawing.Point(3, 12);
            this.CurrentLb.Name = "CurrentLb";
            this.CurrentLb.Size = new System.Drawing.Size(0, 39);
            this.CurrentLb.TabIndex = 4;
            // 
            // YaxMinUpDown
            // 
            this.YaxMinUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMinUpDown.Location = new System.Drawing.Point(671, 95);
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
            // 
            // YaxMaxUpDown
            // 
            this.YaxMaxUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMaxUpDown.Location = new System.Drawing.Point(671, 63);
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
            // 
            // YaxMaxManualUpDown
            // 
            this.YaxMaxManualUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMaxManualUpDown.Location = new System.Drawing.Point(3, 101);
            this.YaxMaxManualUpDown.Maximum = new decimal(new int[] {
            25000,
            0,
            0,
            0});
            this.YaxMaxManualUpDown.Name = "YaxMaxManualUpDown";
            this.YaxMaxManualUpDown.Size = new System.Drawing.Size(70, 26);
            this.YaxMaxManualUpDown.TabIndex = 6;
            this.YaxMaxManualUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxMaxManualUpDown.Value = new decimal(new int[] {
            2500,
            0,
            0,
            0});
            // 
            // YaxMinManualUpDown
            // 
            this.YaxMinManualUpDown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.YaxMinManualUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMinManualUpDown.Location = new System.Drawing.Point(0, 484);
            this.YaxMinManualUpDown.Maximum = new decimal(new int[] {
            2490,
            0,
            0,
            0});
            this.YaxMinManualUpDown.Minimum = new decimal(new int[] {
            2500,
            0,
            0,
            -2147483648});
            this.YaxMinManualUpDown.Name = "YaxMinManualUpDown";
            this.YaxMinManualUpDown.Size = new System.Drawing.Size(70, 21);
            this.YaxMinManualUpDown.TabIndex = 6;
            this.YaxMinManualUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxMinManualUpDown.Value = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(659, 8);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 58);
            this.pictureBox1.TabIndex = 8;
            this.pictureBox1.TabStop = false;
            // 
            // ScreenShotB
            // 
            this.ScreenShotB.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ScreenShotB.Image = ((System.Drawing.Image)(resources.GetObject("ScreenShotB.Image")));
            this.ScreenShotB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.ScreenShotB.Location = new System.Drawing.Point(659, 78);
            this.ScreenShotB.Name = "ScreenShotB";
            this.ScreenShotB.Size = new System.Drawing.Size(103, 30);
            this.ScreenShotB.TabIndex = 1;
            this.ScreenShotB.Text = "Скриншот";
            this.ScreenShotB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.ScreenShotB.UseVisualStyleBackColor = true;
            this.ScreenShotB.Click += new System.EventHandler(this.ScreenShotB_Click);
            // 
            // GraphUpdTimer
            // 
            this.GraphUpdTimer.Interval = 1;
            this.GraphUpdTimer.Tick += new System.EventHandler(this.GraphUpdTimer_Tick);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.MagnFieldLb);
            this.groupBox2.Location = new System.Drawing.Point(474, 63);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(179, 61);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "МАГНИТНОЕ ПОЛЕ ДАТЧИКА";
            // 
            // label7
            // 
            this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label7.Location = new System.Drawing.Point(129, 21);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(46, 33);
            this.label7.TabIndex = 4;
            this.label7.Text = "Гс";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numericUpDown1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.numericUpDown1.Location = new System.Drawing.Point(-3, 867);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            2490,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            2500,
            0,
            0,
            -2147483648});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(70, 21);
            this.numericUpDown1.TabIndex = 6;
            this.numericUpDown1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDown1.Value = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            // 
            // ZeroSetB
            // 
            this.ZeroSetB.Location = new System.Drawing.Point(6, 16);
            this.ZeroSetB.Name = "ZeroSetB";
            this.ZeroSetB.Size = new System.Drawing.Size(81, 30);
            this.ZeroSetB.TabIndex = 9;
            this.ZeroSetB.Text = "Установить";
            this.ZeroSetB.UseVisualStyleBackColor = true;
            this.ZeroSetB.Click += new System.EventHandler(this.ZeroSetB_Click);
            // 
            // YaxIntUpDown
            // 
            this.YaxIntUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxIntUpDown.Location = new System.Drawing.Point(123, 111);
            this.YaxIntUpDown.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.YaxIntUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.YaxIntUpDown.Name = "YaxIntUpDown";
            this.YaxIntUpDown.Size = new System.Drawing.Size(57, 20);
            this.YaxIntUpDown.TabIndex = 6;
            this.YaxIntUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YaxIntUpDown.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.Location = new System.Drawing.Point(121, 95);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(66, 13);
            this.label8.TabIndex = 4;
            this.label8.Text = "Интервал Y";
            // 
            // YaxMinLb
            // 
            this.YaxMinLb.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.YaxMinLb.AutoSize = true;
            this.YaxMinLb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMinLb.Location = new System.Drawing.Point(71, 485);
            this.YaxMinLb.Name = "YaxMinLb";
            this.YaxMinLb.Size = new System.Drawing.Size(38, 20);
            this.YaxMinLb.TabIndex = 4;
            this.YaxMinLb.Text = "Min.";
            // 
            // YaxMaxLb
            // 
            this.YaxMaxLb.AutoSize = true;
            this.YaxMaxLb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxMaxLb.Location = new System.Drawing.Point(74, 104);
            this.YaxMaxLb.Name = "YaxMaxLb";
            this.YaxMaxLb.Size = new System.Drawing.Size(42, 20);
            this.YaxMaxLb.TabIndex = 4;
            this.YaxMaxLb.Text = "Max.";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label9.Location = new System.Drawing.Point(192, 95);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(66, 13);
            this.label9.TabIndex = 4;
            this.label9.Text = "Интервал X";
            // 
            // XaxIntUpDown
            // 
            this.XaxIntUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.XaxIntUpDown.Location = new System.Drawing.Point(194, 111);
            this.XaxIntUpDown.Maximum = new decimal(new int[] {
            120,
            0,
            0,
            0});
            this.XaxIntUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.XaxIntUpDown.Name = "XaxIntUpDown";
            this.XaxIntUpDown.Size = new System.Drawing.Size(57, 20);
            this.XaxIntUpDown.TabIndex = 6;
            this.XaxIntUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.XaxIntUpDown.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // ManualZero
            // 
            this.ManualZero.Enabled = false;
            this.ManualZero.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ManualZero.Location = new System.Drawing.Point(99, 27);
            this.ManualZero.Name = "ManualZero";
            this.ManualZero.Size = new System.Drawing.Size(63, 26);
            this.ManualZero.TabIndex = 0;
            this.ManualZero.Text = "0";
            this.ManualZero.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ManualZeroSet
            // 
            this.ManualZeroSet.AutoSize = true;
            this.ManualZeroSet.Location = new System.Drawing.Point(100, 9);
            this.ManualZeroSet.Name = "ManualZeroSet";
            this.ManualZeroSet.Size = new System.Drawing.Size(68, 17);
            this.ManualZeroSet.TabIndex = 10;
            this.ManualZeroSet.Text = "Вручную";
            this.ManualZeroSet.UseVisualStyleBackColor = true;
            this.ManualZeroSet.CheckedChanged += new System.EventHandler(this.ManualZeroSet_CheckedChanged);
            // 
            // ZeroSetGroupBox
            // 
            this.ZeroSetGroupBox.Controls.Add(this.ManualZero);
            this.ZeroSetGroupBox.Controls.Add(this.ManualZeroSet);
            this.ZeroSetGroupBox.Controls.Add(this.ZeroSetB);
            this.ZeroSetGroupBox.Location = new System.Drawing.Point(281, 72);
            this.ZeroSetGroupBox.Name = "ZeroSetGroupBox";
            this.ZeroSetGroupBox.Size = new System.Drawing.Size(170, 59);
            this.ZeroSetGroupBox.TabIndex = 11;
            this.ZeroSetGroupBox.TabStop = false;
            this.ZeroSetGroupBox.Text = "Уст. 0";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(173, 16);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 13);
            this.label10.TabIndex = 12;
            this.label10.Text = "label10";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(173, 70);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 13);
            this.label11.TabIndex = 12;
            this.label11.Text = "label10";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(165, 35);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 13;
            this.button1.Text = "clear";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(768, 505);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.ZeroSetGroupBox);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.ScreenShotB);
            this.Controls.Add(this.YaxMinManualUpDown);
            this.Controls.Add(this.XaxIntUpDown);
            this.Controls.Add(this.YaxIntUpDown);
            this.Controls.Add(this.YaxMaxManualUpDown);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.YaxMinLb);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.YaxMaxUpDown);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.YaxMaxLb);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.AxTimeGroupBox);
            this.Controls.Add(this.YaxMinUpDown);
            this.Controls.Add(this.TCPconnectionGroupBox);
            this.Controls.Add(this.TemperChart);
            this.DoubleBuffered = true;
            this.ForeColor = System.Drawing.SystemColors.GrayText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "МОНИТОР ТОКА КЗ ВИТКА";
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
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.YaxIntUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.XaxIntUpDown)).EndInit();
            this.ZeroSetGroupBox.ResumeLayout(false);
            this.ZeroSetGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox IPadress;
        private System.Windows.Forms.GroupBox TCPconnectionGroupBox;
        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox LocalPort;
        private System.Windows.Forms.DataVisualization.Charting.Chart TemperChart;
        private System.Windows.Forms.Label MagnFieldLb;
        private System.Windows.Forms.Label label3;
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
        private System.Windows.Forms.Button ScreenShotB;
        private System.Windows.Forms.Label CurrentLb;
        private System.Windows.Forms.Timer GraphUpdTimer;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button ZeroSetB;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown YaxIntUpDown;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label YaxMinLb;
        private System.Windows.Forms.Label YaxMaxLb;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown XaxIntUpDown;
        private System.Windows.Forms.TextBox ManualZero;
        private System.Windows.Forms.CheckBox ManualZeroSet;
        private System.Windows.Forms.GroupBox ZeroSetGroupBox;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button button1;
    }
}

