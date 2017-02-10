#include "Send.h"
#include "Receive.h"

#include <thread>
#include <chrono>

#define send

int main() {
    std::cout << "Lol totally a robot!" << std::endl;

    #ifdef send
        auto sendObj = std::make_unique<SendData>(5801, "localhost");
        sendObj->establish();
        sendObj->sendString("Chantilly Robotics!");
        std::cout << "Sent message" << std::endl;
    #else
        auto receiveObj = std::make_unique<ReceiveData>(5801);
        receiveObj->establish();
        std::cout << receiveObj->receiveChunk(6) << std::endl;
    #endif
}
