// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <gtest/gtest.h>
#include <vector>
#include "boost/format.hpp"

#include "HexCoding.h"
#include "uint256.h"
#include "Elrond/TransactionFactory.h"
#include "TestAccounts.h"

using namespace TW;
using namespace TW::Elrond;

TEST(ElrondTransactionFactory, createEGLDTransfer) {
    Address sender, receiver;
    Address::decode(ALICE_BECH32, sender);
    Address::decode(BOB_BECH32, receiver);

    NetworkConfig networkConfig;
    TransactionFactory factory(networkConfig);

    Proto::TransactionMessage message = factory.createEGLDTransfer(
        sender,
        receiver,
        uint256_t("1000000000000000000")
    );

    ASSERT_EQ(ALICE_BECH32, message.sender());
    ASSERT_EQ(BOB_BECH32, message.receiver());
    ASSERT_EQ("", message.data());
    ASSERT_EQ("1000000000000000000", message.value());
    ASSERT_EQ(50000, message.gas_limit());
    ASSERT_EQ(1000000000, message.gas_price());
    ASSERT_EQ("1", message.chain_id());
    ASSERT_EQ(1, message.version());
}

TEST(ElrondTransactionFactory, createESDTTransfer) {
    Address sender, receiver;
    Address::decode(ALICE_BECH32, sender);
    Address::decode(BOB_BECH32, receiver);

    NetworkConfig networkConfig;
    TransactionFactory factory(networkConfig);

    Proto::TransactionMessage message = factory.createESDTTransfer(
        sender,
        receiver,
        "MYTOKEN-1234",
        uint256_t("10000000000000")
    );

    ASSERT_EQ(ALICE_BECH32, message.sender());
    ASSERT_EQ(BOB_BECH32, message.receiver());
    ASSERT_EQ("ESDTTransfer@4d59544f4b454e2d31323334@09184e72a000", message.data());
    ASSERT_EQ("", message.value());
    ASSERT_EQ(325000, message.gas_limit());
    ASSERT_EQ(1000000000, message.gas_price());
    ASSERT_EQ("1", message.chain_id());
    ASSERT_EQ(1, message.version());
}
