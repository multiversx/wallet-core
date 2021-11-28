// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../proto/Elrond.pb.h"
#include "Address.h"
#include "NetworkConfig.h"
#include "uint256.h"

namespace TW::Elrond {

/// Creates specific transaction objects, wrt. the provided "NetworkConfig".
class TransactionFactory {
    NetworkConfig networkConfig;
public:
    TransactionFactory(const NetworkConfig& networkConfig);
    Proto::TransactionMessage createEGLDTransfer(const Address& sender, const Address& receiver, uint256_t amount);
    Proto::TransactionMessage createESDTTransfer(const Address& sender, const Address& receiver, const std::string& tokenIdentifier, uint256_t amount);
};

} // namespace

/// Wrapper for C interface.
struct TWElrondTransactionFactory {
    TW::Elrond::TransactionFactory impl;
};
