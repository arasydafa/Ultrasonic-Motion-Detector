using Bulb;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.IO.Ports;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ultrasonic_Motion_Detector
{
    public partial class Form1 : Form
    {
        string motion;
        string status;

        public Form1()
        {
            InitializeComponent();

            Text = "Ultrasonic Motion Detector v" + Assembly.GetExecutingAssembly().GetName().Version;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                string[] port = SerialPort.GetPortNames();
                foreach (string name in port)
                {
                    comboBoxPort.Items.Add(name);
                }
                comboBoxPort.Text = comboBoxPort.Items[comboBoxPort.Items.Count - 1].ToString();
                comboBoxBaud.Text = comboBoxBaud.Items[comboBoxBaud.Items.Count - 1].ToString();

                labelTanggal.Text = DateTime.Now.ToString("dddd, dd MMMM yyyy", new CultureInfo("id-ID"));
            }
            catch (Exception ex)
            {
                return;
            }
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            String data = serialPort.ReadLine();
            showData(data);
        }

        private delegate void showDataDelegate(object item);

        private void showData(object item)
        {
            if (InvokeRequired)
            {
                listBox1.Invoke(new showDataDelegate(showData), item);
            }
            else
            { 
                listBox1.Items.Add(item);
                listBox1.SelectedIndex = listBox1.Items.Count - 1;
                splitData(item);
            }
        }

        private void splitData(object item)
        {
            string[] data = item.ToString().Split(',');

            motion = data[0];
            motionBox.Text = motion;
            status = data[1];
            statusBox.Text = status;

            if (motion == "MotionDetected" && status == "Caution")
            {
                motionBox.ForeColor = Color.White;
                motionBox.BackColor = Color.Red;

                statusBox.ForeColor = Color.Black;
                statusBox.BackColor = Color.Yellow;

                pictureBox.Image = Properties.Resources.Walking_Man;
            }
            else if (motion == "NoMotionDetected" && status == "Clear")
            {
                motionBox.ForeColor = Color.White;
                motionBox.BackColor = Color.Green;

                statusBox.ForeColor = Color.White;
                statusBox.BackColor = Color.Green;

                pictureBox.Image = Properties.Resources.Standing_Man;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            labelWaktu.Text = DateTime.Now.ToString("hh : mm : ss");
        }

        private void buttonPort_Click(object sender, EventArgs e)
        {
            try
            {
                if (serialPort.IsOpen == false)
                {
                    buttonPort.Text = "Disconnect";
                    serialPort.PortName = comboBoxPort.Text;
                    serialPort.BaudRate = Int32.Parse(comboBoxBaud.Text);
                    serialPort.NewLine = "\n\r";
                    serialPort.Open();
                    toolStripLabel1.Text = "Connected to " + serialPort.PortName;
                }
                else if (serialPort.IsOpen == true)
                {
                    buttonPort.Text = "Connect";
                    serialPort.Close();
                    toolStripLabel1.Text = "Disconnected from " + serialPort.PortName;
                }
            }
            catch (Exception ex)
            {
                toolStripLabel1.Text = "ERROR : " + ex.Message.ToString();
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics graphics = e.Graphics;
            Pen pen = new Pen(Color.FromArgb(221, 56, 87), 1);

            Rectangle area = new Rectangle(0, 0, this.Width - 1, this.Height - 1);
            LinearGradientBrush brush = new LinearGradientBrush(area, Color.FromArgb(234, 203, 198), 
                                                                      Color.FromArgb(221, 56, 87),
                                                                      LinearGradientMode.Vertical);
            graphics.FillRectangle(brush, area);
            graphics.DrawRectangle(pen, area);
        }
    }
}
