#ifndef LIBDAETRIS_HPP
#define LIBDAETRIS_HPP
#include <functional>

#define LIB_DAETRIS_SERIAL_HPP


namespace LibDaetris
{
class SerialApp : public ofBaseApp {
public:
    using callback_t = std::function<void(int)>;

    SerialApp(std::string port_name, int baud, callback_t callback = empty_callback) : 
        m_port_name(port_name),
        m_baud(baud),
        m_callback(callback)
    {
        // Do Nothing
    }

    void setup() {
        m_serial.setup(m_port_name, m_baud);

        if (!m_serial.isInitialized()) {
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

    static void empty_callback(int) {
        return;
    }
};
}


#endif
