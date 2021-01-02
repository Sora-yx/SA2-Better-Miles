﻿namespace SA2ModManager
{
	partial class MainForm
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
			System.Windows.Forms.GroupBox groupBox2;
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.fileCheckBox = new System.Windows.Forms.CheckBox();
			this.consoleCheckBox = new System.Windows.Forms.CheckBox();
			this.modDescription = new System.Windows.Forms.Label();
			this.modDownButton = new System.Windows.Forms.Button();
			this.modUpButton = new System.Windows.Forms.Button();
			this.modListView = new System.Windows.Forms.ListView();
			this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.saveButton = new System.Windows.Forms.Button();
			this.saveAndPlayButton = new System.Windows.Forms.Button();
			this.installButton = new System.Windows.Forms.Button();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.configureModButton = new System.Windows.Forms.Button();
			this.modBottomButton = new System.Windows.Forms.Button();
			this.modTopButton = new System.Windows.Forms.Button();
			this.buttonNewMod = new System.Windows.Forms.Button();
			this.buttonRefreshModList = new System.Windows.Forms.Button();
			this.tabPage2 = new System.Windows.Forms.TabPage();
			this.codesCheckedListBox = new System.Windows.Forms.CheckedListBox();
			this.tabPage3 = new System.Windows.Forms.TabPage();
			this.installURLHandlerButton = new System.Windows.Forms.Button();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.buttonCheckForUpdates = new System.Windows.Forms.Button();
			this.label4 = new System.Windows.Forms.Label();
			this.checkUpdateModsStartup = new System.Windows.Forms.CheckBox();
			this.numericUpdateFrequency = new System.Windows.Forms.NumericUpDown();
			this.comboUpdateFrequency = new System.Windows.Forms.ComboBox();
			this.checkUpdateStartup = new System.Windows.Forms.CheckBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.borderlessWindowCheckBox = new System.Windows.Forms.CheckBox();
			this.pauseWhenInactiveCheckBox = new System.Windows.Forms.CheckBox();
			this.modContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.openFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.checkForUpdatesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.verifyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.forceUpdateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.uninstallToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
			this.developerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.generateManifestToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.screenCheckBox = new System.Windows.Forms.CheckBox();
			groupBox2 = new System.Windows.Forms.GroupBox();
			groupBox2.SuspendLayout();
			this.tabControl1.SuspendLayout();
			this.tabPage1.SuspendLayout();
			this.tabPage2.SuspendLayout();
			this.tabPage3.SuspendLayout();
			this.groupBox4.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpdateFrequency)).BeginInit();
			this.groupBox1.SuspendLayout();
			this.modContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox2
			// 
			groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			groupBox2.Controls.Add(this.screenCheckBox);
			groupBox2.Controls.Add(this.fileCheckBox);
			groupBox2.Controls.Add(this.consoleCheckBox);
			groupBox2.Location = new System.Drawing.Point(6, 54);
			groupBox2.Name = "groupBox2";
			groupBox2.Size = new System.Drawing.Size(366, 42);
			groupBox2.TabIndex = 1;
			groupBox2.TabStop = false;
			groupBox2.Text = "Debug Messages";
			// 
			// fileCheckBox
			// 
			this.fileCheckBox.AutoSize = true;
			this.fileCheckBox.Location = new System.Drawing.Point(142, 19);
			this.fileCheckBox.Name = "fileCheckBox";
			this.fileCheckBox.Size = new System.Drawing.Size(42, 17);
			this.fileCheckBox.TabIndex = 2;
			this.fileCheckBox.Text = "File";
			this.fileCheckBox.UseVisualStyleBackColor = true;
			// 
			// consoleCheckBox
			// 
			this.consoleCheckBox.AutoSize = true;
			this.consoleCheckBox.Location = new System.Drawing.Point(6, 19);
			this.consoleCheckBox.Name = "consoleCheckBox";
			this.consoleCheckBox.Size = new System.Drawing.Size(64, 17);
			this.consoleCheckBox.TabIndex = 0;
			this.consoleCheckBox.Text = "Console";
			this.consoleCheckBox.UseVisualStyleBackColor = true;
			// 
			// modDescription
			// 
			this.modDescription.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.modDescription.Location = new System.Drawing.Point(6, 249);
			this.modDescription.Name = "modDescription";
			this.modDescription.Size = new System.Drawing.Size(366, 42);
			this.modDescription.TabIndex = 5;
			this.modDescription.Text = "Description: No mod selected.";
			// 
			// modDownButton
			// 
			this.modDownButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modDownButton.AutoSize = true;
			this.modDownButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.modDownButton.Enabled = false;
			this.modDownButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modDownButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.modDownButton.Location = new System.Drawing.Point(344, 62);
			this.modDownButton.Name = "modDownButton";
			this.modDownButton.Size = new System.Drawing.Size(28, 22);
			this.modDownButton.TabIndex = 2;
			this.modDownButton.Text = "↓";
			this.modDownButton.UseVisualStyleBackColor = true;
			this.modDownButton.Click += new System.EventHandler(this.modDownButton_Click);
			// 
			// modUpButton
			// 
			this.modUpButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modUpButton.AutoSize = true;
			this.modUpButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.modUpButton.Enabled = false;
			this.modUpButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modUpButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.modUpButton.Location = new System.Drawing.Point(344, 34);
			this.modUpButton.Name = "modUpButton";
			this.modUpButton.Size = new System.Drawing.Size(28, 22);
			this.modUpButton.TabIndex = 1;
			this.modUpButton.Text = "↑";
			this.modUpButton.UseVisualStyleBackColor = true;
			this.modUpButton.Click += new System.EventHandler(this.modUpButton_Click);
			// 
			// modListView
			// 
			this.modListView.AllowDrop = true;
			this.modListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.modListView.CheckBoxes = true;
			this.modListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3});
			this.modListView.FullRowSelect = true;
			this.modListView.HideSelection = false;
			this.modListView.Location = new System.Drawing.Point(3, 6);
			this.modListView.Name = "modListView";
			this.modListView.Size = new System.Drawing.Size(335, 211);
			this.modListView.TabIndex = 0;
			this.modListView.UseCompatibleStateImageBehavior = false;
			this.modListView.View = System.Windows.Forms.View.Details;
			this.modListView.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.modListView_ItemCheck);
			this.modListView.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.modListView_ItemDrag);
			this.modListView.SelectedIndexChanged += new System.EventHandler(this.modListView_SelectedIndexChanged);
			this.modListView.DragDrop += new System.Windows.Forms.DragEventHandler(this.modListView_DragDrop);
			this.modListView.DragEnter += new System.Windows.Forms.DragEventHandler(this.modListView_DragEnter);
			this.modListView.DragOver += new System.Windows.Forms.DragEventHandler(this.modListView_DragOver);
			this.modListView.MouseClick += new System.Windows.Forms.MouseEventHandler(this.modListView_MouseClick);
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "Name";
			this.columnHeader1.Width = 154;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Author";
			this.columnHeader2.Width = 113;
			// 
			// columnHeader3
			// 
			this.columnHeader3.Text = "Version";
			// 
			// saveButton
			// 
			this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.saveButton.Location = new System.Drawing.Point(92, 325);
			this.saveButton.Name = "saveButton";
			this.saveButton.Size = new System.Drawing.Size(75, 23);
			this.saveButton.TabIndex = 3;
			this.saveButton.Text = "&Save";
			this.saveButton.UseVisualStyleBackColor = true;
			this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
			// 
			// saveAndPlayButton
			// 
			this.saveAndPlayButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.saveAndPlayButton.AutoSize = true;
			this.saveAndPlayButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.saveAndPlayButton.Location = new System.Drawing.Point(12, 325);
			this.saveAndPlayButton.Name = "saveAndPlayButton";
			this.saveAndPlayButton.Size = new System.Drawing.Size(74, 23);
			this.saveAndPlayButton.TabIndex = 4;
			this.saveAndPlayButton.Text = "Save && &Play";
			this.saveAndPlayButton.UseVisualStyleBackColor = true;
			this.saveAndPlayButton.Click += new System.EventHandler(this.saveAndPlayButton_Click);
			// 
			// installButton
			// 
			this.installButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.installButton.AutoSize = true;
			this.installButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.installButton.Location = new System.Drawing.Point(173, 325);
			this.installButton.Name = "installButton";
			this.installButton.Size = new System.Drawing.Size(76, 23);
			this.installButton.TabIndex = 5;
			this.installButton.Text = "Install loader";
			this.installButton.UseVisualStyleBackColor = true;
			this.installButton.Click += new System.EventHandler(this.installButton_Click);
			// 
			// tabControl1
			// 
			this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tabControl1.Controls.Add(this.tabPage1);
			this.tabControl1.Controls.Add(this.tabPage2);
			this.tabControl1.Controls.Add(this.tabPage3);
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Margin = new System.Windows.Forms.Padding(0, 0, 0, 3);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(386, 317);
			this.tabControl1.TabIndex = 6;
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.configureModButton);
			this.tabPage1.Controls.Add(this.modBottomButton);
			this.tabPage1.Controls.Add(this.modTopButton);
			this.tabPage1.Controls.Add(this.buttonNewMod);
			this.tabPage1.Controls.Add(this.buttonRefreshModList);
			this.tabPage1.Controls.Add(this.modDescription);
			this.tabPage1.Controls.Add(this.modListView);
			this.tabPage1.Controls.Add(this.modDownButton);
			this.tabPage1.Controls.Add(this.modUpButton);
			this.tabPage1.Location = new System.Drawing.Point(4, 22);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage1.Size = new System.Drawing.Size(378, 291);
			this.tabPage1.TabIndex = 0;
			this.tabPage1.Text = "Mods";
			this.tabPage1.UseVisualStyleBackColor = true;
			// 
			// configureModButton
			// 
			this.configureModButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.configureModButton.Enabled = false;
			this.configureModButton.Location = new System.Drawing.Point(87, 223);
			this.configureModButton.Name = "configureModButton";
			this.configureModButton.Size = new System.Drawing.Size(75, 23);
			this.configureModButton.TabIndex = 11;
			this.configureModButton.Text = "Configure...";
			this.configureModButton.UseVisualStyleBackColor = true;
			this.configureModButton.Click += new System.EventHandler(this.configureModButton_Click);
			// 
			// modBottomButton
			// 
			this.modBottomButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modBottomButton.AutoSize = true;
			this.modBottomButton.Enabled = false;
			this.modBottomButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modBottomButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.modBottomButton.Location = new System.Drawing.Point(344, 90);
			this.modBottomButton.Name = "modBottomButton";
			this.modBottomButton.Size = new System.Drawing.Size(28, 22);
			this.modBottomButton.TabIndex = 10;
			this.modBottomButton.Text = "⤓";
			this.modBottomButton.UseVisualStyleBackColor = true;
			this.modBottomButton.Click += new System.EventHandler(this.modBottomButton_Click);
			// 
			// modTopButton
			// 
			this.modTopButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modTopButton.AutoSize = true;
			this.modTopButton.Enabled = false;
			this.modTopButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modTopButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.modTopButton.Location = new System.Drawing.Point(344, 6);
			this.modTopButton.Name = "modTopButton";
			this.modTopButton.Size = new System.Drawing.Size(28, 22);
			this.modTopButton.TabIndex = 9;
			this.modTopButton.Text = "⤒";
			this.modTopButton.UseVisualStyleBackColor = true;
			this.modTopButton.Click += new System.EventHandler(this.modTopButton_Click);
			// 
			// buttonNewMod
			// 
			this.buttonNewMod.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonNewMod.Location = new System.Drawing.Point(263, 223);
			this.buttonNewMod.Name = "buttonNewMod";
			this.buttonNewMod.Size = new System.Drawing.Size(75, 23);
			this.buttonNewMod.TabIndex = 8;
			this.buttonNewMod.Text = "&New Mod";
			this.buttonNewMod.UseVisualStyleBackColor = true;
			this.buttonNewMod.Click += new System.EventHandler(this.buttonNewMod_Click);
			// 
			// buttonRefreshModList
			// 
			this.buttonRefreshModList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.buttonRefreshModList.Location = new System.Drawing.Point(6, 223);
			this.buttonRefreshModList.Name = "buttonRefreshModList";
			this.buttonRefreshModList.Size = new System.Drawing.Size(75, 23);
			this.buttonRefreshModList.TabIndex = 6;
			this.buttonRefreshModList.Text = "&Refresh";
			this.buttonRefreshModList.UseVisualStyleBackColor = true;
			this.buttonRefreshModList.Click += new System.EventHandler(this.buttonRefreshModList_Click);
			// 
			// tabPage2
			// 
			this.tabPage2.Controls.Add(this.codesCheckedListBox);
			this.tabPage2.Location = new System.Drawing.Point(4, 22);
			this.tabPage2.Name = "tabPage2";
			this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage2.Size = new System.Drawing.Size(378, 291);
			this.tabPage2.TabIndex = 1;
			this.tabPage2.Text = "Codes";
			this.tabPage2.UseVisualStyleBackColor = true;
			// 
			// codesCheckedListBox
			// 
			this.codesCheckedListBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.codesCheckedListBox.FormattingEnabled = true;
			this.codesCheckedListBox.Location = new System.Drawing.Point(3, 3);
			this.codesCheckedListBox.Name = "codesCheckedListBox";
			this.codesCheckedListBox.Size = new System.Drawing.Size(372, 285);
			this.codesCheckedListBox.TabIndex = 0;
			this.codesCheckedListBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.codesCheckedListBox_ItemCheck);
			// 
			// tabPage3
			// 
			this.tabPage3.Controls.Add(this.installURLHandlerButton);
			this.tabPage3.Controls.Add(this.groupBox4);
			this.tabPage3.Controls.Add(this.groupBox1);
			this.tabPage3.Controls.Add(groupBox2);
			this.tabPage3.Location = new System.Drawing.Point(4, 22);
			this.tabPage3.Name = "tabPage3";
			this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage3.Size = new System.Drawing.Size(378, 291);
			this.tabPage3.TabIndex = 2;
			this.tabPage3.Text = "Options";
			this.tabPage3.UseVisualStyleBackColor = true;
			// 
			// installURLHandlerButton
			// 
			this.installURLHandlerButton.AutoSize = true;
			this.installURLHandlerButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.installURLHandlerButton.Location = new System.Drawing.Point(6, 198);
			this.installURLHandlerButton.Name = "installURLHandlerButton";
			this.installURLHandlerButton.Size = new System.Drawing.Size(109, 23);
			this.installURLHandlerButton.TabIndex = 4;
			this.installURLHandlerButton.Text = "Install URL Handler";
			this.installURLHandlerButton.UseVisualStyleBackColor = true;
			this.installURLHandlerButton.Click += new System.EventHandler(this.installURLHandlerButton_Click);
			// 
			// groupBox4
			// 
			this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox4.Controls.Add(this.buttonCheckForUpdates);
			this.groupBox4.Controls.Add(this.label4);
			this.groupBox4.Controls.Add(this.checkUpdateModsStartup);
			this.groupBox4.Controls.Add(this.numericUpdateFrequency);
			this.groupBox4.Controls.Add(this.comboUpdateFrequency);
			this.groupBox4.Controls.Add(this.checkUpdateStartup);
			this.groupBox4.Location = new System.Drawing.Point(6, 102);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(366, 90);
			this.groupBox4.TabIndex = 3;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Updates";
			// 
			// buttonCheckForUpdates
			// 
			this.buttonCheckForUpdates.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.buttonCheckForUpdates.Location = new System.Drawing.Point(259, 55);
			this.buttonCheckForUpdates.Name = "buttonCheckForUpdates";
			this.buttonCheckForUpdates.Size = new System.Drawing.Size(75, 23);
			this.buttonCheckForUpdates.TabIndex = 5;
			this.buttonCheckForUpdates.Text = "Check Now";
			this.buttonCheckForUpdates.UseVisualStyleBackColor = true;
			this.buttonCheckForUpdates.Click += new System.EventHandler(this.buttonCheckForUpdates_Click);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(6, 40);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(60, 13);
			this.label4.TabIndex = 2;
			this.label4.Text = "Frequency:";
			// 
			// checkUpdateModsStartup
			// 
			this.checkUpdateModsStartup.AutoSize = true;
			this.checkUpdateModsStartup.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.checkUpdateModsStartup.Location = new System.Drawing.Point(133, 19);
			this.checkUpdateModsStartup.Name = "checkUpdateModsStartup";
			this.checkUpdateModsStartup.Size = new System.Drawing.Size(141, 18);
			this.checkUpdateModsStartup.TabIndex = 1;
			this.checkUpdateModsStartup.Text = "Check mods on startup";
			this.checkUpdateModsStartup.UseVisualStyleBackColor = true;
			// 
			// numericUpdateFrequency
			// 
			this.numericUpdateFrequency.Location = new System.Drawing.Point(133, 57);
			this.numericUpdateFrequency.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
			this.numericUpdateFrequency.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.numericUpdateFrequency.Name = "numericUpdateFrequency";
			this.numericUpdateFrequency.Size = new System.Drawing.Size(120, 20);
			this.numericUpdateFrequency.TabIndex = 4;
			this.numericUpdateFrequency.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
			// 
			// comboUpdateFrequency
			// 
			this.comboUpdateFrequency.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboUpdateFrequency.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.comboUpdateFrequency.FormattingEnabled = true;
			this.comboUpdateFrequency.Items.AddRange(new object[] {
            "Always",
            "Hours",
            "Days",
            "Weeks"});
			this.comboUpdateFrequency.Location = new System.Drawing.Point(6, 56);
			this.comboUpdateFrequency.Name = "comboUpdateFrequency";
			this.comboUpdateFrequency.Size = new System.Drawing.Size(121, 21);
			this.comboUpdateFrequency.TabIndex = 3;
			this.comboUpdateFrequency.SelectedIndexChanged += new System.EventHandler(this.comboUpdateFrequency_SelectedIndexChanged);
			// 
			// checkUpdateStartup
			// 
			this.checkUpdateStartup.AutoSize = true;
			this.checkUpdateStartup.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.checkUpdateStartup.Location = new System.Drawing.Point(6, 19);
			this.checkUpdateStartup.Name = "checkUpdateStartup";
			this.checkUpdateStartup.Size = new System.Drawing.Size(113, 18);
			this.checkUpdateStartup.TabIndex = 0;
			this.checkUpdateStartup.Text = "Check on startup";
			this.checkUpdateStartup.UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox1.Controls.Add(this.borderlessWindowCheckBox);
			this.groupBox1.Controls.Add(this.pauseWhenInactiveCheckBox);
			this.groupBox1.Location = new System.Drawing.Point(6, 6);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(366, 42);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Misc.";
			// 
			// borderlessWindowCheckBox
			// 
			this.borderlessWindowCheckBox.AutoSize = true;
			this.borderlessWindowCheckBox.Location = new System.Drawing.Point(141, 19);
			this.borderlessWindowCheckBox.Name = "borderlessWindowCheckBox";
			this.borderlessWindowCheckBox.Size = new System.Drawing.Size(117, 17);
			this.borderlessWindowCheckBox.TabIndex = 1;
			this.borderlessWindowCheckBox.Text = "Borderless Window";
			this.borderlessWindowCheckBox.UseVisualStyleBackColor = true;
			// 
			// pauseWhenInactiveCheckBox
			// 
			this.pauseWhenInactiveCheckBox.AutoSize = true;
			this.pauseWhenInactiveCheckBox.Location = new System.Drawing.Point(6, 19);
			this.pauseWhenInactiveCheckBox.Name = "pauseWhenInactiveCheckBox";
			this.pauseWhenInactiveCheckBox.Size = new System.Drawing.Size(129, 17);
			this.pauseWhenInactiveCheckBox.TabIndex = 0;
			this.pauseWhenInactiveCheckBox.Text = "Pause When Inactive";
			this.pauseWhenInactiveCheckBox.UseVisualStyleBackColor = true;
			// 
			// modContextMenu
			// 
			this.modContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFolderToolStripMenuItem,
            this.toolStripMenuItem1,
            this.checkForUpdatesToolStripMenuItem,
            this.verifyToolStripMenuItem,
            this.forceUpdateToolStripMenuItem,
            this.uninstallToolStripMenuItem,
            this.toolStripMenuItem3,
            this.developerToolStripMenuItem});
			this.modContextMenu.Name = "modContextMenu";
			this.modContextMenu.Size = new System.Drawing.Size(171, 148);
			// 
			// openFolderToolStripMenuItem
			// 
			this.openFolderToolStripMenuItem.Name = "openFolderToolStripMenuItem";
			this.openFolderToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.openFolderToolStripMenuItem.Text = "Open folder";
			this.openFolderToolStripMenuItem.Click += new System.EventHandler(this.openFolderToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(167, 6);
			// 
			// checkForUpdatesToolStripMenuItem
			// 
			this.checkForUpdatesToolStripMenuItem.Name = "checkForUpdatesToolStripMenuItem";
			this.checkForUpdatesToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.checkForUpdatesToolStripMenuItem.Text = "Check for updates";
			this.checkForUpdatesToolStripMenuItem.Click += new System.EventHandler(this.checkForUpdatesToolStripMenuItem_Click);
			// 
			// verifyToolStripMenuItem
			// 
			this.verifyToolStripMenuItem.Name = "verifyToolStripMenuItem";
			this.verifyToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.verifyToolStripMenuItem.Text = "Verify integrity";
			this.verifyToolStripMenuItem.Click += new System.EventHandler(this.verifyToolStripMenuItem_Click);
			// 
			// forceUpdateToolStripMenuItem
			// 
			this.forceUpdateToolStripMenuItem.Name = "forceUpdateToolStripMenuItem";
			this.forceUpdateToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.forceUpdateToolStripMenuItem.Text = "Force update";
			this.forceUpdateToolStripMenuItem.Click += new System.EventHandler(this.forceUpdateToolStripMenuItem_Click);
			// 
			// uninstallToolStripMenuItem
			// 
			this.uninstallToolStripMenuItem.Name = "uninstallToolStripMenuItem";
			this.uninstallToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.uninstallToolStripMenuItem.Text = "Uninstall";
			this.uninstallToolStripMenuItem.Click += new System.EventHandler(this.uninstallToolStripMenuItem_Click);
			// 
			// toolStripMenuItem3
			// 
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(167, 6);
			// 
			// developerToolStripMenuItem
			// 
			this.developerToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.generateManifestToolStripMenuItem});
			this.developerToolStripMenuItem.Name = "developerToolStripMenuItem";
			this.developerToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.developerToolStripMenuItem.Text = "Developer";
			// 
			// generateManifestToolStripMenuItem
			// 
			this.generateManifestToolStripMenuItem.Name = "generateManifestToolStripMenuItem";
			this.generateManifestToolStripMenuItem.Size = new System.Drawing.Size(170, 22);
			this.generateManifestToolStripMenuItem.Text = "Generate manifest";
			this.generateManifestToolStripMenuItem.Click += new System.EventHandler(this.generateManifestToolStripMenuItem_Click);
			// 
			// screenCheckBox
			// 
			this.screenCheckBox.AutoSize = true;
			this.screenCheckBox.Location = new System.Drawing.Point(76, 19);
			this.screenCheckBox.Name = "screenCheckBox";
			this.screenCheckBox.Size = new System.Drawing.Size(60, 17);
			this.screenCheckBox.TabIndex = 1;
			this.screenCheckBox.Text = "Screen";
			this.screenCheckBox.UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(384, 361);
			this.Controls.Add(this.tabControl1);
			this.Controls.Add(this.installButton);
			this.Controls.Add(this.saveAndPlayButton);
			this.Controls.Add(this.saveButton);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MinimumSize = new System.Drawing.Size(400, 400);
			this.Name = "MainForm";
			this.Padding = new System.Windows.Forms.Padding(0, 0, 0, 3);
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
			this.Text = "SA2 Mod Manager";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.Shown += new System.EventHandler(this.MainForm_Shown);
			groupBox2.ResumeLayout(false);
			groupBox2.PerformLayout();
			this.tabControl1.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.tabPage1.PerformLayout();
			this.tabPage2.ResumeLayout(false);
			this.tabPage3.ResumeLayout(false);
			this.tabPage3.PerformLayout();
			this.groupBox4.ResumeLayout(false);
			this.groupBox4.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpdateFrequency)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.modContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ListView modListView;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.Button modDownButton;
		private System.Windows.Forms.Button modUpButton;
		private System.Windows.Forms.Button saveButton;
		private System.Windows.Forms.Button saveAndPlayButton;
		private System.Windows.Forms.Button installButton;
		private System.Windows.Forms.Label modDescription;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.TabPage tabPage2;
		private System.Windows.Forms.CheckedListBox codesCheckedListBox;
		private System.Windows.Forms.Button buttonRefreshModList;
		private System.Windows.Forms.CheckBox fileCheckBox;
		private System.Windows.Forms.CheckBox consoleCheckBox;
		private System.Windows.Forms.Button buttonNewMod;
		private System.Windows.Forms.ColumnHeader columnHeader3;
		private System.Windows.Forms.TabPage tabPage3;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox pauseWhenInactiveCheckBox;
		private System.Windows.Forms.CheckBox borderlessWindowCheckBox;
		private System.Windows.Forms.ContextMenuStrip modContextMenu;
		private System.Windows.Forms.ToolStripMenuItem openFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem checkForUpdatesToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem verifyToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem forceUpdateToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem uninstallToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem developerToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem generateManifestToolStripMenuItem;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Button buttonCheckForUpdates;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.CheckBox checkUpdateModsStartup;
		private System.Windows.Forms.NumericUpDown numericUpdateFrequency;
		private System.Windows.Forms.ComboBox comboUpdateFrequency;
		private System.Windows.Forms.CheckBox checkUpdateStartup;
		private System.Windows.Forms.Button installURLHandlerButton;
		private System.Windows.Forms.Button modTopButton;
		private System.Windows.Forms.Button modBottomButton;
		private System.Windows.Forms.Button configureModButton;
		private System.Windows.Forms.CheckBox screenCheckBox;
	}
}

