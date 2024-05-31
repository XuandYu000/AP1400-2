#include "client.h"

Client::Client(std::string id, const Server *server) : id(id), server((Server const *const) server){
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);
    this->public_key = public_key;
    this->private_key = private_key;
}

std::string Client::get_id() {
    return this->id;
}

std::string Client::get_publickey() const{
    return this->public_key;
}

double Client::get_wallet() {
    return this->server->get_wallet(id);
}

std::string Client::sign(std::string txt) const {
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
    std::string trx = this->get_id() + '-' + receiver + '-' + std::to_string(value);
    return this->server->add_pending_trx(trx, sign(trx));
}

size_t Client::generate_nonce() {
    std::default_random_engine generator;
    std::uniform_int_distribution<> distribution(0,  INT_MAX);

    return distribution(generator) % 10;
}

using MPD = std::map<std::shared_ptr<Client>, double>;
void  show_wallets(const  Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: *((MPD*)&server))
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}