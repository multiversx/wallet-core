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

TEST(ElrondSerialization, SignableString) {
    Proto::TransactionMessage message;
    message.set_nonce(42);
    message.set_value("43");
    message.set_sender("alice");
    message.set_receiver("bob");
    message.set_data("foobar");

    string jsonString = serializeTransactionToSignableString(message);
    ASSERT_EQ(R"({"nonce":42,"value":"43","receiver":"bob","sender":"alice","gasPrice":0,"gasLimit":0,"data":"Zm9vYmFy"})", jsonString);
}

TEST(ElrondSerialization, SignableStringWithRealData) {
    Proto::TransactionMessage message;
    message.set_nonce(15);
    message.set_value("100");
    message.set_sender("erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz");
    message.set_receiver("erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr");
    message.set_gas_price(200000000000000);
    message.set_gas_limit(500000000);
    message.set_data("for dinner");

    string jsonString = serializeTransactionToSignableString(message);
    ASSERT_EQ(R"({"nonce":15,"value":"100","receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000,"data":"Zm9yIGRpbm5lcg=="})", jsonString);
}

TEST(ElrondSerialization, SignableStringWithoutData) {
    Proto::TransactionMessage message;
    message.set_nonce(42);
    message.set_value("43");
    message.set_sender("feed");
    message.set_receiver("abba");

    string jsonString = serializeTransactionToSignableString(message);
    ASSERT_EQ(R"({"nonce":42,"value":"43","receiver":"abba","sender":"feed","gasPrice":0,"gasLimit":0})", jsonString);
}
