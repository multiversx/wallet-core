// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "Elrond/Serialization.h"
#include <gtest/gtest.h>
#include <vector>

using namespace TW;
using namespace TW::Elrond;

TEST(ElrondSerialization, TransactionPayloadIsCorrect) {
    Proto::TransferMessage message;
    message.set_nonce(42);
    message.set_value("43");
    message.set_receiver("abba");
    message.set_sender("feed");

    string jsonString = serializeMessageToSignableString(message);
    ASSERT_EQ(R"({"nonce":42,"value":"43","receiver":"q7o=","sender":"/u0=","gasPrice":0,"gasLimit":0})", jsonString);
}

TEST(ElrondSerialization, TransactionPayloadWithDataIsCorrect) {
    Proto::TransferMessage message;
    message.set_nonce(42);
    message.set_value("43");
    message.set_receiver("abba");
    message.set_sender("feed");
    message.set_data("hello");

    string jsonString = serializeMessageToSignableString(message);
    ASSERT_EQ(R"({"nonce":42,"value":"43","receiver":"q7o=","sender":"/u0=","gasPrice":0,"gasLimit":0,"data":"aGVsbG8="})", jsonString);
}
