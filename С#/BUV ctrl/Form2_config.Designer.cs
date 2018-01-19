namespace BUV_ctrl
{
    partial class Form2_config
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
            this.PortLbl = new System.Windows.Forms.Label();
            this.Iplbl = new System.Windows.Forms.Label();
            this.Port = new System.Windows.Forms.TextBox();
            this.IP_adress = new System.Windows.Forms.TextBox();
            this.AddNewSrcB = new System.Windows.Forms.Button();
            this.NewSrcName = new System.Windows.Forms.TextBox();
            this.Name_lbl = new System.Windows.Forms.Label();
            this.Form2_listView = new System.Windows.Forms.ListView();
            this.NameC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.IP_adrC = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Port_C = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.DeleteSrcB = new System.Windows.Forms.Button();
            this.SaveCfgB = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // PortLbl
            // 
            this.PortLbl.AutoSize = true;
            this.PortLbl.Location = new System.Drawing.Point(234, 10);
            this.PortLbl.Name = "PortLbl";
            this.PortLbl.Size = new System.Drawing.Size(32, 13);
            this.PortLbl.TabIndex = 4;
            this.PortLbl.Text = "Порт";
            // 
            // Iplbl
            // 
            this.Iplbl.AutoSize = true;
            this.Iplbl.Location = new System.Drawing.Point(101, 10);
            this.Iplbl.Name = "Iplbl";
            this.Iplbl.Size = new System.Drawing.Size(50, 13);
            this.Iplbl.TabIndex = 5;
            this.Iplbl.Text = "IP адрес";
            // 
            // Port
            // 
            this.Port.Location = new System.Drawing.Point(237, 26);
            this.Port.Name = "Port";
            this.Port.Size = new System.Drawing.Size(50, 20);
            this.Port.TabIndex = 2;
            this.Port.Text = "4001";
            // 
            // IP_adress
            // 
            this.IP_adress.Location = new System.Drawing.Point(102, 26);
            this.IP_adress.Name = "IP_adress";
            this.IP_adress.Size = new System.Drawing.Size(113, 20);
            this.IP_adress.TabIndex = 3;
            this.IP_adress.Text = "192.168.127.254";
            // 
            // AddNewSrcB
            // 
            this.AddNewSrcB.Location = new System.Drawing.Point(25, 62);
            this.AddNewSrcB.Name = "AddNewSrcB";
            this.AddNewSrcB.Size = new System.Drawing.Size(89, 36);
            this.AddNewSrcB.TabIndex = 6;
            this.AddNewSrcB.Text = "Добавить";
            this.AddNewSrcB.UseVisualStyleBackColor = true;
            this.AddNewSrcB.Click += new System.EventHandler(this.AddNewSrcB_Click);
            // 
            // NewSrcName
            // 
            this.NewSrcName.Location = new System.Drawing.Point(24, 26);
            this.NewSrcName.Name = "NewSrcName";
            this.NewSrcName.Size = new System.Drawing.Size(50, 20);
            this.NewSrcName.TabIndex = 2;
            this.NewSrcName.Text = "1";
            // 
            // Name_lbl
            // 
            this.Name_lbl.AutoSize = true;
            this.Name_lbl.Location = new System.Drawing.Point(21, 10);
            this.Name_lbl.Name = "Name_lbl";
            this.Name_lbl.Size = new System.Drawing.Size(29, 13);
            this.Name_lbl.TabIndex = 4;
            this.Name_lbl.Text = "Имя";
            // 
            // Form2_listView
            // 
            this.Form2_listView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.NameC,
            this.IP_adrC,
            this.Port_C});
            this.Form2_listView.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Form2_listView.FullRowSelect = true;
            this.Form2_listView.GridLines = true;
            this.Form2_listView.Location = new System.Drawing.Point(24, 114);
            this.Form2_listView.Name = "Form2_listView";
            this.Form2_listView.Size = new System.Drawing.Size(275, 401);
            this.Form2_listView.TabIndex = 7;
            this.Form2_listView.UseCompatibleStateImageBehavior = false;
            this.Form2_listView.View = System.Windows.Forms.View.Details;
            this.Form2_listView.Click += new System.EventHandler(this.Form2_listView_Click);
            // 
            // NameC
            // 
            this.NameC.Text = "Имя";
            // 
            // IP_adrC
            // 
            this.IP_adrC.Text = "IP адрес";
            this.IP_adrC.Width = 156;
            // 
            // Port_C
            // 
            this.Port_C.Text = "Порт";
            this.Port_C.Width = 53;
            // 
            // DeleteSrcB
            // 
            this.DeleteSrcB.Location = new System.Drawing.Point(120, 62);
            this.DeleteSrcB.Name = "DeleteSrcB";
            this.DeleteSrcB.Size = new System.Drawing.Size(87, 36);
            this.DeleteSrcB.TabIndex = 6;
            this.DeleteSrcB.Text = "Удалить";
            this.DeleteSrcB.UseVisualStyleBackColor = true;
            this.DeleteSrcB.Click += new System.EventHandler(this.DeleteSrcB_Click);
            // 
            // SaveCfgB
            // 
            this.SaveCfgB.Location = new System.Drawing.Point(213, 62);
            this.SaveCfgB.Name = "SaveCfgB";
            this.SaveCfgB.Size = new System.Drawing.Size(87, 36);
            this.SaveCfgB.TabIndex = 6;
            this.SaveCfgB.Text = "Сохранить";
            this.SaveCfgB.UseVisualStyleBackColor = true;
            this.SaveCfgB.Click += new System.EventHandler(this.SaveCfgB_Click);
            // 
            // Form2_config
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 539);
            this.Controls.Add(this.Form2_listView);
            this.Controls.Add(this.SaveCfgB);
            this.Controls.Add(this.DeleteSrcB);
            this.Controls.Add(this.AddNewSrcB);
            this.Controls.Add(this.Name_lbl);
            this.Controls.Add(this.PortLbl);
            this.Controls.Add(this.Iplbl);
            this.Controls.Add(this.NewSrcName);
            this.Controls.Add(this.Port);
            this.Controls.Add(this.IP_adress);
            this.Name = "Form2_config";
            this.Text = "Form2_config";
            this.Shown += new System.EventHandler(this.Form2_config_Shown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.Label PortLbl;
        public System.Windows.Forms.Label Iplbl;
        public System.Windows.Forms.TextBox Port;
        public System.Windows.Forms.TextBox IP_adress;
        private System.Windows.Forms.Button AddNewSrcB;
        public System.Windows.Forms.TextBox NewSrcName;
        public System.Windows.Forms.Label Name_lbl;
        private System.Windows.Forms.ListView Form2_listView;
        private System.Windows.Forms.ColumnHeader NameC;
        private System.Windows.Forms.ColumnHeader IP_adrC;
        private System.Windows.Forms.ColumnHeader Port_C;
        private System.Windows.Forms.Button DeleteSrcB;
        private System.Windows.Forms.Button SaveCfgB;
    }
}