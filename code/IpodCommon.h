/**
 * Copyright @ 2014 - 2016 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file IpodCommon.h
 * @brief Declaration file of class IpodCommon.
 *
 * This file includes the declaration of class IpodCommon,
 * and the declaration of class members.
 *
 * @attention used for C++ only.
 */

#ifndef IPODCOMMON_H
#define IPODCOMMON_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

/*---------------------------------------------------------------------------*/
// Include headers
/*---------------------------------------------------------------------------*/
#include "CommonBaseBase/CommonBaseBase.h"
#include "fnctl/MediaIPod/MediaIPodDef.h"
#include "ngframeworkbase/NGHardKeyDef.h"
#include "ngapp/NGMediaExt.h"
#include "QVariant"
#include <onsapi/NGONSAPI.h>
#include <onsapi/NGONSAPIDef.h>
#include <onsapi/NGONSIdDefine.h>
#include "ngframeworkbase/NGAPI.h"
#include "UI_ScreenNameID.h"
#include "fnctl/Setting/SettingModelDef.h"
#include "fnctl/Setting/SettingDef.h"
#include "AvCommon.h"
#include "QTimer"


/*---------------------------------------------------------------------------*/
// Declaration
/*---------------------------------------------------------------------------*/
#define HOMECONTROL_Audio "HomeControl"
#define HOMETYPE_AUDIO "2"
#define RestrictionStatus_OperationOn 1
#define RestrictionStatus_ScreenOn 2
#define RestrictionStatus_Off 0
#define ACommon AvCommon::GetInstance()
#define PCommon IpodCommon::GetInstance()
#define appMIST APP::MIST(ACommon->getAppId())

class MediaIPodBasicModel;
class MediaIpodListBaseModel;
class SystemInfoProductModel;
class NGONSAPICallBack;
/**
 * The class of IpodCommon screen.
 *
 * OpeID:
 * - xxxx1
 * - xxxx2
 *
 * ReferenceSpec:
 * - xxxx1
 * - xxxx2
 */
class IpodCommon : public CommonBaseBase, public NGONSAPICallBack
{
    Q_OBJECT

public:
    /*---------------------------------------------------------------------------*/
    // static functions
    /*---------------------------------------------------------------------------*/
    /// Static function, return singleton object
    static IpodCommon* GetInstance();

    /// Static function, delete singleton object
    static void DestroyInstance();

    /*---------------------------------------------------------------------------*/
    // Public functions : Constructor/Destructor
    /*---------------------------------------------------------------------------*/
    /// Constructor
    IpodCommon();
    /// Destructor
    ~IpodCommon();

    /*---------------------------------------------------------------------------*/
    // Public functions
    /*---------------------------------------------------------------------------*/
    /// onCreate
    virtual void onCreate(AppId appId);

    /// onDestory
    virtual void onDestory();

    /// onInitialize
    virtual void onInitialize();

    /// onSourceON
    void onSourceOn(NGMediaSource source);

    /// onSourceOff
    void onSourceOff();

    /// onCurSource
    NGMediaSource getCurSource();

    /// is Source On
    bool getSourceOn();

    /// set Source ON
    void setSourceOn(bool isTrue);

    /// onSysPostHardKeyPressed
    virtual bool onSysPostHardKeyPressed(const HardKeyEvent &event);

    /// onSysPostHardKeyShortPressed
    virtual bool onSysPostHardKeyShortPressed(const HardKeyEvent &event);

    /// onSysPostHardKeyShortPressed
    virtual bool onSysPostHardKeyShortReleased(const HardKeyEvent &event);

    /// onSysPostHardKeyLongPressed
    virtual bool onSysPostHardKeyLongPressed(const HardKeyEvent &event);

    /// onSysPostHardKeyReleased
    virtual bool onSysPostHardKeyReleased(const HardKeyEvent &event);

    /// onSysPostHardKeyRepeat
    virtual bool onSysPostHardKeyRepeat(const HardKeyEvent &event);

    /// openONS
    void openONS(int ONSId);

    /// openONS
    void openONS(int ONSId, std::string str);

    /// closeONS
    void closeONS(int ONSId);

    /// closeAllONS
    void closeAllONS();

    enum IPodScreen
    {
        IPodScreen_Base = 0,
        IPodScreen_Source,
        IPodScreen_Sound,
        IPodScreen_Mode,
        IPodScreen_SongList,
        IPodScreen_Layer1,
        IPodScreen_Layer2,
        IPodScreen_Layer3,
        IPodScreen_Layer4,
        IPodScreen_Layer1_2,
        IPodScreen_Vk,
        IPodScreen_Layer1_3,
        IPodScreen_Layer1_2_3,
        IPodScreen_Layer2_3,
        IPodScreen_Layer1_3_4,
        IPodScreen_Layer3_4,
        IPodScreen_Layer2_3_4,
        IPodScreen_Layer4_Spec,
        IPodScreen_Layer4_Shuffle,
        IPodScreen_3_4_Vk,
        IPodScreen_2_3_Vk,
        IPodScreen_1_3_Vk,
        IPodScreen_2_3_4_Vk,
        IPodScreen_1_3_4_Vk,
        IPodScreen_None
    };

    enum HomePattern
    {
        HomePattern_One = 1,
        HomePattern_Two,
        HomePattern_Three,
        HomePattern_Four,
        HomePattern_Five,
        HomePattern_Six
    };

    void setIPodPrevIndex(int index);

    int getIPodPrevIndex();

    void setIPodTopIndex(int index);

    int getIPodTopIndex();

    void setIPodScreen(IPodScreen srceen);

    IPodScreen getIPodScreen();

    void setIPodPrevScreen(IPodScreen screen);

    IPodScreen getIPodPrevScreen();

    void setIPodSelectIndex(int index);

    int getIPodSelectIndex();

    void setIPodListTotal(int count);

    int getIPodListTotal();

    inline void changeListSelStation(int, int);

    void setDivSelect(int index);

    int getDivSelect();

    bool getIsGettingArtWork();

    bool getIsIPodSearching();

    void setListTransferMap(FCIPOD_LIST_DIRECTION dirt, FCIPOD_DEVICE_NUMBER devs, int index);

    QMap<QString, QVariant> getListTransferMap();

    void requestListData();

    FCIPOD_DEVICE_STATUS getIPodDeviceStatus();

    void setIPodIapDevice();

    FCIPOD_IAP_DEVICE_TYPE  getIPodIapDevice();

    void setIPodDeviceName();

    QString getIPodDeviceName();

    bool getHomeIsIpod();

    MediaIPodBasicModel* getIPodBaseModel();
    MediaIpodListBaseModel* getIPodListModel();

    FCIPOD_DEVICE_NUMBER getDeviceNumber();

    void clearIpodTopIndex();

    bool isError();

    void setIpodListRequestSt(bool isRequest);

    bool getIpodListRequestSt();

    bool getIsTuneRotary();

    void setIsTuneRotary(bool TuneRotary);

    void setIsAllorShuffle(bool isHave);

    void setListVisible(bool vis);

    void setSelectTopIndex(bool isTrue, int index);

    int getSelectTopIndex();

signals:
    /**
      * request command from function control.
      *
      *
      * @param [IN] uri : command name
      * @param [IN] data : command parameters
      *
      * @return void
      *
      */
    void request(QString uri, QVariant data);

    /**
      * request command from function control.
      *
      *
      * @param [IN] uri : command name
      * @param [IN] data : command parameters
      *
      * @return void
      *
      */
    void notifyIPodSelectChange();

    /**
      * request command from function control.
      *
      *
      * @param [IN] uri : command name
      * @param [IN] data : command parameters
      *
      * @return void
      *
      */
    void notifyIPodDivSelectChange();

    void notifyVKInputFinished(std::string);

public slots:
    /**
      * this notify is ipod device status changed.
      *
      * when this notify is get signal, ipod device status is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyIPodErrorStatusChanged(FCIPOD_DEVICE_NUMBER device);

    /**
      * this notify is ipod device status changed.
      *
      * when this notify is get signal, ipod device status is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyIPodDeviceStatusChanged(FCIPOD_DEVICE_NUMBER device);

    /**
      * this notify is ipod device status changed.
      *
      * when this notify is get signal, ipod device status is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyIPodIsGettingArtworkStatusChanged(FCIPOD_DEVICE_NUMBER device);

    /**
      * this notify is ipod device status changed.
      *
      * when this notify is get signal, ipod device status is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyIpodListSearchingStatusChanged(FCIPOD_DEVICE_NUMBER device);

    /**
      * this notify is ipod device status changed.
      *
      * when this notify is get signal, ipod device status is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyIPodDeviceNameChanged(FCIPOD_DEVICE_NUMBER device);

    /**
      * this notify is ipod device status changed.
      *
      * when this notify is get signal, ipod device status is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyIPodListDataChanged(FCIPOD_DEVICE_NUMBER device);

    /**
      * this notify is ipod category type changed.
      *
      * when this notify is get signal, ipod category type is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onNotifyONSUpdateTime();

    /**
      * this notify is ipod category type changed.
      *
      * when this notify is get signal, ipod category type is changed.
      *
      * @param
      *
      * @return void
      *
      */
    void onHmiModeChanged(int hmiMode);

public:


private:
    /*---------------------------------------------------------------------------*/
    // Constant declaration
    /*---------------------------------------------------------------------------*/

    /*---------------------------------------------------------------------------*/
    // Variable declaration
    /*---------------------------------------------------------------------------*/
    static IpodCommon* m_sInstance;
    MediaIPodBasicModel* m_ipodCurModel;
    MediaIpodListBaseModel* m_ipodCurListModel;
    AvCommon* m_avCommon;
    FCProxyBase* m_fcProxyBase;
    FCModelBase* m_fcModelBase;

    NGMediaSource m_source;
    FCIPOD_DEVICE_NUMBER m_device;
    FCIPOD_ERROR_STATUS m_ipodErrorStatus;
    FCIPOD_DEVICE_STATUS m_ipodDeviceStatus;
    FCIPOD_IAP_DEVICE_TYPE m_ipodIapDevice;

    int m_preIndex;
    int m_selectTopIndexGo;
    int m_selectTopIndexBack;
    bool m_sourceOn;
    QList<int> m_topIndex;
    int m_ipodCount;
    int m_ipodTotal;
    IPodScreen m_ipodActiveScreen;
    IPodScreen m_ipodPrevScreen;
    int m_divSelect;
    bool m_isGetArtWork;
    bool m_isSearching;
    bool m_isGetIPodDataSts;
    QString m_ipodDeivceName;
    QMap<QString, QVariant> m_listTransferData;
    bool m_isError;
    bool m_isRequest;
    bool m_isTuneRotary;
    bool m_isAllorShuffle;
    bool m_isVisibleList;

    QTimer m_timer;

private:
    /*---------------------------------------------------------------------------*/
    // Private functions
    /*---------------------------------------------------------------------------*/
    /// Copy constructor
    IpodCommon(const IpodCommon&);

    /// Assign constructor
    IpodCommon& operator = (const IpodCommon&);

    //  Set ipod error status
    void setIPodErrorStatus();
    //  Set ipod art work getting
    void setIPodArtWork();
    //  Set ipod searching status
    void setIPodSearching();
    //   Set ipod device status
    void setIPodDeviceStatus();
    //  Update the Source Plate
    void openSourcePlate();
};

#endif // IPODCOMMON_H
/* EOF */

