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


TEST(ElrondSigner, SignWithoutData) {
    auto input = Proto::SigningInput();
    auto privateKey = PrivateKey(parse_hex("aa137cb6a0022f18ea2d31f00025190fb09961deb624e18cf11f6e867ccb45d3"));
    input.set_private_key(privateKey.bytes.data(), 32);

    input.mutable_transfer()->set_nonce(0);
    input.mutable_transfer()->set_value("0");
    input.mutable_transfer()->set_sender("93ee6143cdc10ce79f15b2a6c2ad38e9b6021c72a1779051f47154fd54cfbd5e");
    input.mutable_transfer()->set_receiver("a967adb3d1574581a6f7ffe0cd6600fb488686704fcff944c88efc7c90b3b13b");
    input.mutable_transfer()->set_gas_price(200000000000000);
    input.mutable_transfer()->set_gas_limit(500000000);
    auto output = Signer::sign(input);
    auto signature = output.encoded();

    ASSERT_EQ("04e98acb3c844bcf49fcd07417fdfe5edc9df4419f7deed49262145d3759f687c1cda202cda51808ad0834b472ccf1f5334b952e3cb1fd0b98721c6bfca10d04", signature);
}

TEST(ElrondSigner, SignWithData) {
    auto input = Proto::SigningInput();
    auto privateKey = PrivateKey(parse_hex("aa137cb6a0022f18ea2d31f00025190fb09961deb624e18cf11f6e867ccb45d3"));
    input.set_private_key(privateKey.bytes.data(), 32);

    input.mutable_transfer()->set_nonce(0);
    input.mutable_transfer()->set_value("0");
    input.mutable_transfer()->set_sender("93ee6143cdc10ce79f15b2a6c2ad38e9b6021c72a1779051f47154fd54cfbd5e");
    input.mutable_transfer()->set_receiver("a967adb3d1574581a6f7ffe0cd6600fb488686704fcff944c88efc7c90b3b13b");
    input.mutable_transfer()->set_gas_price(200000000000000);
    input.mutable_transfer()->set_gas_limit(500000000);
    input.mutable_transfer()->set_data("foo");
    auto output = Signer::sign(input);
    auto signature = output.encoded();

    ASSERT_EQ("d0cc3a4d97aa80f37195e91f041163a2f6e9963e5db508b18f1103739892e6660fac5b015050b3ba1ba1bfb43c17f2a432c10386274e665c3d668a3c21723f04", signature);
}
