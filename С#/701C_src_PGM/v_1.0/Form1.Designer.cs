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
            this.U2setB = new System.Windows.Forms.Button();
            this.U2setVal = new System.Windows.Forms.TextBox();
            this.lbl2 = new System.Windows.Forms.Label();
            this.ChargeOn_B = new System.Windows.Forms.Button();
            this.ChargeOff_B = new System.Windows.Forms.Button();
            this.SrcNumberC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SrcIpC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PortC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SetVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ReadVoltageC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.AddNewSource_B = new System.Windows.Forms.Button();
            this.Update_timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // StatusBox
            // 
            this.StatusBox.Location = new System.Drawing.Point(1, 349);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(475, 20);
            this.StatusBox.TabIndex = 3;
            // 
            // U2setB
            // 
            this.U2setB.Location = new System.Drawing.Point(286, 18);
            this.U2setB.Name = "U2setB";
            this.U2setB.Size = new System.Drawing.Size(72, 41);
            this.U2setB.TabIndex = 2;
            this.U2setB.Text = "Уст. U";
            this.U2setB.UseVisualStyleBackColor = true;
            this.U2setB.Click += new System.EventHandler(this.U2setB_Click);
            // 
            // U2setVal
            // 
            this.U2setVal.Location = new System.Drawing.Point(364, 29);
            this.U2setVal.Name = "U2setVal";
            this.U2setVal.Size = new System.Drawing.Size(50, 20);
            this.U2setVal.TabIndex = 0;
            this.U2setVal.Text = "0";
            // 
            // lbl2
            // 
            this.lbl2.AutoSize = true;
            this.lbl2.Location = new System.Drawing.Point(420, 32);
            this.lbl2.Name = "lbl2";
            this.lbl2.Size = new System.Drawing.Size(14, 13);
            this.lbl2.TabIndex = 1;
            this.lbl2.Text = "B";
            // 
            // ChargeOn_B
            // 
            this.ChargeOn_B.Location = new System.Drawing.Point(273, 74);
            this.ChargeOn_B.Name = "ChargeOn_B";
            this.ChargeOn_B.Size = new System.Drawing.Size(85, 41);
            this.ChargeOn_B.TabIndex = 2;
            this.ChargeOn_B.Text = "ВКЛ. заряд";
            this.ChargeOn_B.UseVisualStyleBackColor = true;
            this.ChargeOn_B.Click += new System.EventHandler(this.Charge_B_Click);
            // 
            // ChargeOff_B
            // 
            this.ChargeOff_B.Location = new System.Drawing.Point(273, 121);
            this.ChargeOff_B.Name = "ChargeOff_B";
            this.ChargeOff_B.Size = new System.Drawing.Size(85, 41);
            this.ChargeOff_B.TabIndex = 2;
            this.ChargeOff_B.Text = "ВЫКЛ. заряд";
            this.ChargeOff_B.UseVisualStyleBackColor = true;
            this.ChargeOff_B.Click += new System.EventHandler(this.DisCharge_B_Click);
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
            this.AddNewSource_B.Location = new System.Drawing.Point(12, 29);
            this.AddNewSource_B.Name = "AddNewSource_B";
            this.AddNewSource_B.Size = new System.Drawing.Size(120, 48);
            this.AddNewSource_B.TabIndex = 2;
            this.AddNewSource_B.Text = "Добавить источник";
            this.AddNewSource_B.UseVisualStyleBackColor = true;
            this.AddNewSource_B.Click += new System.EventHandler(this.NewSource_B_Click);
            // 
            // Update_timer
            // 
            this.Update_timer.Interval = 300;
            this.Update_timer.Tick += new System.EventHandler(this.Update_timer_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(650, 369);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.AddNewSource_B);
            this.Controls.Add(this.ChargeOff_B);
            this.Controls.Add(this.ChargeOn_B);
            this.Controls.Add(this.U2setB);
            this.Controls.Add(this.lbl2);
            this.Controls.Add(this.U2setVal);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "Управление источниками ИП 701С - Троицк";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox StatusBox;
        private System.Windows.Forms.Button U2setB;
        private System.Windows.Forms.TextBox U2setVal;
        private System.Windows.Forms.Label lbl2;
        private System.Windows.Forms.Button ChargeOn_B;
        private System.Windows.Forms.Button ChargeOff_B;
        private System.Windows.Forms.ColumnHeader SrcNumberC;
        private System.Windows.Forms.ColumnHeader SrcIpC;
        private System.Windows.Forms.ColumnHeader PortC;
        private System.Windows.Forms.ColumnHeader SetVoltageC;
        private System.Windows.Forms.ColumnHeader ReadVoltageC;
        private System.Windows.Forms.Button AddNewSource_B;
        private System.Windows.Forms.Timer Update_timer;
    }
}

