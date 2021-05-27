﻿using System.Collections.Generic;
using UnityEngine;

namespace ChatSDK
{
    public class ChatManager_Android : IChatManager
    {

        static string Listener_Obj = "unity_chat_emclient_chat_manager_delegate_obj";

        private AndroidJavaObject wrapper;

        GameObject listenerGameObj;

        public ChatManager_Android()
        {
            using (AndroidJavaClass aj = new AndroidJavaClass("com.hyphenate.unity_chat_sdk.EMChatManagerWrapper"))
            {
                listenerGameObj = new GameObject(Listener_Obj);
                ChatManagerListener listener = listenerGameObj.AddComponent<ChatManagerListener>();
                listener.managerDelegater = Delegate;
                wrapper = aj.CallStatic<AndroidJavaObject>("wrapper");
            }
        }

        public override bool DeleteConversation(string conversationId, bool deleteMessages)
        {
            return wrapper.Call<bool>("deleteConversation", conversationId, deleteMessages);
        }

        public override void DownloadAttachment(string messageId, CallBack handle = null)
        {
            wrapper.Call("downloadAttachment", messageId, handle?.callbackId);
        }

        public override void DownloadThumbnail(string messageId, CallBack handle = null)
        {
            wrapper.Call("downloadThumbnail", messageId, handle?.callbackId);
        }

        public override void FetchHistoryMessages(string conversationId, ConversationType type, string startMessageId = null, int count = 20, ValueCallBack<CursorResult<Message>> handle = null)
        {
            wrapper.Call("fetchHistoryMessages", conversationId, TransformTool.ConversationTypeToInt(type), startMessageId, count, handle?.callbackId);
        }

        public override Conversation GetConversation(string conversationId, ConversationType type, bool createIfNeed = true)
        {
            string jsonString = wrapper.Call<string>("getConversation", conversationId, TransformTool.ConversationTypeToInt(type), createIfNeed);
            return new Conversation(jsonString);
        }

        public override void GetConversationsFromServer(ValueCallBack<List<Conversation>> handle = null)
        {
            wrapper.Call("getConversationsFromServer", handle?.callbackId);
        }

        public override int GetUnreadMessageCount()
        {
            return wrapper.Call<int>("getUnreadMessageCount");
        }

        public override bool ImportMessages(List<Message> messages)
        {
            return wrapper.Call<bool>("importMessages", TransformTool.JsonStringFromMessageList(messages));
        }

        public override List<Conversation> LoadAllConversations()
        {
            string jsonStrong = wrapper.Call<string>("loadAllConversations");
            return TransformTool.JsonStringToConversationList(jsonStrong);
        }

        public override Message LoadMessage(string messageId)
        {
            string jsonStrong = wrapper.Call<string>("getMessage");
            return new Message(jsonStrong);
        }

        public override bool MarkAllConversationsAsRead()
        {
            return wrapper.Call<bool>("markAllChatMsgAsRead");
        }

        public override void RecallMessage(string messageId, CallBack handle = null)
        {
            wrapper.Call("recallMessage", handle?.callbackId);
        }

        public override Message ResendMessage(string messageId, ValueCallBack<Message> handle = null)
        {
            string jsonString = wrapper.Call<string>("resendMessage", messageId, handle?.callbackId);
            return new Message(jsonString);
        }

        public override List<Message> SearchMsgFromDB(string keywards, long timestamp = 0, int maxCount = 20, string from = null, MessageSearchDirection direction = MessageSearchDirection.UP)
        {
            string jsonString = wrapper.Call<string>("searchChatMsgFromDB", keywards, timestamp, maxCount, from, direction == MessageSearchDirection.UP ? "up" : "down");
            return TransformTool.JsonStringToMessageList(jsonString);
        }

        public override void SendConversationReadAck(string conversationId, CallBack handle = null)
        {
            wrapper.Call("ackConversationRead", conversationId, handle?.callbackId);
        }

        public override Message SendMessage(Message message, CallBack handle = null)
        {
            string jsonString = wrapper.Call<string>("sendMessage", message.ToJsonString(), handle?.callbackId);
            return new Message(jsonString);
        }

        public override void SendMessageReadAck(string messageId, CallBack handle = null)
        {
            wrapper.Call("ackMessageRead", messageId, handle?.callbackId);
        }

        public override void UpdateMessage(Message message, CallBack handle = null)
        {
            wrapper.Call("updateChatMessage", message.ToJsonString(), handle?.callbackId);
        }
    }
    
}