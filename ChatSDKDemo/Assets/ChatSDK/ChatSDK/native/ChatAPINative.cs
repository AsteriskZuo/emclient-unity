﻿using System.Runtime.InteropServices;
using System;

namespace ChatSDK{
	public class ChatAPINative
	{

#region DllImport
#if UNITY_STANDALONE_WIN || UNITY_EDITOR
		public const string MyLibName = "hyphenateCWrapper";
#else

#if UNITY_IPHONE
		public const string MyLibName = "__Internal";
#else
        public const string MyLibName = "hyphenateCWrapper";
#endif
#endif
		protected delegate void OnSuccess();
		protected delegate void OnError(int error, string desc);
		protected delegate void OnProgress(int progress);

		[DllImport(MyLibName)]
		internal static extern void Client_CreateAccount(IntPtr client, CallBack callback, string username, string password);

		[DllImport(MyLibName)]
		internal static extern IntPtr Client_InitWithOptions(Options options, ConnectionHub.Delegate @delegate);

		[DllImport(MyLibName)]
		internal static extern void Client_Login(IntPtr client, CallBack callback, string username, string pwdOrToken, bool isToken = false);

		[DllImport(MyLibName)]
		internal static extern void Client_Logout(IntPtr client, CallBack callback, bool unbindDeviceToken);

		[DllImport(MyLibName)]
		internal static extern void Client_Release(IntPtr client);

		[DllImport(MyLibName)]
		internal static extern void Client_StartLog(string logFilePath);

		[DllImport(MyLibName)]
		internal static extern void Client_StopLog();

		[DllImport(MyLibName)]
		internal static extern void ChatManager_SendMessage(IntPtr client, CallBack callback, ref MessageTransferObject mto);


		#endregion native API import
	}
}
