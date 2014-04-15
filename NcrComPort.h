#ifndef NCRCOMPORT_H
#define NCRCOMPORT_H

#include <windows.h>
#include <vector>
#include <string>


class NcrComPort
{
public:
    NcrComPort();
    NcrComPort(const char *port);
    virtual ~NcrComPort();

    void SetModel(int model);
    int GetModel() const;

    void SetDeviceName(const std::wstring &name);
    const std::wstring &GetDeviceName() const;

    int ReadByte();
    bool SendData(const char *data);
    void Open(const char *port);

protected:
private:

    void FillDcb(DCB &dcb);

    DCB                 dcb;
    HANDLE              hPort;
    const char         *Port;
    int                 m_model;
    std::wstring        m_DeviceName;
};

class NcrDeviceList : public std::vector<NcrComPort> {
public:

    NcrDeviceList();

    void AddDevice();
    int GetCurrentDeviceNumber() const;

    NcrComPort &Current();
    const NcrComPort &Current() const;

private:
    int m_CurrentDeviceNumber;
};


#endif // NCRCOMPORT_H
