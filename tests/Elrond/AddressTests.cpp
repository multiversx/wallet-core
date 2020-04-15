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
    ASSERT_TRUE(Address::isValid("erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz"));
    ASSERT_TRUE(Address::isValid("erd19nu5t7hszckwah5nlcadmk5rlchtugzplznskffpwecygcu0520s9tnyy0"));
}

TEST(ElrondAddress, Invalid) {
    ASSERT_FALSE(Address::isValid(""));
    ASSERT_FALSE(Address::isValid("foo"));
    ASSERT_FALSE(Address::isValid("10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_FALSE(Address::isValid("nerd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_FALSE(Address::isValid("foo10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_FALSE(Address::isValid("788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118"));
}

TEST(ElrondAddress, FromString) {
    Address alice, bob, carol;
    ASSERT_TRUE(Address::decode("erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr", alice));
    ASSERT_TRUE(Address::decode("erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz", bob));
    ASSERT_TRUE(Address::decode("erd19nu5t7hszckwah5nlcadmk5rlchtugzplznskffpwecygcu0520s9tnyy0", carol));
    
    ASSERT_EQ("788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118", hex(alice.getKeyHash()));
    ASSERT_EQ("fd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293", hex(bob.getKeyHash()));
    ASSERT_EQ("2cf945faf0162ceede93fe3addda83fe2ebe2041f8a70b2521767044638fa29f", hex(carol.getKeyHash()));
}

TEST(ElrondAddress, FromData) {
    const auto alice = Address(parse_hex("788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118"));
    const auto bob = Address(parse_hex("fd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293"));
    const auto carol = Address(parse_hex("2cf945faf0162ceede93fe3addda83fe2ebe2041f8a70b2521767044638fa29f"));
    
    ASSERT_EQ(alice.string(), "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr");
    ASSERT_EQ(bob.string(), "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz");
    ASSERT_EQ(carol.string(), "erd19nu5t7hszckwah5nlcadmk5rlchtugzplznskffpwecygcu0520s9tnyy0");
}

TEST(ElrondAddress, FromPrivateKey) {
    auto privateKey = PrivateKey(parse_hex("0x6d893bc800f790261f814be252ee9bf51d6efc70e8c46dedc3f9357d06487b04"));
    auto address = Address(privateKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(address.string(), "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr");
    // TODO-Elrond: add more tests
}

TEST(ElrondAddress, FromPublicKey) {
    auto publicKey = PublicKey(parse_hex("788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118"), TWPublicKeyTypeED25519);
    auto address = Address(publicKey);
    ASSERT_EQ(address.string(), "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr");
    // TODO-Elrond: add more tests
}
