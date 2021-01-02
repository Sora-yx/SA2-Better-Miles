﻿using ModManagerCommon;
using System.Collections.Generic;
using System.ComponentModel;

namespace SA2ModManager
{
	class SA2LoaderInfo : LoaderInfo
	{
		public bool DebugConsole { get; set; }
		public bool DebugScreen { get; set; }
		public bool DebugFile { get; set; }
		public bool? ShowConsole { get { return null; } set { if (value.HasValue) DebugConsole = value.Value; } }
		[DefaultValue(true)]
		public bool PauseWhenInactive { get; set; }
		[DefaultValue(false)]
		public bool BorderlessWindow { get; set; }

		public SA2LoaderInfo()
		{
			Mods = new List<string>();
			EnabledCodes = new List<string>();
		}
	}
}