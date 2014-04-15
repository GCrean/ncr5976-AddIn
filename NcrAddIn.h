#ifndef __ADDINNATIVE_H__
#define __ADDINNATIVE_H__

#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"

#include "NcrComPort.h"


typedef struct __Aliases {
    wchar_t         ru[80];
    wchar_t         name[80];
} Aliases;

const int NCR_INT_API = 1;

///////////////////////////////////////////////////////////////////////////////
// class CAddInNCR5976
class CAddInNCR5976 : public IComponentBase
{
public:
    enum Props
    {
        eProp_Version = 0,
        eProp_Result,
        eProp_CurrentDeviceNumber,
        eProp_CurrentDeviceName,
        eProp_Model,
        eProp_DataBits,
        eProp_LoadFonts,
        eProp_Port,
        eProp_Speed,
        eProp_StopBits,
        eProp_Parity,
        eProp_CodePage,
        eProp_ResultDescription,
        eProp_DeviceColumnCount,
        eProp_DeviceTurnedOn,
        eProp_MarqueeRepeatDelay,
        eProp_MarqueeShowDelay,
        eProp_MarqueeType,
        eProp_CurrentWindow,
        eProp_MarqueeFormat,
        eProp_WindowCount,

        eProp_Last      // Always last
    };

    enum Methods
    {
        eMeth_AddDevice = 0,
        eMeth_DeleteDevice,
        eMeth_CreateWindow,
        eMeth_Clear,
        eMeth_ShowTextPos,
        eMeth_ClearText,
        eMeth_DeleteWindow,
		eMeth_SendByte,
        eMeth_Last      // Always last
    };

    CAddInNCR5976(void);
    virtual ~CAddInNCR5976();
    // IInitDoneBase
    virtual bool ADDIN_API Init(void*);
    virtual bool ADDIN_API setMemManager(void* mem);
    virtual long ADDIN_API GetInfo();
    virtual void ADDIN_API Done();
    // ILanguageExtenderBase
    virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T**);
    virtual long ADDIN_API GetNProps();
    virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
    virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
    virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
    virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
    virtual bool ADDIN_API IsPropReadable(const long lPropNum);
    virtual bool ADDIN_API IsPropWritable(const long lPropNum);
    virtual long ADDIN_API GetNMethods();
    virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
    virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum,
                            const long lMethodAlias);
    virtual long ADDIN_API GetNParams(const long lMethodNum);
    virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
                            tVariant *pvarParamDefValue);
    virtual bool ADDIN_API HasRetVal(const long lMethodNum);
    virtual bool ADDIN_API CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray);
    virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
    // LocaleBase
    virtual void ADDIN_API SetLocale(const WCHAR_T* loc);



private:
    long findName(const Aliases *names, const wchar_t *name) const;
    void addError(uint32_t wcode, const wchar_t* source,
                    const wchar_t* descriptor, long code);
    // Attributes
    IAddInDefBase      *m_iConnect;
    IMemoryManager     *m_iMemory;

	NcrDeviceList		m_devices;

};

#endif //__ADDINNATIVE_H__
