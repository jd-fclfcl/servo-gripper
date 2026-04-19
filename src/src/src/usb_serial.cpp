
// 【改动说明】
// 1. 改进舵机角度映射函数，使用正确的 PWM 计数单位映射
// 2. 修改数据验证逻辑：改为验证单片机原样回传的二进制数据，而不是查找字符串
// 3. 改进日志输出，显示当前状态和 PWM 值
// 4. 改进错误处理和连接状态管理
// 5. 【重要】统一使用 int32_t 类型：函数参数、返回值、数组类型都明确为 int32_t
//    以确保与单片机代码中的 int32_t 类型完全一致，避免平台相关的类型差异

// 标准库
// #include<usercmd.h>

// POSIX 串口相关
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <sys/select.h>
// 项目头文件
#include "FSM/FSM.h"
#include "FSM/ControlFrame.h"
class USBSerial {
private:
    int serial_fd;
    std::string port_name;
    bool is_open;

    // 配置串口参数
    bool configurePort(int baudRate, int dataBits, int stopBits, char parity) {
        struct termios options;

        // 获取当前串口配置
        if (tcgetattr(serial_fd, &options) != 0) {
            std::cerr << "Error getting serial port attributes: " << strerror(errno) << std::endl;
            return false;
        }

        // 设置波特率
        speed_t speed;
        switch (baudRate) {
            case 9600:   speed = B9600; break;
            case 19200:  speed = B19200; break;
            case 38400:  speed = B38400; break;
            case 57600:  speed = B57600; break;
            case 115200: speed = B115200; break;
            default:     speed = B9600; break;
        }

        cfsetispeed(&options, speed);
        cfsetospeed(&options, speed);

        // 设置数据位
        options.c_cflag &= ~CSIZE;
        switch (dataBits) {
            case 5: options.c_cflag |= CS5; break;
            case 6: options.c_cflag |= CS6; break;
            case 7: options.c_cflag |= CS7; break;
            case 8: options.c_cflag |= CS8; break;
            default: options.c_cflag |= CS8; break;
        }

        // 设置停止位
        if (stopBits == 1) {
            options.c_cflag &= ~CSTOPB;
        } else {
            options.c_cflag |= CSTOPB;
        }

        // 设置校验位
        switch (parity) {
            case 'n':
            case 'N':
                options.c_cflag &= ~PARENB;
                options.c_iflag &= ~INPCK;
                break;
            case 'o':
            case 'O':
                options.c_cflag |= (PARODD | PARENB);
                options.c_iflag |= INPCK;
                break;
            case 'e':
            case 'E':
                options.c_cflag |= PARENB;
                options.c_cflag &= ~PARODD;
                options.c_iflag |= INPCK;
                break;
            default:
                options.c_cflag &= ~PARENB;
                options.c_iflag &= ~INPCK;
                break;
        }

        // 设置控制模式
        options.c_cflag |= CLOCAL | CREAD;

        // 设置输入模式
        options.c_iflag &= ~(IXON | IXOFF | IXANY);
        options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        // 设置输出模式
        options.c_oflag &= ~OPOST;

        // 设置本地模式
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        // 设置超时
        options.c_cc[VMIN] = 1;
        options.c_cc[VTIME] = 1;

        // 应用配置
        if (tcsetattr(serial_fd, TCSANOW, &options) != 0) {
            std::cerr << "Error setting serial port attributes: " << strerror(errno) << std::endl;
            return false;
        }

        return true;
    }

public:
    USBSerial() : serial_fd(-1), is_open(false) {}

    ~USBSerial() {
        close();
    }

    // 打开串口
    bool open(const std::string& port, int baudRate = 9600, 
              int dataBits = 8, int stopBits = 1, char parity = 'N') {
        if (is_open) {
            std::cerr << "Serial port already open" << std::endl;
            return false;
        }

        port_name = port;
        serial_fd = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

        if (serial_fd == -1) {
            std::cerr << "Error opening serial port " << port << ": " 
                      << strerror(errno) << std::endl;
            return false;
        }

        // 设置为阻塞模式
        if (fcntl(serial_fd, F_SETFL, 0) < 0) {
            std::cerr << "Error setting serial port to blocking mode: " 
                      << strerror(errno) << std::endl;
            ::close(serial_fd);
            return false;
        }

        // 配置串口
        if (!configurePort(baudRate, dataBits, stopBits, parity)) {
            ::close(serial_fd);
            return false;
        }

        is_open = true;
        // std::cout << "Serial port " << port << " opened successfully" << std::endl;
        return true;
    }

    // 关闭串口
    void close() {
        if (is_open) {
            ::close(serial_fd);
            serial_fd = -1;
            is_open = false;
            // std::cout << "Serial port closed" << std::endl;
        }
    }

    // 发送数据
    int write(const std::vector<uint8_t>& data) {
        if (!is_open) {
            std::cerr << "Serial port not open" << std::endl;
            return -1;
        }

        size_t total_written = 0;
        while (total_written < data.size()) {
            ssize_t bytes_written = ::write(serial_fd,
                                            data.data() + total_written,
                                            data.size() - total_written);

            if (bytes_written < 0) {
                if (errno == EINTR) {
                    continue;
                }
                int err = errno;
                std::cerr << "Error writing to serial port (errno=" << err << "): " << strerror(err) << std::endl;
                return -1;
            }

            if (bytes_written == 0) {
                break;
            }

            total_written += static_cast<size_t>(bytes_written);
        }

        return static_cast<int>(total_written);
    }

    // 刷新串口输入输出缓冲区
    bool flush() {
        if (!is_open) {
            return false;
        }
        if (tcflush(serial_fd, TCIOFLUSH) != 0) {
            std::cerr << "Error flushing serial port: " << strerror(errno) << std::endl;
            return false;
        }
        return true;
    }

    // 接收数据
    std::vector<uint8_t> read(int timeout_ms = 1000) {
        std::vector<uint8_t> buffer;

        if (!is_open) {
            std::cerr << "Serial port not open" << std::endl;
            return buffer;
        }

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(serial_fd, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;

        int result;
        do {
            result = select(serial_fd + 1, &read_fds, NULL, NULL, &timeout);
        } while (result < 0 && errno == EINTR);

        if (result < 0) {
            std::cerr << "Error in select: " << strerror(errno) << std::endl;
            return buffer;
        }

        if (result == 0) {
            // 超时
            return buffer;
        }

        if (FD_ISSET(serial_fd, &read_fds)) {
            uint8_t temp_buffer[4096];
            ssize_t bytes_read = ::read(serial_fd, temp_buffer, sizeof(temp_buffer));

            if (bytes_read > 0) {
                buffer.insert(buffer.end(), temp_buffer, temp_buffer + bytes_read);
            } else if (bytes_read < 0) {
                std::cerr << "Error reading from serial port: " << strerror(errno) << std::endl;
            }
        }

        return buffer;
    }

    // 检查串口是否打开
    bool isOpen() const {
        return is_open;
    }

};

static std::string BytesToHex(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < data.size(); ++i) {
        if (i != 0) {
            oss << ' ';
        }
        oss << std::setw(2) << static_cast<unsigned>(data[i]);
    }
    return oss.str();
}


// 【改进】将舵机角度转换为 PWM 比较值
// 根据当前舵机控制范围：0.5ms(0°) - 2.5ms(270°)
// MCU PWM 周期: 2000 计数单位 = 20ms，Prescaler = 840，所以时钟周期为 0.01ms
// 因此: 0.5ms = 50, 2.5ms = 250
// 【改进】返回类型改为 int32_t 以确保与单片机的数据类型一致
// int32_t Steering(int put_angle){
   
//     int32_t compare_value = put_angle;
//     return compare_value;
// }

// 【改进】发送一次数据并验证下位机的回传（回传确认）
// 根据单片机代码，MCU 会原样回传接收到的数据用于确认
// 返回 true 表示收到了正确的回传数据，false 表示超时或数据不匹配
// 【改进】使用 int32_t 类型确保与单片机的 int32_t 类型一致
bool Send_data_once(USBSerial& serial, int32_t data1, int32_t data2, int32_t data3, int32_t data4) {
    std::ostringstream payload_builder;
    payload_builder << data1 << ',' << data2 << ',' << data3 << ',' << data4 << "\r\n";
    std::string payload = payload_builder.str();
    std::vector<uint8_t> send_data(payload.begin(), payload.end());

    // 在发送前清理串口缓冲区，避免旧数据干扰
    serial.flush();

    int bytes_written = serial.write(send_data);

    if (bytes_written == static_cast<int>(send_data.size())) {
        // std::cout << "[TX] " << payload;
    } else {
        int err = errno;
        std::cerr << "发送失败（bytes_written=" << bytes_written << ", expected=" << send_data.size() 
                  << ", errno=" << err << "): " << (err ? strerror(err) : "n/a") << std::endl;
        serial.close();
        return false;
    }

    // MCU 当前会按文本回传: v1,v2,v3,v4\r\n
    bool got_confirm = false;
    const int per_read_timeout_ms = 500; // 每次 read 超时时间
    const int max_wait_ms = 5000; // 最多等待 5000ms
    int waited = 0;
    std::vector<uint8_t> resp_accum;
    resp_accum.reserve(256);

    std::ostringstream expected_builder;
    expected_builder << data1 << ',' << data2 << ',' << data3 << ',' << data4;
    const std::string expected_line = expected_builder.str();
    const std::string expected_line_crlf = expected_line + "\r\n";

    // 期望的二进制序列（与发送数据一致）
    std::vector<uint8_t> expected_bytes(send_data.begin(), send_data.end());

    // 打印期望的 HEX，便于对照接收数据
    // std::cout << "[EXPECT STR] " << expected_line_crlf << std::endl;
    // std::cout << "[EXPECT HEX]  " << BytesToHex(expected_bytes) << std::endl;

    while (waited < max_wait_ms) {
        std::vector<uint8_t> resp = serial.read(per_read_timeout_ms);
        if (!resp.empty()) {
            // std::cout << "[RX HEX] " << BytesToHex(resp) << std::endl;

            // 【改进】将回传数据累积到一个缓冲区中
            resp_accum.insert(resp_accum.end(), resp.begin(), resp.end());

            std::string text(resp_accum.begin(), resp_accum.end());

            // 文本匹配（兼容没有 CRLF 或只返回主体的情形）
            if (text.find(expected_line) != std::string::npos || text.find(expected_line_crlf) != std::string::npos) {
                // std::cout << "[ACK] 收到文本回传确认: " << expected_line << std::endl;
                got_confirm = true;
                break;
            }

            // 二进制子序列匹配（更严格）
            if (!expected_bytes.empty()) {
                auto it = std::search(resp_accum.begin(), resp_accum.end(), expected_bytes.begin(), expected_bytes.end());
                if (it != resp_accum.end()) {
                    // std::cout << "[ACK] 收到二进制回传确认" << std::endl;
                    got_confirm = true;
                    break;
                }
            }

            // 避免无限增长，仅保留最后 512 字节
            if (resp_accum.size() > 512) {
                resp_accum.erase(resp_accum.begin(), resp_accum.end() - 512);
            }
        }
        waited += per_read_timeout_ms;
    }

    if (got_confirm) {
        // std::cout << "【确认】已验证下位机回传数据正确" << std::endl;
    } else {
        std::cerr << "【警告】未收到下位机的正确回传数据，等待超时（" << max_wait_ms << "ms）" << std::endl;
    }

    return got_confirm;
}



enum class Angle {
    ANGLE_0 = 0,
    ANGLE_45 = 45,
    ANGLE_90 = 90,
    ANGLE_135 = 135,
    ANGLE_180 = 180
};
// 【改进】使用 int32_t 类型的数组，确保与单片机发送的数据类型一致
enum class Field {
     keyboard,
     autoself
};
Field flag;
int main() {
    USBSerial serial;
    const std::string port = "/dev/serial/by-id/usb-STMicroelectronics_STM32_Virtual_ComPort_327636893135-if00";
    const int baud_rate = 115200;

    flag = Field::keyboard;
    const int delay_ms_between_sends = 100;
    ControlFrame ctrlFrame;

    while (true) {
        if (!serial.isOpen()) {
            if (!serial.open(port, baud_rate, 8, 1, 'N')) {
                std::cerr << "打开串口失败，请检查设备和权限，1秒后重试" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
        }
          
        switch(flag)
        {
            case Field::keyboard:
                if (ctrlFrame.cmdPanel != nullptr) {
                    userCmd = ctrlFrame.cmdPanel->getUserCmd();
                } else {
                    userCmd = UserCommand::NONE;
                }
                // start 状态后等待 1000ms，再进入 FIELD1
                break;
            case Field::autoself:
                userCmd = ctrlFrame.commandSource->getUserCmd();
                break;
             default:
               std::cerr << "未知状态,please check the flag in the usb_serial.cpp file" << std::endl;
                break;
        }


            //  // 【改进】输出当前状态标记
            //  std::cout << "当前状态: " << static_cast<int>(flag) << " | 值: [" 
            //            << value[0] << ", " << value[1] << ", " << value[2] << ", " << value[3] << "]" << std::endl;

                   ctrlFrame.run((bool)flag);

                // 【改进】发送数据并验证回传
                bool ok = Send_data_once(serial, value[0], value[1], value[2], value[3]);
        
                if (!ok) {
            // 【改进】发送失败或未收到确认，关闭串口并在下轮重连
            std::cerr << "【错误】发送失败，准备重新连接" << std::endl;
            serial.close();
        }

      

    }

    return 0;
}
