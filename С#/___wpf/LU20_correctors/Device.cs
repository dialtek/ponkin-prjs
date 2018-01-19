using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Controls;
using System.Windows.Threading;
using System.Threading;
using Xceed.Wpf.Toolkit;
using System.Windows.Input;


namespace LU20_correctors_ctrl
{
    class Device
    {
        string _type;
        string _id;
        int _shift_hor;
        int _shift_vert;
        string _c_label = "";

        bool _disable ;

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

        public virtual void SendSetVCmd()
        {
        }

        public virtual void CreateControls(MainWindow form)
        { }

        public virtual void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        { }

        public virtual void SaveState()
        { }

        public virtual void LoadState()
        { }
    }

    class DevicePSP405 : Device
    {
        public DevicePSP405(string id, int shift_hor, int shift_vert, string c_label,  EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "PSP405";
            CLabel = c_label;
            IsEnabled = true;
        }

        string FormatV(string V)
        {
            int Vd = Convert.ToInt32(V);
            string V_format = "0";
            if (Vd > 0)
            {
                int tens = Vd / 10000;
                int ones = (Vd - tens * 10000) / 1000;
                int h_mvolts = (Vd - tens * 10000 - ones * 1000) / 100;
                int t_mvolts = (Vd - tens * 10000 - ones * 1000 - h_mvolts * 100) / 10;
                V_format = tens.ToString() + ones.ToString() + "," + h_mvolts.ToString() + t_mvolts.ToString();
            }
                    
            return V_format;
        }

        string FormatI(string I)
        {
            int Id = Convert.ToInt32(I);
            int amps = Id / 1000;
            int h_ma = (Id - amps *1000) / 100;
            int t_ma = (Id - amps * 1000 - h_ma*100) / 10;
            int ma = (Id - amps * 1000 - h_ma*100-t_ma*10);

            string I_format = amps.ToString() + "," + h_ma.ToString() +  t_ma.ToString() + ma.ToString();
            return I_format;
        }

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:
                    var label_U = (TextBox)controls["textbox_UValue"].WPFControl;
                    var label_I = (TextBox)controls["textbox_IValue"].WPFControl;
                    var rectangle_status_out = (Rectangle)controls["rectangle_status_out"].WPFControl;
                    var out_state_label = (Label)controls["label_out_state"].WPFControl;
                    var b_setON = (Button)controls["button_setON"].WPFControl;
                    var b_setOFF = (Button)controls["button_setOFF"].WPFControl;

                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            label_U.Text = FormatV(msg.Value[0]);
                            label_I.Text = FormatI(msg.Value[2]);

                            var reg_4 = Convert.ToInt32(msg.Value[4]);

                            if (reg_4 == 1)
                            {
                                b_setOFF.IsEnabled = true;
                                b_setON.IsEnabled = false;
                            }
                            else
                            {

                                b_setOFF.IsEnabled = false;
                                b_setON.IsEnabled = true;
                            }

                            rectangle_status_out.Fill = new SolidColorBrush(reg_4 == 1 ? Colors.LimeGreen : Colors.LightGray);
                            out_state_label.Content = reg_4 == 1 ? "Вкл." : "Выкл.";
                        });                   
                    break;
            }
            switch (msg.Key["id"])
            {
                case 67: settings_data.VDK_FI_Vmax = msg.Value[1]; break;


            }
            
        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 0;
            var second_line = 35;
            var top = 0;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 885;
            var height_grid = 60;
            var width_control = 100;
            var height_control = 44;

            // ------------------------------ Пример добавления контрола ------------------------------------------------------
            // * Для начала нужно создать WPF контрол (обычный контрол формы)
            // * * обращаю внимание, что имя WPF контрола строится по правилу: "id девайса"_"тип контрола"_"имя контрола"
            // * * string.Format("{0}_label_status_HightU", name
            // * Затем нужно создать девайс контрол, наследний класса Control
            // * * добавить в словарь контролов данного девайса только, что созданный
            // * * имя девайс контрола должно совпадать с "имя контрола" упомянутого раннее.
            // * * вызвать у девайс контрола метод .GetControl(), он возвращает WPF контрол привязанный к этому девайс контролу и нужно добавить этот WPF контрол в device_grid
            // ----------------------------------------------------------------------------------------------------------------
            // ------- полотно
            Control grid = new GridDevice(this, string.Format("{0}_grid", name), 
                                            new Thickness(weight_grid * ShiftHor, height_grid * ShiftVert/10, 0, 0),
                                Colors.WhiteSmoke, weight_grid, height_grid);
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);

            // ------- Информация об устройстве
            var label_С_control = new LabelControl(this, string.Format("{0}_label_С", name), new Thickness(left, top, 0, 0), CLabel, true, 25);
            device_grid.Children.Add((Label)label_С_control.GetControl());
            controls.Add("label_С", label_С_control);
            // ID
            var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name), new Thickness(left+15, top + 35, 0, 0), "ID " + Id, false, 10);
            device_grid.Children.Add((Label)label_id_control.GetControl());
            controls.Add("label_id", label_id_control);
            // вкл/выкл
            var checkbox_disable_control = new CheckBoxDevice(this, string.Format("{0}_checkbox_disable", name), new Thickness(left + 50, top + 40, 0, 0), "");
            var checkbox_disable_control_wpf = (CheckBox)checkbox_disable_control.GetControl();
            checkbox_disable_control_wpf.Unchecked += Checkbox_disable_Unchecked;
            checkbox_disable_control_wpf.Checked += Checkbox_disable_wpf_Checked;
            device_grid.Children.Add(checkbox_disable_control_wpf);
            controls.Add("checkbox_disable", checkbox_disable_control);
            // -----------------------------------------------
            // ------- уст. напряжения
            Control SetVol_UpDown = new DoubleUpDownDevice(this, string.Format("{0}_updown_set_U", name), new Thickness(left + 120, top+5, 0, 0),
                                                        width_control, height_control, false, 40, 0, 0.1, 30);

            var UpDown_setu_wpf = (CommonNumericUpDown<double>)SetVol_UpDown.GetControl();
            //UpDown_setu_wpf.ValueChanged += UpDown_setu_wpf_ValueChanged;
            //UpDown_setu_wpf.Spinned += UpDown_setu_wpf_Spinned;
            device_grid.Children.Add(UpDown_setu_wpf);
            controls.Add("SetVol_UpDown", SetVol_UpDown);
                    
            left += 230;

            Control button_setU_control = new ButtonSet(this, string.Format("{0}_button_setU", name),
                                                new Thickness(left, top+5, 0, 0), "УСТ.",
                                                45, height_control);
            var button_setU_control_wpf = (Button)button_setU_control.GetControl();
            button_setU_control_wpf.Click += Button_setU_Click;
            device_grid.Children.Add(button_setU_control_wpf);
            controls.Add("button_setU", button_setU_control);
            // -----------------------------------------------
            // ------- уст. тока 
            left += 60;

            Control SetCur_UpDown = new DoubleUpDownDevice(this, string.Format("{0}_updown_set_I", name), new Thickness(left, top + 5, 0, 0),
                                            width_control+5, height_control, true, 5, 0, 0.01, 30);

            var UpDown_seti_wpf = (CommonNumericUpDown<double>)SetCur_UpDown.GetControl();
            UpDown_seti_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(UpDown_seti_wpf);
            controls.Add("SetCurr_UpDown", SetCur_UpDown);

            left += height_control*2+25;

            Control button_setI_control = new ButtonSet(this, string.Format("{0}_button_setI", name),
                                                new Thickness(left, top + 5, 0, 0), "УСТ.",
                                                45, height_control);
            var button_setI_control_wpf = (Button)button_setI_control.GetControl();
            button_setI_control_wpf.Click += Button_setI_Click;
            device_grid.Children.Add(button_setI_control_wpf);
            controls.Add("button_setI", button_setI_control);
            // -----------------------------------------------
            // ------- измерения U/I
            left += 75;

            var text_box_UValue_control = new TextBoxDevice(this, string.Format("{0}_textbox_UValue", name),
                                                        new Thickness(left, top + 5, 0, 0),
                                                        width_control, height_control, false,30, true);
            
            var textbox_valueU_control_wpf = (TextBox)text_box_UValue_control.GetControl();
            textbox_valueU_control_wpf.TextChanged += Textbox_valueU_control_wpf_TextChanged;
            device_grid.Children.Add(textbox_valueU_control_wpf);
            controls.Add("textbox_UValue", text_box_UValue_control);

            left += 110;

            var text_box_IValue_control = new TextBoxDevice(this, string.Format("{0}_text_box_IValue", name),
                                                        new Thickness(left, top + 5, 0, 0),
                                                        width_control, height_control, true,30, true);
            var text_box_IValue_control_wpf = (TextBox)text_box_IValue_control.GetControl();
            text_box_IValue_control_wpf.TextChanged += Textbox_IValue_control_wpf_TextChanged;
            text_box_IValue_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(text_box_IValue_control_wpf);
            controls.Add("textbox_IValue", text_box_IValue_control);
            //-----------------------------------------------------------------------
            // ------- выбор полярности
            left += 130;
            var rb_pos_pol_control = new RadioButtonDevice(this, string.Format("{0}_rb_pos_pol", name),
                                                            new Thickness(left, top+5, 0, 0),
                                                            string.Format("{0}_rb", name),
                                                            "");
            var rb_pos_pol_wpf = (RadioButton)rb_pos_pol_control.GetControl();
            rb_pos_pol_wpf.Checked += Rb_pos_pol_wpf_Checked;
            device_grid.Children.Add(rb_pos_pol_wpf);
            controls.Add("rb_pos_pol", rb_pos_pol_control);

            var rb_pos_neg_control = new RadioButtonDevice(this, string.Format("{0}_rb_neg_pol", name),
                                                new Thickness(left, top + 40, 0, 0),
                                                string.Format("{0}_rb", name),
                                                "");
            var rb_neg_pol_wpf = (RadioButton)rb_pos_neg_control.GetControl();
            rb_neg_pol_wpf.Checked += Rb_neg_pol_wpf_Checked;
            device_grid.Children.Add(rb_neg_pol_wpf);
            controls.Add("rb_neg_pol", rb_pos_neg_control);
            // ------- значки +/-
            var label_pol_sign1= new LabelControl(this, string.Format("{0}_label_pol", name), new Thickness(left+15, top-12, 0, 0), "", true, 25);
            device_grid.Children.Add((Label)label_pol_sign1.GetControl());
            controls.Add("label_pol_sign1", label_pol_sign1);

            var label_pol_sign2 = new LabelControl(this, string.Format("{0}_label_pol", name), new Thickness(left + 19, top+18, 0, 0), "", true, 25);
            device_grid.Children.Add((Label)label_pol_sign2.GetControl());
            controls.Add("label_pol_sign2", label_pol_sign2);
            //-----------------------------------------------------------------------
            // ------- вкл/выкл. выход
            left += 60;
            Control button_setON_control = new ButtonSet(this, string.Format("{0}_button_setON", name),
                                    new Thickness(left, top+2, 0, 0), "ВКЛ.",
                                    45, 25);
            var button_setON_control_wpf = (Button)button_setON_control.GetControl();
            button_setON_control_wpf.Click += Button_ON_Click;
            device_grid.Children.Add(button_setON_control_wpf);
            controls.Add("button_setON", button_setON_control);

            Control button_setOFF_control = new ButtonSet(this, string.Format("{0}_button_setOFF", name),
                        new Thickness(left, top +33, 0, 0), "ВЫКЛ.",
                        45, 25);
            var button_setOFF_control_wpf = (Button)button_setOFF_control.GetControl();
            button_setOFF_control_wpf.Click += Button_OFF_Click;
            device_grid.Children.Add(button_setOFF_control_wpf);
            controls.Add("button_setOFF", button_setOFF_control);
            //-----------------------------------------------------------------------
            // ------- статус выхода
            left += 50;

            Control rectangle_status_out_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_out", name),
                                                                new Thickness(left+5, top+10, 0, 0),
                                                                45, 40);
            device_grid.Children.Add((Rectangle)rectangle_status_out_control.GetControl());
            controls.Add("rectangle_status_out", rectangle_status_out_control);

            var label_out_state = new LabelControl(this, string.Format("{0}_label_state", name), new Thickness(left + 10, top+14, 0, 0), "out", false, 14);
            device_grid.Children.Add((Label)label_out_state.GetControl());
            controls.Add("label_out_state", label_out_state);

            _form.MainGrid.Children.Add(device_grid);
        }

        public override void SendSetVCmd()
        {   // отпрвка команду уст. U
            var set_value = (CommonNumericUpDown<Double>)controls["SetVol_UpDown"].WPFControl;
            int send_msg = 0;
            int register = 0;

            try
            {
                send_msg = (int)(set_value.Value * 1000);
                register = 1007;
            }
            catch
            {
                return;
            }
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);

            SendMsgDeviceManager(this, msg_);
        }

        public void SendSetICmd()
        {   // отпрвка команду уст. I
            var set_value = (CommonNumericUpDown<Double>)controls["SetCurr_UpDown"].WPFControl;
            int send_msg = 0;
            int register = 0;

            try
            {
                send_msg = (int)(set_value.Value * 1000);
                register = 1009;
            }
            catch
            {
                return;
            }
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);

            SendMsgDeviceManager(this, msg_);
        }

        public void ChangeIStateEvent()
        {
            var recieve_value = (TextBox)controls["textbox_IValue"].WPFControl;
            var set_value = (CommonNumericUpDown<double>)controls["SetCurr_UpDown"].WPFControl;

            double recieve_value_num = 0;
            double set_value_num = 0;

                try
                {
                    recieve_value_num= Convert.ToDouble(recieve_value.Text);
                    set_value_num= Convert.ToDouble(set_value.Text);
                }
                catch
                {
                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                    (ThreadStart)delegate ()
                    {
                        set_value.Background = new SolidColorBrush(Colors.Yellow);
                    });
                    return;
                }

                if (Math.Abs(recieve_value_num - set_value_num) > 0.01)
                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                    (ThreadStart)delegate ()
                    {
                        set_value.Background = new SolidColorBrush(Colors.Yellow);
                    });
                else
                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                    (ThreadStart)delegate ()
                    {
                        set_value.Background = new SolidColorBrush(Colors.White);
                    });
            
        }

        public void ChangeUStateEvent()
        {
            var recieve_value = (TextBox)controls["textbox_UValue"].WPFControl;
            var set_value = (CommonNumericUpDown<double>)controls["SetVol_UpDown"].WPFControl;

            double recieve_value_num = 0;
            double set_value_num = 0;

            try
            {
                recieve_value_num = Convert.ToDouble(recieve_value.Text);
                set_value_num = Convert.ToDouble(set_value.Text);
            }
            catch
            {
                _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)delegate ()
                {
                    set_value.Background = new SolidColorBrush(Colors.Yellow);
                });
                return;
            }

            if (Math.Abs(recieve_value_num - set_value_num) > 0.01)
                _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)delegate ()
                {
                    set_value.Background = new SolidColorBrush(Colors.Yellow);
                });
            else
                _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)delegate ()
                {
                    set_value.Background = new SolidColorBrush(Colors.White);
                });

        }

        public override void SaveState()
        {
            
        }

        //------------------------ Обработчики контролов ---------------------
        private void Checkbox_disable_wpf_Checked(object sender, RoutedEventArgs e)
        {
            foreach (var control in controls.Values)
            {
                control.WPFControl.IsEnabled = true;
            }

            IsEnabled = true;
        }

        private void Checkbox_disable_Unchecked(object sender, RoutedEventArgs e)
        {
            foreach (var control in controls.Values)
            {
                if (control.Name.Contains("checkbox") == false &&
                    control.Name.Contains("grid") == false)
                    control.WPFControl.IsEnabled = false;
            }
            IsEnabled = false;
        }

        private void Textbox_valueU_control_wpf_TextChanged(object sender, TextChangedEventArgs e)
        {
            ChangeUStateEvent();
            ChangeIStateEvent();
        }

        private void Textbox_IValue_control_wpf_TextChanged(object sender, TextChangedEventArgs e)
        {
            ChangeIStateEvent();
            ChangeUStateEvent();
        }

        private void Rb_pos_pol_wpf_Checked(object sender, RoutedEventArgs e)
        {
            // вкл. положит полярности нагрузки
            // сначала откл. выход
            int send_msg = 0;
            int register = 1004;

            QueueElement msg_;
            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
            // меняем полярность
            send_msg = 1;
            register = 1010;
            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
            // после вкл. выход
            send_msg = 1;
            register = 1004;

            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        private void Rb_neg_pol_wpf_Checked(object sender, RoutedEventArgs e)
        {
            // вкл. отриц. полярности нагрузки
            // сначала откл. выход
            int send_msg = 0;
            int register = 1004;

            QueueElement msg_;
            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
            // меняем полярность
            send_msg = 0;
            register = 1010;
            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
            // после вкл. выход
            send_msg = 1;
            register = 1004;

            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        private void Button_ON_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 1;
            int register = 1004;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        private void Button_OFF_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 1004;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        private void Button_setU_Click(object sender, RoutedEventArgs e)
        {
            SendSetVCmd();
        }

        private void Button_setI_Click(object sender, RoutedEventArgs e)
        {
            SendSetICmd();
        }  
    }
}
