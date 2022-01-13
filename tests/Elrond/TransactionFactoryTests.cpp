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
    TransactionFactory factory;

    auto transfer = Proto::EGLDTransfer();
    transfer.set_sender(ALICE_BECH32);
    transfer.set_receiver(BOB_BECH32);
    transfer.set_amount("1000000000000000000");

    Proto::TransactionMessage transaction = factory.createEGLDTransfer(transfer);

    ASSERT_EQ(ALICE_BECH32, transaction.sender());
    ASSERT_EQ(BOB_BECH32, transaction.receiver());
    ASSERT_EQ("", transaction.data());
    ASSERT_EQ("1000000000000000000", transaction.value());
    ASSERT_EQ(50000, transaction.gas_limit());
    ASSERT_EQ(1000000000, transaction.gas_price());
    ASSERT_EQ("1", transaction.chain_id());
    ASSERT_EQ(1, transaction.version());
}

TEST(ElrondTransactionFactory, createESDTTransfer) {
    TransactionFactory factory;

    auto transfer = Proto::ESDTTransfer();
    transfer.set_sender(ALICE_BECH32);
    transfer.set_receiver(BOB_BECH32);
    transfer.set_token_identifier("MYTOKEN-1234");
    transfer.set_amount("10000000000000");

    Proto::TransactionMessage transaction = factory.createESDTTransfer(transfer);

    ASSERT_EQ(ALICE_BECH32, transaction.sender());
    ASSERT_EQ(BOB_BECH32, transaction.receiver());
    ASSERT_EQ("ESDTTransfer@4d59544f4b454e2d31323334@09184e72a000", transaction.data());
    ASSERT_EQ("0", transaction.value());
    ASSERT_EQ(425000, transaction.gas_limit());
    ASSERT_EQ(1000000000, transaction.gas_price());
    ASSERT_EQ("1", transaction.chain_id());
    ASSERT_EQ(1, transaction.version());
}

TEST(ElrondTransactionFactory, createESDTNFTTransfer) {
    TransactionFactory factory;

    auto transfer = Proto::ESDTNFTTransfer();
    transfer.set_sender(ALICE_BECH32);
    transfer.set_receiver(BOB_BECH32);
    transfer.set_token_collection("LKMEX-aab910");
    transfer.set_token_nonce(4);
    transfer.set_amount("184300000000000000");

    Proto::TransactionMessage transaction = factory.createESDTNFTTransfer(transfer);

    ASSERT_EQ(ALICE_BECH32, transaction.sender());
    ASSERT_EQ(ALICE_BECH32, transaction.receiver());
    ASSERT_EQ("ESDTNFTTransfer@4c4b4d45582d616162393130@04@028ec3dfa01ac000@c70cf50b238372fffaf7b7c5723b06b57859d424a2da621bcc1b2f317543aa36", transaction.data());
    ASSERT_EQ("0", transaction.value());
    ASSERT_EQ(937500, transaction.gas_limit());
    ASSERT_EQ(1000000000, transaction.gas_price());
    ASSERT_EQ("1", transaction.chain_id());
    ASSERT_EQ(1, transaction.version());
}

TEST(ElrondTransactionFactory, createTransfersWithChangedNetworkConfig) {
    NetworkConfig networkConfig;

    // Set dummy values:
    networkConfig.setChainId("T");
    networkConfig.setMinGasPrice(1500000000);
    networkConfig.setMinGasLimit(60000);
    networkConfig.setGasPerDataByte(2000);
    networkConfig.setGasCostESDTTransfer(300000);
    networkConfig.setGasCostESDTNFTTransfer(300000);

    TransactionFactory factory(networkConfig);

    Proto::EGLDTransfer egldTransfer;
    egldTransfer.set_sender(ALICE_BECH32);
    egldTransfer.set_receiver(BOB_BECH32);
    egldTransfer.set_amount("0");

    Proto::ESDTTransfer esdtTransfer;
    esdtTransfer.set_sender(ALICE_BECH32);
    esdtTransfer.set_receiver(BOB_BECH32);
    esdtTransfer.set_token_identifier("MYTOKEN-1234");
    esdtTransfer.set_amount("10000000000000");

    Proto::ESDTNFTTransfer esdtnftTransfer;
    esdtnftTransfer.set_sender(ALICE_BECH32);
    esdtnftTransfer.set_receiver(BOB_BECH32);
    esdtnftTransfer.set_token_collection("LKMEX-aab910");
    esdtnftTransfer.set_token_nonce(4);
    esdtnftTransfer.set_amount("184300000000000000");


    Proto::TransactionMessage tx1 = factory.createEGLDTransfer(egldTransfer);
    Proto::TransactionMessage tx2 = factory.createESDTTransfer(esdtTransfer);
    Proto::TransactionMessage tx3 = factory.createESDTNFTTransfer(esdtnftTransfer);
    
    ASSERT_EQ(60000, tx1.gas_limit());
    ASSERT_EQ(1500000000, tx1.gas_price());
    ASSERT_EQ("T", tx1.chain_id());

    ASSERT_EQ(560000, tx2.gas_limit());
    ASSERT_EQ(1500000000, tx2.gas_price());
    ASSERT_EQ("T", tx2.chain_id());

    ASSERT_EQ(1110000, tx3.gas_limit());
    ASSERT_EQ(1500000000, tx3.gas_price());
    ASSERT_EQ("T", tx3.chain_id());
}
