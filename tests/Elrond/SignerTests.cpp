// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Elrond/Signer.h"
#include "Elrond/Address.h"
#include "HexCoding.h"
#include "PrivateKey.h"
#include "PublicKey.h"

#include <gtest/gtest.h>

using namespace TW;
using namespace TW::Elrond;


TEST(ElrondSigner, Sign) {
    auto input = Proto::SigningInput();
    auto privateKey = PrivateKey(parse_hex("1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf"));
    input.set_private_key(privateKey.bytes.data(), privateKey.size());

    input.mutable_transaction()->set_nonce(0);
    input.mutable_transaction()->set_value("0");
    input.mutable_transaction()->set_sender("erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz");
    input.mutable_transaction()->set_receiver("erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr");
    input.mutable_transaction()->set_gas_price(200000000000000);
    input.mutable_transaction()->set_gas_limit(500000000);
    input.mutable_transaction()->set_data("foo");

    auto output = Signer::sign(input);
    auto signature = output.signature();
    auto signedTransaction = output.signed_transaction();

    ASSERT_EQ("8912cd7310df084cffe67557ef93c8fd30048d00bb71ea5fe9f5ebb6d90194500122eab982d49c5c5c164e7012cb8d29279820f3e7e885a5fe31c5b2cce0e90a", signature);
    ASSERT_EQ(R"({"nonce":0,"value":"0","receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000,"data":"foo","signature":"8912cd7310df084cffe67557ef93c8fd30048d00bb71ea5fe9f5ebb6d90194500122eab982d49c5c5c164e7012cb8d29279820f3e7e885a5fe31c5b2cce0e90a"})", signedTransaction);
}

TEST(ElrondSigner, SignJSON) {
    // Shuffle some fields, assume arbitrary order in the input
    auto input = (R"({"data":"foo","value":"0","nonce":0,"receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000})" 
    auto privateKey = PrivateKey(parse_hex("1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf"));
    
    auto signedTransaction = Signer::signJSON(input, privateKey);
    ASSERT_EQ(R"({"nonce":0,"value":"0","receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000,"data":"foo","signature":"8912cd7310df084cffe67557ef93c8fd30048d00bb71ea5fe9f5ebb6d90194500122eab982d49c5c5c164e7012cb8d29279820f3e7e885a5fe31c5b2cce0e90a"})", signedTransaction);
}

TEST(ElrondSigner, SignWithoutData) {
    auto input = Proto::SigningInput();
    auto privateKey = PrivateKey(parse_hex("1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf"));
    input.set_private_key(privateKey.bytes.data(), privateKey.size());

    input.mutable_transaction()->set_nonce(0);
    input.mutable_transaction()->set_value("0");
    input.mutable_transaction()->set_sender("erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz");
    input.mutable_transaction()->set_receiver("erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr");
    input.mutable_transaction()->set_gas_price(200000000000000);
    input.mutable_transaction()->set_gas_limit(500000000);
    input.mutable_transaction()->set_data("");
    
    auto output = Signer::sign(input);
    auto signature = output.signature();
    auto signedTransaction = output.signed_transaction();

    ASSERT_EQ("4e160bcafb6cb8ab8fc3260d3faf24bf7ce1205b5685adb457803db6d67c648a614308d8354e40b40fbb90c227046d6997493f798b92acb1b4bc49173939e703", signature);
    ASSERT_EQ(R"({"nonce":0,"value":"0","receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000,"data":"","signature":"4e160bcafb6cb8ab8fc3260d3faf24bf7ce1205b5685adb457803db6d67c648a614308d8354e40b40fbb90c227046d6997493f798b92acb1b4bc49173939e703"})", signedTransaction);
}

TEST(ElrondSigner, SignJSONWithoutData) {
    // Shuffle some fields, assume arbitrary order in the input
    auto input = (R"({"data":"foo","value":"0","nonce":0,"receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000})" 
    auto privateKey = PrivateKey(parse_hex("1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf"));
    
    auto signedTransaction = Signer::signJSON(input, privateKey);
    ASSERT_EQ(R"({"nonce":0,"value":"0","receiver":"erd188nydpkagtpwvfklkl2tn0w6g40zdxkwfgwpjqc2a2m2n7ne9g8q2t22sr","sender":"erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz","gasPrice":200000000000000,"gasLimit":500000000,"data":"","signature":"4e160bcafb6cb8ab8fc3260d3faf24bf7ce1205b5685adb457803db6d67c648a614308d8354e40b40fbb90c227046d6997493f798b92acb1b4bc49173939e703"})", signedTransaction);
}
