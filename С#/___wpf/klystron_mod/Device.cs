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

namespace klystron_mod
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

        public virtual void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        { }

        public virtual void SaveState()
        { }

        public virtual void LoadState()
        { }
    }

    class DevicePBF : Device
    {
        public DevicePBF(string id, int shift_hor, int shift_vert, string c_label, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "PBF";
            CLabel = c_label;
            IsEnabled = true;
        }

        string FormatOutput(string b)
        {
            var zeros = "";
            for (int i = b.ToString().Length; i < 4; i++)
                zeros += "0";
            return zeros + b;
        }

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:
                    var label_U = (TextBox)controls["textbox_UValue"].WPFControl;
                    var label_I = (TextBox)controls["textbox_IValue"].WPFControl;

                    var rectangle_status_HightU = (Rectangle)controls["rectangle_status_HightU"].WPFControl;
                    var rectangle_status_protectI = (Rectangle)controls["rectangle_status_protectI"].WPFControl;
                    var rectangle_status_outState = (Rectangle)controls["rectangle_status_HV_EN"].WPFControl;

                    var setV_UpDown = (IntegerUpDown)controls["SetVol_UpDown"].WPFControl;
                    var label_status_protectI = (Label)controls["label_status_protectI"].WPFControl;
                    var label_status_HightU = (Label)controls["label_status_HightU"].WPFControl;
                    var label_status_outState = (Label)controls["label_status_HV_EN"].WPFControl;

                    var button_onHightU = (Button)controls["button_onHightU"].WPFControl;
                    var button_offHightU = (Button)controls["button_offHightU"].WPFControl;

                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                    (ThreadStart)delegate ()
                    {
                        label_U.Text = FormatOutput(msg.Value[5]);

                        //    // добавление устрйоства в опасный список если есть высокое
                        //    if (Convert.ToUInt16(msg.Value[5]) > hv_status.danger_lvl)
                        //    hv_status.add_element(CLabel);
                        //else hv_status.del_element(CLabel);


                        label_I.Text = FormatOutput(msg.Value[6]);

                        var reg_9 = Convert.ToInt32(msg.Value[9]);

                        if (reg_9 == 1)
                        {
                            button_onHightU.IsEnabled = true;
                            button_offHightU.IsEnabled = false;
                            rectangle_status_outState.Fill = new SolidColorBrush(Colors.LimeGreen);
                            label_status_outState.Content = "Вкл.";
                        }
                        else
                        {
                            button_onHightU.IsEnabled = false;
                            button_offHightU.IsEnabled = true;
                            rectangle_status_outState.Fill = new SolidColorBrush(Colors.LightGray);
                            label_status_outState.Content = "Выкл.";
                        }

                        var reg_11 = Convert.ToInt32(msg.Value[11]);
                        rectangle_status_HightU.Fill = new SolidColorBrush(reg_11 == 1 ? Colors.LimeGreen : Colors.LightGray);
                        label_status_HightU.Content = reg_11 == 1 ? "Т. Вкл." : "Т. Вык.";

                        var reg_12 = Convert.ToInt32(msg.Value[12]);
                        rectangle_status_protectI.Fill = new SolidColorBrush(reg_12 == 0 ? Colors.LimeGreen : Colors.Coral);
                        label_status_protectI.Content = reg_12 == 0 ? "Ок" : "I LIM";

                        var reg_0 = Convert.ToInt32(msg.Value[0]);

                            // если были считаны уставки и в программе они не уст.
                            if (setV_UpDown.Value == null)
                            setV_UpDown.Value = reg_0;

                    });
                    break;
                    //case 2:
                    //    cmd_type.wsr:
                    //    break;

            }

        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 1;
            var second_line = 35;
            //var new_line = 35;
            var top = 8;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 420;
            var height_grid = 80;

            //var weight_control = 50;
            var height_control = 25;

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
                                            new Thickness(weight_grid * ShiftHor + 35, height_grid * ShiftVert/10, 0, 0),
                                Colors.WhiteSmoke, weight_grid + 10, height_grid); //WhiteSmoke
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);
            // ------- кнопки вкл/выкл
            left += 10;

            Control button_onHightU_control = new ButtonSetU(this, string.Format("{0}_button_offHightU", name),
                                                new Thickness(left, top, 0, 0), "ВКЛ.",
                                                45, height_control);
            var button_onHightU_control_wpf = (Button)button_onHightU_control.GetControl();
            button_onHightU_control_wpf.Click += Button_onHightU_Click;
            device_grid.Children.Add(button_onHightU_control_wpf);
            controls.Add("button_offHightU", button_onHightU_control);

            Control button_offHightU_control = new ButtonSetU(this, string.Format("{0}_button_onHightU", name),
                                                            new Thickness(left, top + second_line, 0, 0), "ВЫКЛ.",
                                                            45, height_control);
            var button_offHightU_control_wpf = (Button)button_offHightU_control.GetControl();
            button_offHightU_control_wpf.Click += Button_offHightU_Click;
            device_grid.Children.Add(button_offHightU_control_wpf);
            controls.Add("button_onHightU", button_offHightU_control);

            // -----------------------------------------------
            // ------- Установка напряжения

            left += 55;

            var label_setU_control = new LabelControl(this, string.Format("{0}_label_setU", name), new Thickness(left, top-2, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_setU_control.GetControl());
            controls.Add("label_setU", label_setU_control);

            left += 20;

            Control SetVol_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_set_U", name), new Thickness(left, top, 0, 0),
                                            70, height_control, true, 2600, 0, 10);

            var UpDown_setu_wpf = (CommonNumericUpDown<int>)SetVol_UpDown.GetControl();
            UpDown_setu_wpf.KeyDown += UpDown_setu_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_setu_wpf);
            controls.Add("SetVol_UpDown", SetVol_UpDown);

            Control button_setU_control = new ButtonSetU(this, string.Format("{0}_button_setU", name),
                                                            new Thickness(left+7, top + second_line, 0, 0), "Уст.",
                                                            52, height_control);
            var button_setU_control_wpf = (Button)button_setU_control.GetControl();
            button_setU_control_wpf.Click += Button_setU_Click;
            device_grid.Children.Add(button_setU_control_wpf);
            controls.Add("button_setU", button_setU_control);


            left += 65;

            var label_V_control = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left + 7, top-2, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control.GetControl());
            controls.Add("label_V", label_V_control);

            // -------------------------------------
            // ------- Отображение информации напряжение и ток

            left += 35;

            var label_U_control = new LabelControl(this, string.Format("{0}_label_U", name), new Thickness(left - 3, top-2, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_U_control.GetControl());
            controls.Add("label_U", label_U_control);

            var label_I_control = new LabelControl(this, string.Format("{0}_label_I", name), new Thickness(left - 1, top + second_line-2, 0, 0), "I", true);
            device_grid.Children.Add((Label)label_I_control.GetControl());
            controls.Add("label_I", label_I_control);

            left += 20;

            var text_box_UValue_control = new TextBoxDevice(this, string.Format("{0}_textbox_UValue", name),
                                                        new Thickness(left, top, 0, 0),
                                                        52, height_control, true);

            var textbox_valueU_control_wpf = (TextBox)text_box_UValue_control.GetControl();
            textbox_valueU_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            textbox_valueU_control_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_valueU_control_wpf);
            controls.Add("textbox_UValue", text_box_UValue_control);

            var text_box_IValue_control = new TextBoxDevice(this, string.Format("{0}_text_box_IValue", name),
                                                        new Thickness(left, top + second_line, 0, 0),
                                                        52, height_control, true);
            var text_box_IValue_control_wpf = (TextBox)text_box_IValue_control.GetControl();
            text_box_IValue_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(text_box_IValue_control_wpf);
            controls.Add("textbox_IValue", text_box_IValue_control);

            left += 55;

            var label_V_control2 = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left, top-2, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control2.GetControl());
            controls.Add("label_V2", label_V_control2);

            var label_mkA_control = new LabelControl(this, string.Format("{0}_label_mkA", name), new Thickness(left, top + second_line-2, 0, 0), "мкА");
            device_grid.Children.Add((Label)label_mkA_control.GetControl());
            controls.Add("label_mkA", label_mkA_control);

            //-----------------------------------------------------------------------
            // ------- Отображение информации статус напряжения и тока
            left += 40;

            Control rectangle_status_HightU_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_HightU", name),
                                                                new Thickness(left, top, 0, 0),
                                                                50, height_control);
            device_grid.Children.Add((Rectangle)rectangle_status_HightU_control.GetControl());
            controls.Add("rectangle_status_HightU", rectangle_status_HightU_control);

            var label_status_HightU_coltrol = new LabelControl(this, string.Format("{0}_label_status_HightU", name), new Thickness(left+1, top-2, 0, 0), "-");
            device_grid.Children.Add((Label)label_status_HightU_coltrol.GetControl());
            controls.Add("label_status_HightU", label_status_HightU_coltrol);


            Control rectangle_status_protectI_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_protectI", name),
                                                                            new Thickness(left, top + second_line, 0, 0),
                                                                            50, height_control);
            device_grid.Children.Add((Rectangle)rectangle_status_protectI_control.GetControl());
            controls.Add("rectangle_status_protectI", rectangle_status_protectI_control);

            var label_status_protectI_control = new LabelControl(this, string.Format("{0}_label_status_protectI", name), new Thickness(left+7, top + second_line-2, 0, 0), "-");
            device_grid.Children.Add((Label)label_status_protectI_control.GetControl());
            controls.Add("label_status_protectI", label_status_protectI_control);

            //-----------------------------------------------------------------------
            // ------- статус выхода
            left += 60;

            Control rectangle_status_HV_EN = new RectangleDevice(this, string.Format("{0}_rectangle_status_HV_EN", name),
                                                    new Thickness(left, top + 6, 0, 0),
                                                    60, 50);
            device_grid.Children.Add((Rectangle)rectangle_status_HV_EN.GetControl());
            controls.Add("rectangle_status_HV_EN", rectangle_status_HV_EN);

            var label_status_HV_EN_control = new LabelControl(this, string.Format("{0}_label_status_HV_EN", name), new Thickness(left + 12, top + 16, 0, 0), "-");
            device_grid.Children.Add((Label)label_status_HV_EN_control.GetControl());
            controls.Add("label_status_HV_EN", label_status_HV_EN_control);
            // -------
            _form.MainGrid.Children.Add(device_grid);

        }

        private void UpDown_setu_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage();
        }

        public override void SendMessage()
        {
            var set_value = (CommonNumericUpDown<int>)controls["SetVol_UpDown"].WPFControl;

            int send_msg = 0;
            int register = 0;
            try
            {
                send_msg = (int)set_value.Value;
                register = 1000;
            }
            catch
            {
                return;
            }

            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        public void ChangeStateEvent()
        {
            var recieve_value = (TextBox)controls["textbox_UValue"].WPFControl;
            var set_value = (CommonNumericUpDown<int>)controls["SetVol_UpDown"].WPFControl;

            int recieve_value_int = 0;
            int set_value_int = 0;

            try
            {
                recieve_value_int = Convert.ToInt32(recieve_value.Text);
                set_value_int = (int)set_value.Value;
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

            if (Math.Abs(recieve_value_int - set_value_int) > 100)
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
        private void Button_setU_Click(object sender, RoutedEventArgs e)
        {
            SendMessage();
        }

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

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            ChangeStateEvent();
        }

        private void Button_offHightU_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 1009;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        private void Button_onHightU_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 1;
            int register = 1009;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }
    }

    class DeviceSync : Device
    {
        public DeviceSync(string id, int shift_hor, int shift_vert, string c_label, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "Sync";
            CLabel = c_label;
            IsEnabled = true;
        }

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:
                    var textb_ch1_del = (TextBox)controls["textbox_ch1_del"].WPFControl;
                    var textb_ch2_del = (TextBox)controls["textbox_ch2_del"].WPFControl;
                    var textb_ch3_del = (TextBox)controls["textbox_ch3_del"].WPFControl;

                    var UpDown_ch1_del = (IntegerUpDown)controls["UpDown_ch1_del"].WPFControl;
                    var UpDown_ch2_del = (IntegerUpDown)controls["UpDown_ch2_del"].WPFControl;
                    var UpDown_ch3_del = (IntegerUpDown)controls["UpDown_ch3_del"].WPFControl;

                    int set_reg_buf;

                    int delay_buf = 0;

                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            delay_buf = (Convert.ToInt32(msg.Value[0]) * 25) / 1000;  // ch 1 del lsb, (25 ns * x)/1000 = 1 us
                            textb_ch1_del.Text = delay_buf.ToString();

                            delay_buf = (Convert.ToInt32(msg.Value[4]) * 25) / 1000;  // ch 2 del lsb, (25 ns * x)/1000 = 1 us
                            textb_ch2_del.Text = delay_buf.ToString();

                            delay_buf = (Convert.ToInt32(msg.Value[8]) * 25) / 1000;  // ch 3 del lsb, (25 ns * x)/1000 = 1 us
                            textb_ch3_del.Text = delay_buf.ToString();

                            set_reg_buf = (Convert.ToInt32(msg.Value[0]) * 25) / 1000;
                            if (UpDown_ch1_del.Value == null)
                                UpDown_ch1_del.Value = set_reg_buf;

                            set_reg_buf = (Convert.ToInt32(msg.Value[4]) * 25) / 1000;
                            if (UpDown_ch2_del.Value == null)
                                UpDown_ch2_del.Value = set_reg_buf;

                            set_reg_buf = (Convert.ToInt32(msg.Value[8]) * 25) / 1000;
                            if (UpDown_ch3_del.Value == null)
                                UpDown_ch3_del.Value = set_reg_buf;

                        });
                    break;
            }

        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 1;
            var second_line = 35;
            var third_line = 70;
            var fourth_line = 105;
            var top = 8;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 150;
            var height_grid = 160;

            //var weight_control = 50;
            var height_control = 25;

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
                                            new Thickness(weight_grid * ShiftHor / 10, (height_grid * ShiftVert) / 50, 0, 0),
                                Colors.MistyRose, weight_grid + 55, height_grid); //MistyRose
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);
            // -----------------------------------------------
            // ------- Установка Ch 1 delay

            var label_ch1_control = new LabelControl(this, string.Format("{0}_label_ch1", name), new Thickness(left, top-2, 0, 0), "xT1", true);
            device_grid.Children.Add((Label)label_ch1_control.GetControl());
            controls.Add("label_ch1", label_ch1_control);

            left += 32;

            Control SetDel_1_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_ch1_del", name), new Thickness(left, top, 0, 0),
                                            75, height_control, true, 50000, 0, 1);

            var UpDown_ch1_del_wpf = (CommonNumericUpDown<int>)SetDel_1_UpDown.GetControl();
            UpDown_ch1_del_wpf.KeyDown += UpDown_ch1_del_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_ch1_del_wpf);
            controls.Add("UpDown_ch1_del", SetDel_1_UpDown);

            left += 75;
            var label_ch1_us_control = new LabelControl(this, string.Format("{0}_label_ch1_us", name), new Thickness(left, top - 3, 0, 0), "мкс", false);
            device_grid.Children.Add((Label)label_ch1_us_control.GetControl());
            controls.Add("label_ch1_us", label_ch1_us_control);

            // ------- Чтение Ch 1 delay
            left += 35;

            var textbox_ch1_del = new TextBoxDevice(this, string.Format("{0}_textbox_ch1_del", name),
                                            new Thickness(left, top, 0, 0),
                                            52, height_control, true);

            var textbox_ch1_del_wpf = (TextBox)textbox_ch1_del.GetControl();
            textbox_ch1_del_wpf.Foreground = new SolidColorBrush(Colors.Green);
            //textbox_ch1_del_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_ch1_del_wpf);
            controls.Add("textbox_ch1_del", textbox_ch1_del);
            // -----------------------------------------------
            // ------- Установка Ch 2 delay
            left = 1;

            var label_ch2_control = new LabelControl(this, string.Format("{0}_label_ch2", name), new Thickness(left, (top + second_line) - 2, 0, 0), "xT2", true);
            device_grid.Children.Add((Label)label_ch2_control.GetControl());
            controls.Add("label_ch2", label_ch2_control);

            left += 32;

            Control SetDel_2_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_ch2_del", name), new Thickness(left, top+second_line, 0, 0),
                                            75, height_control, true, 50000, 0, 1);

            var UpDown_ch2_del_wpf = (CommonNumericUpDown<int>)SetDel_2_UpDown.GetControl();
            UpDown_ch2_del_wpf.KeyDown += UpDown_ch2_del_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_ch2_del_wpf);
            controls.Add("UpDown_ch2_del", SetDel_2_UpDown);

            left += 75;
            var label_ch2_us_control = new LabelControl(this, string.Format("{0}_label_ch2_us", name), new Thickness(left, (top+second_line) - 3, 0, 0), "мкс", false);
            device_grid.Children.Add((Label)label_ch2_us_control.GetControl());
            controls.Add("label_ch2_us", label_ch2_us_control);

            // ------- Чтение Ch 2 delay
            left += 35;

            var textbox_ch2_del = new TextBoxDevice(this, string.Format("{0}_textbox_ch2_del", name),
                                            new Thickness(left, top+second_line, 0, 0),
                                            52, height_control, true);

            var textbox_ch2_del_wpf = (TextBox)textbox_ch2_del.GetControl();
            textbox_ch2_del_wpf.Foreground = new SolidColorBrush(Colors.Green);
            //textbox_ch1_del_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_ch2_del_wpf);
            controls.Add("textbox_ch2_del", textbox_ch2_del);
            // -----------------------------------------------
            // -----------------------------------------------
            // ------- Установка Ch 3 delay
            left = 1;
            var label_ch3_control = new LabelControl(this, string.Format("{0}_label_ch3", name), new Thickness(left, (top+third_line) - 2, 0, 0), "xT3", true);
            device_grid.Children.Add((Label)label_ch3_control.GetControl());
            controls.Add("label_ch3", label_ch3_control);

            left += 32;

            Control SetDel_3_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_ch3_del", name), new Thickness(left, top + third_line, 0, 0),
                                            75, height_control, true, 50000, 0, 1);

            var UpDown_ch3_del_wpf = (CommonNumericUpDown<int>)SetDel_3_UpDown.GetControl();
            UpDown_ch3_del_wpf.KeyDown += UpDown_ch3_del_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_ch3_del_wpf);
            controls.Add("UpDown_ch3_del", SetDel_3_UpDown);

            left += 75;
            var label_ch3_us_control = new LabelControl(this, string.Format("{0}_label_ch3_us", name), new Thickness(left, (top+third_line) - 3, 0, 0), "мкс", false);
            device_grid.Children.Add((Label)label_ch3_us_control.GetControl());
            controls.Add("label_ch3_us", label_ch3_us_control);

            // ------- Чтение Ch 3 delay
            left += 35;

            var textbox_ch3_del = new TextBoxDevice(this, string.Format("{0}_textbox_ch3_del", name),
                                            new Thickness(left, top+third_line, 0, 0),
                                            52, height_control, true);

            var textbox_ch3_del_wpf = (TextBox)textbox_ch3_del.GetControl();
            textbox_ch3_del_wpf.Foreground = new SolidColorBrush(Colors.Green);
            //textbox_ch1_del_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_ch3_del_wpf);
            controls.Add("textbox_ch3_del", textbox_ch3_del);
            // -----------------------------------------------
            // кнопка уст.
            left = 32;

            Control button_set_control = new ButtonSetU(this, string.Format("{0}_button_set_control", name),
                                    new Thickness(left, top + fourth_line, 0, 0), "Установить",
                                    75, height_control);
            var button_set_control_wpf = (Button)button_set_control.GetControl();
            button_set_control_wpf.Click += Button_set_control_wpf_Click;           ;
            device_grid.Children.Add(button_set_control_wpf);
            controls.Add("button_set_control", button_set_control);

            _form.MainGrid.Children.Add(device_grid);


        }

        private void Button_set_control_wpf_Click(object sender, RoutedEventArgs e)
        {
            SendMessage(1);
            SendMessage(2);
            SendMessage(3);
        }

        private void UpDown_ch3_del_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage(3);
        }

        private void UpDown_ch2_del_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage(2);
        }

        private void UpDown_ch1_del_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage(1);
        }

        private void SendMessage(int param)
        {
            var SetDel_1_UpDown = (CommonNumericUpDown<int>)controls["UpDown_ch1_del"].WPFControl;
            var SetDel_2_UpDown = (CommonNumericUpDown<int>)controls["UpDown_ch2_del"].WPFControl;
            var SetDel_3_UpDown = (CommonNumericUpDown<int>)controls["UpDown_ch3_del"].WPFControl;

            int send_msg = 0;
            int register = 0;

            try
            {

                switch (param)
                {
                    case 1: // задержку к1
                        send_msg = (((int)SetDel_1_UpDown.Value) * 1000) / 25 ;
                        register = 1000;
                        break;
                    //---
                    case 2: // задержку к2
                        send_msg = (((int)SetDel_2_UpDown.Value) * 1000) / 25;
                        register = 1004;
                        break;
                    //---
                    case 3: // задержку к3
                        send_msg = (((int)SetDel_3_UpDown.Value) * 1000) / 25;
                        register = 1008;
                        break;               
                    //---
                    default: break;
                }
            }
            catch { return; }
            // отправка в очередь
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
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
    }

    class DeviceIP702 : Device
    {
        public DeviceIP702(int shift_hor, int shift_vert, string c_label, EventHandler<Dictionary<string,int>> send_msg)
        {
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgIP702Manager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "IP";
            CLabel = c_label;
            IsEnabled = true;
        }

        private event EventHandler<Dictionary<string, int>> send_msg;

        public EventHandler<Dictionary<string, int>> SendMsgIP702Manager
        {
            get { return send_msg; }
            set { send_msg += value; }
        }

        public void GetMsgFromDevice(object sender, string[] msg)
        {   // действия при полученнии данных от устройства
            var textbox_rd_U = (TextBox)controls["textbox_rd_U"].WPFControl;
            var status_control = (Rectangle)controls["status_control"].WPFControl;
            var status_HV_EN = (Rectangle)controls["status_HV_EN"].WPFControl;

            //var setV_UpDown = (IntegerUpDown)controls["SetVol_UpDown"].WPFControl;
            var int_label = (Label)controls["int_label"].WPFControl;
            var short_label = (Label)controls["short_label"].WPFControl;
            var heat_label = (Label)controls["heat_label"].WPFControl;
            var load_label = (Label)controls["load_label"].WPFControl;
            var label_status_HV_EN = (Label)controls["label_status_HV_EN"].WPFControl;

            var button_onHightU = (Button)controls["button_onHightU"].WPFControl;
            var button_offHightU = (Button)controls["button_offHightU"].WPFControl;

            List<bool> status = new List<bool>();

            string SrcStatusByte = msg[4]; // сохр. статус байт

                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            textbox_rd_U.Text = msg[1];
                            // обработка байтов ошибок и информации
                            if (SrcStatusByte.Length == 17)
                            {
                                // сост. выхода
                                if (SrcStatusByte[6] == '1')
                                {
                                    button_onHightU.IsEnabled = false;
                                    button_offHightU.IsEnabled = true;
                                    label_status_HV_EN.Content = "Вкл.";   
                                    status_HV_EN.Fill = new SolidColorBrush(Colors.LimeGreen);
                                }
                                else
                                {
                                    button_onHightU.IsEnabled = true;
                                    button_offHightU.IsEnabled = false;
                                    label_status_HV_EN.Content = "Выкл.";
                                    status_HV_EN.Fill = new SolidColorBrush(Colors.LightGray);
                                }
                                // ---
                                // байт ошибок
                                if (SrcStatusByte[10] == '1')
                                {
                                    int_label.Content = "блок.!";
                                    var x = true;
                                    status.Add(x);
                                }
                                else
                                {
                                    int_label.Content = "блок. снята";
                                    var x = false;
                                    status.Add(x);
                                }
                                if (SrcStatusByte[13] == '1')
                                {
                                    int_label.Content = "обрыв";
                                    var x = true;
                                    status.Add(x);
                                }
                                else if (SrcStatusByte[14] == '1')
                                {
                                    int_label.Content = "кз в нагр.";
                                    var x = true;
                                    status.Add(x);
                                }
                                else
                                {
                                    int_label.Content = "нагр. ок";
                                    var x = false;
                                    status.Add(x);
                                }
                                if (SrcStatusByte[16] == '1')
                                {
                                    heat_label.Content = "перегрев";
                                    var x = true;
                                    status.Add(x);
                                }
                                else
                                {
                                    heat_label.Content = "темп. ок";
                                    var x = false;
                                    status.Add(x);
                                }
                                var y = true;
                                if(status.Contains(y))
                                 status_control.Fill = new SolidColorBrush(Colors.Coral);
                                else
                                 status_control.Fill = new SolidColorBrush(Colors.LimeGreen);
                            }
                        });

        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 1;
            var second_line = 35;
            var third_line = 70;
            var fourth_line = 105;
            var top = 8;
            var name = Type;

            var weight_grid = 450;
            var height_grid = 100;

            //var weight_control = 50;
            var height_control = 25;

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
                                            new Thickness((weight_grid * ShiftHor) / 50, height_grid * ShiftVert / 10, 0, 0),
                                Colors.PapayaWhip, weight_grid-20, height_grid-25); 
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);
            // -----------------------------------------------
            // ------- кнопки вкл/выкл
            left += 10;

            Control button_onHightU_control = new ButtonSetU(this, string.Format("{0}_button_offHightU", name),
                                                new Thickness(left, top, 0, 0), "ВКЛ.",
                                                45, height_control);
            var button_onHightU_control_wpf = (Button)button_onHightU_control.GetControl();
            button_onHightU_control_wpf.Click += Button_onHightU_control_wpf_Click;
            device_grid.Children.Add(button_onHightU_control_wpf);
            controls.Add("button_offHightU", button_onHightU_control);

            Control button_offHightU_control = new ButtonSetU(this, string.Format("{0}_button_onHightU", name),
                                                            new Thickness(left, top + second_line, 0, 0), "ВЫКЛ.",
                                                            45, height_control);
            var button_offHightU_control_wpf = (Button)button_offHightU_control.GetControl();
            button_offHightU_control_wpf.Click += Button_offHightU_control_wpf_Click;
            device_grid.Children.Add(button_offHightU_control_wpf);
            controls.Add("button_onHightU", button_offHightU_control);

            // -----------------------------------------------
            // уст. и чтение напряжения

            left += 57;

            var label_U_control = new LabelControl(this, string.Format("{0}_label_U", name), new Thickness(left - 3, top-2, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_U_control.GetControl());
            controls.Add("label_U", label_U_control);

            left += 17;

            Control SetU_UpDown = new NumUpDownDevice(this, string.Format("{0}_SetU_UpDown", name), new Thickness(left, top, 0, 0),
                                            75, height_control, true, 15000, 0, 100);

            var UpDownU_wpf = (CommonNumericUpDown<int>)SetU_UpDown.GetControl();
            UpDownU_wpf.KeyDown += UpDownU_wpf_KeyDown; ;  // confirm by enter pressed
            device_grid.Children.Add(UpDownU_wpf);
            controls.Add("UpDownU_wpf", SetU_UpDown);

            Control button_setU = new ButtonSetU(this, string.Format("{0}_button_setU", name),
                                                new Thickness(left+7, top + second_line, 0, 0), "Уст.",
                                                45, height_control);
            var button_setU_wpf = (Button)button_setU.GetControl();
            button_setU_wpf.Click += Button_setU_wpf_Click;
            device_grid.Children.Add(button_setU_wpf);
            controls.Add("button_setU", button_setU);

            // ------- Чтение U
            left += 105;

            var textbox_rd_U = new TextBoxDevice(this, string.Format("{0}_textbox_rd_U", name),
                                            new Thickness(left, top+15, 0, 0),
                                            75, height_control, true);

            var textbox_rd_U_wpf = (TextBox)textbox_rd_U.GetControl();
            textbox_rd_U_wpf.Foreground = new SolidColorBrush(Colors.Green);
            //textbox_ch1_del_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_rd_U_wpf);
            controls.Add("textbox_rd_U", textbox_rd_U);

            left += 75;

            var label_V= new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left, top + 13, 0, 0), "В");
            device_grid.Children.Add((Label)label_V.GetControl());
            controls.Add("label_V", label_V);
            //-----------------------------------------------------------------------
            // ------- Отображение статус информации 
            left += 35;

            Control status_control = new RectangleDevice(this, string.Format("{0}_status_control", name),
                                                                new Thickness(left, top+5, 0, 0),
                                                                50, 50);
            device_grid.Children.Add((Rectangle)status_control.GetControl());
            controls.Add("status_control", status_control);

            // interlock label
            var int_label = new LabelControl(this, string.Format("{0}_int_label", name), new Thickness(left-2, top-2, 0, 0), "-",false,11);
            device_grid.Children.Add((Label)int_label.GetControl());
            controls.Add("int_label", int_label);

            // load label
            var load_label = new LabelControl(this, string.Format("{0}_load_label", name), new Thickness(left-2, top+10, 0, 0), "-", false, 11);
            device_grid.Children.Add((Label)load_label.GetControl());
            controls.Add("load_label", load_label);

            // short label
            var short_label = new LabelControl(this, string.Format("{0}_short_label", name), new Thickness(left-2, top + 22, 0, 0), "-", false, 11);
            device_grid.Children.Add((Label)short_label.GetControl());
            controls.Add("short_label", short_label);

            // heat label
            var heat_label = new LabelControl(this, string.Format("{0}_heat_label", name), new Thickness(left-2, top + 34, 0, 0), "-", false, 11);
            device_grid.Children.Add((Label)heat_label.GetControl());
            controls.Add("heat_label", heat_label);
            //-----------------------------------------------------------------------
            // ------- статус выхода
            left += 60;

            Control rectangle_status_HV_EN = new RectangleDevice(this, string.Format("{0}_rectangle_status_HV_EN", name),
                                                    new Thickness(left, top + 5, 0, 0),
                                                    60, 50);
            device_grid.Children.Add((Rectangle)rectangle_status_HV_EN.GetControl());
            controls.Add("status_HV_EN", rectangle_status_HV_EN);

            var label_status_HV_EN_control = new LabelControl(this, string.Format("{0}_label_status_HV_EN", name), new Thickness(left + 12, top + 15, 0, 0), "-");
            device_grid.Children.Add((Label)label_status_HV_EN_control.GetControl());
            controls.Add("label_status_HV_EN", label_status_HV_EN_control);
            // -------

            _form.MainGrid.Children.Add(device_grid);
        }

        private void UpDownU_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            // by ENTER key
            if (e.Key == Key.Enter) SendMessage();
        }

        private void Button_setU_wpf_Click(object sender, RoutedEventArgs e)
        {
            // уст. напряжения
            SendMessage();
        }

        private void Button_offHightU_control_wpf_Click(object sender, RoutedEventArgs e)
        {
            // выкл. высокого напряжения
            var dict = new Dictionary<string, int>();
            dict.Add("set_output", 0);
            SendMsgIP702Manager(this, dict);
        }

        private void Button_onHightU_control_wpf_Click(object sender, RoutedEventArgs e)
        {
            // вкл. высокого напряжения
            var dict = new Dictionary<string, int>();
            dict.Add("set_output", 1);
            SendMsgIP702Manager(this, dict);
        }

        public override void SendMessage()
        {
            var SetU_UpDown = (CommonNumericUpDown<int>)controls["UpDownU_wpf"].WPFControl;

            var dict = new Dictionary<string, int>();
            int V2set = (int)SetU_UpDown.Value;
            dict.Add("set_voltage", V2set);

            SendMsgIP702Manager(this, dict);
        }

        public override void SaveState()
        {

        }
    }

}
