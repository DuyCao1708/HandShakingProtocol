using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WFAHandShakingProtocol
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string dataSend;
        byte[] bytesSend = new byte[18];
        string dataReceived;
        byte[] tempBytes;
        byte[] bytesReceived;

        int successCount = 0;
        int errorCount = 0;

        //int count = 0;

        //STX
        byte[] bSTX = new byte[1] { 0x02 };
        //CMD
        byte[] bGMOV = new byte[4] { 0x4D, 0x4F, 0x56, 0x4C }; // Command GMOV if movButton is clicked
        byte[] bGPOS = new byte[4] { 0x47, 0x50, 0x4F, 0x53 }; // Command GPOS if posButton is clicked
        byte[] bGVEL = new byte[4] { 0x47, 0x56, 0x45, 0x4C }; // Command GVEL if velButton is clicked
        byte[] bGSTT = new byte[4] { 0x47, 0x53, 0x54, 0x54 }; // Command GSTT if sttButton is clicked
        byte[] bGCUS = new byte[4] { 0x47, 0x43, 0x55, 0x53 }; // Command GCUS if client sends data manually
        byte[] bGTIM = new byte[4] { 0x47, 0x54, 0x49, 0x4D }; // Command GTIM if client sends data automatically by timer
        //OPTION
        byte[] bOPT = new byte[3] { 0x4C, 0x30, 0x32 }; // Default transmit L-0-2
        //DATA
        byte[] bDATA = new byte[8] { 0x54, 0x55, 0x43, 0x41, 0x4F, 0x44, 0x55, 0x59 }; // Default transmit T-U-C-A-O-D-U-Y
        //SYNC/ACK
        byte[] bSYNC = new byte[1] { 0x16 };
        byte[] bACK = new byte[1] { 0x06 };
        //ETX
        byte[] bETX = new byte[1] { 0x03 };

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] portsName = SerialPort.GetPortNames();
            nameCBox.Items.AddRange(portsName);
            //Default value for baudrate
            baudrateBox.SelectedItem = "9600";
            //Maximum character for manually send data
            sendText.MaxLength = 8;
            //Unable editting for counter success and error
            successText.ReadOnly = true;
            errorText.ReadOnly = true;
            //Set event timer tick by 2 seconds
            timer.Interval = 50;
            //Always display latest item
            receivedDataBox.IntegralHeight = true;
            //Set count
            successText.Text = successCount.ToString();
            errorText.Text = errorCount.ToString();
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort.PortName = nameCBox.Text;
                serialPort.BaudRate = Convert.ToInt32(baudrateBox.Text);

                serialPort.Open();
                appStatusText.Text = "Port opened!";
                eventRadio.Checked = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Close();
                appStatusText.Text = "Port closed!";
                eventRadio.Checked = false;
                timerRadio.Checked = false;
                this.Invoke(new EventHandler(clearButton_Click));
            }
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            receivedDataBox.Items.Clear();
            successText.Text = "0";
            successCount = 0;
            errorText.Text = "0";
            errorCount = 0;
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            dataSend = sendText.Text;
            // Convert data in textBox into byte array
            byte[] bytes = Encoding.ASCII.GetBytes(dataSend);
            if (bytes.Length < 8)
            {
                // If byte array has less than 8 elements, add 0x00 into the remainings
                byte[] newbytes = new byte[8];
                Array.Copy(bytes, newbytes, bytes.Length);
                for (int i = bytes.Length; i < newbytes.Length; i++)
                {
                    newbytes[i] = 0x00;
                }
                Array.Resize(ref bytes, 8);
                Array.Copy(newbytes, bytes, newbytes.Length);
            }
            // Concatenate arrays to create a transmitting framedata
            byte[] cusDataSend = bSTX.Concat(bGCUS).Concat(bOPT).Concat(bytes).Concat(bSYNC).Concat(bETX).ToArray();
            // Convert the recent array to string of bytes, consisting of hex of each byte
            string cusDataSendToHex = BitConverter.ToString(cusDataSend).Replace("-", " ");
            // Eliminate the start, sync/ack, exit byte of the framedata to display on the listBox
            byte[] cusDataSendDisplay = bGCUS.Concat(bOPT).Concat(bytes).ToArray();
            // Replace the escape sequence created by 0 character in bytes when concatenating
            string cusDataSendToChar = Encoding.ASCII.GetString(cusDataSendDisplay).Replace("\0", "");

            if (serialPort.IsOpen && eventRadio.Checked)
            {
                // Write framedata to serial port
                serialPort.Write(cusDataSend, 0, cusDataSend.Length);
                // Store the written data to validate later
                Array.Copy(cusDataSend, bytesSend, cusDataSend.Length);
                receivedDataBox.Items.Add("CUS data (HEX): " + cusDataSendToHex);
                receivedDataBox.Items.Add("CUS data (CHAR): " + cusDataSendToChar);
                receivedDataBox.Items.Add("");
                // Always display the lastest item
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            }
        }

        private void posButton_Click(object sender, EventArgs e)
        {
            byte[] posDataSend = bSTX.Concat(bGPOS).Concat(bOPT).Concat(bDATA).Concat(bSYNC).Concat(bETX).ToArray();
            string posDataSendToHex = BitConverter.ToString(posDataSend).Replace("-", " ");
            byte[] posDataSendDisplay = bGPOS.Concat(bOPT).Concat(bDATA).ToArray();
            string posDataSendToChar = Encoding.ASCII.GetString(posDataSendDisplay).Replace("\0", "");

            if (serialPort.IsOpen && eventRadio.Checked)
            {
                serialPort.Write(posDataSend, 0, posDataSend.Length);
                Array.Copy(posDataSend, bytesSend, posDataSend.Length);
                receivedDataBox.Items.Add("POS data (HEX): " + posDataSendToHex);
                receivedDataBox.Items.Add("POS data (CHAR): " + posDataSendToChar);
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            }
        }

        private void movButton_Click(object sender, EventArgs e)
        {
            byte[] movDataSend = bSTX.Concat(bGMOV).Concat(bOPT).Concat(bDATA).Concat(bSYNC).Concat(bETX).ToArray();
            string movDataSendToHex = BitConverter.ToString(movDataSend).Replace("-", " ");
            byte[] movDataSendDisplay = bGMOV.Concat(bOPT).Concat(bDATA).ToArray();
            string movDataSendToChar = Encoding.ASCII.GetString(movDataSendDisplay).Replace("\0", "");

            if (serialPort.IsOpen && eventRadio.Checked)
            {
                serialPort.Write(movDataSend, 0, movDataSend.Length);
                Array.Copy(movDataSend, bytesSend, movDataSend.Length);
                receivedDataBox.Items.Add("MOV data (HEX): " + movDataSendToHex);
                receivedDataBox.Items.Add("MOV data (CHAR): " + movDataSendToChar);
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            }
        }

        private void velButton_Click(object sender, EventArgs e)
        {
            byte[] velDataSend = bSTX.Concat(bGVEL).Concat(bOPT).Concat(bDATA).Concat(bSYNC).Concat(bETX).ToArray();
            string velDataSendToHex = BitConverter.ToString(velDataSend).Replace("-", " ");
            byte[] velDataSendDisplay = bGVEL.Concat(bOPT).Concat(bDATA).ToArray();
            string velDataSendToChar = Encoding.ASCII.GetString(velDataSendDisplay).Replace("\0", "");

            if (serialPort.IsOpen && eventRadio.Checked)
            {
                serialPort.Write(velDataSend, 0, velDataSend.Length);
                Array.Copy(velDataSend, bytesSend, velDataSend.Length);
                receivedDataBox.Items.Add("VEL data (HEX): " + velDataSendToHex);
                receivedDataBox.Items.Add("VEL data (CHAR): " + velDataSendToChar);
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            }
        }

        private void sttButton_Click(object sender, EventArgs e)
        {
            byte[] sttDataSend = bSTX.Concat(bGSTT).Concat(bOPT).Concat(bDATA).Concat(bSYNC).Concat(bETX).ToArray();
            string sttDataSendToHex = BitConverter.ToString(sttDataSend).Replace("-", " ");
            byte[] sttDataSendDisplay = bGSTT.Concat(bOPT).Concat(bDATA).ToArray();
            string sttDataSendToChar = Encoding.ASCII.GetString(sttDataSendDisplay).Replace("\0", "");

            if (serialPort.IsOpen && eventRadio.Checked)
            {
                serialPort.Write(sttDataSend, 0, sttDataSend.Length);
                Array.Copy(sttDataSend, bytesSend, sttDataSend.Length);
                receivedDataBox.Items.Add("STT data (HEX): " + sttDataSendToHex);
                receivedDataBox.Items.Add("STT data (CHAR): " + sttDataSendToChar);
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            }
        }

        private void timerRadio_CheckedChanged(object sender, EventArgs e)
        {
            if (timerRadio.Checked)
            {
                timer.Start();
            }
        }

        private void eventRadio_CheckedChanged(object sender, EventArgs e)
        {
            if (eventRadio.Checked || !timerRadio.Checked)
            {
                timer.Stop();
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            byte[] timDataSend = bSTX.Concat(bGTIM).Concat(bOPT).Concat(bDATA).Concat(bSYNC).Concat(bETX).ToArray();
            string timDataSendToHex = BitConverter.ToString(timDataSend).Replace("-", " ");
            byte[] timDataSendDisplay = bGTIM.Concat(bOPT).Concat(bDATA).ToArray();
            string timDataSendToChar = Encoding.ASCII.GetString(timDataSendDisplay).Replace("\0", "");

            if (serialPort.IsOpen && timerRadio.Checked)
            {
                serialPort.Write(timDataSend, 0, timDataSend.Length);
                Array.Copy(timDataSend, bytesSend, timDataSend.Length);
                receivedDataBox.Items.Add("TIM data (HEX): " + timDataSendToHex);
                receivedDataBox.Items.Add("TIM data (CHAR): " + timDataSendToChar);
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            }

            //count++;
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // When data available in buffer, read those
            dataReceived = serialPort.ReadExisting();
            // Store data to a temporary variable until it has 18 elements
            if (tempBytes == null)
            {
                tempBytes = Encoding.ASCII.GetBytes(dataReceived);
            }    
            else
            {
                tempBytes = tempBytes.Concat(Encoding.ASCII.GetBytes(dataReceived)).ToArray();
            }
            if (tempBytes.Length == 18)
            {
                // Convey data from temp variable to official variable and renew temp variable
                bytesReceived = tempBytes;
                tempBytes = new byte[0];

                // Execute AppendDataToReceivedDataBox to display received data
                this.Invoke(new EventHandler(AppendDataToReceivedDataBox));
            }
        }

        private void AppendDataToReceivedDataBox(object sender, EventArgs e)
        {
            // Check if byte received data has 18 elements, if not then return null
            if (bytesReceived.Length != 18) return;
            string dataReceivedToHex = BitConverter.ToString(bytesReceived).Replace("-", " ");
            string dataReceivedToChar = Encoding.ASCII.GetString(bytesReceived).Replace("\0", "").Replace("\u0006", "").Replace("\u0003", "").Replace("\u0002", "");
            receivedDataBox.Items.Add("Received data (HEX): " + dataReceivedToHex);
            receivedDataBox.Items.Add("Received data (CHAR): " + dataReceivedToChar);
            receivedDataBox.Items.Add("");
            receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
            // Execute ValidateData to validate received data and display result
            this.Invoke(new EventHandler(ValidateData));
        }

        private void ValidateData(object sender, EventArgs e)
        {
            byte[] bytesCommandReceived = new byte[4];
            byte[] bytesOptionReceived = new byte[3];
            byte[] bytesDataReceived = new byte[8];

            // Extract command, option and data byte
            Array.Copy(bytesReceived, 1, bytesCommandReceived, 0, 4);
            Array.Copy(bytesReceived, 5, bytesOptionReceived, 0, 3);
            Array.Copy(bytesReceived, 8, bytesDataReceived, 0, 8);

            // Extract sent data
            byte[] bytesDataSend = new byte[8];
            Array.Copy(bytesSend, 8, bytesDataSend, 0, 8);

            // Declare flag to validate
            bool validateFlag = true; 

            // Check if command bytes are wrong
            if (!bytesCommandReceived.SequenceEqual(bGPOS) && !bytesCommandReceived.SequenceEqual(bGVEL) && !bytesCommandReceived.SequenceEqual(bGSTT) && !bytesCommandReceived.SequenceEqual(bGMOV) && !bytesCommandReceived.SequenceEqual(bGCUS) && !bytesCommandReceived.SequenceEqual(bGTIM)) 
            {
                validateFlag = false;
            }

            // Check if option bytes are wrong
            if (!bytesOptionReceived.SequenceEqual(bOPT))
            {
                validateFlag = false;
            }

            // Check if data bytes are wrong
            if (!bytesDataReceived.SequenceEqual(bytesDataSend))
            {
                validateFlag = false;
            }

            // Display result bases on validation flag, success if true and vice versa
            if (validateFlag)
            {
                receivedDataBox.Items.Add("Transmission/Reception SUCCESSFUL!");
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
                successCount++;
                successText.Text = (successCount).ToString();
            }
            else
            {
                receivedDataBox.Items.Add("Transmission/Reception FAILED!");
                receivedDataBox.Items.Add("");
                receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;
                errorCount++;
                errorText.Text = (errorCount).ToString();
            }
            receivedDataBox.TopIndex = receivedDataBox.Items.Count - 1;

            // Renew sent bytes to prepare a new transmission
            bytesSend = new byte[18];

            //if (count == 10000)
            //{
            //    timer.Stop();
            //    eventRadio.Checked = true;
            //    timerRadio.Checked = false;
            //}    
        }
    }
}
