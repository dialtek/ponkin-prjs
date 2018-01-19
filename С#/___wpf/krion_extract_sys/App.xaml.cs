using System;
using System.Threading;
using System.Windows;

namespace extract_system
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        // check if same process is already running:
        Mutex m;
        public App()
        {

            bool isnew;
            m = new Mutex(true, "awijwwsnswh", out isnew);
            if (!isnew)
            {
                MessageBox.Show("Программа уже запущена",
                                "Программа СУДИ", MessageBoxButton.OK, MessageBoxImage.Warning);
                Environment.Exit(0);
            }
        }
    }
}
