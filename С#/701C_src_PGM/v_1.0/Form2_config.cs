using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _701C_src_PGM
{
    /// <summary>
    /// Класс настройки источников
    /// </summary>
    public partial class Form2_config : Form
    {

        private List<ListViewItem> lviList = new List<ListViewItem>();
        ListViewItem[] Src_data_Form2 = new ListViewItem[50];
        private int NumOfAddedSrc = 0;

        public static int numberOfNewSouces = 0;
        int selectedSourceNum = 0;

        public Form2_config()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Добавление нового источника
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddNewSrcB_Click(object sender, EventArgs e)
        {
            // добавление нового источника

            ListViewItem lvi = new ListViewItem();

            lvi.Text = NewSrcName.Text;             // добавляем новые элементы в листвью итем
            lvi.SubItems.Add(IP_adress.Text);
            lvi.SubItems.Add(Port.Text);

            NumOfAddedSrc++;                    // инкремент числа новых источников
            lviList.Add(lvi);
            Form2_listView.Items.Clear();

            for (int i = 0; i < lviList.Count; i++)
            {
                Form2_listView.Items.Add(lviList[i]);
            }
        }

        private void DeleteSrcB_Click(object sender, EventArgs e)
        {
            // удаление источника

            NumOfAddedSrc--;                                 // декремент числа новых источников
            Form2_listView.Items.RemoveAt(selectedSourceNum);

            //Form1.SrcNames.RemoveAt(selectedSourceNum);    // сохраняем имя
            //Form1.IPadrList.RemoveAt(selectedSourceNum);   // сохраняем IP
            //Form1.PortList.RemoveAt(selectedSourceNum);    // сохраняем порт

            //if (selectedSourceNum > Form1.NumberOfSources)
            //{
            //    lviList.RemoveAt(selectedSourceNum);
            //    numberOfNewSouces--;                    
            //}

            //else
            //{
            //    Form1.NumberOfSources--;
            //    Form1.ListView1.Items.Remove(Form1.Src_data[selectedSourceNum]);
            //    Form1.Src_data[selectedSourceNum].SubItems.Clear();
            //}

        }

        private void Form2_listView_Click(object sender, EventArgs e)
        {
            /// сохр. номера выбранного источника

            ListViewItem LVI_temp = new ListViewItem();

            if (Form2_listView.SelectedIndices.Count > 0)
            {
                LVI_temp = Form2_listView.SelectedItems[0];   // вытаскиваем номер выбранного источника
                selectedSourceNum = LVI_temp.Index;       // запоминаем номер выбранного источника
                //StatusBox.Text = "Выбран источник № " + (SelSourceNumber + 1).ToString();
            }
        }

        private void Form2_config_Shown(object sender, EventArgs e)
        {
           // массив элементов ListViewItem для динамического заполнения таблицы данными об источниках питания 
            
            Form2_listView.Items.Clear();

            for (int i = 0; i < Form1.NumberOfSources; i++)
            {
                Src_data_Form2[i] = (ListViewItem)Form1.Src_data[i].Clone();
                Form2_listView.Items.Add(Src_data_Form2[i]);
                lviList.Add(Src_data_Form2[i]);
                Form2_listView.Items[i].SubItems[1].Text = Form1.IPadrList[i];

            }


        }

        private void SaveCfgB_Click(object sender, EventArgs e)
        {
            /// Зафиксировать результат
            /// 

            int NumOfSouces = Form2_listView.Items.Count;

            for (int i = 0; i < NumOfSouces; i++)
            {
                ListViewItem lvi = new ListViewItem();
                lvi = Form2_listView.Items[i];
                Form1.SrcNames.Add(lvi.Text);               // сохраняем имена
                Form1.IPadrList.Add(lvi.SubItems[1].Text);  // сохраняем IP
                Form1.PortList.Add(lvi.SubItems[2].Text);              // сохраняем порт
            }

            numberOfNewSouces = NumOfAddedSrc;
        }
    }
}
