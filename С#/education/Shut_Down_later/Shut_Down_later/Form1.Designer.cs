namespace Shut_Down_later
{
    partial class Автовыключатель
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
            this.Button_run = new System.Windows.Forms.Button();
            this.label_inf = new System.Windows.Forms.Label();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // Button_run
            // 
            this.Button_run.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Button_run.Location = new System.Drawing.Point(92, 45);
            this.Button_run.Name = "Button_run";
            this.Button_run.Size = new System.Drawing.Size(208, 34);
            this.Button_run.TabIndex = 0;
            this.Button_run.Text = "Выкл. ПК через час";
            this.Button_run.UseVisualStyleBackColor = true;
            this.Button_run.Click += new System.EventHandler(this.Button_run_Click);
            // 
            // label_inf
            // 
            this.label_inf.AutoSize = true;
            this.label_inf.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label_inf.Location = new System.Drawing.Point(12, 9);
            this.label_inf.Name = "label_inf";
            this.label_inf.Size = new System.Drawing.Size(164, 26);
            this.label_inf.TabIndex = 1;
            this.label_inf.Text = "До выкл. ос.....";
            this.label_inf.Visible = false;
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // Автовыключатель
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(383, 99);
            this.Controls.Add(this.label_inf);
            this.Controls.Add(this.Button_run);
            this.Name = "Автовыключатель";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Автовыключатель";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Button_run;
        private System.Windows.Forms.Label label_inf;
        private System.Windows.Forms.Timer timer;
    }
}

