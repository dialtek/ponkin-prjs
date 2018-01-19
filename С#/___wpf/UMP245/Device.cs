using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Controls;
using System.Windows.Threading;
using System.Threading;

namespace UMP245
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
                    var rectangle_status_HV_EN = (Rectangle)controls["rectangle_status_HV_EN"].WPFControl;

                    var label_status_protectI = (Label)controls["label_status_protectI"].WPFControl;
                    var label_status_HightU = (Label)controls["label_status_HightU"].WPFControl;
                    var label_status_HV_EN = (Label)controls["label_status_HV_EN"].WPFControl;

                    var button_onHightU = (Button)controls["button_onHightU"].WPFControl;
                    var button_offHightU = (Button)controls["button_offHightU"].WPFControl;

                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            label_U.Text = FormatOutput(msg.Value[5]);

                            //// добавление устрйоства в опасный список если есть высокое
                            //if (Convert.ToUInt16(msg.Value[5]) > hv_status.danger_lvl)
                            //        hv_status.add_element(CLabel);
                            //    else hv_status.del_element(CLabel);

                            label_I.Text = FormatOutput(msg.Value[6]);

                            var reg_9 = Convert.ToInt32(msg.Value[9]);

                            if (reg_9 == 1)
                            {
                                button_onHightU.IsEnabled = true;
                                button_offHightU.IsEnabled = false;
                                rectangle_status_HV_EN.Fill = new SolidColorBrush(Colors.LimeGreen);
                                label_status_HV_EN.Content = "ВКЛ.";
                            }
                            else
                            {
                                button_onHightU.IsEnabled = false;
                                button_offHightU.IsEnabled = true;
                                rectangle_status_HV_EN.Fill = new SolidColorBrush(Colors.LightGray);
                                label_status_HV_EN.Content = "ВЫКЛ.";
                            }

                            var reg_11 = Convert.ToInt32(msg.Value[11]);
                            rectangle_status_HightU.Fill = new SolidColorBrush(reg_11 == 1 ? Colors.LimeGreen : Colors.LightGray);
                            label_status_HightU.Content = reg_11 == 1 ? "Тумблер Вкл." : "Тумблер Выкл.";

                            var reg_12 = Convert.ToInt32(msg.Value[12]);
                            rectangle_status_protectI.Fill = new SolidColorBrush(reg_12 == 0 ? Colors.LimeGreen : Colors.Red);
                            label_status_protectI.Content = reg_12 == 0 ? "Ок" : "I LIM";

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
            var left = 5;
            var second_line = 35;
            //var new_line = 35;
            var top = 20;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 480;
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
                                            new Thickness(weight_grid * ShiftHor + 5, height_grid * ShiftVert + 40, 0, 0),
                                Colors.WhiteSmoke, weight_grid + 10, height_grid); //WhiteSmoke
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);

            // ------- Информация о железяке
            //left += 10;

            //var label_С_control = new LabelControl(this, string.Format("{0}_label_С", name), new Thickness(left, top, 0, 0), CLabel, true);
            //device_grid.Children.Add((Label)label_С_control.GetControl());
            //controls.Add("label_С", label_С_control);

            //var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name), new Thickness(left, top + 20, 0, 0), "ID " + Id, false, 10);
            //device_grid.Children.Add((Label)label_id_control.GetControl());
            //controls.Add("label_id", label_id_control);

            //var checkbox_disable_control = new CheckBoxDevice(this, string.Format("{0}_checkbox_disable", name), new Thickness(left + 5, top + 45, 0, 0), "");
            //var checkbox_disable_control_wpf = (CheckBox)checkbox_disable_control.GetControl();
            //checkbox_disable_control_wpf.Unchecked += Checkbox_disable_Unchecked;
            //checkbox_disable_control_wpf.Checked += Checkbox_disable_wpf_Checked;
            //device_grid.Children.Add(checkbox_disable_control_wpf);
            //controls.Add("checkbox_disable", checkbox_disable_control);

            // -----------------------------------------------
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

            var label_setU_control = new LabelControl(this, string.Format("{0}_label_setU", name), new Thickness(left, top, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_setU_control.GetControl());
            controls.Add("label_setU", label_setU_control);

            left += 20;

            var textbox_U_control = new TextBoxDevice(this, string.Format("{0}_textbox_setU", name),
                                                        new Thickness(left, top + 5, 0, 0),
                                                        52, height_control);
            var textbox_setU_control_wpf = (TextBox)textbox_U_control.GetControl();
            textbox_setU_control_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_setU_control_wpf);
            controls.Add("textbox_setU", textbox_U_control);

            Control button_setU_control = new ButtonSetU(this, string.Format("{0}_button_setU", name),
                                                            new Thickness(left, top + second_line, 0, 0), "Уст.",
                                                            52, height_control);
            var button_setU_control_wpf = (Button)button_setU_control.GetControl();
            button_setU_control_wpf.Click += Button_setU_Click;
            device_grid.Children.Add(button_setU_control_wpf);
            controls.Add("button_setU", button_setU_control);


            left += 45;

            var label_V_control = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left + 7, top, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control.GetControl());
            controls.Add("label_V", label_V_control);

            // -------------------------------------
            // ------- Отображение информации напряжение и ток

            left += 40;

            var label_U_control = new LabelControl(this, string.Format("{0}_label_U", name), new Thickness(left - 3, top, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_U_control.GetControl());
            controls.Add("label_U", label_U_control);

            var label_I_control = new LabelControl(this, string.Format("{0}_label_I", name), new Thickness(left - 1, top + second_line, 0, 0), "I", true);
            device_grid.Children.Add((Label)label_I_control.GetControl());
            controls.Add("label_I", label_I_control);

            left += 20;

            var text_box_UValue_control = new TextBoxDevice(this, string.Format("{0}_textbox_UValue", name),
                                                        new Thickness(left, top + 5, 0, 0),
                                                        52, height_control, true);

            var textbox_valueU_control_wpf = (TextBox)text_box_UValue_control.GetControl();
            textbox_valueU_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            textbox_valueU_control_wpf.TextChanged += TextBox_TextChanged;
            device_grid.Children.Add(textbox_valueU_control_wpf);
            controls.Add("textbox_UValue", text_box_UValue_control);

            var text_box_IValue_control = new TextBoxDevice(this, string.Format("{0}_text_box_IValue", name),
                                                        new Thickness(left, top + second_line + 5, 0, 0),
                                                        52, height_control, true);
            var text_box_IValue_control_wpf = (TextBox)text_box_IValue_control.GetControl();
            text_box_IValue_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(text_box_IValue_control_wpf);
            controls.Add("textbox_IValue", text_box_IValue_control);

            left += 55;

            var label_V_control2 = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left, top, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control2.GetControl());
            controls.Add("label_V2", label_V_control2);

            var label_mkA_control = new LabelControl(this, string.Format("{0}_label_mkA", name), new Thickness(left, top + second_line, 0, 0), "мкА");
            device_grid.Children.Add((Label)label_mkA_control.GetControl());
            controls.Add("label_mkA", label_mkA_control);

            //-----------------------------------------------------------------------
            // ------- Отображение информации статус напряжения и тока
            left += 50;

            Control rectangle_status_HightU_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_HightU", name),
                                                                new Thickness(left, top + 4, 0, 0),
                                                                100, height_control);
            device_grid.Children.Add((Rectangle)rectangle_status_HightU_control.GetControl());
            controls.Add("rectangle_status_HightU", rectangle_status_HightU_control);

            var label_status_HightU_coltrol = new LabelControl(this, string.Format("{0}_label_status_HightU", name), new Thickness(left, top, 0, 0), "Вкл.");
            device_grid.Children.Add((Label)label_status_HightU_coltrol.GetControl());
            controls.Add("label_status_HightU", label_status_HightU_coltrol);


            Control rectangle_status_protectI_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_protectI", name),
                                                                            new Thickness(left, top + second_line + 3, 0, 0),
                                                                            100, height_control);
            device_grid.Children.Add((Rectangle)rectangle_status_protectI_control.GetControl());
            controls.Add("rectangle_status_protectI", rectangle_status_protectI_control);

            var label_status_protectI_control = new LabelControl(this, string.Format("{0}_label_status_protectI", name), new Thickness(left + 35, top + second_line, 0, 0), "Ок.");
            device_grid.Children.Add((Label)label_status_protectI_control.GetControl());
            controls.Add("label_status_protectI", label_status_protectI_control);

            //-----------------------------------------------------------------------
            // ------- статус выхода
            left += 120;

            Control rectangle_status_HV_EN = new RectangleDevice(this, string.Format("{0}_rectangle_status_HV_EN", name),
                                                    new Thickness(left, top + 8, 0, 0),
                                                    60, 50);
            device_grid.Children.Add((Rectangle)rectangle_status_HV_EN.GetControl());
            controls.Add("rectangle_status_HV_EN", rectangle_status_HV_EN);

            var label_status_HV_EN_control = new LabelControl(this, string.Format("{0}_label_status_HV_EN", name), new Thickness(left + 9, top + 18, 0, 0), "ВКЛ.");
            device_grid.Children.Add((Label)label_status_HV_EN_control.GetControl());
            controls.Add("label_status_HV_EN", label_status_HV_EN_control);

            //--------- кнопки вкл/выкл



            #region
            //// это создание контрола Grid, то есть основное полотно, на которое дальше будет наносится другие контролы этого девайса
            //Control grid = new GridDevice(this, string.Format("{0}_grid", name), new Thickness(200 * ShiftHor, 200 * ShiftVert, 0, 0), 
            //                                Colors.Transparent, weight, height);
            //var device_grid = (Grid) grid.GetControl();
            //controls.Add("grid", grid);

            //var label_status_HightU_coltrol = new LabelControl(this, string.Format("{0}_label_status_HightU", name), new Thickness(left, top - 5, 0, 0), "Высокое напр");
            //device_grid.Children.Add( (Label) label_status_HightU_coltrol.GetControl() );
            //controls.Add("label_status_HightU", label_status_HightU_coltrol);

            //Control rectangle_status_HightU_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_HightU", name), new Thickness(left + second_column, top, 0, 0));
            //device_grid.Children.Add((Rectangle)rectangle_status_HightU_control.GetControl());
            //controls.Add("rectangle_status_HightU", rectangle_status_HightU_control);

            //top = top + new_line;

            //Control rectangle_status_protectI_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_protectI", name), new Thickness(left + second_column, top, 0, 0));
            //device_grid.Children.Add((Rectangle)rectangle_status_protectI_control.GetControl());
            //controls.Add("rectangle_status_protectI", rectangle_status_protectI_control);

            //var label_protectI_control = new LabelControl(this, string.Format("{0}_label_protectI", name), new Thickness(left, top - 5, 0, 0), "Защита по току");
            //device_grid.Children.Add((Label)label_protectI_control.GetControl());
            //controls.Add("label_protectI", label_protectI_control);

            //top = top + new_line;

            //var label_U_control = new LabelControl(this, string.Format("{0}_label_U", name), new Thickness(left, top, 0, 0), "Напряжение");
            //device_grid.Children.Add((Label)label_U_control.GetControl());
            //controls.Add("label_U", label_U_control);

            //var label_valueU_contol = new LabelControl(this, string.Format("{0}_label_valueU", name), new Thickness(left + second_column, top, 0, 0), "U_value");
            //var label_valueU = (Label)label_valueU_contol.GetControl();
            //controls.Add("label_valueU", label_valueU_contol);

            //top = top + new_line;

            //var label_I_control = new LabelControl(this, string.Format("{0}_label_I", name), new Thickness(left, top, 0, 0), "Ток");
            //device_grid.Children.Add((Label)label_I_control.GetControl());
            //controls.Add("label_I", label_I_control);

            //var label_valueI_control = new LabelControl(this, string.Format("{0}_label_valueI", name), new Thickness(left + second_column, top, 0, 0), "I value");
            //device_grid.Children.Add((Label)label_valueI_control.GetControl());
            //controls.Add("label_valueI", label_valueI_control);

            //top = top + new_line;

            //var label_setU_control = new LabelControl(this, string.Format("{0}_label_setU", name), new Thickness(left, top, 0, 0), "Устан. напр");
            //device_grid.Children.Add((Label)label_setU_control.GetControl());
            //controls.Add("label_setU", label_setU_control);

            //var label_setUvalue_control = new LabelControl(this, string.Format("{0}_label_setUvalue", name), new Thickness(left + second_column, top, 0, 0), "Set U value");
            //device_grid.Children.Add((Label)label_setUvalue_control.GetControl());
            //controls.Add("label_setUvalue", label_setUvalue_control);

            //top = top + new_line + 5;

            //var text_box_U_control = new TextBoxDevice(this, string.Format("{0}_textbox_setU", name), new Thickness(left, top, 0, 0));
            //device_grid.Children.Add((TextBox)text_box_U_control.GetControl());
            //controls.Add("textbox_setU", text_box_U_control);

            //Control button_setU_control = new ButtonSetU(this, string.Format("{0}_button_setU", name), new Thickness(left + second_column, top, 0, 0));
            //device_grid.Children.Add((Button)button_setU_control.GetControl());
            //controls.Add("button_setU", button_setU_control);

            //        var rb_power_on_control = new RadioButtonDevice(this, string.Format("{0}_rb_on", name),
            //new Thickness(left, 10, 0, 0),
            //string.Format("{0}_rb", name),
            //"On");
            //        var rb_power_on = (RadioButton)rb_power_on_control.GetControl();
            //        controls.Add("rb_on", rb_power_on_control);
            //        var rb_power_off_control = new RadioButtonDevice(this, string.Format("{0}_rb_off", name),
            //            new Thickness(left, 30, 0, 0),
            //            string.Format("{0}_rb", name),
            //            "Off");
            //        var rb_power_off = (RadioButton)rb_power_off_control.GetControl();
            //        controls.Add("rb_off", rb_power_off_control);

            #endregion

            _form.MainGrid.Children.Add(device_grid);


        }

        public override void SendMessage()
        {
            var set_value_U = (TextBox)controls["textbox_setU"].WPFControl;
            int send_msg = 0;
            int register = 1000;
            try
            {
                send_msg = (set_value_U.Text == "") ? Convert.ToInt32("error") : Convert.ToInt32(set_value_U.Text);
                send_msg = (send_msg >= 2200) ? 2200 : send_msg;
                send_msg = (send_msg < 0) ? 0 : send_msg;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        public void ChangeStateEvent()
        {
            var recieve_value = (TextBox)controls["textbox_UValue"].WPFControl;
            var set_value = (TextBox)controls["textbox_setU"].WPFControl;

            int recieve_value_int = 0;
            int set_value_int = 0;

            try
            {
                recieve_value_int = Convert.ToInt32(recieve_value.Text);
                set_value_int = Convert.ToInt32(set_value.Text);
            }
            catch
            {
                _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)delegate ()
                {
                    set_value.Background = new SolidColorBrush(Colors.LightGray);
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

    class DeviceUMPctrl : Device
    {
        public DeviceUMPctrl(string id, int shift_hor, int shift_vert, string c_label, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "UMP";
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

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:

                    var falling_W = (TextBox)controls["textbox_fal"].WPFControl;
                    var reflected_W = (TextBox)controls["textbox_refl"].WPFControl;
                    var rd_status_label = (Label)controls["label_upd"].WPFControl;

                    settings_data.rf_delay = msg.Value[9];  // сохр. задержку ВЧ
                    settings_data.rf_with = msg.Value[10];  // сохр. длит ВЧ
                    var adc_data_ready = msg.Value[13];
                    settings_data.rf_level = msg.Value[14];

                    double buf1, buf2;
                    string dbm_result;

                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            if (adc_data_ready == "1")
                            {
                                // актуальны
                                 if(rd_status_label.Visibility != Visibility.Visible)
                                     rd_status_label.Visibility = Visibility.Visible;
   
                                // пересчет из отсчетов АЦП в дбм для мощн.падающей
                                buf1 = Convert.ToDouble(msg.Value[11]);

                                buf2 = -5.78861E-16 * Math.Pow(buf1, 6);
                                buf2 += 1.67371E-12 * Math.Pow(buf1, 5);
                                buf2 += -1.93543E-9 * Math.Pow(buf1, 4);
                                buf2 += 1.15923E-6 * Math.Pow(buf1, 3);
                                buf2 += -4.012E-4 * Math.Pow(buf1, 2);
                                buf2 += 0.09893 * buf1;
                                buf2 += 35.919;

                                if (buf1 < 12.0) dbm_result = "< +37";
                                else dbm_result = "+" + buf2.ToString("0.00");
                                falling_W.Text = dbm_result;

                                // пересчет из отсчетов АЦП в дбм для мощн.отраж
                                buf1 = Convert.ToDouble(msg.Value[12]);

                                buf2 = -2.171250E-16 * Math.Pow(buf1, 6);
                                buf2 += 7.33E-13 * Math.Pow(buf1, 5);
                                buf2 += -9.93E-10 * Math.Pow(buf1, 4);
                                buf2 += 7.04E-07 * Math.Pow(buf1, 3);
                                buf2 += -2.95E-04 * Math.Pow(buf1, 2);
                                buf2 += 0.08969 * buf1;
                                buf2 += 34.91971;

                                if (buf1 < 25.0) dbm_result = "< +37";
                                else dbm_result = "+" + buf2.ToString("0.00");
                                reflected_W.Text = dbm_result;
                            }
                            else
                            {   // данные не актуальны
                                rd_status_label.Visibility = Visibility.Hidden;
                            }
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
            var left = 5;
            var second_line = 35;
            var top = 20;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 480;
            var height_grid = 80;
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
                                            new Thickness(weight_grid * ShiftHor + 5, height_grid+65 * ShiftVert + 40, 0, 0),
                                Colors.WhiteSmoke, weight_grid + 10, height_grid); //WhiteSmoke
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);

            // -----------------------------------------------
            // ------- Отображение информации падающ

            left += 15;

            var label_fal_control = new LabelControl(this, string.Format("{0}_label_fal", name), new Thickness(left, top, 0, 0), "Падающая", true);
            device_grid.Children.Add((Label)label_fal_control.GetControl());
            controls.Add("label_fal", label_fal_control);

            left += 95;
            var text_box_fal_control = new TextBoxDevice(this, string.Format("{0}_textbox_fal", name),
                                                        new Thickness(left, top + 5, 0, 0),
                                                        65, height_control, true);

            var textbox_fal_control_wpf = (TextBox)text_box_fal_control.GetControl();
            textbox_fal_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(textbox_fal_control_wpf);
            controls.Add("textbox_fal", text_box_fal_control);

            left += 65;
            var label_dbm_control_fal = new LabelControl(this, string.Format("{0}_label_dbm1", name), new Thickness(left, top, 0, 0), "дБм");
            device_grid.Children.Add((Label)label_dbm_control_fal.GetControl());
            controls.Add("label_dbm1", label_dbm_control_fal);

            // отраж

            left += 80;
            var label_refl_control = new LabelControl(this, string.Format("{0}_label_refl", name), new Thickness(left, top, 0, 0), "Отраженная", true);
            device_grid.Children.Add((Label)label_refl_control.GetControl());
            controls.Add("label_refl", label_refl_control);

            left += 105;
            var text_box_refl_control = new TextBoxDevice(this, string.Format("{0}_textbox_refl", name),
                                            new Thickness(left, top + 5, 0, 0),
                                            65, height_control, true);
            left += 100;
            var textbox_refl_control_wpf = (TextBox)text_box_refl_control.GetControl();
            textbox_refl_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(textbox_refl_control_wpf);
            controls.Add("textbox_refl", text_box_refl_control);
            
            left = 430;
            var label_dbm_control_refl = new LabelControl(this, string.Format("{0}_label_dbm2", name), new Thickness(left, top, 0, 0), "дБм");
            device_grid.Children.Add((Label)label_dbm_control_refl.GetControl());
            controls.Add("label_dbm2", label_dbm_control_refl);

            left = 20;
            //статус актуальных данных
            var label_upd_control = new LabelControl(this, string.Format("{0}_label_upd", name), new Thickness(left, top+second_line-5, 0, 0), "измерения", true);
            var label_upd_control_wpf = (Label)label_upd_control.GetControl();
            label_upd_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            device_grid.Children.Add(label_upd_control_wpf);
            controls.Add("label_upd", label_upd_control);

            //-----------------------------------------------------------------------

            _form.MainGrid.Children.Add(device_grid);
        }

        public override void SendMessage()
        {

        }

        public void ChangeStateEvent()
        {

        }

        public override void SaveState()
        {

        }

    }
}
