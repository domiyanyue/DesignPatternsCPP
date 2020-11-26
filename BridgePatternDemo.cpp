#include <iostream>

class EntertainmentDevice {
  public:
    int deviceState;
    int maxSetting;
    int volumeSetting = 0;

  public:
    EntertainmentDevice(){};

    virtual void buttonFivePressed() = 0;
    virtual void buttonSixPressed() = 0;

    void deviceFeedback() {
        if (deviceState > maxSetting || deviceState < 0) {
            deviceState = 0;
        }
        std::cout << "On state : " << deviceState << "\n";
    }

    void buttonSevenPressed() {
        volumeSetting++;
        std::cout << "Volume Ldevel : " << volumeSetting << "\n";
    }

    void buttonEightPressed() {
        volumeSetting--;
        std::cout << "Volume Ldevel : " << volumeSetting << "\n";
    }
};

class TVDevice : public EntertainmentDevice {
  public:
    TVDevice(int newDeviceState, int newMaxSetting) : EntertainmentDevice() {
        deviceState = newDeviceState;
        maxSetting = newMaxSetting;
    }

    void buttonFivePressed() {
        std::cout << "Channel Down\n";
        deviceState--;
    }

    void buttonSixPressed() {
        std::cout << "Channel Up\n";
        deviceState++;
    }
};

class RemoteButton {
  private:
    EntertainmentDevice *entertainmentDevice;

  public:
    RemoteButton(EntertainmentDevice *newDevice) {
        entertainmentDevice = newDevice;
    }

    void buttonFivePressed() { entertainmentDevice->buttonFivePressed(); }

    void buttonSixPressed() { entertainmentDevice->buttonSixPressed(); }

    void deviceFeedback() { entertainmentDevice->deviceFeedback(); }

    virtual void buttonNinePressed() = 0;
};

class TVRemoteMute : public RemoteButton {
  public:
    TVRemoteMute(EntertainmentDevice *newDevice) : RemoteButton(newDevice) {}

    void buttonNinePressed() { std::cout << "TV was muted\n"; }
};

class TVRemotePause : public RemoteButton {
  public:
    TVRemotePause(EntertainmentDevice *newDevice) : RemoteButton(newDevice) {}

    void buttonNinePressed() { std::cout << "TV was paused\n"; }
};

int main() {
    RemoteButton *tv = new TVRemoteMute(new TVDevice(1, 200));
    RemoteButton *tv2 = new TVRemotePause(new TVDevice(1, 200));

    std::cout << "Test TV with mute: \n";
    tv->buttonFivePressed();
    tv->buttonSixPressed();
    tv->buttonNinePressed();

    std::cout << "Test TV with pause: \n";
    tv2->buttonFivePressed();
    tv2->buttonSixPressed();
    tv2->buttonSixPressed();
    tv2->buttonSixPressed();
    tv2->buttonNinePressed();

    return 0;
}