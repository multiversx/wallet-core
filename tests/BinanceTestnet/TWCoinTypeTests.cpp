// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//
// This is a GENERATED FILE, changes made here MAY BE LOST.
// Generated one-time (codegen/bin/cointests)
//

#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <gtest/gtest.h>


TEST(TWBinanceTestnetCoinType, TWCoinType) {
    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeBinanceTestnet));
    auto txId = TWStringCreateWithUTF8Bytes("D56ADEF5B70597A4B9281B10C76D7B8D4EB5F59B8C520EE9266A2688203FB3A4");
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeBinanceTestnet, txId));
    auto accId = TWStringCreateWithUTF8Bytes("tbnb16a8qfhr5frpe2as3panjune840vwpj45mjudux");
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeBinanceTestnet, accId));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeBinanceTestnet));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeBinanceTestnet));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeBinanceTestnet), 8);
    ASSERT_EQ(TWBlockchainBinanceTestnet, TWCoinTypeBlockchain(TWCoinTypeBinanceTestnet));
    ASSERT_EQ(0x0, TWCoinTypeP2shPrefix(TWCoinTypeBinanceTestnet));
    ASSERT_EQ(0x0, TWCoinTypeStaticPrefix(TWCoinTypeBinanceTestnet));
    assertStringsEqual(symbol, "TBNB");
    assertStringsEqual(txUrl, "https://testnet-explorer.binance.org/tx/D56ADEF5B70597A4B9281B10C76D7B8D4EB5F59B8C520EE9266A2688203FB3A4");
    assertStringsEqual(accUrl, "https://testnet-explorer.binance.org/address/tbnb16a8qfhr5frpe2as3panjune840vwpj45mjudux");
    assertStringsEqual(id, "binancetestnet");
    assertStringsEqual(name, "TBNB");
}
