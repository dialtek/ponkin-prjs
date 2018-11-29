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

namespace extract_system
{
    class Device
    {
        string _type;
        string _id;
        int _shift_hor;
        int _shift_vert;
        string _c_label = "";
        List<string> _R_list = new List<string>() { "", "", "" };

        bool _disable;

        string _S1 = "", _S2 = "", _S3 = "";

        private event EventHandler<QueueElement> _send_msg;
        public MainWindow _form;

        public Dictionary<string, Control> controls;
        public bool IsEnabled
        {
            get { return _disable; }
            set { _disable = value; }
        }

        public List<string> R_list
        {
            get { return _R_list; }
            set { _R_list = value; }
        }

        public string S1
        {
            get { return _S1; }
            set { _S1 = value; }
        }

        public string S2
        {
            get { return _S2; }
            set { _S2 = value; }
        }
        public string S3
        {
            get { return _S3; }
            set { _S3 = value; }
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
        public DevicePBF(string id, int shift_hor, int shift_vert, string c_label,  EventHandler<QueueElement> send_msg)
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
            try
            {
                switch (msg.Key["cmd"])
                {
                    case (byte)cmd_type.rhr:
                        var label_U = (TextBox)controls["textbox_UValue"].WPFControl;
                        var label_I = (TextBox)controls["textbox_IValue"].WPFControl;

                        var rectangle_status_HightU = (Rectangle)controls["rectangle_status_HightU"].WPFControl;
                        var rectangle_status_protectI = (Rectangle)controls["rectangle_status_protectI"].WPFControl;
                        var rectangle_status_outState = (Rectangle)controls["rectangle_status_outState_control"].WPFControl;

                        var setV_UpDown = (IntegerUpDown)controls["SetVol_UpDown"].WPFControl;
                        var label_status_protectI = (Label)controls["label_status_protectI"].WPFControl;
                        var label_status_HightU = (Label)controls["label_status_HightU"].WPFControl;
                        var label_status_outState = (Label)controls["label_status_outState"].WPFControl;

                        var button_onHightU = (Button)controls["button_onHightU"].WPFControl;
                        var button_offHightU = (Button)controls["button_offHightU"].WPFControl;

                        _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            label_U.Text = FormatOutput(msg.Value[5]);

                            // добавление устрйоства в опасный список если есть высокое
                            if (Convert.ToUInt16(msg.Value[5]) > hv_status.danger_lvl)
                                hv_status.add_element(CLabel);
                            else hv_status.del_element(CLabel);


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
                            label_status_HightU.Content = reg_11 == 1 ? "Тумблер Вкл." : "Тумблер Выкл.";

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
        catch
         {
         return;
         }

        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 5;
            var second_line = 46;
            var top = 12;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 410;
            var height_grid = 5;

            var w_control = 55;
            var h_control = 29;

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
                                            new Thickness(425 * ShiftHor/10, height_grid * ShiftVert, 0, 0),
                                Colors.MistyRose, weight_grid+10, height_grid*20); 
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);

            // ------- Информация о железяке
            var label_С_control = new LabelControl(this, string.Format("{0}_label_С", name), new Thickness(left-8, top, 0, 0), CLabel, true,16);
            device_grid.Children.Add((Label)label_С_control.GetControl());
            controls.Add("label_С", label_С_control);

            var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name), new Thickness(left-7, top + 20, 0, 0), "ID " + Id, false, 10);
            device_grid.Children.Add((Label)label_id_control.GetControl());
            controls.Add("label_id", label_id_control);

            var checkbox_disable_control = new CheckBoxDevice(this, string.Format("{0}_checkbox_disable", name), new Thickness(left-2, top + 45, 0, 0), "");
            var checkbox_disable_control_wpf = (CheckBox)checkbox_disable_control.GetControl();
            checkbox_disable_control_wpf.Unchecked += Checkbox_disable_Unchecked;
            checkbox_disable_control_wpf.Checked += Checkbox_disable_wpf_Checked;
            device_grid.Children.Add(checkbox_disable_control_wpf);
            controls.Add("checkbox_disable", checkbox_disable_control);

            // -----------------------------------------------
            // ------- кнопки вкл/выкл
            left += 35;

            Control button_onHightU_control = new ButtonSetU(this, string.Format("{0}_button_offHightU", name),
                                                new Thickness(left, top, 0, 0), "ВКЛ.",
                                                w_control, h_control);
            var button_onHightU_control_wpf = (Button)button_onHightU_control.GetControl();
            button_onHightU_control_wpf.Click += Button_onHightU_Click;
            device_grid.Children.Add(button_onHightU_control_wpf);
            controls.Add("button_offHightU", button_onHightU_control);

            Control button_offHightU_control = new ButtonSetU(this, string.Format("{0}_button_onHightU", name),
                                                            new Thickness(left, top + second_line, 0, 0), "ВЫКЛ.",
                                                            w_control, h_control);
            var button_offHightU_control_wpf = (Button)button_offHightU_control.GetControl();
            button_offHightU_control_wpf.Click += Button_offHightU_Click;
            device_grid.Children.Add(button_offHightU_control_wpf);
            controls.Add("button_onHightU", button_offHightU_control);
            // -----------------------------------------------
            // ------- Установка напряжения
            left += 65;

            var label_setU_control = new LabelControl(this, string.Format("{0}_label_setU", name), new Thickness(left+25, top, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_setU_control.GetControl());
            controls.Add("label_setU", label_setU_control);

            Control SetVol_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_set_U", name), new Thickness(left+12, top, 0, 0),
                                                        w_control+10, h_control,true,3200,0,10);

            var UpDown_setu_wpf = (CommonNumericUpDown<int>)SetVol_UpDown.GetControl();
            UpDown_setu_wpf.KeyDown += UpDown_setu_wpf_KeyDown;  // confirm by enter pressed
            device_grid.Children.Add(UpDown_setu_wpf);
            controls.Add("SetVol_UpDown", SetVol_UpDown);


            Control button_setU_control = new ButtonSetU(this, string.Format("{0}_button_setU", name), new Thickness(left+17, top+second_line, 0, 0),"Уст.",
                                                       w_control, h_control);
            var button_setU_control_wpf = (Button)button_setU_control.GetControl();
            button_setU_control_wpf.Click += Button_setU_control_wpf_Click;
            device_grid.Children.Add((Button)button_setU_control.GetControl());
            controls.Add("button_setU", button_setU_control);


            left += 55;

            var label_V_control = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left+20, top, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control.GetControl());
            controls.Add("label_V", label_V_control);

            // -------------------------------------
            // ------- Отображение информации напряжение и ток

            left += 45;

            var label_U_control = new LabelControl(this, string.Format("{0}_label_U", name), new Thickness(left-3, top, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_U_control.GetControl());
            controls.Add("label_U", label_U_control);

            var label_I_control = new LabelControl(this, string.Format("{0}_label_I", name), new Thickness(left, top + second_line, 0, 0), "I", true);
            device_grid.Children.Add((Label)label_I_control.GetControl());
            controls.Add("label_I", label_I_control);

            left += 15;

            var text_box_UValue_control = new TextBoxDevice(this, string.Format("{0}_textbox_UValue", name),
                                                        new Thickness(left, top, 0, 0),
                                                        55, h_control, true);
            
            var textbox_valueU_control_wpf = (TextBox)text_box_UValue_control.GetControl();
            textbox_valueU_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            textbox_valueU_control_wpf.TextChanged += Textbox_valueU_control_wpf_TextChanged;
            textbox_valueU_control_wpf.IsEnabled = false;
            device_grid.Children.Add(textbox_valueU_control_wpf);
            controls.Add("textbox_UValue", text_box_UValue_control);

            var text_box_IValue_control = new TextBoxDevice(this, string.Format("{0}_text_box_IValue", name),
                                                        new Thickness(left, top + second_line, 0, 0),
                                                        55, h_control, true);
            var text_box_IValue_control_wpf = (TextBox)text_box_IValue_control.GetControl();
            text_box_IValue_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            text_box_IValue_control_wpf.IsEnabled = false;
            device_grid.Children.Add(text_box_IValue_control_wpf);
            controls.Add("textbox_IValue", text_box_IValue_control);

            left += 54;

            var label_V_control2 = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left, top, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control2.GetControl());
            controls.Add("label_V2", label_V_control2);

            var label_mkA_control = new LabelControl(this, string.Format("{0}_label_mkA", name), new Thickness(left, top + second_line, 0, 0), "мкА");
            device_grid.Children.Add((Label)label_mkA_control.GetControl());
            controls.Add("label_mkA", label_mkA_control);

            //-----------------------------------------------------------------------
            // ------- Отображение информации статус напряжения и тока
            left += 40;

            Control rectangle_status_HightU_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_HightU", name),
                                                                new Thickness(left, top, 0, 0),
                                                                100, h_control);
            device_grid.Children.Add((Rectangle)rectangle_status_HightU_control.GetControl());
            controls.Add("rectangle_status_HightU", rectangle_status_HightU_control);

            var label_status_HightU_coltrol = new LabelControl(this, string.Format("{0}_label_status_HightU", name), new Thickness(left+4, top-2, 0, 0), "");
            device_grid.Children.Add((Label)label_status_HightU_coltrol.GetControl());
            controls.Add("label_status_HightU", label_status_HightU_coltrol);
            // статус бит выхода
            Control rectangle_status_outState_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_outState_control", name),
                                                                    new Thickness(left, top + second_line, 0, 0),
                                                                    45, h_control);
            device_grid.Children.Add((Rectangle)rectangle_status_outState_control.GetControl());
            controls.Add("rectangle_status_outState_control", rectangle_status_outState_control);

            var label_status_outState_control = new LabelControl(this, string.Format("{0}_label_status_outState", name), new Thickness(left + 3, (top + second_line) - 1, 0, 0), "");
            device_grid.Children.Add((Label)label_status_outState_control.GetControl());
            controls.Add("label_status_outState", label_status_outState_control);

            // перегруз по току
            Control rectangle_status_protectI_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_protectI", name), 
                                                                            new Thickness(left+54, top + second_line, 0, 0),
                                                                            45, h_control);
            device_grid.Children.Add((Rectangle)rectangle_status_protectI_control.GetControl());
            controls.Add("rectangle_status_protectI", rectangle_status_protectI_control);

            var label_status_protectI_control = new LabelControl(this, string.Format("{0}_label_status_protectI", name), new Thickness(left+59, (top + second_line)-1, 0, 0), "");
            device_grid.Children.Add((Label)label_status_protectI_control.GetControl());
            controls.Add("label_status_protectI", label_status_protectI_control);

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

        private void Button_setU_control_wpf_Click(object sender, RoutedEventArgs e)
        {
            SendMessage();
        }

        private void Textbox_valueU_control_wpf_TextChanged(object sender, TextChangedEventArgs e)
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

            // сброс перегрузки по току
            send_msg = 0;
            register = 1012;
            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }
    }

    class DeviceDCHV : Device
    {

        public DeviceDCHV(string id, int shift_hor, int shift_vert, string c_label, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            CLabel = c_label;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "DCHV";
            IsEnabled = true;
        }

        string FormatOutput(string b)
        {
            var zeros = "";
            for (int i = b.ToString().Length; i < 4; i++)
                zeros += "0";
            return zeros + b;
        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var left = 25;
            var second_line = 46;
            var top = 12;
            var w_control = 55;
            var h_control = 29;

            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 350;
            var height_grid = 20;



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
                                            new Thickness(weight_grid * ShiftHor/20 + 110, height_grid * ShiftVert, 0, 0),
                                            Colors.PapayaWhip, weight_grid, height_grid*5);
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);
            // -----------------------------------------------
            // ------- кнопки вкл/выкл

            var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name),
                                        new Thickness(left-25, top+65, 0, 0),
                                        "ID " + Id, false, 10);
            device_grid.Children.Add((Label)label_id_control.GetControl());
            controls.Add("label_id", label_id_control);

            left += 5;

            Control button_onHightU_control = new ButtonSetU(this, string.Format("{0}_button_offHightU", name),
                                                            new Thickness(left, top, 0, 0), "ВКЛ.",
                                                            w_control, h_control);
            var button_onHightU_control_wpf = (Button)button_onHightU_control.GetControl();
            button_onHightU_control_wpf.Click += Button_onHightU_Click;
            device_grid.Children.Add(button_onHightU_control_wpf);
            controls.Add("button_offHightU", button_onHightU_control);

            Control button_offHightU_control = new ButtonSetU(this, string.Format("{0}_button_onHightU", name),
                                                            new Thickness(left, top+second_line, 0, 0), "ВЫКЛ.",
                                                            w_control, h_control);
            var button_offHightU_control_wpf = (Button)button_offHightU_control.GetControl();
            button_offHightU_control_wpf.Click += Button_offHightU_Click;
            device_grid.Children.Add(button_offHightU_control_wpf);
            controls.Add("button_onHightU", button_offHightU_control);
            // -------------------------------------
            // ------- Отображение информации напряжение и ток

            left += 76;

            var label_I_control = new LabelControl(this, string.Format("{0}_label_I", name), new Thickness(left+8, (top + second_line)-2, 0, 0), "I", true);
            device_grid.Children.Add((Label)label_I_control.GetControl());
            controls.Add("label_I", label_I_control);

            var label_U_control = new LabelControl(this, string.Format("{0}_label_U", name), new Thickness(left+5, top-2, 0, 0), "U", true);
            device_grid.Children.Add((Label)label_U_control.GetControl());
            controls.Add("label_U", label_U_control);

            left += 27;

            var text_box_IValue_control = new TextBoxDevice(this, string.Format("{0}_textbox_IValue", name),
                                                        new Thickness(left, top + second_line, 0, 0),
                                                        w_control, h_control, true);
            var text_box_IValue_control_wpf = (TextBox)text_box_IValue_control.GetControl();
            text_box_IValue_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            text_box_IValue_control_wpf.IsEnabled = false;
            device_grid.Children.Add(text_box_IValue_control_wpf);
            controls.Add("textbox_IValue", text_box_IValue_control);

            var text_box_UValue_control = new TextBoxDevice(this, string.Format("{0}_textbox_UValue", name),
                                            new Thickness(left, top, 0, 0),
                                            w_control, h_control, true);

            var textbox_valueU_control_wpf = (TextBox)text_box_UValue_control.GetControl();
            textbox_valueU_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
            textbox_valueU_control_wpf.IsEnabled = false;
            device_grid.Children.Add(textbox_valueU_control_wpf);
            controls.Add("textbox_UValue", text_box_UValue_control);

            // В и мкА
            left += 55;

            var label_mkA_control = new LabelControl(this, string.Format("{0}_label_mkA", name), new Thickness(left, (top + second_line) - 2, 0, 0), "мкА");
            device_grid.Children.Add((Label)label_mkA_control.GetControl());
            controls.Add("label_mkA", label_mkA_control);

            var label_V_control2 = new LabelControl(this, string.Format("{0}_label_V", name), new Thickness(left, top - 2, 0, 0), "В");
            device_grid.Children.Add((Label)label_V_control2.GetControl());
            controls.Add("label_V2", label_V_control2);

            //-----------------------------------------------------------------------
            // ------- Отображение информации статус напряжения и тока
            left += 50;

            Control rectangle_status_HightU_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_HightU", name),
                                                                new Thickness(left, top, 0, 0),
                                                                100, h_control);
            device_grid.Children.Add((Rectangle)rectangle_status_HightU_control.GetControl());
            controls.Add("rectangle_status_HightU", rectangle_status_HightU_control);

            var label_status_HightU_coltrol = new LabelControl(this, string.Format("{0}_label_status_HightU", name), new Thickness(left + 4, top - 2, 0, 0), "");
            device_grid.Children.Add((Label)label_status_HightU_coltrol.GetControl());
            controls.Add("label_status_HightU", label_status_HightU_coltrol);
            // статус бит выхода
            Control rectangle_status_outState_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_outState_control", name),
                                                                    new Thickness(left, top + second_line, 0, 0),
                                                                    45, h_control);
            device_grid.Children.Add((Rectangle)rectangle_status_outState_control.GetControl());
            controls.Add("rectangle_status_outState_control", rectangle_status_outState_control);

            var label_status_outState_control = new LabelControl(this, string.Format("{0}_label_status_outState", name), new Thickness(left + 3, (top + second_line) - 1, 0, 0), "");
            device_grid.Children.Add((Label)label_status_outState_control.GetControl());
            controls.Add("label_status_outState", label_status_outState_control);

            // перегруз по току
            Control rectangle_status_protectI_control = new RectangleDevice(this, string.Format("{0}_rectangle_status_protectI", name),
                                                                            new Thickness(left + 54, top + second_line, 0, 0),
                                                                            45, h_control);
            device_grid.Children.Add((Rectangle)rectangle_status_protectI_control.GetControl());
            controls.Add("rectangle_status_protectI", rectangle_status_protectI_control);

            var label_status_protectI_control = new LabelControl(this, string.Format("{0}_label_status_protectI", name), new Thickness(left + 59, (top + second_line) - 1, 0, 0), "");
            device_grid.Children.Add((Label)label_status_protectI_control.GetControl());
            controls.Add("label_status_protectI", label_status_protectI_control);

            _form.MainGrid.Children.Add(device_grid);
        }

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            var label_U = (TextBox)controls["textbox_UValue"].WPFControl;
            var label_I = (TextBox)controls["textbox_IValue"].WPFControl;
            var rectangle_status_HightU = (Rectangle)controls["rectangle_status_HightU"].WPFControl;
            var rectangle_status_protectI = (Rectangle)controls["rectangle_status_protectI"].WPFControl;      
            var label_status_protectI = (Label)controls["label_status_protectI"].WPFControl;
            var label_status_HightU = (Label)controls["label_status_HightU"].WPFControl;       
            var button_onHightU = (Button)controls["button_onHightU"].WPFControl;
            var button_offHightU = (Button)controls["button_offHightU"].WPFControl;

            var rectangle_status_outState = (Rectangle)controls["rectangle_status_outState_control"].WPFControl;
            var label_status_outState = (Label)controls["label_status_outState"].WPFControl;


            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:

                        _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            //сохр. значение для передачи в форму с настройками
                       if (msg.Key["id"] == 20)
                           settings_data.DCHV_V = FormatOutput(msg.Value[0]);

                       //     // сохр. уровня напряжения для модулятора ИО
                       //if (msg.Key["id"] == 24)
                       //     settings_data.ion_cool_V = FormatOutput(msg.Value[0]);

                            label_U.Text = FormatOutput(msg.Value[5]); // напряжение 
                            label_I.Text = FormatOutput(msg.Value[6]); // ток

                        // добавление устрйоства в опасный список если есть высокое
                        if (Convert.ToUInt16(msg.Value[5]) > hv_status.danger_lvl)
                                hv_status.add_element(CLabel);
                            else hv_status.del_element(CLabel);

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
                            label_status_HightU.Content = reg_11 == 1 ? "Тумблер Вкл." : "Тумблер Выкл.";

                            var reg_12 = Convert.ToInt32(msg.Value[12]);
                            rectangle_status_protectI.Fill = new SolidColorBrush(reg_12 == 0 ? Colors.LimeGreen : Colors.Coral);
                            label_status_protectI.Content = reg_12 == 0 ? "Ок" : "I LIM";

                        });
                   
                    break;
                //case 2:
                //    cmd_type.wsr:
                //    break;
                //default:
                //    label_U.Text = "";
                //    label_I.Text = "";
                //    break;

            }

        }

        private void Button_offHightU_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 1009;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        private void Button_onHightU_Click(object sender, RoutedEventArgs e)
        {   // вкл. высокого
            int send_msg = 1;
            int register = 1009;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);

            // сброс перегрузки по току
            send_msg = 0;
            register = 1012;
            msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

    }

    class DeviceExtModule : Device
    {

        // TODO такая сопля не должна торчать.
        public event EventHandler<string> _slow_mode_on;

        public DeviceExtModule(string id, int shift_hor, int shift_vert, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "ExtModule";
            IsEnabled = true;
        }

        string FormatOutput(string b)
        {
            var zeros = "";
            for (int i = b.ToString().Length; i < 4; i++)
                zeros += "0";
            return zeros + b;
        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var second_line = 46;
            var top = 12;
            var left = 10;
            var third_line = second_line + 35;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 350;
            var height_grid = 22;

            var w_control = 55;
            var h_control = 29;

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
                                            new Thickness(weight_grid * ShiftHor + 110, 120, 0, 0),
                                            Colors.PapayaWhip, weight_grid, (int)(height_grid*9.7));
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);
            // -----------------------------------------------
            // ------- и выбор вывода
            var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name),
                                                    new Thickness(left-10, top-2, 0, 0),
                                                    "ID " + Id, false, 10);
            device_grid.Children.Add((Label)label_id_control.GetControl());
            controls.Add("label_id", label_id_control);
            
            var rb_fast_control = new RadioButtonDevice(this, string.Format("{0}_rb_fast", name),
                                                            new Thickness(left + 80, top, 0, 0),
                                                            string.Format("{0}_rb", name),
                                                            "Быстрый");
            var rb_fast_wpf = (RadioButton)rb_fast_control.GetControl();
            rb_fast_wpf.Checked += Rb_fast_Checked;
            device_grid.Children.Add(rb_fast_wpf);
            controls.Add("rb_on", rb_fast_control);


            var rb_slow_control = new RadioButtonDevice(this, string.Format("{0}_rb_slow", name),
                                                            new Thickness(left + 180, top, 0, 0),
                                                            string.Format("{0}_rb", name),
                                                            "Медленный");
            var rb_slow_wpf = (RadioButton)rb_slow_control.GetControl();
            rb_slow_wpf.Checked += Rb_slow_Checked;
            device_grid.Children.Add(rb_slow_wpf);
            controls.Add("rb_off", rb_slow_control);
            // -----------------------------------------------
            // -------  Первая строка

            top += 20;

            var label_time_control = new LabelControl(this, string.Format("{0}_label_time", name),
                                                        new Thickness(left+115, top, 0, 0),
                                                        "t, мкс", false, 14);
            device_grid.Children.Add((Label)label_time_control.GetControl());
            controls.Add("label_time", label_time_control);

            var label_incline_control = new LabelControl(this, string.Format("{0}_label_incline", name),
                                                        new Thickness(left + 190, top, 0, 0),
                                                        "наклон", false, 14);
            device_grid.Children.Add((Label)label_incline_control.GetControl());
            controls.Add("label_incline", label_incline_control);

            top += 25;

            var label_sector_control = new LabelControl(this, string.Format("{0}_label_sector_1", name),
                                                        new Thickness(left, top, 0, 0),
                                                        "Участок 1", true, 16);
            device_grid.Children.Add((Label)label_sector_control.GetControl());
            controls.Add("label_sector_1", label_sector_control);

            var textbox_time1_control = new TextBoxDevice(this, string.Format("{0}_textbox_time_1", name),
                                                        new Thickness(left + 110, top + 5, 0, 0),
                                                        w_control, h_control, true);
            var textbox_time1_control_wpf = (TextBox)textbox_time1_control.GetControl();
            textbox_time1_control_wpf.KeyDown   += Textbox_time1_control_wpf_KeyDown; // confirm by enter pressed
            //textbox_time1_control_wpf.MouseLeftButtonDown += Textbox_time1_control_wpf_MouseDown; ; 

            device_grid.Children.Add(textbox_time1_control_wpf);
            controls.Add("textbox_time_1", textbox_time1_control);

            var textbox_incline1_control = new TextBoxDevice(this, string.Format("{0}_textbox_incline_1", name),
                                                        new Thickness(left + 190, top + 5, 0, 0),
                                                        w_control, h_control, true);
            var textbox_incline1_control_wpf = (TextBox)textbox_incline1_control.GetControl();
            textbox_incline1_control_wpf.KeyDown += Textbox_incline1_control_wpf_KeyDown;
            //textbox_incline1_control_wpf.MouseLeftButtonDown += Textbox_incline1_control_wpf_MouseDown;
            device_grid.Children.Add(textbox_incline1_control_wpf);
            controls.Add("textbox_incline_1", textbox_incline1_control);

            Control button_set_control = new ButtonSetU(this, string.Format("{0}_button_set", name),
                                                            new Thickness(left + 270, top + 5, 0, 0), "Уст.",
                                                            w_control, h_control);
            var button_set_control_wpf = (Button)button_set_control.GetControl();
            button_set_control_wpf.Click += Button_set_Click;
            device_grid.Children.Add(button_set_control_wpf);
            controls.Add("button_set", button_set_control);

            top += 30;

            var checkbox_hide_control = new CheckBoxDevice(this, string.Format("{0}_checkbox_disable", name), 
                                                                new Thickness(left + 5, top + 5, 0, 0), 
                                                                "Скрыть др.");
            var checkbox_hide_control_wpf = (CheckBox)checkbox_hide_control.GetControl();
            checkbox_hide_control_wpf.Unchecked += Checkbox_hide_Unchecked;
            checkbox_hide_control_wpf.Checked += Checkbox_hide_Checked;
            checkbox_hide_control_wpf.IsChecked = true;
            device_grid.Children.Add(checkbox_hide_control_wpf);
            controls.Add("checkbox_disable", checkbox_hide_control);


            // -----------------------------------------------
            // -------  Остальные 3 строки

            for (int i = 2; i <= 4; i++)
            {
                top += 30;

                label_sector_control = new LabelControl(this, string.Format("{0}_label_sector_" + i.ToString(), name),
                                                            new Thickness(left, top, 0, 0),
                                                            "Участок " + i.ToString(), true, 16);
                var label_sector_control_wpf = (Label)label_sector_control.GetControl();
                label_sector_control_wpf.Visibility = Visibility.Hidden;
                device_grid.Children.Add(label_sector_control_wpf);
                controls.Add("label_sector_" + i.ToString(), label_sector_control);

                textbox_time1_control = new TextBoxDevice(this, string.Format("{0}_textbox_time_" + i.ToString(), name),
                                                new Thickness(left + 110, top + 5, 0, 0),
                                                55, h_control, true);
                textbox_time1_control_wpf = (TextBox)textbox_time1_control.GetControl();
   
                textbox_time1_control_wpf.Visibility = Visibility.Hidden;

                device_grid.Children.Add(textbox_time1_control_wpf);
                controls.Add("textbox_time_" + i.ToString(), textbox_time1_control);

                textbox_incline1_control = new TextBoxDevice(this, string.Format("{0}_textbox_incline_" + i.ToString(), name),
                                                            new Thickness(left + 190, top + 5, 0, 0),
                                                            55, h_control, true);
                textbox_incline1_control_wpf = (TextBox)textbox_incline1_control.GetControl();
                textbox_incline1_control_wpf.Visibility = Visibility.Hidden;
                device_grid.Children.Add(textbox_incline1_control_wpf);
                controls.Add("textbox_incline_" + i.ToString(), textbox_incline1_control);
            }


            foreach (var control in controls.Values)
            {
                if (control.Name.Contains("rb") == false &&
                    control.Name.Contains("grid") == false)
                    control.WPFControl.IsEnabled = false;

            }

            _form.MainGrid.Children.Add(device_grid);
        }

        private void Textbox_incline1_control_wpf_MouseDown(object sender, MouseButtonEventArgs e)
        {
            SendMessage(2);
        }

        private void Textbox_incline1_control_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            SendMessage(2);
        }

        private void Textbox_time1_control_wpf_MouseDown(object sender, MouseButtonEventArgs e)
        {   
           SendMessage(1);
        }

        private void Textbox_time1_control_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            // при нажати ENTER
            if (e.Key == Key.Enter) SendMessage(1);
        }

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            try
            { 
            var textbox_time = (TextBox)controls["textbox_time_1"].WPFControl;
            var textbox_incline = (TextBox)controls["textbox_incline_1"].WPFControl;
            var rb_on = (RadioButton)controls["rb_on"].WPFControl;
            var rb_off = (RadioButton)controls["rb_off"].WPFControl;

            string mode = msg.Value[10]; // 1 - быстрый, 0 - медл. вывод

                switch (msg.Key["cmd"])
                {
                    case (byte)cmd_type.rhr:
                        _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            // восстанавливаем значение при открытии проги
                            if (textbox_time.Text == "") textbox_time.Text = msg.Value[0];
                            if (textbox_incline.Text == "") textbox_incline.Text = msg.Value[1];

                            // если режим вывода программы не уст.
                            if (rb_on.IsChecked == false && rb_off.IsChecked == false)
                            {
                                if (mode == "1")    // если в железе уст. быстрый вывод
                                {   // вызов события для уст. GUI в соответ. с настр. железа
                                    rb_on.RaiseEvent(new RoutedEventArgs(RadioButton.CheckedEvent));
                                    rb_on.IsChecked = true;
                                }

                                if (mode == "0")    // если в железе уст. медл. вывод
                                {  // вызов события для уст. GUI в соответ. с настр. железа
                                    rb_off.RaiseEvent(new RoutedEventArgs(RadioButton.CheckedEvent));
                                    rb_off.IsChecked = true;
                                }
                            }

                            //сохр. значение для передачи в форму с настройками
                            settings_data.q_extr_time = msg.Value[12];
                        });
                        break;
                        //case 2:
                        //    cmd_type.wsr:
                        //    break;

                }
            }
            catch { return; }

        }

        private void SendMessage(int param)
        {
            var time1 = (TextBox)controls["textbox_time_1"].WPFControl;
            var incline1 = (TextBox)controls["textbox_incline_1"].WPFControl;

            var time2 = (TextBox)controls["textbox_time_2"].WPFControl;
            var incline2 = (TextBox)controls["textbox_incline_2"].WPFControl;

            var time3 = (TextBox)controls["textbox_time_3"].WPFControl;
            var incline3 = (TextBox)controls["textbox_incline_3"].WPFControl;

            var time4 = (TextBox)controls["textbox_time_4"].WPFControl;
            var incline4 = (TextBox)controls["textbox_incline_4"].WPFControl;

            int send_msg = 0;
            int register = 0;

            try
            {

                switch (param)
                {
                    case 1: // уст. время 1
                        send_msg = Convert.ToInt32(time1.Text);
                        if (send_msg > 300)
                        {
                            send_msg = 300;
                            time1.Text = "300";
                        }
                        
                        register = 1000;
                        break;
                    //---
                    case 2: // уст. наклон 1 
                        send_msg = Convert.ToInt32(incline1.Text);
                        if (send_msg > 64)
                        {
                            send_msg = 64;
                            incline1.Text = "64";
                        }
                        
                        register = 1000;
                        register = 1001;
                        break;
                    //---
                    case 3: // уст. время 2
                        send_msg = Convert.ToInt32(time2.Text);
                        if (send_msg > 300)
                        {
                            send_msg = 300;
                            time2.Text = "300";
                        }
                        
                        register = 1002;
                        break;
                    //---
                    case 4: // уст. наклон 2
                        send_msg = Convert.ToInt32(incline2.Text);
                        if (send_msg > 64)
                        {
                            send_msg = 64;
                            incline2.Text = "64";
                        }
                        register = 1003;
                        break;
                    //---
                    case 5: // уст. время 3
                        send_msg = Convert.ToInt32(time3.Text);
                        if (send_msg > 300)
                        {
                            send_msg = 300;
                            time3.Text = "300";
                        }
                        
                        register = 1004;
                        break;
                    //---
                    case 6: // уст. наклон 3 
                        send_msg = Convert.ToInt32(incline3.Text);
                        if (send_msg > 64)
                        {
                            send_msg = 64;
                            incline3.Text = "64";
                        }
                        register = 1005;
                        break;
                    //---
                    case 7: // уст. время 4
                        send_msg = Convert.ToInt32(time4.Text);
                        if (send_msg > 300)
                        {
                            send_msg = 300;
                            time4.Text = "300";
                        }
                        
                        register = 1006;
                        break;
                    //---
                    case 8: // уст. наклон 4 
                        send_msg = Convert.ToInt32(incline4.Text);
                        if (send_msg > 64)
                        {
                            send_msg = 64;
                            incline4.Text = "64";
                        }
                        register = 1007;
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

        private void Button_set_Click(object sender, RoutedEventArgs e)
        {
            for (int i = 1; i < 9; i++)
            {
                SendMessage(i);
            }
        }

        private void Checkbox_hide_Checked(object sender, RoutedEventArgs e)
        {
            
            for (int i = 2; i <= 4; i++)
            {
                controls["textbox_incline_" + i.ToString()].WPFControl.Visibility = Visibility.Hidden;
                controls["textbox_time_" + i.ToString()].WPFControl.Visibility = Visibility.Hidden;
                controls["label_sector_" + i.ToString()].WPFControl.Visibility = Visibility.Hidden;
            }
        }
        private void Checkbox_hide_Unchecked(object sender, RoutedEventArgs e)
        {
            for (int i = 2; i <= 4; i++)
            {
                controls["textbox_incline_" + i.ToString()].WPFControl.Visibility = Visibility.Visible;
                controls["textbox_time_" + i.ToString()].WPFControl.Visibility = Visibility.Visible;
                controls["label_sector_" + i.ToString()].WPFControl.Visibility = Visibility.Visible;
            }
        }
        private void Rb_slow_Checked(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 1010;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
            _slow_mode_on(this, "on");

            foreach (var control in controls.Values)
            {
                control.WPFControl.IsEnabled = true;
            }
        }
        private void Rb_fast_Checked(object sender, RoutedEventArgs e)
        {
            int send_msg = 1;
            int register = 1010;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);

            _slow_mode_on(this, "off");

            foreach (var control in controls.Values)
            {
                if (control.Name.Contains("rb") == false &&
                    control.Name.Contains("grid") == false)
                    control.WPFControl.IsEnabled = false;

            }
        }

    }

    class DeviceDividerKey : Device
    {
        public DeviceDividerKey(string id, int shift_hor, int shift_vert, EventHandler<QueueElement> send_msg, string s1, string s2, string s3, List<string> r_list)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "DividerKey";
            IsEnabled = true;
            // сохр. названия секций
            S1 = s1;
            S2 = s2;
            S3 = s3;
            R_list = r_list;

        }

        string FormatOutput(string b)
        {
            var zeros = "";
            for (int i = b.ToString().Length; i < 4; i++)
                zeros += "0";
            return zeros + b;
        }

        public override void CreateControls(MainWindow form_in)
        {  
            _form = form_in;
            var left = 55;
            var second_line = 35;
            var third_line = second_line + 35;
            var top = 10;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 350;
            var height_grid = 20;

            var weight_control = 50;
            var height_control = 29;

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
                                            new Thickness(weight_grid * ShiftHor/10 + 110, 553, 0, 0),
                                            Colors.LightYellow, weight_grid, (int)(height_grid*3.6));
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);

            // -----------------------------------------------
            // ------- и выбор вывода

            var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name),
                                                    new Thickness(left-50, top, 0, 0),
                                                    "ID " + Id, false, 10);
            device_grid.Children.Add((Label)label_id_control.GetControl());
            controls.Add("label_id", label_id_control);

            var combobox_sector_control = new ComboboxDevice(this, string.Format("{0}_combobox_sector", name),
                                                            new Thickness(left + 75, top, 0, 0),
                                                            90, 60
                                                            );

            var combobox_sector_control_wpf = (ComboBox)combobox_sector_control.GetControl();
            combobox_sector_control_wpf.Items.Add(R_list[0]);
            combobox_sector_control_wpf.Items.Add(R_list[1]);
            combobox_sector_control_wpf.Items.Add(R_list[2]);

            combobox_sector_control_wpf.SelectionChanged += Combobox_SelectionChanged;
            device_grid.Children.Add(combobox_sector_control_wpf);
            controls.Add("combobox_sector", combobox_sector_control);


            // ----------------------------------------------------
            // ---------- 

            List<string> C_list = new List<string>() { S1, S2, S3 };
            top += 30;
            left += 10;
            for (int i = 0; i < 3; i++)
            {
               
                var label_C2_control = new LabelControl(this, string.Format("{0}_label_" + C_list[i], name),
                                                        new Thickness(left - 60, top-4, 0, 0),
                                                        C_list[i], true, 16);
                device_grid.Children.Add((Label)label_C2_control.GetControl());
                controls.Add("label_" + C_list[i], label_C2_control);

                var textbox_с2_control = new TextBoxDevice(this, string.Format("{0}_textbox_" + i.ToString(), name),
                                                            new Thickness(left - 20, top, 0, 0),
                                                            55, height_control, true);

                var textbox_с2_control_wpf = (TextBox)textbox_с2_control.GetControl();
                textbox_с2_control_wpf.Foreground = new SolidColorBrush(Colors.Green);
                textbox_с2_control_wpf.IsEnabled = false;
                device_grid.Children.Add(textbox_с2_control_wpf);
                controls.Add("textbox_" + i.ToString(), textbox_с2_control);


                var label_с2V_control = new LabelControl(this, string.Format("{0}_label_V" + C_list[i], name), new Thickness(left+33, top-2, 0, 0), "В");
                device_grid.Children.Add((Label)label_с2V_control.GetControl());
                controls.Add("label_V" + C_list[i], label_с2V_control);

                left += 110;
            }
            


            _form.MainGrid.Children.Add(device_grid);


        }
        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            try
            {
                switch (msg.Key["cmd"])
                {
                    case (byte)cmd_type.rhr:
                        var textbox_1 = (TextBox)controls["textbox_0"].WPFControl;
                        var textbox_2 = (TextBox)controls["textbox_1"].WPFControl;
                        var textbox_3 = (TextBox)controls["textbox_2"].WPFControl;
                        var combobox = (ComboBox)controls["combobox_sector"].WPFControl;

                        _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                        (ThreadStart)delegate ()
                        {
                            textbox_1.Text = FormatOutput(msg.Value[3]);
                            textbox_2.Text = FormatOutput(msg.Value[4]);
                            textbox_3.Text = FormatOutput(msg.Value[5]);

                            // в случае открытия программы, данные загружаются из блока
                            if (combobox.SelectedIndex < 0)
                            {
                                switch (msg.Value[0])
                                {
                                    case "0":
                                        combobox.SelectedItem = R_list[0];
                                        break;
                                    case "1":
                                        combobox.SelectedItem = R_list[1];
                                        break;
                                    case "2":
                                        combobox.SelectedItem = R_list[2];
                                        break;
                                }
                            }
                        });
                        break;
                }
            }
            catch
            { return; }

        }

        private void Combobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var combobox = (ComboBox)controls["combobox_sector"].WPFControl;
            int send_msg = 0;

            send_msg = combobox.SelectedIndex;

            int register = 1000;
            QueueElement msg_ = new QueueElementW(Convert.ToInt32(Id), register, send_msg);
            SendMsgDeviceManager(this, msg_);
        }

        public void EventSlowModeOn(object sender, string mode)
        {
            if(mode == "on")
            {
                var combobox = (ComboBox)controls["combobox_sector"].WPFControl;
                if (combobox.SelectedItem != null)
                {
                    combobox.SelectedItem = (combobox.SelectedItem.ToString() == "51 R") ? "1 k" : combobox.SelectedItem;
                    if(combobox.SelectedItem.ToString() == "1 k")
                        SendMsgDeviceManager(this, new QueueElementW(Convert.ToInt32(Id), 1000, 1));
                }
                combobox.Items.Remove("51 R");
            }
            else
            {
                var combobox = (ComboBox)controls["combobox_sector"].WPFControl;

                var flag_500 = 0;
                foreach(var item in combobox.Items)
                {
                    flag_500 = (item.ToString() == "51 R") ? 1 : 0;
                    if (flag_500 == 1)
                        break;
                }
                if(flag_500 == 0)
                    combobox.Items.Add("51 R");
            }
        }

    }

    class DeviceModIonCool : Device
    {

        public DeviceModIonCool(string id, int shift_hor, int shift_vert, EventHandler<QueueElement> send_msg)
        {
            Id = id;
            ShiftHor = shift_hor;
            ShiftVert = shift_vert;

            SendMsgDeviceManager = send_msg;
            controls = new Dictionary<string, Control>();
            Type = "ExtModule";
            IsEnabled = true;
        }

        string FormatOutput(string b)
        {
            var zeros = "";
            for (int i = b.ToString().Length; i < 4; i++)
                zeros += "0";
            return zeros + b;
        }

        public override void CreateControls(MainWindow form_in)
        {
            _form = form_in;
            var second_line = 46;
            var top = 5;
            var left = 10;
            var third_line = second_line + 35;
            var name = string.Format("{0}_{1}", Type, Id);

            var weight_grid = 350;
            var height_grid = 30;

            var w_control = 55;
            var h_control = 29;

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
                                            new Thickness(weight_grid * ShiftHor/10 + 110, 120, 0, 0),
                                            Colors.PapayaWhip, weight_grid, (int)(height_grid * 5));
            var device_grid = (Grid)grid.GetControl();
            controls.Add("grid", grid);
            // -----------------------------------------------
            // ID
            var label_id_control = new LabelControl(this, string.Format("{0}_label_id", name),
                                                    new Thickness(left - 10, top - 2, 0, 0),
                                                    "ID " + Id, false, 10);
            device_grid.Children.Add((Label)label_id_control.GetControl());
            controls.Add("label_id", label_id_control);
            // -----------------------------------------------
            // -------  Первая строка

            var label_time_control = new LabelControl(this, string.Format("{0}_label_time", name),
                                                        new Thickness(left + 110, top, 0, 0),
                                                        "t, мкс", false, 14);
            device_grid.Children.Add((Label)label_time_control.GetControl());
            controls.Add("label_time", label_time_control);

            var label_incline_control = new LabelControl(this, string.Format("{0}_label_incline", name),
                                                        new Thickness(left + 195, top, 0, 0),
                                                        "наклон", false, 14);
            device_grid.Children.Add((Label)label_incline_control.GetControl());
            controls.Add("label_incline", label_incline_control);

            top += 25;

            var label_sector_control = new LabelControl(this, string.Format("{0}_label_sector_control", name),
                                                        new Thickness(left-10, top, 0, 0),
                                                        "Пер. фронт", true, 16);
            device_grid.Children.Add((Label)label_sector_control.GetControl());
            controls.Add("label_sector_control", label_sector_control);

            // время
            Control time1_control_UpDown = new NumUpDownDevice(this, string.Format("{0}_time1_control_UpDown", name), new Thickness(left + 100, top + 5, 0, 0),
                                w_control + 10, h_control, true, 600, 10, 10);
            var time1_control_UpDown_wpf = (CommonNumericUpDown<int>)time1_control_UpDown.GetControl();
            time1_control_UpDown_wpf.KeyDown += Time1_control_UpDown_wpf_KeyDown; // confirm by enter pressed
            device_grid.Children.Add(time1_control_UpDown_wpf);
            controls.Add("time1_control_UpDown", time1_control_UpDown);

            // наклон
            Control incline1_control_UpDown = new NumUpDownDevice(this, string.Format("{0}_incline1_control_UpDown", name), new Thickness(left + 190, top + 5, 0, 0),
                    w_control + 10, h_control, true, 64, 0, 1);
            var incline1_control_UpDown_wpf = (CommonNumericUpDown<int>)incline1_control_UpDown.GetControl();
            incline1_control_UpDown_wpf.KeyDown += Incline1_control_UpDown_wpf_KeyDown; // confirm by enter pressed
            device_grid.Children.Add(incline1_control_UpDown_wpf);
            controls.Add("incline1_control_UpDown", incline1_control_UpDown);

            Control button_set_control = new ButtonSetU(this, string.Format("{0}_button_set", name),
                                                            new Thickness(left + 270, top + 5, 0, 0), "Уст.",
                                                            w_control, h_control);
            var button_set_control_wpf = (Button)button_set_control.GetControl();
            button_set_control_wpf.Click += Button_set_Click;
            device_grid.Children.Add(button_set_control_wpf);
            controls.Add("button_set", button_set_control);

            /// вторая строчка
            /// ----------------------------
            // лейбл
            var label_section = new LabelControl(this, string.Format("{0}_label_section", name),
                                            new Thickness(left + 20, top+23, 0, 0),
                                            "C25", true, 16);
            device_grid.Children.Add((Label)label_section.GetControl());
            controls.Add("label_section", label_section);

            // лейбл Т полки
            var label_delay_control = new LabelControl(this, string.Format("{0}_label_delay", name),
                                            new Thickness(left + 90, top+second_line, 0, 0),
                                            "t полки, мкс", false, 14);
            device_grid.Children.Add((Label)label_delay_control.GetControl());
            controls.Add("label_delay", label_delay_control);

            // лейбл период
            var label_period_control = new LabelControl(this, string.Format("{0}_label_incline", name),
                                                        new Thickness(left + 180, top+ second_line, 0, 0),
                                                        "период, мкс", false, 14);
            device_grid.Children.Add((Label)label_period_control.GetControl());
            controls.Add("label_period", label_period_control);

            // лейбл N импульсов за цикл
            var label_pulse_cnt= new LabelControl(this, string.Format("{0}_label_incline", name),
                                                        new Thickness(left + 13, top + second_line, 0, 0),
                                                        "счетчик", false, 14);
            device_grid.Children.Add((Label)label_pulse_cnt.GetControl());
            controls.Add("label_pulse_cnt", label_pulse_cnt);

            // N импульсов за цикл
            var textbox_pulse_cnt = new TextBoxDevice(this, string.Format("{0}_textbox_pulse_cnt", name),
                                            new Thickness(left + 10, top + second_line + 30, 0, 0),
                                            w_control + 10, h_control, true,true);
            var textbox_pulse_cnt_wpf = (TextBox)textbox_pulse_cnt.GetControl();
            textbox_pulse_cnt_wpf.Foreground = new SolidColorBrush(Colors.Green);
            textbox_pulse_cnt_wpf.IsEnabled = false;
            device_grid.Children.Add(textbox_pulse_cnt_wpf);
            controls.Add("textbox_pulse_cnt", textbox_pulse_cnt);

            //уст. t полки
            Control SetPulseWidth_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_pulse_width", name), new Thickness(left + 100, top + second_line + 30, 0, 0),
                                            w_control + 10, h_control, true,100,1,5);
            var UpDown_pulseWidth_wpf = (CommonNumericUpDown<int>)SetPulseWidth_UpDown.GetControl();
            UpDown_pulseWidth_wpf.KeyDown += UpDown_pulseWidth_wpf_KeyDown; // confirm by enter pressed
            device_grid.Children.Add(UpDown_pulseWidth_wpf);
            controls.Add("SetPulseWidth_UpDown", SetPulseWidth_UpDown);

            // период имп. ИО
            Control SetPeriod_UpDown = new NumUpDownDevice(this, string.Format("{0}_updown_period", name), new Thickness(left + 180, top + second_line + 30, 0, 0),
                                w_control + 30, h_control, true, 60000, 10, 10);
            var UpDown_period_wpf = (CommonNumericUpDown<int>)SetPeriod_UpDown.GetControl();
            UpDown_period_wpf.KeyDown += UpDown_period_wpf_KeyDown;        // confirm by enter pressed
            device_grid.Children.Add(UpDown_period_wpf);
            controls.Add("SetPeriod_UpDown", SetPeriod_UpDown);

            // кнопка уст. второй линии
            Control button_set_cycle = new ButtonSetU(this, string.Format("{0}_button_set_cycle", name),
                                                new Thickness(left + 270, top + second_line + 30, 0, 0), "Уст.",
                                                w_control, h_control);
            var button_set_cycle_wpf = (Button)button_set_cycle.GetControl();
            button_set_cycle_wpf.Click += button_set_cycle_Click;
            device_grid.Children.Add(button_set_cycle_wpf);
            controls.Add("button_set_cycle", button_set_cycle);

            _form.MainGrid.Children.Add(device_grid);
        }

        private void UpDown_period_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage(4); // уст. период
        }

        private void UpDown_pulseWidth_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage(3); // уст. t полки
        }

        private void Incline1_control_UpDown_wpf_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) SendMessage(2); // уст. наклон
        }

        private void Time1_control_UpDown_wpf_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if(e.Key == Key.Enter) SendMessage(1);  // уст. t
        }

        private void SendMessage(int param)
        {
            var time = (CommonNumericUpDown<int>)controls["time1_control_UpDown"].WPFControl;
            var incline = (CommonNumericUpDown<int>)controls["incline1_control_UpDown"].WPFControl;

            var PulseWidth = (CommonNumericUpDown<int>)controls["SetPulseWidth_UpDown"].WPFControl;
            var Period = (CommonNumericUpDown<int>)controls["SetPeriod_UpDown"].WPFControl;

            int send_msg = 0;
            int register = 0;

            try
            {

                switch (param)
                {
                    case 1: // уст. время 
                        send_msg = (int)time.Value;
                        register = 1000;
                        break;
                    //---
                    case 2: // уст. наклон 
                        send_msg = (int)incline.Value;
                        register = 1001;
                        break;
                    //---
                    case 3: // уст. длит. импульса 
                        send_msg = (int)PulseWidth.Value;
                        register = 1008;
                        break;
                    //---
                    case 4:
                        send_msg = (int)Period.Value;
                        register = 1009;
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

        public override void GetMsgFromDevice(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            var PulseWidth = (CommonNumericUpDown<int>)controls["SetPulseWidth_UpDown"].WPFControl;
            var Period = (CommonNumericUpDown<int>)controls["SetPeriod_UpDown"].WPFControl;
            var pulse_cnt_textbox = (TextBox)controls["textbox_pulse_cnt"].WPFControl;
            var time = (CommonNumericUpDown<int>)controls["time1_control_UpDown"].WPFControl;
            var incline = (CommonNumericUpDown<int>)controls["incline1_control_UpDown"].WPFControl;

            var reg_0 = Convert.ToInt32(msg.Value[0]);  // t
            var reg_1 = Convert.ToInt32(msg.Value[1]);  // наклон
            var reg_8 = Convert.ToInt32(msg.Value[8]);  // длит. импульса
            var reg_9 = Convert.ToInt32(msg.Value[9]);  // период

            switch (msg.Key["cmd"])
            {
                case (byte)cmd_type.rhr:
                    _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                    (ThreadStart)delegate ()
                    {
                        // если были считаны уставки и в программе они не уст.
                        if (time.Value == null)        time.Value = reg_0;
                        if (incline.Value == null)     incline.Value = reg_1;

                        if (PulseWidth.Value == null)  PulseWidth.Value = reg_8;
                        if (Period.Value == null)      Period.Value = reg_9;

                        pulse_cnt_textbox.Text = msg.Value[16];

                    });
                    break;
            
            }

        }

        private void Button_set_Click(object sender, RoutedEventArgs e)
        {
            SendMessage(1);    // t
            SendMessage(2);    // наклон
        }

        private void button_set_cycle_Click(object sender, RoutedEventArgs e)
        {
            SendMessage(3);    // длит. полки
            SendMessage(4);    // период
        }
    }

}
