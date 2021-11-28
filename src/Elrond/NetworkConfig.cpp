// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "NetworkConfig.h"

using namespace TW;
using namespace TW::Elrond;

NetworkConfig::NetworkConfig() :
    chainId("1"), // Mainnet
    gasPerDataByte(1500),
    minGasLimit(50000),
    minGasPrice(1000000000),
    gasCostESDTTransfer(200000),
    gasCostESDTNFTTransfer(200000) {
}

void NetworkConfig::setChainId(const std::string& value) {
    this->chainId = value;
}

void NetworkConfig::setGasPerDataByte(uint value) {
    this->gasPerDataByte = value;
}
    
void NetworkConfig::setMinGasLimit(uint value) {
    this->minGasLimit = value;
}

void NetworkConfig::setMinGasPrice(uint64_t value) {
    this->minGasPrice = value;
}

void NetworkConfig::setGasCostESDTTransfer(uint value) {
    this->gasCostESDTTransfer = value;
}

void NetworkConfig::setGasCostESDTNFTTransfer(uint value) {
    this->gasCostESDTNFTTransfer = value;
}

const std::string& NetworkConfig::getChainId() {
    return this->chainId;
}

uint NetworkConfig::getGasPerDataByte() {
    return this->gasPerDataByte;
}

uint NetworkConfig::getMinGasLimit() {
    return this->minGasLimit;
}

uint64_t NetworkConfig::getMinGasPrice() {
    return this->minGasPrice;
}

uint NetworkConfig::getGasCostESDTTransfer() {
    return this->gasCostESDTTransfer;
}

uint NetworkConfig::getGasCostESDTNFTTransfer() {
    return this->gasCostESDTNFTTransfer;
}
