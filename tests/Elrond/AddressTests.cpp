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

const auto ALICE_BECH32 = "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz";
const auto ALICE_SEED_HEX = "1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf";
const auto ALICE_PUBKEY_HEX = "fd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293";
const auto BOB_BECH32 = "erd1cux02zersde0l7hhklzhywcxk4u9n4py5tdxyx7vrvhnza2r4gmq4vw35r";
const auto BOB_SEED_HEX = "e3a3a3d1ac40d42d8fd4c569a9749b65a1250dd3d10b6f4e438297662ea4850e";
const auto BOB_PUBKEY_HEX = "c70cf50b238372fffaf7b7c5723b06b57859d424a2da621bcc1b2f317543aa36";
const auto CAROL_BECH32 = "erd19nu5t7hszckwah5nlcadmk5rlchtugzplznskffpwecygcu0520s9tnyy0";
const auto CAROL_SEED_HEX = "a926316cc3daf8ff25ba3e417797e6dfd51f62ae735ab07148234732f7314052";
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
    auto aliceKey = PrivateKey(parse_hex(ALICE_SEED_HEX));
    auto alice = Address(aliceKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(ALICE_BECH32, alice.string());

    auto bobKey = PrivateKey(parse_hex(BOB_SEED_HEX));
    auto bob = Address(bobKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(BOB_BECH32, bob.string());

    auto carolKey = PrivateKey(parse_hex(CAROL_SEED_HEX));
    auto carol = Address(carolKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(CAROL_BECH32, carol.string());
}

TEST(ElrondAddress, FromPublicKey) {
    auto alice = PublicKey(parse_hex(ALICE_PUBKEY_HEX), TWPublicKeyTypeED25519);
    ASSERT_EQ(ALICE_BECH32, Address(alice).string());

    auto bob = PublicKey(parse_hex(BOB_PUBKEY_HEX), TWPublicKeyTypeED25519);
    ASSERT_EQ(BOB_BECH32, Address(bob).string());

    auto carol = PublicKey(parse_hex(CAROL_PUBKEY_HEX), TWPublicKeyTypeED25519);
    ASSERT_EQ(CAROL_BECH32, Address(carol).string());
}
