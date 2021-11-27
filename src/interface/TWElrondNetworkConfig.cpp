// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWElrondNetworkConfig.h>

#include "Elrond/NetworkConfig.h"
#include "Data.h"
#include "assert.h"

using namespace TW;
using namespace TW::Elrond;

struct TWElrondNetworkConfig *_Nonnull TWElrondNetworkConfigCreate() {
    auto networkConfig = NetworkConfig();
    return new TWElrondNetworkConfig{ networkConfig };
}

void TWElrondNetworkConfigDelete(struct TWElrondNetworkConfig *_Nonnull self) {
    assert(self != nullptr);
    delete self;
}
