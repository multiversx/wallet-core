// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "NetworkConfig.h"

using namespace TW;
using namespace TW::Elrond;

// A NetworkConfig object should be synchronized with the current network configuration, as fetched from https://api.elrond.com/network/config.
// Howerver, we initialize the fields with their default Mainnet values (as of November 2021):
NetworkConfig::NetworkConfig() :
    chainId("1"), // Mainnet
    gasPerByte(1500),
    minGasLimit(50000),
    minGasPrice(1000000000) {
}

void NetworkConfig::setChainId(const std::string& value) {
    this->chainId = value;
}

void NetworkConfig::setGasPerByte(int value) {
    this->gasPerByte = value;
}
    
void NetworkConfig::setMinGasLimit(int value) {
    this->minGasLimit = value;
}

void NetworkConfig::setMinGasPrice(long value) {
    this->minGasPrice = value;
}

const std::string& NetworkConfig::getChainId() {
    return this->chainId;
}

int NetworkConfig::getGasPerByte() {
    return this->gasPerByte;
}

int NetworkConfig::getMinGasLimit() {
    return this->minGasLimit;
}

long NetworkConfig::getMinGasPrice() {
    return this->minGasPrice;
}
