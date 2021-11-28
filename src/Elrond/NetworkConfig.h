// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <string>

namespace TW::Elrond {

class NetworkConfig {
    std::string chainId;
    int gasPerByte;
    int minGasLimit;
    long minGasPrice;
public:
    NetworkConfig();
    void setChainId(const std::string& value);
    void setGasPerByte(int value);
    void setMinGasLimit(int value);
    void setMinGasPrice(long value);

    const std::string& getChainId();
    int getGasPerByte();
    int getMinGasLimit();
    long getMinGasPrice();
};

} // namespace

/// Wrapper for C interface.
struct TWElrondNetworkConfig {
    TW::Elrond::NetworkConfig impl;
};
