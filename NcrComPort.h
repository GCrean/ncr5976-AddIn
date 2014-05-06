#ifndef NCRCOMPORT_H
#define NCRCOMPORT_H

#include <windows.h>
#include <vector>
#include <string>

#define MIN_DISPLAY_INTERVAL 300

class NcrMarqueeData {
public:

	NcrMarqueeData();
	NcrMarqueeData(const NcrMarqueeData &src);

	void Step();
	void Stop();

	std::string			text;
	int					direction;
	HANDLE				timerId;

	unsigned			x, y, pos;
	unsigned			width;
	const char		   *port;
};

class NcrWindow
{
public:

	NcrWindow();

	~NcrWindow();

	NcrWindow(
		const char *port,
		int Yview,
		int Xview,
		int Hview,
		int Wview,
		int Hwindow,
		int Wwindow);

	int Yview;
	int Xview;
	int Hview;
	int Wview;
	int Hwindow;
	int Wwindow;

	int MarqueeType;
	int MarqueeFormat;
	int MarqueeRepeatWait;
	int MarqueeUnitWait;

	HANDLE timerId;

	std::string Text;
	const char *port;

	void OutputText();
	void StartMarquee();
	void StopMarquee();

};

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
	void SendStringLimited(const char *str, int n);
	void SendStringLimitedBlanked(const char *str, int n);

    void Open(const char *port);
	void Close();

	int GetResult() const;

	void TurnOn();
	void TurnOff();
	bool TurnedOn() const;

	void ClearText();

	void SetCursorPos(int Row, int Col);
	unsigned GetColumnCount() const;

	int WindowCount() const;
	int CurrentWindowNumber() const;
	void CurrentWindowNumber(int num);
	NcrWindow &CurrentWindow();
	const NcrWindow &CurrentWindow() const;

	void CreateNcrWindow(int Yview, int Xview, int Hview, int Wview, int Hwindow, int Wwindow);
	void DeleteNcrWindow();

	void SendStringPosThreaded(int row, int column, const char *str);

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

	std::vector<NcrWindow> m_windows;
	int					m_current_window;

	int OpenPort();
	void ClosePort();
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


extern int timer_counter;

HANDLE AddMarquee(const char *port, const std::string &text, int x, int y, int ms, int W);
void DeleteMarquee(HANDLE timerId);

void StopAllMarquees();

#endif // NCRCOMPORT_H
