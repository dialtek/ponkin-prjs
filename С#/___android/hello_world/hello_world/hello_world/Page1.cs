using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using Xamarin.Forms;

namespace hello_world
{
    public class Page1 : ContentPage
    {
        Label text_lbl = new Label { Text = ""};
        Button Set = new Button
        {
            Text = "Кнопка",
            BorderWidth = 1,
            HorizontalOptions = LayoutOptions.Center,
            VerticalOptions = LayoutOptions.CenterAndExpand
        };

        string state = "hide_msg";
        Image ima = new Image { Source = "dialtek_logo" };

        Label header;
        Picker picker;

        public Page1()
        {
            StackLayout stacklayout = new StackLayout {VerticalOptions = LayoutOptions.Start, HorizontalOptions = LayoutOptions.Center };
            ScrollView scrollview = new ScrollView { VerticalOptions = LayoutOptions.Start, HorizontalOptions = LayoutOptions.Center };
            ima.Scale = 0.35;
            ima.IsVisible = false;
            text_lbl.HorizontalTextAlignment = TextAlignment.Center;

            // выбранный элемент
            header = new Label
            {
                Text = "Выбор элемента",
                FontSize = Device.GetNamedSize(NamedSize.Large, typeof(Label))
            };

            // список элементов
            picker = new Picker
            {
                Title = "Элемент списка"
            };
            picker.Items.Add("1");
            picker.Items.Add("2");
            picker.Items.Add("3");
            picker.Items.Add("4");
            picker.SelectedIndexChanged += Picker_SelectedIndexChanged;

            // слайдер
            Slider slider = new Slider
            {
                Minimum = 0, Maximum = 100, Value = 50, WidthRequest = 500

            };
            slider.ValueChanged += Slider_ValueChanged;

            stacklayout.Children.Add(Set);
            stacklayout.Children.Add(text_lbl);
            stacklayout.Children.Add(ima);
            stacklayout.Children.Add(picker);
            stacklayout.Children.Add(slider);

            scrollview.Content = stacklayout;

            Set.Clicked += Set_Clicked; // нажатие кнопки
            Content = scrollview;

        }

        private void Slider_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            text_lbl.Text = String.Format("Выбрано: {0:F1}", e.NewValue);
        }

        private void Picker_SelectedIndexChanged(object sender, EventArgs e)
        {   // список
            header.Text = "Вы выбрали: " + picker.Items[picker.SelectedIndex];
        }

        private void Set_Clicked(object sender, EventArgs e)
        {
            // кнопка
            switch (state)
            {
                case "show_msg":
                    text_lbl.Text = "Ура, событие!";
                    Set.Text = "Скрыть";
                    state = "hide_msg";
                    ima.IsVisible = true;
                    break;
                //---
                case "hide_msg":
                    text_lbl.Text = "";
                    Set.Text = "Показать";
                    state = "show_msg";
                    ima.IsVisible = false;
                    break;
            }
        }
    }
}