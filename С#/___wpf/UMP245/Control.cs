﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;

using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;
using System.Windows.Shapes;

namespace UMP245
{
    class Control
    {
        Device _device;
        UIElement _wpfcontrol;
        string _type;
        string _name;
        public string Type
        {
            get { return _type; }
            set { _type = value; }
        }
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        public Device pDevice
        {
            get { return _device; }
            set { _device = value; }
        }

        public UIElement WPFControl
        {
            get { return _wpfcontrol; }
            set { _wpfcontrol = value; }
        }

        public UIElement GetControl()
        {
            return _wpfcontrol;
        }


    }

    class ButtonSetU: Control
    {
        public ButtonSetU(Device device, string name, Thickness margin, string content, int width, int height)
        {
            pDevice = device;
            Name = name;

            var button_device = new Button();
            button_device.Name = string.Format("{0}_button_setU", name);
            button_device.Content = content;
            button_device.VerticalAlignment = VerticalAlignment.Top;
            button_device.HorizontalAlignment = HorizontalAlignment.Left;
            button_device.Margin = margin;
            button_device.Width = width;
            button_device.Height = height;

            WPFControl = button_device;
        }
        


    }

    class GridDevice : Control
    {
        public GridDevice(Device device, string name, Thickness margin, Color color, int width, int height)
        {

            Name = name;

            var device_grid = new Grid();
            device_grid.Name = string.Format("{0}_grid", name);
            device_grid.VerticalAlignment = VerticalAlignment.Top;
            device_grid.HorizontalAlignment = HorizontalAlignment.Left;
            device_grid.Margin = margin;
            device_grid.Width = width;
            device_grid.Height = height;
            device_grid.Background = new SolidColorBrush(Colors.Transparent);
            device_grid.ShowGridLines = true;

            var border = new Border();
            border.Background = new SolidColorBrush(color);
            border.BorderBrush = new SolidColorBrush(Colors.Black);
            border.BorderThickness = new Thickness(1, 1, 1, 1);
            border.CornerRadius = new CornerRadius(8, 8, 8, 8);
            device_grid.Children.Add(border);
            WPFControl = device_grid;
        }
    }

    class LabelControl : Control
    {
        public LabelControl(Device device, string name, Thickness margin, string content, bool bold = false, int fontsize = 15)
        {
            Name = name;

            var device_grid = new Label();
            device_grid.Name = name;
            device_grid.Content = content;
            device_grid.Margin = margin;
            device_grid.Margin = margin;
            device_grid.FontSize = fontsize;
            //device_grid.FontWeight = FontWeight.FromOpenTypeWeight(150);
            device_grid.FontWeight = (bold == false) ? FontWeight.FromOpenTypeWeight(5) : FontWeights.Bold;

            WPFControl = device_grid;
        }
    }

    class RadioButtonDevice : Control
    {
        public RadioButtonDevice(Device device, string name, Thickness margin, string GroupName, string content)
        {
            Name = name;

            var device_grid = new RadioButton();
            device_grid.GroupName = GroupName;
            device_grid.Content = content;
            device_grid.Name =  name;
            device_grid.VerticalAlignment = VerticalAlignment.Top;
            device_grid.HorizontalAlignment = HorizontalAlignment.Left;
            device_grid.Margin = margin;

            WPFControl = device_grid;
        }
    }

    class CheckBoxDevice : Control
    {
        public CheckBoxDevice(Device device, string name, Thickness margin, string content)
        {
            pDevice = device;
            Name = name;

            var device_grid = new CheckBox();
            device_grid.Content = content;
            device_grid.Name = name;
            device_grid.VerticalAlignment = VerticalAlignment.Top;
            device_grid.HorizontalAlignment = HorizontalAlignment.Left;
            device_grid.Margin = margin;
            device_grid.IsChecked = true;
            WPFControl = device_grid;
        }

    }

    class TextBoxDevice : Control
    {
        public TextBoxDevice(Device device, string name, Thickness margin, int width, int height, bool bold = false)
        {

            pDevice = device;
            Name = name;

            var device_grid = new TextBox();
            device_grid.Name = name;
            device_grid.VerticalAlignment = VerticalAlignment.Top;
            device_grid.HorizontalAlignment = HorizontalAlignment.Left;
            device_grid.Margin = margin;
            device_grid.Width = width;
            device_grid.Height = height;
            device_grid.Foreground = new SolidColorBrush(Colors.Black);
            device_grid.FontWeight = (bold == false) ? FontWeight.FromOpenTypeWeight(5) : FontWeights.Bold;
            device_grid.FontSize = 16;
            device_grid.TextAlignment = TextAlignment.Center;
            device_grid.FontFamily = new FontFamily("Consolas");
            WPFControl = device_grid;
        }
        
    }

    class RectangleDevice : Control
    {
        public RectangleDevice(Device device, string name, Thickness margin, int width, int height)
        {
            Name = name;

            var device_grid = new Rectangle();

            device_grid.Name = name;
            device_grid.VerticalAlignment = VerticalAlignment.Top;
            device_grid.HorizontalAlignment = HorizontalAlignment.Left;
            device_grid.Margin = margin;
            device_grid.Width = width;
            device_grid.Height = height;

            device_grid.Fill = new SolidColorBrush(Colors.Gray);
            
            WPFControl = device_grid;
        }
    }

    class ComboboxDevice : Control
    {
        public ComboboxDevice(Device device, string name, Thickness margin, int width, int height)
        {
            Name = name;

            var device_grid = new ComboBox();

            device_grid.Name = name;
            device_grid.VerticalAlignment = VerticalAlignment.Top;
            device_grid.HorizontalAlignment = HorizontalAlignment.Left;
            device_grid.Margin = margin;
            device_grid.Width = width;
            //device_grid.Height = height;

            WPFControl = device_grid;
        }
    }

}
