namespace MDR32FL
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
            this.port_close = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Port_read_text = new System.Windows.Forms.TextBox();
            this.Read = new System.Windows.Forms.Label();
            this.PortList = new System.Windows.Forms.ComboBox();
            this.Port_label = new System.Windows.Forms.Label();
            this.Port_text2send = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.StatusBox = new System.Windows.Forms.TextBox();
            this.status_pic = new System.Windows.Forms.PictureBox();
            this.search_hex_btn = new System.Windows.Forms.Button();
            this.Program_btn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.status_pic)).BeginInit();
            this.SuspendLayout();
            // 
            // port_close
            // 
            this.port_close.Location = new System.Drawing.Point(302, 201);
            this.port_close.Name = "port_close";
            this.port_close.Size = new System.Drawing.Size(75, 23);
            this.port_close.TabIndex = 0;
            this.port_close.Text = "Close port";
            this.port_close.UseVisualStyleBackColor = true;
            this.port_close.Click += new System.EventHandler(this.port_close_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(276, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(131, 25);
            this.label1.TabIndex = 2;
            this.label1.Text = "Text to send";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Port_read_text
            // 
            this.Port_read_text.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Port_read_text.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Port_read_text.Location = new System.Drawing.Point(236, 118);
            this.Port_read_text.Name = "Port_read_text";
            this.Port_read_text.ReadOnly = true;
            this.Port_read_text.Size = new System.Drawing.Size(211, 31);
            this.Port_read_text.TabIndex = 1;
            this.Port_read_text.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Read
            // 
            this.Read.AutoSize = true;
            this.Read.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Read.Location = new System.Drawing.Point(297, 90);
            this.Read.Name = "Read";
            this.Read.Size = new System.Drawing.Size(63, 25);
            this.Read.TabIndex = 2;
            this.Read.Text = "Read";
            // 
            // PortList
            // 
            this.PortList.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PortList.FormattingEnabled = true;
            this.PortList.Location = new System.Drawing.Point(36, 59);
            this.PortList.Name = "PortList";
            this.PortList.Size = new System.Drawing.Size(73, 24);
            this.PortList.TabIndex = 5;
            // 
            // Port_label
            // 
            this.Port_label.AutoSize = true;
            this.Port_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Port_label.Location = new System.Drawing.Point(47, 36);
            this.Port_label.Name = "Port_label";
            this.Port_label.Size = new System.Drawing.Size(48, 20);
            this.Port_label.TabIndex = 6;
            this.Port_label.Text = "Порт";
            // 
            // Port_text2send
            // 
            this.Port_text2send.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Port_text2send.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Port_text2send.Location = new System.Drawing.Point(291, 59);
            this.Port_text2send.Name = "Port_text2send";
            this.Port_text2send.Size = new System.Drawing.Size(100, 31);
            this.Port_text2send.TabIndex = 1;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(2, 276);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(445, 15);
            this.progressBar1.TabIndex = 7;
            // 
            // StatusBox
            // 
            this.StatusBox.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.StatusBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.StatusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StatusBox.Location = new System.Drawing.Point(2, 255);
            this.StatusBox.Name = "StatusBox";
            this.StatusBox.ReadOnly = true;
            this.StatusBox.Size = new System.Drawing.Size(445, 20);
            this.StatusBox.TabIndex = 8;
            // 
            // status_pic
            // 
            this.status_pic.ErrorImage = global::MDR32FL.Properties.Resources.cancel_48;
            this.status_pic.InitialImage = global::MDR32FL.Properties.Resources.accepted_48;
            this.status_pic.Location = new System.Drawing.Point(166, 135);
            this.status_pic.Name = "status_pic";
            this.status_pic.Size = new System.Drawing.Size(47, 50);
            this.status_pic.TabIndex = 3;
            this.status_pic.TabStop = false;
            // 
            // search_hex_btn
            // 
            this.search_hex_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.search_hex_btn.Image = global::MDR32FL.Properties.Resources.folder_yellow_explorer_icon;
            this.search_hex_btn.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.search_hex_btn.Location = new System.Drawing.Point(12, 90);
            this.search_hex_btn.Name = "search_hex_btn";
            this.search_hex_btn.Size = new System.Drawing.Size(126, 42);
            this.search_hex_btn.TabIndex = 0;
            this.search_hex_btn.Text = "*.hex файл ...";
            this.search_hex_btn.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.search_hex_btn.UseVisualStyleBackColor = true;
            this.search_hex_btn.Click += new System.EventHandler(this.port_open_Click);
            // 
            // Program_btn
            // 
            this.Program_btn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.Program_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Program_btn.Image = global::MDR32FL.Properties.Resources.memory_icon;
            this.Program_btn.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.Program_btn.Location = new System.Drawing.Point(12, 138);
            this.Program_btn.Name = "Program_btn";
            this.Program_btn.Size = new System.Drawing.Size(126, 42);
            this.Program_btn.TabIndex = 0;
            this.Program_btn.Text = "          Старт";
            this.Program_btn.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.Program_btn.UseVisualStyleBackColor = true;
            this.Program_btn.Click += new System.EventHandler(this.Program_btn_Click);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(449, 293);
            this.Controls.Add(this.StatusBox);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.Port_label);
            this.Controls.Add(this.PortList);
            this.Controls.Add(this.status_pic);
            this.Controls.Add(this.Read);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Port_read_text);
            this.Controls.Add(this.Port_text2send);
            this.Controls.Add(this.port_close);
            this.Controls.Add(this.search_hex_btn);
            this.Controls.Add(this.Program_btn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Программа для прошивки МК Миландр серии 1986  ";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.status_pic)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button Program_btn;
        private System.Windows.Forms.Button search_hex_btn;
        private System.Windows.Forms.Button port_close;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox Port_read_text;
        private System.Windows.Forms.Label Read;
        private System.Windows.Forms.PictureBox status_pic;
        private System.Windows.Forms.ComboBox PortList;
        private System.Windows.Forms.Label Port_label;
        private System.Windows.Forms.TextBox Port_text2send;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox StatusBox;
    }
}

