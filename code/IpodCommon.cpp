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

/*---------------------------------------------------------------------------*/
// Include headers
/*---------------------------------------------------------------------------*/
#include "IpodCommon.h"
#include <qmlframework/NQDivView.h>
#include "Ipod/IpodDivView.h"
#include "fnctl/MediaIPod/MediaIPodBasicModel.h"
#include "fnctl/MediaIPod/MediaIPod1BasicModel.h"
#include "fnctl/MediaIPod/MediaIPod2BasicModel.h"
#include "fnctl/MediaIPod/MediaIpod1ListModel.h"
#include "fnctl/MediaIPod/MediaIpod2ListModel.h"
#include "fnctl/MediaIPod/MediaIPodModelDef.h"
#include "fnctl/MediaIPod/MediaIPodInterfaceDef.h"
#include "UI_TransitionNameID.h"
#include <qmlframework/NQAPI.h>
#include "UI_ChoiceNameID.h"
#include "ngresource/ViewInfoDef.h"
#include <qmlframework/NQNotifier.h>

/*---------------------------------------------------------------------------*/
// Constant definition
/*---------------------------------------------------------------------------*/
#define LogTag ("Ipod")
#define INVALID -3
#define INVALID_0 0
#define INVALID_1 -1

/*---------------------------------------------------------------------------*/
// Variable definition
/*---------------------------------------------------------------------------*/
IpodCommon* IpodCommon::m_sInstance = NULL;

/*---------------------------------------------------------------------------*/
// Static functions
/*---------------------------------------------------------------------------*/

// Get instance
IpodCommon* IpodCommon::GetInstance()
{
    if (NULL == m_sInstance) {
        m_sInstance = new IpodCommon();
    }
    return m_sInstance;
}

// Destroy instance
void IpodCommon::DestroyInstance()
{
    if (NULL != m_sInstance) {
        m_sInstance->deleteLater();
        m_sInstance = NULL;
    }
}

/*---------------------------------------------------------------------------*/
// Public functions : Constructor/Destructor
/*---------------------------------------------------------------------------*/
// Constructor
IpodCommon::IpodCommon() : CommonBaseBase()
  , m_ipodCurModel(NULL)
  , m_ipodCurListModel(NULL)
  , m_avCommon(ACommon)
  , m_fcProxyBase(NULL)
  , m_fcModelBase(NULL)
  , m_source(NGMediaSource_Invalid)
  , m_device(FCIPOD_DEVICE_NUMBER_NONE)
  , m_ipodErrorStatus(FCIPOD_ERROR_INVALID)
  , m_ipodDeviceStatus(FCIPOD_DEVICE_STATUS_NODEVICE)
  , m_ipodIapDevice(FCIPOD_IAP_DEVICE_NONE)
  , m_preIndex(INVALID)
  , m_selectTopIndexGo(INVALID_0)
  , m_selectTopIndexBack(INVALID_0)
  , m_sourceOn(false)
  , m_ipodCount(INVALID_1)
  , m_ipodTotal(0)
  , m_ipodActiveScreen(IPodScreen_None)
  , m_ipodPrevScreen(IPodScreen_None)
  , m_divSelect(INVALID)
  , m_isGetArtWork(false)
  , m_isSearching(false)
  , m_isGetIPodDataSts(false)
  , m_ipodDeivceName("")
  , m_isError(false)
  , m_isRequest(false)
  , m_isTuneRotary(false)
  , m_isAllorShuffle(false)
  , m_isVisibleList(false)
{
}

// Destructor
IpodCommon::~IpodCommon()
{
}

/*---------------------------------------------------------------------------*/
// Public functions
/*---------------------------------------------------------------------------*/
/*
 * onCreate(function describe)
 * unitTest's usecase
 */
//  onCreate
void IpodCommon::onCreate(AppId appId)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    setAppId(appId);
}

/*
 * onDestory(function describe)
 * unitTest's usecase
 * UT1: when proxy is not NULL, disconnect the requset of proxy
 */
//  onDestory
void IpodCommon::onDestory()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    //  Set Variable declaration is NULL, or disconnect requset and notify
    m_ipodCurModel = NULL;
    m_ipodCurListModel = NULL;
    m_avCommon = NULL;
    m_fcProxyBase = NULL;
    m_fcModelBase = NULL;
    m_source = NGMediaSource_Invalid;
    m_device = FCIPOD_DEVICE_NUMBER_NONE;
    m_ipodErrorStatus = FCIPOD_ERROR_INVALID;
    m_ipodDeviceStatus = FCIPOD_DEVICE_STATUS_NODEVICE;
    m_ipodIapDevice = FCIPOD_IAP_DEVICE_NONE;
    m_preIndex = INVALID;
    m_selectTopIndexGo = INVALID_0;
    m_selectTopIndexBack = INVALID_0;
    m_sourceOn = false;
    m_ipodCount = INVALID_1;
    m_ipodTotal = 0;
    m_ipodActiveScreen = IPodScreen_None;
    m_ipodPrevScreen = IPodScreen_None;
    m_divSelect = 1;
    m_isGetArtWork = false;
    m_isSearching = false;
    m_isGetIPodDataSts = false;
    m_ipodDeivceName = "";
    m_isError = false;
    m_isRequest = false;
    m_isTuneRotary = false;
    m_isVisibleList = false;
}

/*
 * onInitialize(function describe)
 * unitTest's usecase
 * UT1: when proxy is NULL, set proxy is ipod proxy
 * UT2: when is not NULL, connect the request of proxy
 */
//  onInitialize
void IpodCommon::onInitialize()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    //  Set the ipod common init
}

/*
 * onSourceOn(function describe)
 * unitTest's usecase
 * UT1: source is USB1, set ipod source is Ipod1
 * UT2: source is Ipod2 and UsbDeviceKind is USB, set ipod source is Ipod1
 * UT3:  source is Ipod2 and UsbDeviceKind is Ipod, set ipod source is Ipod2
 * UT4: source is Ipod2 and UsbDeviceKind is None, do nothing
 * UT5: this source is not ipod, do nothing
 */
//  onSourceON
void IpodCommon::onSourceOn(NGMediaSource source)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */

    NGLogDebug(LogTag, "NGMediaSource is (%d).", source);

    //  Get Ipod Source and make Ipod model
    m_sourceOn = true;
    m_ipodPrevScreen = IPodScreen_None;
    m_selectTopIndexGo = INVALID_0;
    if (NULL == m_avCommon) {
        NGLogDebug(LogTag, "IPodCommon::onSourceOn AvCommon is NULL.");
        return;
    }
    NGMediaUsbDeviceKind usbKind;
    APP::NGUsbDeviceType(NGMediaMgrUsbPort1, usbKind);
    //  source is USB1, set ipod source is Ipod1             <-UT1
    if ((NGMediaSource_USB1 == source) || ((NGMediaSource_USB2 == source) && (NGMediaUsbDeviceKind_USB == usbKind))) {
        NGLogDebug(LogTag, "Source is NGMediaSource_USB1 NGMediaUsbDeviceKind_Ipod.");
        m_source = NGMediaSource_USB1;
        m_device = FCIPOD_DEVICE_NUMBER_1;
        m_fcProxyBase = m_avCommon->getBaseProxyIPod();
        if (NULL != m_fcProxyBase) {
            m_fcModelBase = m_fcProxyBase->getModel(FC_IPOD1_MODEL_NAME_BASIC);
            if (NULL != m_fcModelBase) {
                m_ipodCurModel = static_cast<MediaIPod1BasicModel*>(m_fcModelBase);
            }
            m_fcModelBase = m_fcProxyBase->getModel(FC_IPOD1_MODEL_NAME_LIST);
            if (NULL != m_fcModelBase) {
                 m_ipodCurListModel = static_cast<MediaIpod1ListModel*>(m_fcModelBase);
            }
        }
    }
    else if ((NGMediaSource_USB2 == source) && (NGMediaUsbDeviceKind_Ipod == usbKind)) {
        NGLogDebug(LogTag, "Source is NGMediaSource_USB2 NGMediaUsbDeviceKind_Ipod.");
        m_source = NGMediaSource_USB2;
        m_device = FCIPOD_DEVICE_NUMBER_2;
        m_fcProxyBase = m_avCommon->getBaseProxyIPod();
        if (NULL != m_fcProxyBase) {
            m_fcModelBase = m_fcProxyBase->getModel(FC_IPOD2_MODEL_NAME_BASIC);
            if (NULL != m_fcModelBase) {
                m_ipodCurModel = static_cast<MediaIPod2BasicModel*>(m_fcModelBase);
            }
            m_fcModelBase = m_fcProxyBase->getModel(FC_IPOD2_MODEL_NAME_LIST);
            if (NULL != m_fcModelBase) {
                 m_ipodCurListModel = static_cast<MediaIpod2ListModel*>(m_fcModelBase);
            }
        }
    }
    // this source is not ipod, do nothing          <-UT5
    else {
        NGLogDebug(LogTag, "NGMediaSource is (%d).", (int)source);
    }
    //  ONS Update Time
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onNotifyONSUpdateTime()));
    // Connect the request of ipod FC proxy.
    connect(this, SIGNAL(request(QString, QVariant)), m_avCommon->getBaseProxyIPod(), SIGNAL(request(QString, QVariant)));
    if (NULL != m_ipodCurModel) {
        connect(m_ipodCurModel, SIGNAL(notifyIPodErrorStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodErrorStatusChanged(FCIPOD_DEVICE_NUMBER)));
        connect(m_ipodCurModel, SIGNAL(notifyIPodIsGettingArtworkStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodIsGettingArtworkStatusChanged(FCIPOD_DEVICE_NUMBER)));
        connect(m_ipodCurModel, SIGNAL(notifyIPodDeviceStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodDeviceStatusChanged(FCIPOD_DEVICE_NUMBER)));
        connect(m_ipodCurModel, SIGNAL(notifyIPodDeviceNameChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodDeviceNameChanged(FCIPOD_DEVICE_NUMBER)));
    }
    if (NULL != m_ipodCurListModel) {
        connect(m_ipodCurListModel, SIGNAL(notifyIpodListSearchingStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIpodListSearchingStatusChanged(FCIPOD_DEVICE_NUMBER)));
        connect(m_ipodCurListModel, SIGNAL(notifyIPodListDataChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodListDataChanged(FCIPOD_DEVICE_NUMBER)));
    }
    if (NULL != NQNotifier::instance()) {
        connect(NQNotifier::instance(), SIGNAL(hmiModeChanged(int)), this, SLOT(onHmiModeChanged(int)));
    }

    setIPodIapDevice();
    setIPodDeviceName();
    setIPodErrorStatus();
    setIPodArtWork();
    setIPodSearching();
    setIPodDeviceStatus();
}

/*
 * onSourceOff(function describe)
 * unitTest's usecase
 */
//  onSourceOff
void IpodCommon::onSourceOff()
{
    m_sourceOn = false;
    m_ipodPrevScreen = IPodScreen_None;
    m_selectTopIndexGo = INVALID_0;
    setIPodScreen(IPodScreen_None);
    if (NULL == m_avCommon) {
        NGLogDebug(LogTag, "IpodCommon::onSourceOff() AvCommon is NULL.");
        return;
    }
    closeAllONS();
    //  ONS Update Time
    disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(onNotifyONSUpdateTime()));
    // Connect the request of ipod FC proxy.
    disconnect(this, SIGNAL(request(QString, QVariant)), AvCommon::GetInstance()->getBaseProxyIPod(), SIGNAL(request(QString, QVariant)));
    if (NULL != m_ipodCurModel) {
        disconnect(m_ipodCurModel, SIGNAL(notifyIPodErrorStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodErrorStatusChanged(FCIPOD_DEVICE_NUMBER)));
        disconnect(m_ipodCurModel, SIGNAL(notifyIPodIsGettingArtworkStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodIsGettingArtworkStatusChanged(FCIPOD_DEVICE_NUMBER)));
        disconnect(m_ipodCurModel, SIGNAL(notifyIPodDeviceStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodDeviceStatusChanged(FCIPOD_DEVICE_NUMBER)));
    }
    if (NULL != m_ipodCurListModel) {
        disconnect(m_ipodCurListModel, SIGNAL(notifyIpodListSearchingStatusChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIpodListSearchingStatusChanged(FCIPOD_DEVICE_NUMBER)));
        disconnect(m_ipodCurListModel, SIGNAL(notifyIPodListDataChanged(FCIPOD_DEVICE_NUMBER)), this, SLOT(onNotifyIPodListDataChanged(FCIPOD_DEVICE_NUMBER)));
    }
    if (NULL != NQNotifier::instance()) {
        disconnect(NQNotifier::instance(), SIGNAL(hmiModeChanged(int)), this, SLOT(onHmiModeChanged(int)));
    }
}

/*
 * getCurSource(function describe)
 * unitTest's usecase
 */
//  getCurSource
NGMediaSource IpodCommon::getCurSource()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */
    //  return the ipod source id
    return m_source;
}

/*
 * getSourceOn(function describe)
 * unitTest's usecase
 */
//  getSourceOn
bool IpodCommon::getSourceOn()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */
    //  return the ipod source on
    return m_sourceOn;
}

/*
 * setSourceOn(function describe)
 * unitTest's usecase
 */
//  setSourceOn
void IpodCommon::setSourceOn(bool isTrue)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */
    //  return the ipod source on
    m_sourceOn = isTrue;
}

/*
 * onSysPostHardKeyPressed(function describe)
 * unitTest's usecase
 * UT1: hard key is PlayPause
 * UT2: when ipod PlayPause status is Playing, open ONS of Pause
 * UT3: when ipod PlayPause status is not Playing, close ONS of Pause
 * UT4: hard key is TuneEnter
 */
//  onSysPostHardKeyPressed
bool IpodCommon::onSysPostHardKeyPressed(const HardKeyEvent &event)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    NGLogDebug(LogTag, "onSysPostHardKeyPressed is %d.", event.key);
    //   Hard key pressed event
    bool ret = false;
    if (HardKeyDispatchType_Press != event.type) {
        return ret;
    }
    FCIPOD_PLAY_STATUS pSts = FCIPOD_PLAY_STATUS_UNKNOWN;
    if (NULL != m_ipodCurModel) {
        pSts = m_ipodCurModel->getIPodPlayStatus();
    }

    switch (event.key) {
    //  hard key is PlayPause               <-UT1
    case HardKey_PlayPause:
    {
        NGLogDebug(LogTag, "HardKey_PlayPause");
        APP::Beep(BeepType_Beep1);
        //  requset playSts change
        QMap<QString, QVariant> qmap;
        qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
        emit request(FC_MEDIA_IPOD_REQ_PLAYPAUSECHANGE, qmap);
        //  when ipod PlayPause status is Playing, open ONS of Pause            <-UT2
        if (FCIPOD_PLAY_STATUS_PLAYING == pSts) {
            openONS(TEMP_MSG_01_09_02_02);
        }
        //  when ipod PlayPause status is not Playing, close ONS of Pause           <-UT3
        else {
            closeONS(TEMP_MSG_01_09_02_02);
            openSourcePlate();
        }
        ret = true;
    }
        break;
    // hard Key is back
    case HardKey_Back:
    {
        NGLogDebug(LogTag, "HardKey_Back");
        APP::Beep(BeepType_Beep1);
        ret = true;
    }
        break;

    case HardKey_TuneEnter:
    {
        NGLogDebug(LogTag, "HardKey_TuneEnter select index --- %d", m_ipodCount);
        APP::Beep (BeepType_Beep1);
        if (m_ipodActiveScreen == IPodScreen_Layer4) {
            if (m_ipodCount > -2 && m_isVisibleList) {
                setListTransferMap (FCIPOD_LIST_DIRECTION_NONE, m_device, m_ipodCount);
                requestListData ();
            }
        }
        else if (m_ipodActiveScreen == IPodScreen_SongList) {
            if (m_ipodCount > -2 && m_isVisibleList) {
                QMap<QString, QVariant> qmap;
                qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
                qmap.insert(FC_MEDIA_IPOD_PAR_LIST_REQ_INDEX_NAME, m_ipodCount);
                emit request(FC_MEDIA_IPOD_REQ_LISTPLAY, qmap);
            }
        }
        else if (m_ipodActiveScreen == IPodScreen_Layer1 || m_ipodActiveScreen == IPodScreen_Layer2
            || m_ipodActiveScreen == IPodScreen_Layer3) {
            if (m_ipodCount > -2 && m_isVisibleList) {
                QMap<QString, QVariant> qmap;
                qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
                qmap.insert(FC_MEDIA_IPOD_PAR_LIST_REQ_INDEX_NAME, m_ipodCount);
                emit request(FC_MEDIA_IPOD_REQ_LIST_UP_DOWN, qmap);

                qmap.clear ();
                qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
                qmap.insert(FC_MEDIA_IPOD_PAR_SET_SHUFFLE_DIRECTLY_NAME, FCIPOD_RANDOM_OFF);
                emit request(FC_MEDIA_IPOD_REQ_RANDOMCHANGE_DIRECTLY, qmap);

                m_isTuneRotary = true;
            }
        }
        else {
            NGLogDebug(LogTag, "HardKey_TuneEnter -------list do nothing");
        }
        ret = true;
    }
        break;
    //  hard Key is Power OFF
    case HardKey_Power:
    {
        NGLogDebug(LogTag, "HardKey_Power");
        if (NULL != m_ipodCurModel) {
            if ((FCIPOD_PLAY_STATUS_FASTFORWARD == pSts) || (FCIPOD_PLAY_STATUS_FASTREWIND == pSts)) {
                //  requset track up
                QMap<QString, QVariant> qmap;
                qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
                emit request(FC_MEDIA_IPOD_REQ_STOPFFFR, qmap);
                NGLogDebug(LogTag, "-----------------------FC_MEDIA_IPOD_REQ_STOPFFFR--------------------------");
            }
        }
    }
        break;
    case HardKey_VolumeUp:
    case HardKey_VolumeDown:
    {
        NGLogDebug(LogTag, "HardKey_VolumeUp/Down, Vol is change");
        if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
        }
        else {
            NGLogDebug(LogTag, "HardKey_VolumeUp/Down, Vol is not change");
        }
        ret = false;
    }
        break;
    default:
        break;
    }

    return ret;
}

/*
 * onSysPostHardKeyShortPressed(function describe)
 * unitTest's usecase
 */
//  onSysPostHardKeyShortPressed
bool IpodCommon::onSysPostHardKeyShortPressed(const HardKeyEvent &event)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    NGLogDebug(LogTag, "HardKeyDispatchType_Short is %d.", event.type);
    if (HardKeyDispatchType_Short != event.type) {
        return false;
    }

    return false;
}

/*
 * onSysPostHardKeyShortPressed(function describe)
 * unitTest's usecase
 * UT1: when hard key's event type is HardKeyDispatchType_Short, return
 * UT2: hard key is SeekUp, hard key's event device is HardKeyDevice_BodyKey
 * UT3: hard key is SeekDown, hard key's event device is HardKeyDevice_BodyKey
 * UT4: hard key's is Up,Up2,Right, and hard key's event device is HardKeyDevice_WiredKey
 * UT5: hard key's is Down,Down2,Left, and hard key's event device is HardKeyDevice_WiredKey
 * UT6: hard key's is TuneUp, and hard key's event device is HardKeyDevice_RearController
 * UT7: hard key's is TuneDown, and hard key's event device is HardKeyDevice_RearController
 */
//  onSysPostHardKeyShortPressed
bool IpodCommon::onSysPostHardKeyShortReleased(const HardKeyEvent &event)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    NGLogDebug(LogTag, "onSysPostHardKeyShortReleased is (%d).", event.key);
    FCIPOD_PLAY_STATUS pSts = FCIPOD_PLAY_STATUS_UNKNOWN;
    if (NULL != m_ipodCurModel) {
        pSts = m_ipodCurModel->getIPodPlayStatus();
    }
    //  Hand key short pressed event
    bool ret = false;
    NGLogDebug(LogTag, "HardKeyDispatchType_ShortRelease is %d.", event.type);
    //  when hard key's event type is HardKeyDispatchType_Short, return         <-UT1
    if (HardKeyDispatchType_ShortRelease != event.type) {
        return ret;
    }

    switch (event.key) {
    //  hard key is SeekUp, hard key's event device is HardKeyDevice_BodyKey              <-UT2
    case HardKey_TrackUp:
    case HardKey_SeekUp:
    {
        if ((HardKeyDevice_BodyKey == event.device) || (HardKeyDevice_RseRemoteController == event.device)) {
            NGLogDebug(LogTag, "HardKey_SeekUp is short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FILEUP, qmap);
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
                //  PlayPause is Stop or Pause, change the PlayPause Status
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            ret = true;
        }
    }
        break;
    //  hard key is SeekDown, hard key's event device is HardKeyDevice_BodyKey            <-UT3
    case HardKey_TrackDown:
    case HardKey_SeekDown:
    {
        if ((HardKeyDevice_BodyKey == event.device) || (HardKeyDevice_RseRemoteController == event.device)) {
            NGLogDebug(LogTag, "HardKey_SeekDown is short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track dwon
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FILEDOWN, qmap);
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
                //  PlayPause is Stop or Pause, change the PlayPause Status
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            ret = true;
        }
    }
        break;
    // hard key's is Up,Up2,Right, and hard key's event device is HardKeyDevice_WiredKey               <-UT4
    case HardKey_Up:
    case HardKey_Up2:
    case HardKey_Right:
    {
        if (HardKeyDevice_WiredKey == event.device) {
            NGLogDebug(LogTag, "HardKey_Up is short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FILEUP, qmap);
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
                //  PlayPause is Stop or Pause, change the PlayPause Status
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            ret = true;
        }
    }
        break;
    // hard key's is Down,Down2,Left, and hard key's event device is HardKeyDevice_WiredKey               <-UT5
    case HardKey_Down2:
    case HardKey_Left:
    case HardKey_Down:
    {
        if (HardKeyDevice_WiredKey == event.device) {
            NGLogDebug(LogTag, "HardKey_Left  is short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track down
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FILEDOWN, qmap);
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
                //  PlayPause is Stop or Pause, change the PlayPause Status
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            ret = true;
        }
    }
        break;
    // hard key's is TuneUp, and hard key's event device is HardKeyDevice_RearController               <-UT6
    case HardKey_TuneUp:
    {
        if (HardKeyDevice_RearController == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneUp is short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FILEUP, qmap);
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
                //  PlayPause is Stop or Pause, change the PlayPause Status
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            ret = true;
        }
    }
        break;
    // hard key's is TuneDown, and hard key's event device is HardKeyDevice_RearController               <-UT7
    case HardKey_TuneDown:
    {
        if (HardKeyDevice_RearController == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneDown is short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FILEDOWN, qmap);
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts) {
                //  PlayPause is Stop or Pause, change the PlayPause Status
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            ret = true;
        }
    }
        break;
    case HardKey_FastRewind:
    {
        if (HardKeyDevice_RseRemoteController == event.device) {
            NGLogDebug(LogTag, "HardKey_FastRewind is Short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTREWIND, qmap);
        }
        ret = true;
    }
        break;
    case HardKey_FastForward:
    {
        if (HardKeyDevice_RseRemoteController == event.device) {
            NGLogDebug(LogTag, "HardKey_FastForward is Short");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            openSourcePlate();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTFORWARD, qmap);
        }
        ret = true;
    }
        break;
    default:
        break;
    }

    return ret;
}

/*
 * onSysPostHardKeyLongPressed(function describe)
 * unitTest's usecase
 * UT1: hard key is SeekUp, hard key's event device is HardKeyDevice_BodyKey
 * UT2: hard key is SeekDown, hard key's event device is HardKeyDevice_BodyKey
 * UT3: hard key is Up,Up2,Right, hard key's event device is HardKeyDevice_WiredKey
 * UT4: hard key is Down,Down2,Left, hard key's event device is HardKeyDevice_WiredKey
 * UT5: hard key is TuneUp, hard key's event device is HardKeyDevice_RearController
 * UT6: hard key is TuneDown, hard key's event device is HardKeyDevice_RearController
 * UT7: hard key is Source,Mode
 * UT8: Ipod Play status is PLAYING , open ONS
 * UT9:Ipod Play status is not PLAYING , close ONS
 */
//  onSysPostHardKeyLongPressed
bool IpodCommon::onSysPostHardKeyLongPressed(const HardKeyEvent &event)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    //  hard key long pressed event
    bool ret = false;
    if (HardKeyDispatchType_Long != event.type) {
        return ret;
    }
    FCIPOD_PLAY_STATUS pSts = FCIPOD_PLAY_STATUS_UNKNOWN;
    if (NULL != m_ipodCurModel) {
        pSts = m_ipodCurModel->getIPodPlayStatus();
    }
    switch (event.key) {
    //  hard key is SeekUp, hard key's event device is HardKeyDevice_BodyKey              <-UT1
    case HardKey_TrackUp:
    case HardKey_SeekUp:
    {
        if ((HardKeyDevice_BodyKey == event.device) || (HardKeyDevice_RseRemoteController == event.device)) {
            NGLogDebug(LogTag, "HardKey_SeekUp is Long");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                NGLogDebug(LogTag, "FCIPOD_PLAY_STATUS_STOP is Long");
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset ff
            m_timer.start(1000);
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTFORWARD, qmap);
            ret = true;
        }
    }
        break;
    //  hard key is SeekDown, hard key's event device is HardKeyDevice_BodyKey              <-UT2
    case HardKey_TrackDown:
    case HardKey_SeekDown:
    {
        if ((HardKeyDevice_BodyKey == event.device) || (HardKeyDevice_RseRemoteController == event.device)) {
            NGLogDebug(LogTag, "HardKey_SeekDown is Long");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset rev
            m_timer.start(1000);
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTREWIND, qmap);
            ret = true;
        }
    }
        break;
    //  hard key is Up,Up2,Right, hard key's event device is HardKeyDevice_WiredKey              <-UT3
    case HardKey_Up:
    case HardKey_Up2:
    case HardKey_Right:
    {
        if (HardKeyDevice_WiredKey == event.device) {
            NGLogDebug(LogTag, "HardKey_Up is Long");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            m_timer.start(1000);
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTFORWARD, qmap);
            ret = true;
        }
    }
        break;
    //  hard key is Down,Down2,Left, hard key's event device is HardKeyDevice_WiredKey              <-UT4
    case HardKey_Left:
    case HardKey_Down:
    case HardKey_Down2:
    {
        if (HardKeyDevice_WiredKey == event.device) {
            NGLogDebug(LogTag, "HardKey_Left is Long");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            m_timer.start(1000);
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTREWIND, qmap);
            ret = true;
        }
    }
        break;
    //  hard key is TuneUp, hard key's event device is HardKeyDevice_RearController              <-UT5
    case HardKey_TuneUp:
    {
        if (HardKeyDevice_RearController == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneUp is Long");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            m_timer.start(1000);
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTFORWARD, qmap);
            ret = true;
        }
    }
        break;
    //  hard key is TuneDown, hard key's event device is HardKeyDevice_RearController              <-UT6
    case HardKey_TuneDown:
    {
        if (HardKeyDevice_RearController == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneDown is Long");
            APP::Beep(BeepType_Beep1);
            if (FCIPOD_PLAY_STATUS_STOP == pSts) {
                return ret;
            }
            if (isError()) {
                return ret;
            }
            //  requset track up
            m_timer.start(1000);
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_FASTREWIND, qmap);
            ret = true;
        }
    }
        break;
     //  hard key is Source,Mode              <-UT7
    case HardKey_Source:
    case HardKey_Mode:
    {
        NGLogDebug(LogTag, "HardKey_Source is Long");
        //  requset track up
        QMap<QString, QVariant> qmap;
        qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
        emit request(FC_MEDIA_IPOD_REQ_PLAYPAUSECHANGE, qmap);
        //  Ipod Play status is PLAYING , open ONS              <-UT8
        if (FCIPOD_PLAY_STATUS_PLAYING == pSts) {
            openONS(TEMP_MSG_01_09_02_02);
        }
        //  Ipod Play status is not PLAYING , close ONS              <-UT9
        else {
            closeONS(TEMP_MSG_01_09_02_02);
            openSourcePlate();
        }
        ret = true;
    }
        break;
    default:
        break;
    }

    return ret;
}

/*
 * onSysPostHardKeyReleased(function describe)
 * unitTest's usecase
 * UT1: hard key is SeekUp, hard key's event device is HardKeyDevice_BodyKey
 * UT2: hard key is SeekDown, hard key's event device is HardKeyDevice_BodyKey
 * UT3: hard key is Up,Up2,Right, hard key's event device is HardKeyDevice_WiredKey
 * UT4: hard key is Down,Down2,Left, hard key's event device is HardKeyDevice_WiredKey
 * UT5: hard key is TuneUp, hard key's event device is HardKeyDevice_RearController
 * UT6: hard key is TuneDown, hard key's event device is HardKeyDevice_RearController
 */
//  onSysPostHardKeyReleased
bool IpodCommon::onSysPostHardKeyReleased(const HardKeyEvent &event)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    //  Hard Key release event
    NGLogDebug(LogTag, "onSysPostHardKeyReleased");
    bool ret = false;
    FCIPOD_PLAY_STATUS pSts = FCIPOD_PLAY_STATUS_UNKNOWN;
    if (NULL != m_ipodCurModel) {
        pSts = m_ipodCurModel->getIPodPlayStatus();
    }

    switch (event.key) {
    //  hard key is SeekUp, hard key's event device is HardKeyDevice_BodyKey              <-UT1
    case HardKey_TrackUp:
    case HardKey_TrackDown:
    case HardKey_SeekUp:
    case HardKey_SeekDown:
    {
        if ((HardKeyDevice_BodyKey == event.device) || (HardKeyDevice_RseRemoteController == event.device)) {
            NGLogDebug(LogTag, "HardKey_SeekUp is Release");
            //  requset ff
            m_timer.stop();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_STOPFFFR, qmap);
            NGLogDebug(LogTag, "-----------------------FC_MEDIA_IPOD_REQ_STOPFFFR--------------------------");
            ret = true;
        }
    }
        break;
    //  hard key is Down,Down2,Left, hard key's event device is HardKeyDevice_WiredKey              <-UT4
    case HardKey_Up:
    case HardKey_Up2:
    case HardKey_Right:
    case HardKey_Left:
    case HardKey_Down:
    case HardKey_Down2:
    {
        if (HardKeyDevice_WiredKey == event.device) {
            NGLogDebug(LogTag, "HardKey_Left is Release");
            //  requset track up
            m_timer.stop();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_STOPFFFR, qmap);
            NGLogDebug(LogTag, "-----------------------FC_MEDIA_IPOD_REQ_STOPFFFR--------------------------");
            ret = true;
        }
    }
        break;
        //  hard key is TuneUp, hard key's event device is HardKeyDevice_RearController              <-UT5
    case HardKey_TuneUp:
    case HardKey_TuneDown:
    {
        if (HardKeyDevice_RearController == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneUp is Release");
            //  requset track up
            m_timer.stop();
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            emit request(FC_MEDIA_IPOD_REQ_STOPFFFR, qmap);
            NGLogDebug(LogTag, "-----------------------FC_MEDIA_IPOD_REQ_STOPFFFR--------------------------");
            ret = true;
        }
    }
        break;
    default:
        break;
    }

    return ret;
}

/*
 * onSysPostHardKeyRepeat(function describe)
 * unitTest's usecase
 * UT1: hard key is TuneRotary, hard key's event device is HardKeyDevice_BodyKey
 * UT2: hard key is TuneRotary, and event value > 0,requset is FASTCHANGE
 * UT3: hard key is TuneRotary, and event value < 0,requset is FASTCHANGE
 * UT4: hard key is TuneUp, hard key's event device is HardKeyDevice_BodyKey
 * UT5: hard key is TuneDown, hard key's event device is HardKeyDevice_BodyKey
 */
//  onSysPostHardKeyRepeat
bool IpodCommon::onSysPostHardKeyRepeat(const HardKeyEvent &event)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    // Hard Key Repeat event
    bool ret = false;

    switch (event.key) {
    //  hard key is TuneRotary, hard key's event device is HardKeyDevice_BodyKey              <-UT1
    case HardKey_TuneRotary:
    {
        if (HardKeyDevice_BodyKey == event.device) {
            if (IPodScreen_Mode == m_ipodActiveScreen) {
                ret = false;
            }
            else if (IPodScreen_Layer1 == m_ipodActiveScreen || IPodScreen_Layer2 == m_ipodActiveScreen
                || IPodScreen_Layer3 == m_ipodActiveScreen || IPodScreen_Layer4 == m_ipodActiveScreen
                || IPodScreen_SongList == m_ipodActiveScreen) {
                changeListSelStation(m_ipodTotal, event.value);
                ret = false;
            }
            else {
                NGLogDebug(LogTag, "IPodScreen_Base.HardKey_TuneRotary is Repeat. Rotary right is %d.", event.value);
                //  hard key is TuneRotary, and event value > 0,requset is FASTCHANGE       <-UT2
                NGLogDebug(LogTag, "HardKey_TuneRotary is Repeat. Rotary right.");
                //  requset track up
                QMap<QString, QVariant> qmap;
                int count = event.value;
                qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
                qmap.insert(FC_MEDIA_IPOD_PAR_TRACK_CHANGE_KEY_NAME, count);
                emit request(FC_MEDIA_IPOD_REQ_FASTCHANGE, qmap);
                ret = true;
            }
        }
        else {
            NGLogDebug(LogTag, "IPodScreen_None.HardKey_TuneRotary is Repeat. Rotary right is %d.", event.value);
        }
        ret = false;
    }
        break;
        //  hard key is TuneUp, hard key's event device is HardKeyDevice_BodyKey              <-UT4
    case HardKey_TuneUp:
    {
        if (HardKeyDevice_BodyKey == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneUp is Repeat");
            //  requset track up
            QMap<QString, QVariant> qmap;
            int count = event.repeatCount;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            qmap.insert(FC_MEDIA_IPOD_PAR_TRACK_CHANGE_KEY_NAME, count);
            emit request(FC_MEDIA_IPOD_REQ_FASTCHANGE, qmap);
            ret = true;
        }
    }

        break;
        //  hard key is TuneDown, hard key's event device is HardKeyDevice_BodyKey              <-UT5
    case HardKey_TuneDown:
    {
        if (HardKeyDevice_BodyKey == event.device) {
            NGLogDebug(LogTag, "HardKey_TuneUp is Repeat");
            //  requset track up
            QMap<QString, QVariant> qmap;
            int count = -event.repeatCount;
            qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
            qmap.insert(FC_MEDIA_IPOD_PAR_TRACK_CHANGE_KEY_NAME, count);
            emit request(FC_MEDIA_IPOD_REQ_FASTCHANGE, qmap);
            ret = true;
        }
    }
        break;

    case HardKey_VolumeRotary:
    {
        NGLogDebug(LogTag, "HardKey_VolumeRotary is Repeat. Rotary right is %d.", (int)event.value);
        if ((HardKeyDevice_BodyKey == event.device) && (NULL != m_ipodCurModel)) {
            FCIPOD_PLAY_STATUS pSts = m_ipodCurModel->getIPodPlayStatus();
            if (FCIPOD_PLAY_STATUS_PAUSED == pSts)  {
                QMap<QString, QVariant> qmap;
                qmap.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, m_device);
                emit request(FC_MEDIA_IPOD_REQ_PLAY, qmap);
            }
            else {
                NGLogDebug(LogTag, "HardKey_VolumeRotary is Repeat. Now IPod Play Pause Status is Not PAUSED.");
            }
        }
        ret = false;
    }
        break;
    default:
        NGLogDebug(LogTag, "Default is Repeat");
        break;
    }

    return ret;
}

/*
 * openONS(function describe)
 * unitTest's usecase
 * UT1: ONS id is TEMP_MSG_ONS_POD_004, open this ONS
 * UT2: ONS id is TEMP_MSG_A_ONS_POD_001, open this ONS
 * UT3: ONS id is TEMP_MSG_A_ONS_POD_005, open this ONS
 * UT4: ONS id is TEMP_MSG_A_ONS_POD_012, open this ONS
 * UT5: ONS id is TEMP_MSG_A_ONS_POD_013, open this ONS
 * UT6: ONS id is TEMP_MSG_A_ONS_POD_015, open this ONS
 * UT7: ONS id is TEMP_MSG_A_ONS_POD_020, open this ONS
 * UT8: ONS id is TEMP_MSG_01_09_02_02, open this ONS
 * UT9: ONS id is MSG_11_07_03_01, open this ONS
 * UT10: default, do nothing
 */
//  openONS
void IpodCommon::openONS(int ONSId)
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */
    NGLogDebug(LogTag, "ONSId %d", ONSId);
    closeAllONS();

    NGONSContext context;
    NGONSItemContext itemContext;

    switch (ONSId) {
    //  ONS id is TEMP_MSG_ONS_POD_004, open this ONS              <-UT1
    case TEMP_MSG_ONS_POD_004:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_01";
        context.textList.push_back(itemContext);
    }
        break;
        //  ONS id is TEMP_MSG_A_ONS_POD_001, open this ONS              <-UT2
    case TEMP_MSG_A_ONS_POD_001:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_00";
        context.textList.push_back(itemContext);
    }
        break;
        //  ONS id is TEMP_MSG_A_ONS_POD_005, open this ONS              <-UT3
    case TEMP_MSG_A_ONS_POD_005:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_02";
        context.textList.push_back(itemContext);
    }
        break;
        //  ONS id is TEMP_MSG_A_ONS_POD_012, open this ONS              <-UT4
    case TEMP_MSG_A_ONS_POD_012:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_03";
        context.textList.push_back(itemContext);
    }
        break;
        //  ONS id is TEMP_MSG_A_ONS_POD_013, open this ONS              <-UT5
    case TEMP_MSG_A_ONS_POD_013:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_04";
        context.textList.push_back(itemContext);
    }
        break;
        //  ONS id is TEMP_MSG_A_ONS_POD_015, open this ONS              <-UT6
    case TEMP_MSG_A_ONS_POD_015:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_05";
        context.textList.push_back(itemContext);
    }
        break;
        //  ONS id is TEMP_MSG_A_ONS_POD_020, open this ONS              <-UT7
    case TEMP_MSG_A_ONS_POD_020:
    {
        itemContext.type = NGONSItemContextType_StringId;
        itemContext.valueStr = "MSG_MM_11_11_26_RES_06";
        context.textList.push_back(itemContext);
    }
        break;
        //  default, do nothing                 <-UT10
    default:
    {
        // do nothing
    }
        break;
    }

    GetNGONSAPI()->openONS(ONSId, context, *this);
}

void IpodCommon::openSourcePlate()
{
    NGLogDebug(LogTag, "TopMode viewName");
    bool isHome = getHomeIsIpod();
    int curTopMode = APP::AppCtrlInterface()->getTopNormalModeId();
    FCIPOD_PLAY_STATUS pSts = FCIPOD_PLAY_STATUS_UNKNOWN;
    if (NULL != m_ipodCurModel) {
        pSts = m_ipodCurModel->getIPodPlayStatus();
    }
    if ((HmiMode_Base_AudioTOPScreen == curTopMode) || (HmiMode_Base_OtherAudio == curTopMode)
        || (isHome) || (FCIPOD_PLAY_STATUS_STOP == pSts)) {
        return;
    }
    NGONSStatus onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_006);
    if (NGONSStatus_Opened == onsSts) {
        GetNGONSAPI()->updateONSTimer(TEMP_MSG_A_ONS_POD_006);
    }
    else {
        GetNGONSAPI()->openONS(TEMP_MSG_A_ONS_POD_006, *this);
    }
}

/// onHmiModeChanged
void IpodCommon::onHmiModeChanged(int hmiMode)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */
    // if current is audio top and audio other
    NGLogDebug(LogTag, "onHmiModeChanged, hmiMode is %d", hmiMode);
    if (NULL != APP::AppCtrlInterface()) {
        NGLogDebug(LogTag, "IpodCommon::onHmiModeChanged, APP::AppCtrlInterface() is NULL");
        // get current is audio top screen or not
        int curTopMode = APP::AppCtrlInterface()->getTopNormalModeId();
        if ((HmiMode_Base_AudioTOPScreen == curTopMode) || (HmiMode_Base_OtherAudio == curTopMode) || (HmiMode_Base_HOME == curTopMode)) {
            NGLogDebug(LogTag, "current screen is Audio top screen or Audio other screen");
            openSourcePlate();
        }
    }
}

bool IpodCommon::getHomeIsIpod()
{
    if (NULL != APP::AppCtrlInterface()) {
        int curTopMode = APP::AppCtrlInterface()->getTopModeId();
        std::string viewName = APP::AppCtrlInterface()->getTopViewId();

        NGLogDebug(LogTag, "TopMode %d viewName %s", curTopMode, viewName.c_str());

        if (HOMECONTROL_Audio == viewName) {
            if (NULL != AvCommon::GetInstance()) {
                FCProxyBase* settingProxy = AvCommon::GetInstance()->getBaseProxySetting();
                if (NULL != settingProxy) {
                    QString curPattern = QString("");
                    FCModelBase* basicModel = settingProxy->getModel(FC_SETTING_MODEL_NAME_SETTINGS);
                    if (NULL != basicModel) {
                        SettingModel* settingModel = static_cast<SettingModel*>(basicModel);

                        if (NULL != settingModel) {
                            switch (settingModel->getCurPattern()) {
                            case HomePattern_One:
                                curPattern = settingModel->getPatternOne();
                                break;
                            case HomePattern_Two:
                                curPattern = settingModel->getPatternTwo();
                                break;
                            case HomePattern_Three:
                                curPattern = settingModel->getPatternThree();
                                break;
                            case HomePattern_Four:
                                curPattern = settingModel->getPatternFour();
                                break;
                            case HomePattern_Five:
                                curPattern = settingModel->getPatternFive();
                                break;
                            case HomePattern_Six:
                                curPattern = settingModel->getPatternSix();
                                break;
                            default:
                                break;
                            }
                            NGLogDebug(LogTag, "curPattern [%s]", curPattern.toStdString().c_str());
                            if (0 < curPattern.contains(HOMETYPE_AUDIO, Qt::CaseInsensitive)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void IpodCommon::openONS(int ONSId, std::string str)
{
    NGLogDebug(LogTag, "ONSId %d", ONSId);
    closeAllONS();

    NGONSContext context;
    NGONSItemContext itemContext;

    itemContext.type = NGONSItemContextType_RawString;
    itemContext.valueStr = str;
    context.textList.push_back(itemContext);

    GetNGONSAPI()->openONS(ONSId, context, *this);
}

/*
 * closeONS(function describe)
 * unitTest's usecase
 */
//  closeONS
void IpodCommon::closeONS(int ONSId)
{
    NGLogDebug(LogTag, "ONSId %d", ONSId);

    GetNGONSAPI()->closeONS(ONSId);
    GetNGONSAPI ()->unregisterONSCallBack (*this);
}

/*
 * closeAllONS(function describe)
 * unitTest's usecase
 * UT1: when ONS ID TEMP_MSG_ONS_POD_004 is NGONSStatus_Opened, close this ONS
 * UT2: when ONS ID TEMP_MSG_A_ONS_POD_001 is NGONSStatus_Opened, close this ONS
 * UT3: when ONS ID TEMP_MSG_A_ONS_POD_005 is NGONSStatus_Opened, close this ONS
 * UT4: when ONS ID TEMP_MSG_A_ONS_POD_012 is NGONSStatus_Opened, close this ONS
 * UT5: when ONS ID TEMP_MSG_A_ONS_POD_013 is NGONSStatus_Opened, close this ONS
 * UT6: when ONS ID TEMP_MSG_A_ONS_POD_015 is NGONSStatus_Opened, close this ONS
 * UT7: when ONS ID TEMP_MSG_A_ONS_POD_020 is NGONSStatus_Opened, close this ONS
 * UT8: when ONS ID TEMP_MSG_01_09_02_02 is NGONSStatus_Opened, close this ONS
 * UT9: when ONS ID MSG_11_07_03_00 is NGONSStatus_Opened, close this ONS
 * UT10: when ONS ID MSG_11_07_03_01 is NGONSStatus_Opened, close this ONS
 */
//  closeAllONS
void IpodCommon::closeAllONS()
{
    NGLogDebug(LogTag, "this is closeAllONS");
    //  when ONS ID TEMP_MSG_ONS_POD_004 is NGONSStatus_Opened, close this ONS              <-UT1
    NGONSStatus onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_ONS_POD_004);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_ONS_POD_004 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_ONS_POD_004);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_001 is NGONSStatus_Opened, close this ONS              <-UT2
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_001);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_001 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_001);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_005 is NGONSStatus_Opened, close this ONS              <-UT3
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_005);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_005 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_005);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_012 is NGONSStatus_Opened, close this ONS              <-UT4
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_012);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_012 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_012);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_013 is NGONSStatus_Opened, close this ONS              <-UT5
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_013);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_013 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_013);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_015 is NGONSStatus_Opened, close this ONS              <-UT6
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_015);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_015 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_015);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_020 is NGONSStatus_Opened, close this ONS              <-UT7
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_020);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_020 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_020);
    }
    //  when ONS ID TEMP_MSG_A_ONS_POD_006 is NGONSStatus_Opened, close this ONS              <-UT7
    onsSts = GetNGONSAPI()->getONSStatus(TEMP_MSG_A_ONS_POD_006);
    if (NGONSStatus_Opened == onsSts) {
        NGLogDebug(LogTag, "TEMP_MSG_A_ONS_POD_006 is close");
        GetNGONSAPI()->closeONS(TEMP_MSG_A_ONS_POD_006);
    }
    GetNGONSAPI ()->unregisterONSCallBack (*this);
}

/*
 * onNotifyIPodErrorStatusChanged(function describe)
 * unitTest's usecase
 */
//  onNotifyIPodErrorStatusChanged
void IpodCommon::onNotifyIPodErrorStatusChanged(FCIPOD_DEVICE_NUMBER device)
{
    //  This is get dvice is ipod, go to log.
    if ((FCIPOD_DEVICE_NUMBER_1 == device)
        || (FCIPOD_DEVICE_NUMBER_2 == device)) {
        NGLogDebug(LogTag, "onNotifyIPodErrorStatusChanged");
    }
    // set ipod error status
    setIPodErrorStatus();
}

void IpodCommon::setIPodErrorStatus()
{
    if (NULL != m_ipodCurModel) {
        m_ipodErrorStatus = m_ipodCurModel->getIPodErrorStatus();
        switch (m_ipodErrorStatus) {
        case FCIPOD_ERROR_NOTRACK:
        {
            openONS(TEMP_MSG_ONS_POD_004);
            m_isError = true;
        }
            break;
        case FCIPOD_ERROR_COMMUNICATION:
        case FCIPOD_ERROR_OVER_CURRENT:
        {
            openONS(TEMP_MSG_A_ONS_POD_001);
            m_isError = true;
        }
            break;
        case FCIPOD_ERROR_AUTHENTICATION:
        {
            openONS(TEMP_MSG_A_ONS_POD_013);
            m_isError = true;
        }
            break;
        case FCIPOD_ERROR_NOT_SUPPORT_FIRMWARE_VERSION:
        {
            openONS(TEMP_MSG_A_ONS_POD_012);
            m_isError = true;
        }
            break;
        case FCIPOD_ERROR_NOT_SUPPORT_IPOD:
        {
            NGLogDebug(LogTag, "onNotifyIPodErrorStatusChanged  is FCIPOD_ERROR_NOT_SUPPORT_IPOD");
            m_isError = true;
        }
            break;
        case FCIPOD_ERROR_INVALID:
        {
            NGLogDebug(LogTag, "onNotifyIPodErrorStatusChanged  is FCIPOD_ERROR_INVALID1");
            m_isError = false;
        }
            break;
        default:
        {
            NGLogDebug(LogTag, "onNotifyIPodErrorStatusChanged  is FCIPOD_ERROR_INVALID");
            m_isError = false;
        }
            break;
        }
    }
}

/*
 * isError(function describe)
 * unitTest's usecase
 */
//  isError
bool IpodCommon::isError()
{
    NGLogDebug(LogTag, "isError is %d.", m_isError);
    return m_isError;
}

void IpodCommon::setIpodListRequestSt(bool isRequest)
{
    m_isRequest = isRequest;
}

bool IpodCommon::getIpodListRequestSt()
{
    return m_isRequest;
}

/*
 * onNotifyIPodIsGettingArtworkStatusChanged(function describe)
 * unitTest's usecase
 */
// onNotifyIPodIsGettingArtworkStatusChanged
void IpodCommon::onNotifyIPodIsGettingArtworkStatusChanged(FCIPOD_DEVICE_NUMBER device)
{
    //  This is get dvice is ipod, go to log.
    if ((FCIPOD_DEVICE_NUMBER_1 == device)
        || (FCIPOD_DEVICE_NUMBER_2 == device)) {
        NGLogDebug(LogTag, "onNotifyIPodIsGettingArtworkStatusChanged");
    }
    setIPodArtWork();
}

/*
 * (function describe)
 * unitTest's usecase
 */
// onNotifyIpodListSearchingStatusChanged
void IpodCommon::onNotifyIpodListSearchingStatusChanged(FCIPOD_DEVICE_NUMBER device)
{
    //  This is get dvice is ipod, go to log.
    if ((FCIPOD_DEVICE_NUMBER_1 == device)
        || (FCIPOD_DEVICE_NUMBER_2 == device)) {
        NGLogDebug(LogTag, "onNotifyIpodListSearchingStatusChanged");
    }
    setIPodSearching();
}

/*
 * onNotifyIPodDeviceStatusChanged(function describe)
 * unitTest's usecase
 */
// onNotifyIPodDeviceStatusChanged
void IpodCommon::onNotifyIPodDeviceStatusChanged(FCIPOD_DEVICE_NUMBER device)
{
    //  This is get dvice is ipod, go to log.
    if ((FCIPOD_DEVICE_NUMBER_1 == device)
        || (FCIPOD_DEVICE_NUMBER_2 == device)) {
        NGLogDebug(LogTag, "onNotifyIPodDeviceStatusChanged");
    }
    // Set Ipod iap device
    setIPodIapDevice();
    // Set ipod sevice status
    setIPodDeviceStatus();
    if (NULL != m_ipodCurModel) {
        m_ipodDeviceStatus = m_ipodCurModel->getIPodDeviceStatus();
        if (FCIPOD_DEVICE_STATUS_NODEVICE == m_ipodDeviceStatus) {
            APP::Beep(BeepType_Beep1);
        }
    }
}

/*
 * onNotifyIPodDeviceNameChanged(function describe)
 * unitTest's usecase
 */
// onNotifyIPodDeviceNameChanged
void IpodCommon::onNotifyIPodDeviceNameChanged(FCIPOD_DEVICE_NUMBER device)
{
    //  This is get dvice is ipod, go to log.
    if ((FCIPOD_DEVICE_NUMBER_1 == device)
        || (FCIPOD_DEVICE_NUMBER_2 == device)) {
        NGLogDebug(LogTag, "onNotifyIPodDeviceStatusChanged");
    }
    // Set ipod sevice status
    setIPodDeviceName();
}

/*
 * onNotifyIPodListDataChanged(function describe)
 * unitTest's usecase
 */
// onNotifyIPodListDataChanged
void IpodCommon::onNotifyIPodListDataChanged(FCIPOD_DEVICE_NUMBER device)
{
    //  This is get dvice is ipod, go to log.
    if ((FCIPOD_DEVICE_NUMBER_1 == device)
        || (FCIPOD_DEVICE_NUMBER_2 == device)) {
        NGLogDebug(LogTag, "onNotifyIPodListDataChanged");
    }
    if (((IPodScreen_Mode == m_ipodActiveScreen) || (IPodScreen_Layer1 == m_ipodActiveScreen)
        || (IPodScreen_Layer2 == m_ipodActiveScreen) || (IPodScreen_Layer3 == m_ipodActiveScreen)
        || (IPodScreen_Layer4 == m_ipodActiveScreen))) {
        if (APP::MIST(AvCommon::GetInstance()->getAppId())) {
            NGLogDebug(LogTag, "----------------------------------------------APP::MIST(AvCommon::GetInstance()->getAppId())");
            APP::MIST(AvCommon::GetInstance()->getAppId())->setContextValue(KEY_SELECTSOURCE, VALUE_GOIPODBASE);
            NGLogDebug(LogTag, "----------------------------------------------setContextValue(KEY_SELECTSOURCE, VALUE_GOIPODBASE)");
            APP::MIST(AvCommon::GetInstance()->getAppId())->trigger(TRIGGER_GOAVSOURCE);
            NGLogDebug(LogTag, "----------------------------------------------trigger(TRIGGER_GOAVSOURCE)");
        }
    }
}

/*
 * onNotifyONSUpdateTime(function describe)
 * unitTest's usecase
 */
// onNotifyONSUpdateTime
void IpodCommon::onNotifyONSUpdateTime()
{
    NGLogDebug(LogTag, "onNotifyONSUpdateTime");
    openSourcePlate();
}

//  setIPodDeviceStatus
void IpodCommon::setIPodDeviceStatus()
{
    if (NULL != m_ipodCurModel) {
        m_ipodIapDevice = m_ipodCurModel->getIPodDeviceIapType();
        if (FCIPOD_IAP2_DEVICE == m_ipodIapDevice) {
            m_ipodDeviceStatus = m_ipodCurModel->getIPodDeviceStatus();
            if ((FCIPOD_DEVICE_STATUS_SYNCDBDATAOK != m_ipodDeviceStatus)
                && ((IPodScreen_Mode == m_ipodActiveScreen) || (IPodScreen_Layer1 == m_ipodActiveScreen)
                || (IPodScreen_Layer2 == m_ipodActiveScreen) || (IPodScreen_Layer3 == m_ipodActiveScreen)
                || (IPodScreen_Layer4 == m_ipodActiveScreen))) {
                if (NULL != AvCommon::GetInstance()) {
                    if (APP::MIST(AvCommon::GetInstance()->getAppId())) {
                        NGLogDebug(LogTag, "----------------------------------------------APP::MIST(AvCommon::GetInstance()->getAppId())");
                        APP::MIST(AvCommon::GetInstance()->getAppId())->setContextValue(KEY_SELECTSOURCE, VALUE_GOIPODBASE);
                        NGLogDebug(LogTag, "----------------------------------------------setContextValue(KEY_SELECTSOURCE, VALUE_GOIPODBASE)");
                        APP::MIST(AvCommon::GetInstance()->getAppId())->trigger(TRIGGER_GOAVSOURCE);
                        NGLogDebug(LogTag, "----------------------------------------------trigger(TRIGGER_GOAVSOURCE)");
                    }
                }
            }
        }
    }
}

FCIPOD_DEVICE_STATUS IpodCommon::getIPodDeviceStatus()
{
    return m_ipodDeviceStatus;
}

void IpodCommon::setIPodIapDevice()
{
    if (NULL != m_ipodCurModel) {
        m_ipodIapDevice = m_ipodCurModel->getIPodDeviceIapType();
        NGLogDebug(LogTag, "getIPodDeviceIapType------------------------------------  is %d.", m_ipodIapDevice);
    }
}

FCIPOD_IAP_DEVICE_TYPE IpodCommon::getIPodIapDevice()
{
    return m_ipodIapDevice;
}

void IpodCommon::setIPodSearching()
{
    if (NULL != m_ipodCurListModel) {
        m_isSearching = m_ipodCurListModel->getIsIpodListSearching();
    }
}

bool IpodCommon::getIsIPodSearching()
{
    return m_isSearching;
}

QMap<QString, QVariant> IpodCommon::getListTransferMap()
{
    return m_listTransferData;
}

void IpodCommon::requestListData()
{
    emit request(FC_MEDIA_IPOD_REQ_LISTINFO, m_listTransferData);
    m_listTransferData.clear ();
    m_isRequest = false;
}

void IpodCommon::setListTransferMap(FCIPOD_LIST_DIRECTION dirt, FCIPOD_DEVICE_NUMBER devs, int index)
{
    NGLogDebug(LogTag, "IpodCommon::setListTransferMap.");
    if (FCIPOD_LIST_DIRECTION_BACK != dirt) {
        m_listTransferData.insert(FC_MEDIA_IPOD_PAR_LIST_REQ_INDEX_NAME, index);
    }
    m_listTransferData.insert(FC_MEDIA_IPOD_PAR_LIST_REQ_DIRECTION_NAME, dirt);
    m_listTransferData.insert(FC_MEDIA_IPOD_PAR_DEVICE_NUMBER_KEY_NAME, devs);
    m_isRequest = true;
}

void IpodCommon::setIPodArtWork()
{
    if (NULL != m_ipodCurModel) {
        m_isGetArtWork = m_ipodCurModel->getIPodIsGettingArtwork();
    }
}

bool IpodCommon::getIsGettingArtWork()
{
    return m_isGetArtWork;
}

void IpodCommon::setIPodPrevIndex(int index)
{
    m_preIndex = index;
}

int IpodCommon::getIPodPrevIndex()
{
    return m_preIndex;
}

void IpodCommon::setIPodTopIndex(int index)
{
    m_topIndex.push_back (index);
}

int IpodCommon::getIPodTopIndex()
{
    int index = 0;
    if (!m_topIndex.isEmpty ()) {
        index = m_topIndex.back ();
        m_topIndex.pop_back ();
    }
    return index;
}

void IpodCommon::setIPodScreen(IPodScreen srceen)
{
    m_ipodActiveScreen = srceen;
    NGLogDebug(LogTag, "setIPodScreen  is %d.", m_ipodActiveScreen);
}

IpodCommon::IPodScreen IpodCommon::getIPodScreen()
{
    NGLogDebug(LogTag, "getIPodScreen  is %d.", m_ipodActiveScreen);
    return m_ipodActiveScreen;
}

void IpodCommon::setIPodPrevScreen(IPodScreen srceen)
{
    m_ipodPrevScreen = srceen;
    NGLogDebug(LogTag, "setIPodPrevScreen  is %d.", m_ipodPrevScreen);
}

IpodCommon::IPodScreen IpodCommon::getIPodPrevScreen()
{
    NGLogDebug(LogTag, "getIPodScreen  is %d.", m_ipodPrevScreen);
    return m_ipodPrevScreen;
}

void IpodCommon::setIPodSelectIndex(int index)
{
    m_ipodCount = index;
}

int IpodCommon::getIPodSelectIndex()
{
    return m_ipodCount;
}

void IpodCommon::setIPodListTotal(int count)
{
    m_ipodTotal = count;
}

int IpodCommon::getIPodListTotal()
{
    return m_ipodTotal;
}

void IpodCommon::changeListSelStation(int total, int e_value)
{
    NGLogDebug(LogTag, "IPodScreen_Mode.HardKey_TuneRotary is Repeat. Rotary right is %d.", e_value);
    if (0 < e_value) {
        if (total <= m_ipodCount + 1) {
            if (m_isAllorShuffle) {
                m_ipodCount = -1;
            }
            else {
                m_ipodCount = 0;
            }
        }
        else {
            m_ipodCount += 1;
        }
        NGLogDebug(LogTag, "IPodScreen_Mode.m_preIndex > 0 %d.", m_ipodCount);
    }
    else {
        if (!m_isAllorShuffle && 0 >= m_ipodCount) {
            m_ipodCount = total - 1;
        }
        else if (m_isAllorShuffle && -1 >= m_ipodCount) {
            m_ipodCount = total - 1;
        }
        else {  
            m_ipodCount -= 1;
        }
        NGLogDebug(LogTag, "IPodScreen_Mode.m_preIndex < 0   %d.", m_ipodCount);
    }
    emit notifyIPodSelectChange();
}

void IpodCommon::setDivSelect(int index)
{
    m_divSelect = index;
    emit notifyIPodDivSelectChange();
}

int IpodCommon::getDivSelect()
{
    return m_divSelect;
}

void IpodCommon::setIPodDeviceName()
{
    if (NULL != m_ipodCurModel) {
        m_ipodDeivceName = m_ipodCurModel->getIPodDeviceName();
        NGLogDebug(LogTag, "ipodDeivceName is %s", m_ipodDeivceName.toUtf8().data());
    }
}

QString IpodCommon::getIPodDeviceName()
{
    NGLogDebug(LogTag, "ipodDeivceName is %s", m_ipodDeivceName.toUtf8().data());
    return m_ipodDeivceName;
}

MediaIPodBasicModel *IpodCommon::getIPodBaseModel()
{
    return m_ipodCurModel;
}

MediaIpodListBaseModel *IpodCommon::getIPodListModel()
{
    return m_ipodCurListModel;
}

FCIPOD_DEVICE_NUMBER IpodCommon::getDeviceNumber()
{
    return m_device;
}

void IpodCommon::clearIpodTopIndex()
{
    NGLogDebug(LogTag, "clearIpodTopIndex");

    if (!m_topIndex.isEmpty ()) {
        m_topIndex.clear ();
    }
}

bool IpodCommon::getIsTuneRotary()
{
    return m_isTuneRotary;
}

void IpodCommon::setIsTuneRotary(bool TuneRotary)
{
    m_isTuneRotary = TuneRotary;
}

void IpodCommon::setIsAllorShuffle(bool isHave)
{
    m_isAllorShuffle = isHave;
}

void IpodCommon::setListVisible(bool vis)
{
    m_isVisibleList = vis;
}

void IpodCommon::setSelectTopIndex(bool isTrue, int index)
{
    if (isTrue) {
        m_selectTopIndexGo = m_selectTopIndexBack;
    }
    else {
        m_selectTopIndexBack = index;
    }
}

int IpodCommon::getSelectTopIndex()
{
    return m_selectTopIndexGo;
}

/*---------------------------------------------------------------------------*/
// Private functions
/*---------------------------------------------------------------------------*/

/* EOF */

