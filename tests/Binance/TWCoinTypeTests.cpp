// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//
// This is a GENERATED FILE, changes made here MAY BE LOST.
// Generated one-time (codegen/bin/cointests)
//

#include "Scope.h"
#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <gtest/gtest.h>


TEST(TWBinanceCoinType, TWCoinType) {
    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeBinance));
    auto txId = WRAPS(TWStringCreateWithUTF8Bytes("A93625C9F9ABEA1A8E31585B30BBB16C34FAE0D172EB5B6B2F834AF077BF06BB"));
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeBinance, txId.get()));
    auto accId = WRAPS(TWStringCreateWithUTF8Bytes("bnb1u7jm0cll5h3224y0tapwn6gf6pr49ytewx4gsz"));
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeBinance, accId.get()));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeBinance));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeBinance));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeBinance), 8);
    ASSERT_EQ(TWBlockchainBinance, TWCoinTypeBlockchain(TWCoinTypeBinance));
    ASSERT_EQ(0x0, TWCoinTypeP2shPrefix(TWCoinTypeBinance));
    ASSERT_EQ(0x0, TWCoinTypeStaticPrefix(TWCoinTypeBinance));
    assertStringsEqual(symbol, "BNB");
    assertStringsEqual(txUrl, "https://explorer.binance.org/tx/A93625C9F9ABEA1A8E31585B30BBB16C34FAE0D172EB5B6B2F834AF077BF06BB");
    assertStringsEqual(accUrl, "https://explorer.binance.org/address/bnb1u7jm0cll5h3224y0tapwn6gf6pr49ytewx4gsz");
    assertStringsEqual(id, "binance");
    assertStringsEqual(name, "BNB");
}

TEST(TWBinanceCoinTypeTestnet, TWCoinType) {
    TW::Scope::SetTestnet();

    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeBinance));
    auto txId = TWStringCreateWithUTF8Bytes("D56ADEF5B70597A4B9281B10C76D7B8D4EB5F59B8C520EE9266A2688203FB3A4");
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeBinance, txId));
    auto accId = TWStringCreateWithUTF8Bytes("tbnb16a8qfhr5frpe2as3panjune840vwpj45mjudux");
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeBinance, accId));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeBinance));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeBinance));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeBinance), 8);
    ASSERT_EQ(TWBlockchainBinance, TWCoinTypeBlockchain(TWCoinTypeBinance));
    ASSERT_EQ(0x0, TWCoinTypeP2shPrefix(TWCoinTypeBinance));
    ASSERT_EQ(0x0, TWCoinTypeStaticPrefix(TWCoinTypeBinance));
    assertStringsEqual(symbol, "BNB");
    assertStringsEqual(id, "binance");
    assertStringsEqual(name, "BNB");

    TW::Scope::SetMainnet();
}
