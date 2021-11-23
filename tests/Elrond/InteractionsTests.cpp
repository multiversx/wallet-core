// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <gtest/gtest.h>
#include <vector>
#include "boost/format.hpp"

#include "HexCoding.h"
#include "Elrond/Interactions.h"

using namespace TW;
using namespace TW::Elrond;

TEST(ElrondInteractions, ESDTTransfer) {
    InteractionTransferESDT interaction;

    interaction.setSender(Address(data("erd1k2s324ww2g0yj38qn2ch2jwctdy8mnfxep94q9arncc6xecg3xaq6mjse8")));
    interaction.setReceiver(Address(data("erd1uv40ahysflse896x4ktnh6ecx43u7cmy9wnxnvcyp7deg299a4sq6vaywa")));
    interaction.setTransfer("MYTOKEN-1234", "10000000000000");

    Proto::TransactionMessage message = interaction.buildTransaction();
    message.set_nonce(42);
    message.set_chain_id("1");

    ASSERT_EQ("ESDTTransfer@4d59544f4b454e2d31323334@09184e72a000", message.data());
}
