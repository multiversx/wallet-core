// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <gtest/gtest.h>
#include <vector>
#include "boost/format.hpp"

#include "HexCoding.h"
#include "Elrond/TransactionFactory.h"

using namespace TW;
using namespace TW::Elrond;

TEST(ElrondTransactionFactory, createESDTTransfer) {
    TransactionFactory factory;

    Address sender, receiver;
    Address::decode("erd1k2s324ww2g0yj38qn2ch2jwctdy8mnfxep94q9arncc6xecg3xaq6mjse8", sender);
    Address::decode("erd1uv40ahysflse896x4ktnh6ecx43u7cmy9wnxnvcyp7deg299a4sq6vaywa", receiver);

    Proto::TransactionMessage message = factory.createESDTTransfer(
        sender,
        receiver,
        "MYTOKEN-1234",
        uint256_t("10000000000000")
    );

    ASSERT_EQ("ESDTTransfer@4d59544f4b454e2d31323334@09184e72a000", message.data());
}
