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
    /// Класс отрисовки профиля пучка в отдельном окне с ресайзингом
    /// </summary>
    public partial class FormBarGraph : Form
    {
        private ZedGraph.ZedGraphControl _Axis_profile_graph = new ZedGraphControl(); // график данных по Х
        private GraphPane _Axis_Pane;                         // область рисования графика
        
        private double[] _profile_data = new double[21];
        private Color _BarColor = Color.Blue;
        private int _YmaxVal = 13;
        private PointPairList _BarData;  // Здесь храним данные

        public FormBarGraph()
        {
            InitializeComponent();
        }

        private void FormBarGraph_Load(object sender, EventArgs e)
        {
            _BarData = new PointPairList();

            _Axis_Pane = _Axis_profile_graph.GraphPane;
            _Axis_Pane.PaneFill.Color = Color.Wheat;   // цвет внешний
            _Axis_profile_graph.GraphPane.AxisFill.Color = Color.Wheat;
            _Axis_Pane.XAxis.Min = 0;
            _Axis_Pane.XAxis.Max = 22;
            _Axis_Pane.XAxis.Step = 1;               // осн. шкала
            _Axis_Pane.XAxis.MinorStep = 0.5;         // не осн. шкала
            _Axis_Pane.XAxis.ScaleFontSpec.Size = 10;
            _Axis_Pane.YAxis.ScaleFontSpec.Size = 10;
            _Axis_Pane.YAxis.Min  = 0;
            _Axis_Pane.YAxis.Step = 1;         // осн. шкала
            _Axis_Pane.XAxis.ScaleFormat = "D";
            _Axis_Pane.XAxis.Title = "Channels";
            _Axis_Pane.YAxis.Title = "Charge, pC";

            this._Axis_profile_graph.Location = new System.Drawing.Point(0, 0);
            this._Axis_profile_graph.Size = new System.Drawing.Size(400, 600);
            this._Axis_profile_graph.TabIndex = 0;

            this._Axis_profile_graph.Dock = DockStyle.Fill;
            this.Controls.Add(this._Axis_profile_graph);

            Form1.OnChargeRead +=Form1_OnChargeRead; // подписка на событие чтения заряда
           
        }

        void Form1_OnChargeRead(object sender, Dictionary <string,double[]> e)
        {
            /// событие получения заряда от МК
            /// 
            string BarName = ""; 

            try
            {
                foreach (KeyValuePair<string, double[]> pair in e)
                {
                    BarName = pair.Key;
                    //double xCoord = -5;

                    if (BarName == this._Axis_profile_graph.Name)
                    {
                        double[] MidLineCoordsX = {11,11}; // координаты линии середин детектора
                        double[] MidLineCoordsY = {0,13};

                        
                        _Axis_Pane.YAxis.Max = _YmaxVal; // уст. Ymax

                        _profile_data = pair.Value;
                        //_BarData.Clear();

                        //for(int i = 0; i < 21; i++)
                        //{
                        //  _BarData.Add(xCoord, _profile_data[i]);
                        //  xCoord += 0.5;

                        //}
                        

                        _Axis_profile_graph.GraphPane.CurveList.Clear();
                        _Axis_profile_graph.GraphPane.GraphItemList.Clear();
                        _Axis_profile_graph.IsShowPointValues = true;
                        BarItem _Bar = _Axis_Pane.AddBar("Заряд, пКл", null, _profile_data, _BarColor);
                        //BarItem _Bar = _Axis_Pane.AddBar("Заряд, пКл", _BarData, _BarColor); 
                        //LineItem MidLine = _Axis_Pane.AddCurve("",MidLineCoordsX, MidLineCoordsY,Color.Black);  // добавляем линию - середину детектора
                        //BarItem MidBar = _Axis_Pane.AddBar("vvv", null, MidLine,Color.Black);
                        _Bar.Bar.Fill = new Fill(Color.Wheat);
                        _Axis_Pane.MinClusterGap = 0.0f;    // Расстояния между столбиками гистограммы = 0.0
                        _Bar.Bar.Border.IsVisible = true;   // Сделаем границы столбцов невидимыми  
                        _Bar.Bar.Fill.Type = FillType.Solid;// Отключим градиентную заливку

                        for (int i = 0; i < _Bar.Points.Count; i++)
                        { /// добавление текст. значение на вершину столбца
                            TextItem barlabel = new TextItem(_Bar.Points[i].Y.ToString(), (float)(_Bar.Points[i].X), (float)(_Bar.Points[i].Y + 0.4));
                            _Axis_profile_graph.GraphPane.GraphItemList.Add(barlabel);
                            barlabel.FontSpec.Border.IsVisible = false;
                            barlabel.FontSpec.Fill.Color = Color.Transparent;
                        }
                        
                        _Axis_profile_graph.GraphPane.XAxis.IsShowMinorGrid = false;
                        _Axis_profile_graph.GraphPane.XAxis.IsShowGrid = true;
                        _Axis_profile_graph.GraphPane.XAxis.GridDashOn = 8;
                        _Axis_profile_graph.GraphPane.XAxis.GridDashOff = 4;
                        _Axis_profile_graph.GraphPane.XAxis.GridColor = Color.Gray;

                        _Axis_profile_graph.GraphPane.YAxis.IsShowMinorGrid = false;
                        _Axis_profile_graph.GraphPane.YAxis.IsShowGrid = true;
                        _Axis_profile_graph.GraphPane.YAxis.GridDashOn = 8;
                        _Axis_profile_graph.GraphPane.YAxis.GridDashOff = 4;
                        _Axis_profile_graph.GraphPane.YAxis.GridColor = Color.Gray;

                        _Axis_profile_graph.AxisChange();
                        //_Axis_profile_graph.Refresh();
                        _Axis_profile_graph.Invalidate();

                        //for (int i = 0; i < _Bar.Points.Count; i++)
                        //{

                        //}


                        #region Bar graphs on left side
                        
                        //BarItem Y_Bar = Y_Pane.AddBar("Заряд, пКл", null, Y_profile_data, Color.Blue);
                        ////Y_Pane.BarBase = BarBase.Y;
                        ////BarItem Y_Bar = Y_Pane.AddBar("Заряд, пКл", StripCurrentNum, null, Color.Blue);
                        //// сначала идут данные по оси X (длины столцов), потом по оси Y (положения столбцов)
                        //// Для вертикальных гистограмм значения по осям X и Y имеют противоположные значения.
                        //Y_Bar.Bar.Fill = new Fill(Color.MediumSlateBlue);
                        //Y_Pane.MinClusterGap = 0.0f;         // Расстояния между столбиками гистограммы = 0.0
                        //Y_Bar.Bar.Border.IsVisible = false;  // Сделаем границы столбцов невидимыми
                        //Y_Bar.Bar.Fill.Type = FillType.Solid;// Отключим градиентную заливку
                        #endregion

                    }
                }
            }
            catch (Exception)
            {
                return;
            }


        }

        /// <summary>
        /// Установка и чтение имени графика
        /// </summary>
        public string G_Name
        {
            get { return this._Axis_profile_graph.Name; }
            set { this._Axis_profile_graph.Name = value; }
        }

        /// <summary>
        /// Установка и чтение заголовка графика
        /// </summary>
        public string Title
        {
            get { return _Axis_profile_graph.GraphPane.Title; }
            set { _Axis_profile_graph.GraphPane.Title = value; }
        }

        /// <summary>
        /// Установка и чтение цвета диаграммы
        /// </summary>
        public Color BarColor
        {
            get { return this._BarColor; }
            set { this._BarColor = value; }
        }

        /// <summary>
        /// Установка и чтение Ymax
        /// </summary>
        public int Ymax
        {
            get { return this._YmaxVal; }
            set { this._YmaxVal = value; }
        }

        private void FormBarGraph_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

    }
}
