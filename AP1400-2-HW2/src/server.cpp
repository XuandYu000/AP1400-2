#include "server.h"

std::vector<std::string> pending_trxs;

Server::Server() { this->clients = {}; }

std::string add4RandomNum(std::string id) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1000, 9999);
    std::string num = std::to_string(distribution(generator));

    return id + num;
}

std::shared_ptr<Client> Server::add_client(std::string id) {
    // Find whether the id already exists.
    for (const auto& [key, value] : clients) {
        if (key->get_id() == id) {
            id = add4RandomNum(id);
        }
    }

    Client *client = new Client(id, (const Server*) this);
    std::shared_ptr<Client> ptr(client);
    clients.insert({ptr, 5.0});
    return ptr;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (const auto& [key, value] : clients) {
        if (key->get_id() == id) {
            return key;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for (const auto& [key, value] : clients) {
        if (key->get_id() == id) {
            return value;
        }
    }
    return -1;
}

bool validTrx(std::string trx, size_t& pos1, size_t& pos2) {
    size_t cnt = 0;

    for (int i = 0, len = trx.size(); i < len; i++) {
        if(trx[i] == '-') {
            cnt++;
            if (cnt == 1) {
                pos1 = i;
            }
            if (cnt == 2) {
                pos2 = i;
            }
        }
    }

    if (cnt == 2) {
        return true;
    } else {
        return false;
    }
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    // The two '-'s' positions.
    size_t pos1, pos2;
    if(!validTrx(trx, pos1, pos2)) {
        throw std::runtime_error("The trx format is not valid. It should be {name1}-{name2}-{money}.");
    }

    sender = std::string (trx.begin(), trx.begin() + pos1);
    receiver = std::string (trx, pos1 + 1, pos2 - pos1 - 1);
    value = std::stod(std::string (trx.begin() + pos2 + 1, trx.end()));

    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender{}, receiver{};
    double value = 0;
    try {
        parse_trx(trx, sender, receiver, value);
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    auto p_sender = get_client(sender);
    auto p_receiver = get_client(receiver);
    if (p_sender == nullptr || p_receiver == nullptr) {
        return false;
    }

    bool authentic = crypto::verifySignature(p_sender->get_publickey(), trx, signature);
    if (!authentic) {
        return false;
    }

    if (get_wallet(p_sender->get_id()) < value) {
        return false;
    }

    pending_trxs.push_back(trx);
    return true;
}

size_t Server::mine() {
    std::string mempool{};
    for (const auto& trx : pending_trxs) {
        mempool += trx;
    }
    size_t nonce = 0;
    bool flag = false;
    while(!flag) {
        for (auto& c_w : clients) {
            nonce = c_w.first->generate_nonce();
            if (crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000") != std::string::npos) {
                flag = true;
                c_w.second += 6.25;
                for (const auto& trx : pending_trxs) {
                    std::string sender{}, receiver{};
                    double value = 0;
                    parse_trx(trx, sender, receiver, value);
                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }
                pending_trxs.clear();
                return nonce;
            }
        }
    }
    return nonce;
}