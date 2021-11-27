// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

namespace TW::Elrond {

class NetworkConfig {
public:
    NetworkConfig();
};

} // namespace

/// Wrapper for C interface.
struct TWElrondNetworkConfig {
    TW::Elrond::NetworkConfig impl;
};
