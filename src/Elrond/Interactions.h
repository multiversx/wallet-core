// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../proto/Elrond.pb.h"
#include "Address.h"

namespace TW::Elrond {

class InteractionTransferESDT {
private:
    Address sender;
    Address receiver;
    std::string tokenIdentifier;
    std::string amount;
public:
    InteractionTransferESDT();
    void setSender(const Address& sender);
    void setReceiver(const Address& receiver);
    void setTransfer(const std::string& tokenIdentifier, const std::string& amount);
    Proto::TransactionMessage buildTransaction();
};

} // namespace

/// Wrapper for C interface.
struct TWElrondInteractionTransferESDT {
    TW::Elrond::InteractionTransferESDT impl;
};
