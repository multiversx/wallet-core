// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "Elrond/Address.h"
#include "PublicKey.h"
#include "PrivateKey.h"
#include <gtest/gtest.h>
#include <vector>

using namespace TW;
using namespace TW::Elrond;

TEST(ElrondAddress, Valid) {
    ASSERT_TRUE(Address::isValid("erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_TRUE(Address::isValid("erd1wcfp4v3c7k5qzurue2xq2n60dq362kj56ccu9qz4pgd95vm09gaqsmh2h9"));
}

TEST(ElrondAddress, Invalid) {
    ASSERT_FALSE(Address::isValid(""));
    ASSERT_FALSE(Address::isValid("foo"));
    ASSERT_FALSE(Address::isValid("10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
}

TEST(ElrondAddress, FromString) {
    Address alice;
    ASSERT_TRUE(Address::decode("erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr", alice));
    ASSERT_EQ("788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118", hex(alice.getKeyHash()));
}

TEST(ElrondAddress, FromData) {
    const auto alice = Address(parse_hex("0x788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118"));
    ASSERT_EQ(alice.string(), "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr");
}

TEST(ElrondAddress, FromPrivateKey) {
    auto privateKey = PrivateKey(parse_hex("0x6d893bc800f790261f814be252ee9bf51d6efc70e8c46dedc3f9357d06487b04"));
    auto address = Address(privateKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(address.string(), "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr");
}

TEST(ElrondAddress, FromPublicKey) {
    auto publicKey = PublicKey(parse_hex("0x788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118"), TWPublicKeyTypeED25519);
    auto address = Address(publicKey);
    ASSERT_EQ(address.string(), "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr");
}
