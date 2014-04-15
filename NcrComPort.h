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
	bool SendByte(int byte);
	void SendString(const char *str);

    void Open(const char *port);

	int GetResult() const;

	void TurnOn();
	void TurnOff();
	bool TurnedOn() const;

	void ClearText();

protected:
private:

    void FillDcb(DCB &dcb);

    DCB                 dcb;
    HANDLE              hPort;
    const char         *Port;
    int                 m_model;
    std::wstring        m_DeviceName;

	int					m_Result;
	bool				m_turned_on;
};

class NcrDeviceList : public std::vector<NcrComPort> {
public:

    NcrDeviceList();

    void AddDevice();
	void DeleteDevice();

    int GetCurrentDeviceNumber() const;

    NcrComPort &Current();
    const NcrComPort &Current() const;

	void Current(unsigned DeviceNumber);

private:
    unsigned m_CurrentDeviceNumber;
};


#endif // NCRCOMPORT_H
