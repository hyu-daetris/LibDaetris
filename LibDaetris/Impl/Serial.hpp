#ifndef LIB_DAETRIS_SERIAL_HPP
#define LIB_DAETRIS_SERIAL_HPP

#include "ofMain.h"

template <typename F>
class SerialApp : public ofBaseApp {
public:
    template <typename Fp>
    SerialApp(std::string port_name, int baud, Fp&& callback) : 
        m_port_name(port_name),
        m_baud(baud),
        m_callback(std::forward<Fp>(callback))
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

    F m_callback;
    ofSerial m_serial;
};

#endif