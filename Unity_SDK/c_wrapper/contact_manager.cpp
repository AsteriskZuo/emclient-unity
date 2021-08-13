//
//  contact_manager.cpp
//  hyphenateCWrapper
//
//  Created by Qiang Yu on 2021/7/21.
//  Copyright © 2021 easemob. All rights reserved.
//
#include "contact_manager.h"

#include "emclient.h"

EMContactListener *gContactListener = NULL;

EMContactListener* ContactManager_GetListeners()
{
    return gContactListener;
}

AGORA_API void ContactManager_AddListener(void *client,
                                        FUNC_OnContactAdded onContactAdded,
                                        FUNC_OnContactDeleted onContactDeleted,
                                        FUNC_OnContactInvited onContactInvited,
                                        FUNC_OnFriendRequestAccepted onFriendRequestAccepted,
                                        FUNC_OnFriendRequestDeclined OnFriendRequestDeclined
                                        )
{
    if(gContactListener == NULL) { //only set once!
        gContactListener = new ContactManagerListener(onContactAdded, onContactDeleted, onContactInvited, onFriendRequestAccepted, OnFriendRequestDeclined);
        CLIENT->getContactManager().registerContactListener(gContactListener);
    }
}

AGORA_API void ContactManager_AddContact(void *client, const char* username, const char* reason, FUNC_OnSuccess onSuccess, FUNC_OnError onError) {
    EMError error;
    CLIENT->getContactManager().inviteContact(username, reason, error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("AddContact success.");
        if(onSuccess) onSuccess();
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_DeleteContact(void *client, const char* username, bool keepConversation, FUNC_OnSuccess onSuccess, FUNC_OnError onError) {
    EMError error;
    CLIENT->getContactManager().deleteContact(username, error, keepConversation);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("DeleteContact success.");
        if(onSuccess) onSuccess();
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_GetContactsFromServer(void *client, FUNC_OnSuccess_With_Result onSuccess, FUNC_OnError onError) {
    EMError error;
    vector<std::string> vec = CLIENT->getContactManager().getContactsFromServer(error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("GetContactsFromServer success.");
        size_t size = vec.size();
        auto contactTOArray = new TOArray();
        TOArray *data[1] = {contactTOArray};
        data[0]->Type = DataType::ListOfString;
        data[0]->Size = (int)size;
        for(int i=0; i<size; i++) {
            data[0]->Data[i] = (void*)(vec[i].c_str());
        }
        onSuccess((void**)data, DataType::ListOfString, 1);
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_GetContactsFromDB(void *client, FUNC_OnSuccess_With_Result onSuccess, FUNC_OnError onError) {
    EMError error;
    vector<std::string> vec = CLIENT->getContactManager().getContactsFromDB(error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("GetContactsFromDB success.");
        size_t size = vec.size();
        auto contactTOArray = new TOArray();
        TOArray *data[1] = {contactTOArray};
        data[0]->Type = DataType::ListOfString;
        data[0]->Size = (int)size;
        for(int i=0; i<size; i++) {
            data[0]->Data[i] = (void*)(vec[i].c_str());
        }
        onSuccess((void**)data, DataType::ListOfString, 1);
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_AddToBlackList(void *client, const char* username, bool both, FUNC_OnSuccess onSuccess, FUNC_OnError onError)
{
    EMError error;
    CLIENT->getContactManager().addToBlackList(username, both, error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("AddToBlackList success.");
        if(onSuccess) onSuccess();
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_RemoveFromBlackList(void *client, const char* username,FUNC_OnSuccess onSuccess, FUNC_OnError onError)
{
    EMError error;
    CLIENT->getContactManager().removeFromBlackList(username, error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("RemoveFromBlackList success.");
        if(onSuccess) onSuccess();
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_GetBlackListFromServer(void *client, FUNC_OnSuccess_With_Result onSuccess, FUNC_OnError onError)
{
    EMError error;
    vector<std::string> vec = CLIENT->getContactManager().getBlackListFromServer(error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("GetBlackListFromServer success.");
        size_t size = vec.size();
        auto blackListTOArray = new TOArray();
        TOArray *data[1] = {blackListTOArray};
        data[0]->Type = DataType::ListOfString;
        data[0]->Size = (int)size;
        for(int i=0; i<size; i++) {
            data[0]->Data[i] = (void*)(vec[i].c_str());
        }
        onSuccess((void**)data, DataType::ListOfString, 1);
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_AcceptInvitation(void *client, const char* username,FUNC_OnSuccess onSuccess, FUNC_OnError onError)
{
    EMError error;
    CLIENT->getContactManager().acceptInvitation(username, error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("AcceptInvitation success.");
        if(onSuccess) onSuccess();
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_DeclineInvitation(void *client, const char* username,FUNC_OnSuccess onSuccess, FUNC_OnError onError)
{
    EMError error;
    CLIENT->getContactManager().declineInvitation(username, error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("DeclineInvitation success.");
        if(onSuccess) onSuccess();
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}

AGORA_API void ContactManager_GetSelfIdsOnOtherPlatform(void *client, FUNC_OnSuccess_With_Result onSuccess, FUNC_OnError onError)
{
    EMError error;
    vector<std::string> vec = CLIENT->getContactManager().getSelfIdsOnOtherPlatform(error);
    if(error.mErrorCode == EMError::EM_NO_ERROR) {
        LOG("GetSelfIdsOnOtherPlatform success.");
        size_t size = vec.size();
        auto selfIdListTOArray = new TOArray();
        TOArray *data[1] = {selfIdListTOArray};
        data[0]->Type = DataType::ListOfString;
        data[0]->Size = (int)size;
        for(int i=0; i<size; i++) {
            data[0]->Data[i] = (void*)(vec[i].c_str());
        }
        onSuccess((void**)data, DataType::ListOfString, 1);
    } else {
        if(onError) onError(error.mErrorCode, error.mDescription.c_str());
    }
}