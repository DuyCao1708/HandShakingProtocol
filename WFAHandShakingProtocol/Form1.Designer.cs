
namespace WFAHandShakingProtocol
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.errorText = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.successText = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.appStatusText = new System.Windows.Forms.Label();
            this.clearButton = new System.Windows.Forms.Button();
            this.receivedDataBox = new System.Windows.Forms.ListBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.closeButton = new System.Windows.Forms.Button();
            this.openButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.baudrateBox = new System.Windows.Forms.ComboBox();
            this.nameCBox = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.sttButton = new System.Windows.Forms.Button();
            this.velButton = new System.Windows.Forms.Button();
            this.movButton = new System.Windows.Forms.Button();
            this.posButton = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.eventRadio = new System.Windows.Forms.RadioButton();
            this.timerRadio = new System.Windows.Forms.RadioButton();
            this.sendButton = new System.Windows.Forms.Button();
            this.sendText = new System.Windows.Forms.TextBox();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.chBoxLedPC13 = new System.Windows.Forms.CheckBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.setALedButton = new System.Windows.Forms.Button();
            this.tBarALed = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.aLedText = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tBarALed)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.errorText);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.successText);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.appStatusText);
            this.groupBox1.Controls.Add(this.clearButton);
            this.groupBox1.Controls.Add(this.receivedDataBox);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(642, 421);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Receive Data";
            // 
            // errorText
            // 
            this.errorText.Location = new System.Drawing.Point(478, 380);
            this.errorText.Name = "errorText";
            this.errorText.Size = new System.Drawing.Size(73, 26);
            this.errorText.TabIndex = 12;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(429, 383);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 20);
            this.label3.TabIndex = 11;
            this.label3.Text = "Error";
            // 
            // successText
            // 
            this.successText.Location = new System.Drawing.Point(348, 380);
            this.successText.Name = "successText";
            this.successText.Size = new System.Drawing.Size(73, 26);
            this.successText.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(272, 383);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 20);
            this.label4.TabIndex = 9;
            this.label4.Text = "Success";
            // 
            // appStatusText
            // 
            this.appStatusText.AutoSize = true;
            this.appStatusText.Location = new System.Drawing.Point(6, 383);
            this.appStatusText.Name = "appStatusText";
            this.appStatusText.Size = new System.Drawing.Size(135, 20);
            this.appStatusText.TabIndex = 7;
            this.appStatusText.Text = "Application status";
            // 
            // clearButton
            // 
            this.clearButton.Location = new System.Drawing.Point(561, 374);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(75, 39);
            this.clearButton.TabIndex = 6;
            this.clearButton.Text = "Clear";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
            // 
            // receivedDataBox
            // 
            this.receivedDataBox.FormattingEnabled = true;
            this.receivedDataBox.ItemHeight = 20;
            this.receivedDataBox.Location = new System.Drawing.Point(6, 25);
            this.receivedDataBox.Name = "receivedDataBox";
            this.receivedDataBox.Size = new System.Drawing.Size(630, 344);
            this.receivedDataBox.TabIndex = 5;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.closeButton);
            this.groupBox2.Controls.Add(this.openButton);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.baudrateBox);
            this.groupBox2.Controls.Add(this.nameCBox);
            this.groupBox2.Location = new System.Drawing.Point(666, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(356, 274);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Serial";
            // 
            // closeButton
            // 
            this.closeButton.Location = new System.Drawing.Point(217, 191);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(75, 41);
            this.closeButton.TabIndex = 7;
            this.closeButton.Text = "Close";
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // openButton
            // 
            this.openButton.Location = new System.Drawing.Point(72, 191);
            this.openButton.Name = "openButton";
            this.openButton.Size = new System.Drawing.Size(75, 41);
            this.openButton.TabIndex = 6;
            this.openButton.Text = "Open";
            this.openButton.UseVisualStyleBackColor = true;
            this.openButton.Click += new System.EventHandler(this.openButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(37, 126);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 20);
            this.label2.TabIndex = 5;
            this.label2.Text = "Baudrate";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 60);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Name";
            // 
            // baudrateBox
            // 
            this.baudrateBox.FormattingEnabled = true;
            this.baudrateBox.Items.AddRange(new object[] {
            "4800",
            "9600",
            "19200",
            "115200"});
            this.baudrateBox.Location = new System.Drawing.Point(151, 123);
            this.baudrateBox.Name = "baudrateBox";
            this.baudrateBox.Size = new System.Drawing.Size(185, 28);
            this.baudrateBox.TabIndex = 3;
            // 
            // nameCBox
            // 
            this.nameCBox.FormattingEnabled = true;
            this.nameCBox.Location = new System.Drawing.Point(151, 57);
            this.nameCBox.Name = "nameCBox";
            this.nameCBox.Size = new System.Drawing.Size(185, 28);
            this.nameCBox.TabIndex = 2;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.sttButton);
            this.groupBox3.Controls.Add(this.velButton);
            this.groupBox3.Controls.Add(this.movButton);
            this.groupBox3.Controls.Add(this.posButton);
            this.groupBox3.Location = new System.Drawing.Point(666, 293);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(357, 257);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Static Command";
            // 
            // sttButton
            // 
            this.sttButton.Location = new System.Drawing.Point(186, 151);
            this.sttButton.Name = "sttButton";
            this.sttButton.Size = new System.Drawing.Size(170, 100);
            this.sttButton.TabIndex = 3;
            this.sttButton.Text = "STT";
            this.sttButton.UseVisualStyleBackColor = true;
            this.sttButton.Click += new System.EventHandler(this.sttButton_Click);
            // 
            // velButton
            // 
            this.velButton.Location = new System.Drawing.Point(6, 151);
            this.velButton.Name = "velButton";
            this.velButton.Size = new System.Drawing.Size(170, 100);
            this.velButton.TabIndex = 2;
            this.velButton.Text = "VEL";
            this.velButton.UseVisualStyleBackColor = true;
            this.velButton.Click += new System.EventHandler(this.velButton_Click);
            // 
            // movButton
            // 
            this.movButton.Location = new System.Drawing.Point(184, 34);
            this.movButton.Name = "movButton";
            this.movButton.Size = new System.Drawing.Size(170, 100);
            this.movButton.TabIndex = 1;
            this.movButton.Text = "MOV";
            this.movButton.UseVisualStyleBackColor = true;
            this.movButton.Click += new System.EventHandler(this.movButton_Click);
            // 
            // posButton
            // 
            this.posButton.Location = new System.Drawing.Point(6, 34);
            this.posButton.Name = "posButton";
            this.posButton.Size = new System.Drawing.Size(170, 100);
            this.posButton.TabIndex = 0;
            this.posButton.Text = "POS";
            this.posButton.UseVisualStyleBackColor = true;
            this.posButton.Click += new System.EventHandler(this.posButton_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.eventRadio);
            this.groupBox4.Controls.Add(this.timerRadio);
            this.groupBox4.Controls.Add(this.sendButton);
            this.groupBox4.Controls.Add(this.sendText);
            this.groupBox4.Location = new System.Drawing.Point(12, 439);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(642, 111);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Send Data";
            // 
            // eventRadio
            // 
            this.eventRadio.AutoSize = true;
            this.eventRadio.Location = new System.Drawing.Point(107, 71);
            this.eventRadio.Name = "eventRadio";
            this.eventRadio.Size = new System.Drawing.Size(75, 24);
            this.eventRadio.TabIndex = 3;
            this.eventRadio.TabStop = true;
            this.eventRadio.Text = "Event";
            this.eventRadio.UseVisualStyleBackColor = true;
            this.eventRadio.CheckedChanged += new System.EventHandler(this.eventRadio_CheckedChanged);
            // 
            // timerRadio
            // 
            this.timerRadio.AutoSize = true;
            this.timerRadio.Location = new System.Drawing.Point(7, 71);
            this.timerRadio.Name = "timerRadio";
            this.timerRadio.Size = new System.Drawing.Size(73, 24);
            this.timerRadio.TabIndex = 2;
            this.timerRadio.TabStop = true;
            this.timerRadio.Text = "Timer";
            this.timerRadio.UseVisualStyleBackColor = true;
            this.timerRadio.CheckedChanged += new System.EventHandler(this.timerRadio_CheckedChanged);
            // 
            // sendButton
            // 
            this.sendButton.Location = new System.Drawing.Point(561, 22);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(75, 33);
            this.sendButton.TabIndex = 1;
            this.sendButton.Text = "SEND";
            this.sendButton.UseVisualStyleBackColor = true;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // sendText
            // 
            this.sendText.Location = new System.Drawing.Point(6, 25);
            this.sendText.Name = "sendText";
            this.sendText.Size = new System.Drawing.Size(549, 26);
            this.sendText.TabIndex = 0;
            // 
            // timer
            // 
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // serialPort
            // 
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.chBoxLedPC13);
            this.groupBox5.Location = new System.Drawing.Point(1028, 12);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(156, 80);
            this.groupBox5.TabIndex = 4;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "DLED - PC13";
            // 
            // chBoxLedPC13
            // 
            this.chBoxLedPC13.AutoSize = true;
            this.chBoxLedPC13.Location = new System.Drawing.Point(27, 34);
            this.chBoxLedPC13.Name = "chBoxLedPC13";
            this.chBoxLedPC13.Size = new System.Drawing.Size(102, 24);
            this.chBoxLedPC13.TabIndex = 0;
            this.chBoxLedPC13.Text = "ON / OFF";
            this.chBoxLedPC13.UseVisualStyleBackColor = true;
            this.chBoxLedPC13.CheckedChanged += new System.EventHandler(this.chBoxLedPC13_CheckedChanged);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.aLedText);
            this.groupBox6.Controls.Add(this.label6);
            this.groupBox6.Controls.Add(this.label5);
            this.groupBox6.Controls.Add(this.tBarALed);
            this.groupBox6.Controls.Add(this.setALedButton);
            this.groupBox6.Location = new System.Drawing.Point(1029, 99);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(155, 452);
            this.groupBox6.TabIndex = 5;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "ALED";
            // 
            // setALedButton
            // 
            this.setALedButton.Location = new System.Drawing.Point(26, 411);
            this.setALedButton.Name = "setALedButton";
            this.setALedButton.Size = new System.Drawing.Size(110, 35);
            this.setALedButton.TabIndex = 0;
            this.setALedButton.Text = "Set";
            this.setALedButton.UseVisualStyleBackColor = true;
            this.setALedButton.Click += new System.EventHandler(this.setALedButton_Click);
            // 
            // tBarALed
            // 
            this.tBarALed.Location = new System.Drawing.Point(50, 55);
            this.tBarALed.Maximum = 625;
            this.tBarALed.Name = "tBarALed";
            this.tBarALed.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tBarALed.Size = new System.Drawing.Size(69, 279);
            this.tBarALed.TabIndex = 4;
            this.tBarALed.Scroll += new System.EventHandler(this.tBarALed_Scroll);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(46, 36);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(36, 20);
            this.label5.TabIndex = 5;
            this.label5.Text = "625";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(46, 337);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(18, 20);
            this.label6.TabIndex = 6;
            this.label6.Text = "0";
            // 
            // aLedText
            // 
            this.aLedText.Location = new System.Drawing.Point(28, 369);
            this.aLedText.Name = "aLedText";
            this.aLedText.Size = new System.Drawing.Size(108, 26);
            this.aLedText.TabIndex = 7;
            this.aLedText.TextChanged += new System.EventHandler(this.aLedText_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1196, 563);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tBarALed)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button clearButton;
        private System.Windows.Forms.ListBox receivedDataBox;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.Button openButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox baudrateBox;
        private System.Windows.Forms.ComboBox nameCBox;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button sttButton;
        private System.Windows.Forms.Button velButton;
        private System.Windows.Forms.Button movButton;
        private System.Windows.Forms.Button posButton;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.RadioButton eventRadio;
        private System.Windows.Forms.RadioButton timerRadio;
        private System.Windows.Forms.Button sendButton;
        private System.Windows.Forms.TextBox sendText;
        private System.Windows.Forms.Timer timer;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Label appStatusText;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox errorText;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox successText;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.CheckBox chBoxLedPC13;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TrackBar tBarALed;
        private System.Windows.Forms.Button setALedButton;
        private System.Windows.Forms.TextBox aLedText;
    }
}

