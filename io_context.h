#pragma once

#include <set>

class Socket;
class Send;
class Recv;
class Accept;

class IoContext {
    friend class Socket;
    friend class Send;
    friend class Recv;
    friend class Accept;

public:
    IoContext();

    void run();

private:
    constexpr static std::size_t max_events = 10;
    const int fd_;
    void Attach(Socket *socket);
    void WatchRead(Socket *socket);
    void UnwatchRead(Socket *socket);
    void WatchWrite(Socket *socket);
    void UnwatchWrite(Socket *socket);
    void Detach(Socket *socket);
};
