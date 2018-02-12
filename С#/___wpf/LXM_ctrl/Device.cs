using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using Xceed.Wpf.Toolkit;
using System.Windows.Controls;
using System.Windows.Threading;
using System.Threading;

namespace LXM_ctrl
{
    class Device
    {
        string _type;
        string _id;
        int _shift_hor;
        int _shift_vert;
        string _c_label = "";

        bool _disable;

        private event EventHandler<QueueElement> _send_msg;
        public MainWindow _form;

        public Dictionary<string, Control> controls;
        public bool IsEnabled
        {
            get { return _disable; }
            set { _disable = value; }
        }

        public string Type
        {
            get { return _type; }
            set { _type = value; }
        }
        public string Id
        {
            get { return _id; }
            set { _id = value; }
        }
        public int ShiftHor
        {
            get { return _shift_hor; }
            set { _shift_hor = value; }
        }
        public int ShiftVert
        {
            get { return _shift_vert; }
            set { _shift_vert = value; }
        }
        public string CLabel
        {
            get { return _c_label; }
            set { _c_label = value; }
        }

        public EventHandler<QueueElement> SendMsgDeviceManager
        {
            get { return _send_msg; }
            set { _send_msg += value; }
        }

        public virtual void SendMessage()
        {
        }

        public virtual void CreateControls(MainWindow form)
        { }

        public virtual void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, UInt16>, List<string>> msg)
        { }

        public virtual void SaveState()
        { }

        public virtual void LoadState()
        { }
    }

    class DeviceCom : Device
    {
        public DeviceCom(string id, int shift_hor, int shift_vert, string c_label, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "dev_com";
            CLabel = c_label;
            IsEnabled = true;
        }

        string FormatOutput(string b)
        {
            var zeros = "";
            //"0.00";
            //for (int i = b.ToString().Length; i < 2; i++)
            //    zeros += "0";
            return "+" + zeros + b;
        }

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, UInt16>, List<string>> msg)
        {
            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:

                    var textbox_read = (TextBox)controls["textbox_read"].WPFControl;
                    var format = (CommonNumericUpDown<int>)controls["Set_form_UpDown"].WPFControl;
                    Int32 rd_value = 0;
                    //settings_data.rf_delay = msg.Value[9];  // сохр. задержку ВЧ

                    if (msg.Value[0] != null && msg.Value[1] != null)
                    {
                        rd_value = (Convert.ToUInt16(msg.Value[0]) << 16) | Convert.ToUInt16(msg.Value[1]);
                        _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                            (ThreadStart)delegate ()
                            {
                                rd_value = (((rd_value + 12529) / 849)); //- Convert.ToInt32(format.Value));
                                textbox_read.Text = rd_value.ToString();
                            });
                    }

                    break;
                    //---
                    //case (byte)cmd_type.wmr:

                    //break;

            }

        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 0;
            var top = 0;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 375;
            var height_grid = 70;

            var w_control = 75;
            var h_control = 30;

            // ------------------------------ Пример добавления контрола ------------------------------------------------------
            // * Для начала нужно создать WPF контрол (обычный контрол формы)
            // * * обращаю внимание, что имя WPF контрола строится по правилу: "id девайса"_"тип контрола"_"имя контрола"
            // * * string.Format("{0}_label_status_HightU", name
            // * Затем нужно создать девайс контрол, наследний класса Control
            // * * добавить в словарь контролов данного девайса только, что созданный
            // * * имя девайс контрола должно совпадать с "имя контрола" упомянутого раннее.
            // * * вызвать у девайс контрола метод .GetControl(), он возвращает WPF контрол привязанный к этому девайс контролу и нужно добавить этот WPF контрол в device_grid
            // ----------------------------------------------------------------------------------------------------------------
            Control grid = new GridDevice(this, string.Format("{0}_grid", name),
                                            new Thickness(weight_grid * ShiftHor + 5, height_grid * ShiftVert, 0, 0),
                                Colors.WhiteSmoke, weight_grid + 10, height_grid); //WhiteSmoke
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);

            // -----------------------------------------------
            ///// надпись формат
            left += 15;
            var label_form = new LabelControl(this, string.Format("{0}_label", name), new Thickness(left, top, 0, 0), "Формат, мм ", false);
            device_grid.Children.Add((Label)label_form.GetControl());
            controls.Add("label_form", label_form);

            ///// поле уст. формат
            Control Set_form_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_set", name), new Thickness(left, top + 25, 0, 0),
                                                                    w_control, h_control, false, 20000,1, 1);

            var UpDown_set_form_wpf = (CommonNumericUpDown<int>)Set_form_UpDown.GetControl();
            UpDown_set_form_wpf.Value = 620;//Convert.ToInt32(settings_data.format);
            //UpDown_set_wpf.KeyDown += UpDown_setu_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_set_form_wpf);
            controls.Add("Set_form_UpDown", Set_form_UpDown);

            ///// надпись нахлест
            left += 85;
            var label_ov = new LabelControl(this, string.Format("{0}_label", name), new Thickness(left, top, 0, 0), "Нахлёст, мм ", false);
            device_grid.Children.Add((Label)label_ov.GetControl());
            controls.Add("label_ov", label_ov);

            ///// поле уст. нахлест
            Control Set_ov_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_set", name), new Thickness(left, top+25, 0, 0),
                                                                    w_control, h_control, false, 500, -500, 1);

            var UpDown_set_ov_wpf = (CommonNumericUpDown<int>)Set_ov_UpDown.GetControl();
            UpDown_set_ov_wpf.Value = 1;//Convert.ToInt32(settings_data.overlap);
            //UpDown_set_wpf.KeyDown += UpDown_setu_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_set_ov_wpf);
            controls.Add("Set_ov_UpDown", Set_ov_UpDown);

            ///// кнопка уст.
            left += 95;
            Control button_set = new ButtonSetU(this, string.Format("{0}_button", name),
                                               new Thickness(left, top+25, 0, 0), "Установить",75, h_control);
            var button_set_wpf = (Button)button_set.GetControl();
            button_set_wpf.Click += button_set_Click;
            device_grid.Children.Add(button_set_wpf);
            controls.Add("button_set", button_set);

            ///// поле чтения
            left += 95;
            var textbox_read = new TextBoxDevice(this, string.Format("{0}_textbox_read", name),
                                                                    new Thickness(left, top+25, 0, 0),
                                                                    w_control, h_control, false);

            var textbox_read_wpf = (TextBox)textbox_read.GetControl();
            textbox_read_wpf.Foreground = new SolidColorBrush(Colors.Green);
            textbox_read_wpf.IsEnabled = true;
            textbox_read_wpf.IsReadOnly = false;
            device_grid.Children.Add(textbox_read_wpf);
            controls.Add("textbox_read", textbox_read);

            ///// надпись чтение
            var label_read = new LabelControl(this, string.Format("{0}_label", name), new Thickness(left-9, top, 0, 0), "Конт. значение", false);
            device_grid.Children.Add((Label)label_read.GetControl());
            controls.Add("label_read", label_read);

            //-----------------------------------------------------------------------

            _form.MainGrid.Children.Add(device_grid);
        }

        private void button_set_Click(object sender, RoutedEventArgs e)
        {
            SendMessage();
        }

        public override void SendMessage()
        {
            var overlap = (CommonNumericUpDown<int>)controls["Set_ov_UpDown"].WPFControl;
            var format  = (CommonNumericUpDown<int>)controls["Set_form_UpDown"].WPFControl;
            settings_data.format = format.Value.ToString();
            settings_data.overlap = overlap.Value.ToString();

            int register = Convert.ToUInt16(settings_data.reg_addr);
            UInt16 data_msb = 0, data_lsb = 0;
            Int32 send_msg = 0;
            byte[] send_arr = { 0x00, 0x00, 0x00, 0x00 };

            try
            {
                if (overlap.Value != null && format.Value != null)
                {
                    send_msg = 849 * ((Int32)format.Value + (Int32)overlap.Value) - 12529; // y = 849,3x - 12529
                   
                    data_msb = (UInt16)(send_msg >> 16);
                    send_msg &= 0x0000ffff;
                    data_lsb = (UInt16)send_msg;

                    send_arr[0] = (byte)(data_lsb & 0x00ff);
                    send_arr[1] = (byte)(data_lsb >> 8);
                    send_arr[2] = (byte)(data_msb & 0x00ff);
                    send_arr[3] = (byte)(data_msb >> 8);
                }
            }
            catch
            {
                return;
            }

            QueueElement msg_ = new QueueElementWM(Convert.ToInt32(Id), register, send_arr);
            SendMsgDeviceManager(this, msg_);
        }

        public void ChangeStateEvent()
        {

        }

        public override void SaveState()
        {

        }

    }
}
