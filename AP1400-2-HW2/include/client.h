#ifndef CLIENT_H
#define CLIENT_H

#include <random>
#include <string>
#include "server.h"

// Client 使用了 Serve, 前置声明
// Note: 类或结构体的前向声明只能用来定义指针对象或引用
class Server;
class Client
{
public:
    Client(std::string id, const Server *server);
    std::string get_id();
    std::string get_publickey() const;
    double get_wallet();
    std::string sign(std::string txt) const;
    bool transfer_money(std::string receiver, double value);
    size_t generate_nonce();
private:
    Server const *const server; // const* 声明这是个常量指针，不能被修改；const 声明这是个指针常量，其指向的内容不能被修改。
    const std::string id;
    std::string public_key;
    std::string private_key;
};

#endif //CLIENT_H