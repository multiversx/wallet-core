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

const auto ALICE_BECH32 = "erd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr";
const auto ALICE_PUBKEY_HEX = "788a66f11d24e8a3da1dcc1aefdd2f7e92ea410a06f7b7de8a4b0d8139198118";
const auto BOB_BECH32 = "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz";
const auto BOB_PUBKEY_HEX = "fd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293";
const auto CAROL_BECH32 = "erd19nu5t7hszckwah5nlcadmk5rlchtugzplznskffpwecygcu0520s9tnyy0";
const auto CAROL_PUBKEY_HEX = "2cf945faf0162ceede93fe3addda83fe2ebe2041f8a70b2521767044638fa29f";

TEST(ElrondAddress, Valid) {
    ASSERT_TRUE(Address::isValid(ALICE_BECH32));
    ASSERT_TRUE(Address::isValid(BOB_BECH32));
    ASSERT_TRUE(Address::isValid(CAROL_BECH32));
}

TEST(ElrondAddress, Invalid) {
    ASSERT_FALSE(Address::isValid(""));
    ASSERT_FALSE(Address::isValid("foo"));
    ASSERT_FALSE(Address::isValid("10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_FALSE(Address::isValid("nerd10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_FALSE(Address::isValid("foo10z9xdugayn528ksaesdwlhf006fw5sg2qmmm0h52fvxczwgesyvq5pwemr"));
    ASSERT_FALSE(Address::isValid(ALICE_PUBKEY_HEX));
}

TEST(ElrondAddress, FromString) {
    Address alice, bob, carol;
    ASSERT_TRUE(Address::decode(ALICE_BECH32, alice));
    ASSERT_TRUE(Address::decode(BOB_BECH32, bob));
    ASSERT_TRUE(Address::decode(CAROL_BECH32, carol));
    
    ASSERT_EQ(ALICE_PUBKEY_HEX, hex(alice.getKeyHash()));
    ASSERT_EQ(BOB_PUBKEY_HEX, hex(bob.getKeyHash()));
    ASSERT_EQ(CAROL_PUBKEY_HEX, hex(carol.getKeyHash()));
}

TEST(ElrondAddress, FromData) {
    const auto alice = Address(parse_hex(ALICE_PUBKEY_HEX));
    const auto bob = Address(parse_hex(BOB_PUBKEY_HEX));
    const auto carol = Address(parse_hex(CAROL_PUBKEY_HEX));
    
    ASSERT_EQ(ALICE_BECH32, alice.string());
    ASSERT_EQ(BOB_BECH32, bob.string());
    ASSERT_EQ(CAROL_BECH32, carol.string());
}

TEST(ElrondAddress, FromPrivateKey) {
    auto privateKey = PrivateKey(parse_hex(ALICE_PUBKEY_HEX));
    auto address = Address(privateKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(ALICE_BECH32, address.string());
    // TODO-Elrond: add more tests
}

TEST(ElrondAddress, FromPublicKey) {
    auto alice = PublicKey(parse_hex(ALICE_PUBKEY_HEX), TWPublicKeyTypeED25519);
    ASSERT_EQ(ALICE_BECH32, Address(alice).string());

    auto bob = PublicKey(parse_hex(BOB_PUBKEY_HEX), TWPublicKeyTypeED25519);
    ASSERT_EQ(BOB_BECH32, Address(bob).string());

    auto carol = PublicKey(parse_hex(CAROL_PUBKEY_HEX), TWPublicKeyTypeED25519);
    ASSERT_EQ(CAROL_BECH32, Address(carol).string());
}
