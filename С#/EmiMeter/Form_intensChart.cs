using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using System.Media;
using System.IO.Ports;
using ZedGraph;

namespace EmiMeterSln
{
    /// <summary>
    /// Класс отрисовки быстрого графика интенсивности заряда
    /// </summary>
    public partial class Form_intensChart : Form
    {
        private ZedGraph.ZedGraphControl _IntensChart; // график данных интенсивности
        private GraphPane _Q_Pane;
        
        private uint _capacity = 500; // Количество отображаемых точек

        private PointPairList intens_data;  // Здесь храним данные
        private double _sum_charge = 0;
        private UInt64 _currentX = 0;
        private Color _ChartColor = Color.Navy;

        public Form_intensChart()
        {
            InitializeComponent();
        }

        private void Form_intensChart_Load(object sender, EventArgs e)
        {
            /// График  - данные интенсивности пучка --------------
            intens_data = new PointPairList();
            this._IntensChart = new ZedGraph.ZedGraphControl();
            _Q_Pane = _IntensChart.GraphPane;
            _Q_Pane.PaneFill.Color = Color.Wheat;   // цвет внешний
            _IntensChart.GraphPane.AxisFill.Color = Color.Wheat;
            _Q_Pane.YAxis.Min = 0;
            //_Q_Pane.YAxis.Max = 30;
            _Q_Pane.YAxis.ScaleFontSpec.Size = 18;
            _Q_Pane.XAxis.ScaleFontSpec.Size = 18;
            _Q_Pane.XAxis.ScaleFormat = "f";
            _Q_Pane.YAxis.Title = "I, uА";
            _Q_Pane.XAxis.Title = "";
            //_Q_Pane.YAxis.Step = 0.5;         // осн. шкала

            LineItem IntensCurve = _Q_Pane.AddCurve("Intensity", intens_data, Color.LightYellow , SymbolType.None);
            this._IntensChart.Location = new System.Drawing.Point(0, 0);
            this._IntensChart.Name = "Intens_graph";
            this._IntensChart.Size = new System.Drawing.Size(this.Width, this.Width);
            this._IntensChart.TabIndex = 0;

            this._IntensChart.Dock = DockStyle.Fill;
            this.Controls.Add(this._IntensChart);
            this._IntensChart.GraphPane.Title = "Beam Intensity, uA"; // Set the Titles

            Form1.OnIntensRead += Form1_OnIntensRead; ; // подписка на событие чтения заряда

        }

        private void Form1_OnIntensRead(object sender, double e)
        {
            /// событие получения заряда от МК

            _sum_charge = e; // сохраняем полный заряд

            _IntensChart.GraphPane.CurveList.Clear();
            // обновляем показания
            _currentX++;
            intens_data.Add(_currentX, _sum_charge);
            LineItem IntensCurve = _Q_Pane.AddCurve("Intensity", intens_data, _ChartColor, SymbolType.None);
            // Рассчитаем интервал по оси X
            double xmin = _currentX - (double)_capacity;
            double xmax = _currentX;

            _Q_Pane.XAxis.Min = xmin;
            _Q_Pane.XAxis.Max = xmax;
            _IntensChart.AxisChange();
            //_IntensChart.Refresh();
            _IntensChart.Invalidate();
        }

        /// <summary>
        /// Установка и чтение цвета графика
        /// </summary>
        public Color ChartColor
        {
            get { return this._ChartColor; }
            set { this._ChartColor = value; }
        }

        /// <summary>
        /// Установка и чтение цвета графика
        /// </summary>
        public uint Capacity
        {
            get { return this._capacity; }
            set { this._capacity = value; }
        }

        private void Form_intensChart_SizeChanged(object sender, EventArgs e)
        {
            //Thread.Sleep(1);
        }

        private void Form_intensChart_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }
    }
}
