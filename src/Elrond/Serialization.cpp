// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Serialization.h"

#include "../Elrond/Address.h"
#include "../proto/Elrond.pb.h"
#include "Base64.h"
#include "PrivateKey.h"

using namespace TW::Elrond;

using string = std::string;

std::map<std::string, int> fields_order {
    {"nonce", 1},
    {"value", 2},
    {"receiver", 3},
    {"sender", 4},
    {"gas_price", 5},
    {"gas_limit", 6},
    {"data", 7}
};

struct FieldsSorter {
    bool operator() (const string& lhs, const string& rhs) const {
        return fields_order[lhs] < fields_order[rhs]; 
    }
};

template<class Key, class T, class Compare, class Allocator>
using sorted_map = std::map<Key, T, FieldsSorter, Allocator>;
using sorted_json = nlohmann::basic_json<sorted_map>;
using json = nlohmann::json;

static string encodeTransactionData(string data) {
    TW::Data buffer = TW::data(data); 
    string encoded = TW::Base64::encode(buffer);
    return encoded;
}

string TW::Elrond::serializeMessageToSignableString(const Proto::TransferMessage& message) {
    sorted_json payload {
        {"nonce", json(message.nonce())},
        {"value", json(message.value())},
        {"receiver", json(message.receiver())},
        {"sender", json(message.sender())},
        {"gas_price", json(message.gas_price())},
        {"gas_limit", json(message.gas_limit())}
    };

    if (!message.data().empty()) {
        payload["data"] = json(encodeTransactionData(message.data()));
    }

    string jsonString = payload.dump();
    return jsonString;
}
