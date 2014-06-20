namespace Enhancement
{
    partial class Enhancement
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.buttonSaveTrain = new System.Windows.Forms.Button();
            this.textBoxTrainDetail = new System.Windows.Forms.TextBox();
            this.buttonTrain = new System.Windows.Forms.Button();
            this.buttonSelectHigh = new System.Windows.Forms.Button();
            this.buttonSelectLow = new System.Windows.Forms.Button();
            this.textBoxLocationHigh = new System.Windows.Forms.TextBox();
            this.textBoxLocationLow = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBoxLow = new System.Windows.Forms.PictureBox();
            this.buttonSelectImage = new System.Windows.Forms.Button();
            this.pictureBoxHigh = new System.Windows.Forms.PictureBox();
            this.buttonSaveImage = new System.Windows.Forms.Button();
            this.tabControl.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxHigh)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Controls.Add(this.tabPage1);
            this.tabControl.Controls.Add(this.tabPage2);
            this.tabControl.Location = new System.Drawing.Point(14, 15);
            this.tabControl.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(900, 454);
            this.tabControl.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.buttonSaveImage);
            this.tabPage1.Controls.Add(this.pictureBoxHigh);
            this.tabPage1.Controls.Add(this.buttonSelectImage);
            this.tabPage1.Controls.Add(this.pictureBoxLow);
            this.tabPage1.Location = new System.Drawing.Point(4, 26);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.tabPage1.Size = new System.Drawing.Size(892, 424);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Enhance";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.buttonSaveTrain);
            this.tabPage2.Controls.Add(this.textBoxTrainDetail);
            this.tabPage2.Controls.Add(this.buttonTrain);
            this.tabPage2.Controls.Add(this.buttonSelectHigh);
            this.tabPage2.Controls.Add(this.buttonSelectLow);
            this.tabPage2.Controls.Add(this.textBoxLocationHigh);
            this.tabPage2.Controls.Add(this.textBoxLocationLow);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Location = new System.Drawing.Point(4, 26);
            this.tabPage2.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.tabPage2.Size = new System.Drawing.Size(892, 424);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Train";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // buttonSaveTrain
            // 
            this.buttonSaveTrain.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSaveTrain.Enabled = false;
            this.buttonSaveTrain.Location = new System.Drawing.Point(652, 355);
            this.buttonSaveTrain.Name = "buttonSaveTrain";
            this.buttonSaveTrain.Size = new System.Drawing.Size(196, 32);
            this.buttonSaveTrain.TabIndex = 17;
            this.buttonSaveTrain.Text = "Save";
            this.buttonSaveTrain.UseVisualStyleBackColor = true;
            // 
            // textBoxTrainDetail
            // 
            this.textBoxTrainDetail.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxTrainDetail.Location = new System.Drawing.Point(35, 153);
            this.textBoxTrainDetail.Multiline = true;
            this.textBoxTrainDetail.Name = "textBoxTrainDetail";
            this.textBoxTrainDetail.Size = new System.Drawing.Size(813, 196);
            this.textBoxTrainDetail.TabIndex = 16;
            // 
            // buttonTrain
            // 
            this.buttonTrain.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonTrain.Location = new System.Drawing.Point(35, 114);
            this.buttonTrain.Name = "buttonTrain";
            this.buttonTrain.Size = new System.Drawing.Size(813, 32);
            this.buttonTrain.TabIndex = 15;
            this.buttonTrain.Text = "Train";
            this.buttonTrain.UseVisualStyleBackColor = true;
            // 
            // buttonSelectHigh
            // 
            this.buttonSelectHigh.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSelectHigh.Location = new System.Drawing.Point(773, 71);
            this.buttonSelectHigh.Name = "buttonSelectHigh";
            this.buttonSelectHigh.Size = new System.Drawing.Size(75, 30);
            this.buttonSelectHigh.TabIndex = 14;
            this.buttonSelectHigh.Text = "Select...";
            this.buttonSelectHigh.UseVisualStyleBackColor = true;
            // 
            // buttonSelectLow
            // 
            this.buttonSelectLow.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSelectLow.Location = new System.Drawing.Point(773, 31);
            this.buttonSelectLow.Name = "buttonSelectLow";
            this.buttonSelectLow.Size = new System.Drawing.Size(75, 30);
            this.buttonSelectLow.TabIndex = 13;
            this.buttonSelectLow.Text = "Select...";
            this.buttonSelectLow.UseVisualStyleBackColor = true;
            // 
            // textBoxLocationHigh
            // 
            this.textBoxLocationHigh.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxLocationHigh.Location = new System.Drawing.Point(169, 75);
            this.textBoxLocationHigh.Name = "textBoxLocationHigh";
            this.textBoxLocationHigh.Size = new System.Drawing.Size(598, 25);
            this.textBoxLocationHigh.TabIndex = 12;
            // 
            // textBoxLocationLow
            // 
            this.textBoxLocationLow.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxLocationLow.Location = new System.Drawing.Point(169, 35);
            this.textBoxLocationLow.Name = "textBoxLocationLow";
            this.textBoxLocationLow.Size = new System.Drawing.Size(598, 25);
            this.textBoxLocationLow.TabIndex = 11;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(32, 78);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(131, 17);
            this.label2.TabIndex = 10;
            this.label2.Text = "High quality dataset: ";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(36, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 17);
            this.label1.TabIndex = 9;
            this.label1.Text = "Low quality dataset: ";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // pictureBoxLow
            // 
            this.pictureBoxLow.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBoxLow.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBoxLow.Location = new System.Drawing.Point(22, 27);
            this.pictureBoxLow.Name = "pictureBoxLow";
            this.pictureBoxLow.Size = new System.Drawing.Size(393, 295);
            this.pictureBoxLow.TabIndex = 0;
            this.pictureBoxLow.TabStop = false;
            // 
            // buttonSelectImage
            // 
            this.buttonSelectImage.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSelectImage.Location = new System.Drawing.Point(22, 349);
            this.buttonSelectImage.Name = "buttonSelectImage";
            this.buttonSelectImage.Size = new System.Drawing.Size(393, 44);
            this.buttonSelectImage.TabIndex = 1;
            this.buttonSelectImage.Text = "Select Image";
            this.buttonSelectImage.UseVisualStyleBackColor = true;
            // 
            // pictureBoxHigh
            // 
            this.pictureBoxHigh.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBoxHigh.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBoxHigh.Location = new System.Drawing.Point(461, 27);
            this.pictureBoxHigh.Name = "pictureBoxHigh";
            this.pictureBoxHigh.Size = new System.Drawing.Size(393, 295);
            this.pictureBoxHigh.TabIndex = 2;
            this.pictureBoxHigh.TabStop = false;
            // 
            // buttonSaveImage
            // 
            this.buttonSaveImage.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSaveImage.Enabled = false;
            this.buttonSaveImage.Location = new System.Drawing.Point(461, 349);
            this.buttonSaveImage.Name = "buttonSaveImage";
            this.buttonSaveImage.Size = new System.Drawing.Size(393, 44);
            this.buttonSaveImage.TabIndex = 3;
            this.buttonSaveImage.Text = "Save Image";
            this.buttonSaveImage.UseVisualStyleBackColor = true;
            // 
            // Enhancement
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(928, 485);
            this.Controls.Add(this.tabControl);
            this.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.MaximizeBox = false;
            this.Name = "Enhancement";
            this.Text = "Enhancement";
            this.tabControl.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxHigh)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button buttonSaveImage;
        private System.Windows.Forms.PictureBox pictureBoxHigh;
        private System.Windows.Forms.Button buttonSelectImage;
        private System.Windows.Forms.PictureBox pictureBoxLow;
        private System.Windows.Forms.Button buttonSaveTrain;
        private System.Windows.Forms.TextBox textBoxTrainDetail;
        private System.Windows.Forms.Button buttonTrain;
        private System.Windows.Forms.Button buttonSelectHigh;
        private System.Windows.Forms.Button buttonSelectLow;
        private System.Windows.Forms.TextBox textBoxLocationHigh;
        private System.Windows.Forms.TextBox textBoxLocationLow;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}

