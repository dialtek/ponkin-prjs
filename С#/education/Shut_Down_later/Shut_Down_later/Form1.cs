using System;
using System.Windows.Forms;
using System.Diagnostics;

namespace Shut_Down_later
{
    public partial class Автовыключатель : Form
    {
        DateTime mShutdownTime;

        public Автовыключатель()
        {
            InitializeComponent();
        }

        private void Button_run_Click(object sender, EventArgs e)
        { 
            mShutdownTime = DateTime.Now.AddHours(1);
            label_inf.Visible = true;
            label_inf.Text = "";
            timer.Start();
        }

        private void timer_Tick(object sender, EventArgs e)
        {   
            

            if (DateTime.Now < mShutdownTime)
            {
                TimeSpan ts = mShutdownTime - DateTime.Now;
                label_inf.Text = "До выкл. осталось " + ts.Minutes + " мин. "
                                                      + ts.Seconds + " сек.";
            }
                
            else { 
                Close();
                // Process.Start("shutdown.exe", "-h");
                 
                 }
            
        }

    }
}