// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../Data.h"
#include "../PrivateKey.h"
#include "../proto/Binance.pb.h"

namespace TW::BinanceTestnet {

/// Helper class that performs BinanceTestnet transaction signing.
class Signer {
public:
    /// Hide default constructor
    Signer() = delete;

    /// Signs a Proto::SigningInput transaction
    static TW::Binance::Proto::SigningOutput sign(const TW::Binance::Proto::SigningInput& input) noexcept;

    /// Signs a json Proto::SigningInput with private key
    static std::string signJSON(const std::string& json, const Data& key);
};

} // namespace TW::BinanceTestnet

/// Wrapper for C interface.
struct TWBinanceTestnetSigner {
    TW::BinanceTestnet::Signer impl;
};
