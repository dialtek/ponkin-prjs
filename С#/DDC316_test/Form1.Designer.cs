namespace DDC_316_test
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.PortList = new System.Windows.Forms.ComboBox();
            this.StartRdB = new System.Windows.Forms.Button();
            this.RefreshTimer = new System.Windows.Forms.Timer(this.components);
            this.StopRdB = new System.Windows.Forms.Button();
            this.Chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.XaxisLabel = new System.Windows.Forms.Label();
            this.YaxisLabel = new System.Windows.Forms.Label();
            this.PCBtemper = new System.Windows.Forms.Label();
            this.StatusBox = new System.Windows.Forms.TextBox();
            this.ZeroSetB = new System.Windows.Forms.Button();
            this.Σlabel = new System.Windows.Forms.Label();
            this.TotalCurrentL = new System.Windows.Forms.Label();
            this.LhepPictureBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.Chart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LhepPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // PortList
            // 
            this.PortList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.PortList.FormattingEnabled = true;
            this.PortList.Location = new System.Drawing.Point(9, 473);
            this.PortList.Name = "PortList";
            this.PortList.Size = new System.Drawing.Size(121, 21);
            this.PortList.TabIndex = 1;
            // 
            // StartRdB
            // 
            this.StartRdB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.StartRdB.AutoSize = true;
            this.StartRdB.Location = new System.Drawing.Point(9, 500);
            this.StartRdB.Name = "StartRdB";
            this.StartRdB.Size = new System.Drawing.Size(56, 32);
            this.StartRdB.TabIndex = 2;
            this.StartRdB.Text = "Старт";
            this.StartRdB.UseVisualStyleBackColor = true;
            this.StartRdB.Click += new System.EventHandler(this.StartRdB_Click);
            // 
            // RefreshTimer
            // 
            this.RefreshTimer.Interval = 20;
            this.RefreshTimer.Tick += new System.EventHandler(this.RefreshTimer_Tick);
            // 
            // StopRdB
            // 
            this.StopRdB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.StopRdB.Location = new System.Drawing.Point(71, 500);
            this.StopRdB.Name = "StopRdB";
            this.StopRdB.Size = new System.Drawing.Size(59, 32);
            this.StopRdB.TabIndex = 3;
            this.StopRdB.Text = "Стоп";
            this.StopRdB.UseVisualStyleBackColor = true;
            this.StopRdB.Click += new System.EventHandler(this.StopRdB_Click);
            // 
            // Chart
            // 
            this.Chart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Chart.BorderlineColor = System.Drawing.Color.DeepSkyBlue;
            this.Chart.BorderlineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            this.Chart.BorderlineWidth = 2;
            this.Chart.BorderSkin.PageColor = System.Drawing.Color.Transparent;
            chartArea1.AlignmentOrientation = ((System.Windows.Forms.DataVisualization.Charting.AreaAlignmentOrientations)((System.Windows.Forms.DataVisualization.Charting.AreaAlignmentOrientations.Vertical | System.Windows.Forms.DataVisualization.Charting.AreaAlignmentOrientations.Horizontal)));
            chartArea1.Area3DStyle.IsRightAngleAxes = false;
            chartArea1.AxisX.Interval = 1D;
            chartArea1.AxisX.IntervalAutoMode = System.Windows.Forms.DataVisualization.Charting.IntervalAutoMode.VariableCount;
            chartArea1.AxisX.IsLabelAutoFit = false;
            chartArea1.AxisX.LabelStyle.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            chartArea1.AxisX.LabelStyle.ForeColor = System.Drawing.Color.DimGray;
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisX.MajorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisX.MajorTickMark.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisX.MinorGrid.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisX.MinorTickMark.LineColor = System.Drawing.Color.LightGray;
            chartArea1.AxisX.ScaleBreakStyle.Spacing = 1D;
            chartArea1.AxisX.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.No;
            chartArea1.AxisX.TextOrientation = System.Windows.Forms.DataVisualization.Charting.TextOrientation.Horizontal;
            chartArea1.AxisY.InterlacedColor = System.Drawing.Color.White;
            chartArea1.AxisY.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea1.AxisY.IsLabelAutoFit = false;
            chartArea1.AxisY.LabelStyle.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            chartArea1.AxisY.LabelStyle.ForeColor = System.Drawing.Color.DimGray;
            chartArea1.AxisY.LabelStyle.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea1.AxisY.LineWidth = 2;
            chartArea1.AxisY.MajorGrid.Enabled = false;
            chartArea1.AxisY.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.Yes;
            chartArea1.AxisY.ScrollBar.BackColor = System.Drawing.Color.White;
            chartArea1.AxisY.TextOrientation = System.Windows.Forms.DataVisualization.Charting.TextOrientation.Horizontal;
            chartArea1.AxisY.TitleFont = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            chartArea1.AxisY.ToolTip = "Ток";
            chartArea1.BackGradientStyle = System.Windows.Forms.DataVisualization.Charting.GradientStyle.TopBottom;
            chartArea1.BackHatchStyle = System.Windows.Forms.DataVisualization.Charting.ChartHatchStyle.Percent50;
            chartArea1.Name = "ChartArea1";
            this.Chart.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.Chart.Legends.Add(legend1);
            this.Chart.Location = new System.Drawing.Point(0, -1);
            this.Chart.Name = "Chart";
            series1.BorderWidth = 0;
            series1.ChartArea = "ChartArea1";
            series1.IsValueShownAsLabel = true;
            series1.IsVisibleInLegend = false;
            series1.IsXValueIndexed = true;
            series1.Label = "#VAL";
            series1.Legend = "Legend1";
            series1.MarkerBorderColor = System.Drawing.Color.Transparent;
            series1.Name = "StripsCurrent";
            this.Chart.Series.Add(series1);
            this.Chart.Size = new System.Drawing.Size(1049, 464);
            this.Chart.TabIndex = 4;
            // 
            // XaxisLabel
            // 
            this.XaxisLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.XaxisLabel.AutoSize = true;
            this.XaxisLabel.BackColor = System.Drawing.Color.White;
            this.XaxisLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.XaxisLabel.Location = new System.Drawing.Point(78, 441);
            this.XaxisLabel.Name = "XaxisLabel";
            this.XaxisLabel.Size = new System.Drawing.Size(161, 20);
            this.XaxisLabel.TabIndex = 5;
            this.XaxisLabel.Text = "Каналы коллектора";
            // 
            // YaxisLabel
            // 
            this.YaxisLabel.AutoSize = true;
            this.YaxisLabel.BackColor = System.Drawing.Color.White;
            this.YaxisLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.YaxisLabel.Location = new System.Drawing.Point(3, 31);
            this.YaxisLabel.Name = "YaxisLabel";
            this.YaxisLabel.Size = new System.Drawing.Size(64, 20);
            this.YaxisLabel.TabIndex = 6;
            this.YaxisLabel.Text = "Q, пКл";
            this.YaxisLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // PCBtemper
            // 
            this.PCBtemper.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.PCBtemper.AutoSize = true;
            this.PCBtemper.BackColor = System.Drawing.Color.Transparent;
            this.PCBtemper.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PCBtemper.Location = new System.Drawing.Point(5, 438);
            this.PCBtemper.Name = "PCBtemper";
            this.PCBtemper.Size = new System.Drawing.Size(0, 24);
            this.PCBtemper.TabIndex = 6;
            // 
            // StatusBox
            // 
            this.StatusBox.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.Location = new System.Drawing.Point(0, 534);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(1049, 22);
            this.StatusBox.TabIndex = 0;
            this.StatusBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ZeroSetB
            // 
            this.ZeroSetB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.ZeroSetB.Location = new System.Drawing.Point(164, 466);
            this.ZeroSetB.Name = "ZeroSetB";
            this.ZeroSetB.Size = new System.Drawing.Size(122, 32);
            this.ZeroSetB.TabIndex = 4;
            this.ZeroSetB.Text = "Установить ноль";
            this.ZeroSetB.UseVisualStyleBackColor = true;
            this.ZeroSetB.Click += new System.EventHandler(this.ZeroSetB_Click);
            // 
            // Σlabel
            // 
            this.Σlabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Σlabel.AutoSize = true;
            this.Σlabel.Font = new System.Drawing.Font("Times New Roman", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Σlabel.Location = new System.Drawing.Point(690, 481);
            this.Σlabel.Name = "Σlabel";
            this.Σlabel.Size = new System.Drawing.Size(161, 32);
            this.Σlabel.TabIndex = 9;
            this.Σlabel.Text = "Σ Q [пКл]=";
            // 
            // TotalCurrentL
            // 
            this.TotalCurrentL.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.TotalCurrentL.AutoSize = true;
            this.TotalCurrentL.Font = new System.Drawing.Font("Times New Roman", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TotalCurrentL.Location = new System.Drawing.Point(833, 482);
            this.TotalCurrentL.Name = "TotalCurrentL";
            this.TotalCurrentL.Size = new System.Drawing.Size(0, 31);
            this.TotalCurrentL.TabIndex = 9;
            // 
            // LhepPictureBox
            // 
            this.LhepPictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.LhepPictureBox.Image = global::DDC_316_test.Properties.Resources.LHEP_emblema_small;
            this.LhepPictureBox.Location = new System.Drawing.Point(947, 476);
            this.LhepPictureBox.Name = "LhepPictureBox";
            this.LhepPictureBox.Size = new System.Drawing.Size(100, 58);
            this.LhepPictureBox.TabIndex = 12;
            this.LhepPictureBox.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1049, 556);
            this.Controls.Add(this.LhepPictureBox);
            this.Controls.Add(this.TotalCurrentL);
            this.Controls.Add(this.Σlabel);
            this.Controls.Add(this.YaxisLabel);
            this.Controls.Add(this.ZeroSetB);
            this.Controls.Add(this.PCBtemper);
            this.Controls.Add(this.XaxisLabel);
            this.Controls.Add(this.StopRdB);
            this.Controls.Add(this.StartRdB);
            this.Controls.Add(this.PortList);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.Chart);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(1065, 594);
            this.Name = "Form1";
            this.Text = "Программа тестирования ЗЦП DDC316 ";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Chart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LhepPictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox PortList;
        private System.Windows.Forms.Button StartRdB;
        private System.Windows.Forms.Timer RefreshTimer;
        private System.Windows.Forms.Button StopRdB;
        private System.Windows.Forms.DataVisualization.Charting.Chart Chart;
        private System.Windows.Forms.Label XaxisLabel;
        private System.Windows.Forms.Label YaxisLabel;
        private System.Windows.Forms.Label PCBtemper;
        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Button ZeroSetB;
        private System.Windows.Forms.Label Σlabel;
        private System.Windows.Forms.Label TotalCurrentL;
        private System.Windows.Forms.PictureBox LhepPictureBox;
    }
}

