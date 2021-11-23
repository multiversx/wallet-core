// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Interactions.h"

#include "uint256.h"
#include "HexCoding.h"

using namespace TW;
using namespace TW::Elrond;

InteractionTransferESDT::InteractionTransferESDT(): 
    sender(Address()), 
    receiver(Address()) {
}

void InteractionTransferESDT::setSender(const Address& sender) {
    this->sender = sender;
}

void InteractionTransferESDT::setReceiver(const Address& receiver) {
    this->receiver = receiver;
}

void InteractionTransferESDT::setTransfer(const std::string& tokenIdentifier, const std::string& amount) {
    this->tokenIdentifier = tokenIdentifier;
    this->amount = amount;
}

Proto::TransactionMessage InteractionTransferESDT::buildTransaction() {
    Proto::TransactionMessage message;

    uint256_t amountAsU256 = uint256_t(this->amount);
    auto amountAsData = Data();
    encode256BE(amountAsData, amountAsU256, 256);

    std::string encodedTokenIdentifier = hex(TW::data(this->tokenIdentifier));
    std::string encodedAmount = hex(amountAsData);
    // TODO: trim zero-padding.

    std::string data = std::string("ESDTTransfer") + std::string("@") + encodedTokenIdentifier + std::string("@") + encodedAmount;

    message.set_sender(this->sender.string());
    message.set_receiver(this->receiver.string());
    message.set_data(data);

    return message;
}
