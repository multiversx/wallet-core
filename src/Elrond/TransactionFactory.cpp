// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TransactionFactory.h"

#include "Codec.h"
#include "HexCoding.h"
#include "uint256.h"

using namespace TW;
using namespace TW::Elrond;

TransactionFactory::TransactionFactory(const NetworkConfig& networkConfig) {
    this->networkConfig = networkConfig;
}

Proto::TransactionMessage TransactionFactory::createEGLDTransfer(const Address& sender, const Address& receiver, uint256_t amount) {
    Proto::TransactionMessage message;

    message.set_sender(sender.string());
    message.set_receiver(receiver.string());
    message.set_value(toString(amount));
    message.set_gas_limit(this->networkConfig.getMinGasLimit());
    message.set_gas_price(this->networkConfig.getMinGasPrice());
    message.set_version(1);

    return message;
}

Proto::TransactionMessage TransactionFactory::createESDTTransfer(const Address& sender, const Address& receiver, const std::string& tokenIdentifier, uint256_t amount) {
    Proto::TransactionMessage message;

    std::string encodedTokenIdentifier = Codec::encodeStringTopLevel(tokenIdentifier);
    std::string encodedAmount = Codec::encodeBigIntTopLevel(amount);

    std::string data = 
        std::string("ESDTTransfer") + 
        std::string("@") + 
        encodedTokenIdentifier +
        std::string("@") + 
        encodedAmount;

    message.set_sender(sender.string());
    message.set_receiver(receiver.string());
    message.set_data(data);
    message.set_gas_price(this->networkConfig.getMinGasPrice());
    message.set_version(1);

    return message;
}
