#pragma once

#include <coroutine>
#include <memory>

#include "task.h"

class Send;
class Recv;
class Accept;

class Socket;
class IoContext;

class Socket {
    friend class Accept;
    friend class Recv;
    friend class Send;
    friend class IoContext;

public:
    Socket(std::string_view port, IoContext &io_context);

    Socket(const Socket &) = delete;
    Socket(Socket &&socket) : io_context_(socket.io_context_), fd_(socket.fd_), io_state_(socket.io_state_) {
        socket.fd_ = -1;
    }

    ~Socket();

    task<std::shared_ptr<Socket>> accept();

    Recv recv(void *buffer, std::size_t len);

    Send send(void *buffer, std::size_t len);

    bool ResumeRecv();

    bool ResumeSend();

private:
    explicit Socket(int fd, IoContext &io_context);

private:
    IoContext &io_context_;
    int fd_ = -1;
    uint32_t io_state_ = 0U;  // 当前已经注册的可读可写等事件，epoll 需要用 modify 所以需要将旧的事件保存起来
    // 因为可能有两个协程同时在等待一个 socket，所以要用两个 coroutine_handle 来保存。
    std::coroutine_handle<> coro_recv_;  // 接收数据的协程
    std::coroutine_handle<> coro_send_;  // 发送数据的协程
};
