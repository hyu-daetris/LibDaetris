#ifndef LIB_DAETRIS_SERIAL_HPP
#define LIB_DAETRIS_SERIAL_HPP

#include "ofMain.h"

namespace LibDaetris
{
class SerialApp : public ofBaseApp {
public:
    using callback_t = void(*)(int);

    SerialApp(std::string port_name, int baud, callback_t callback) : 
        m_port_name(port_name),
        m_baud(baud),
        m_callback(callback)
    {
        // Do Nothing
    }

    void setup() {
        m_serial.setup(m_port_name, m_baud);

        if (m_serial.isInitialized()) {
            throw std::runtime_error("Serial port couldn't initialized");
        }
    }

    void update() {
        if (m_serial.available() > 0) {
            m_callback(m_serial.readByte());
        }
    }


private:
    std::string m_port_name;
    int m_baud;

    callback_t m_callback;
    ofSerial m_serial;
};
}

#endif