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
    gasCostESDTNFTTransfer(200000),
    gasCostDataCopyPerByte(100) {
}

void NetworkConfig::setChainId(const std::string& value) {
    this->chainId = value;
}

void NetworkConfig::setGasPerDataByte(int value) {
    this->gasPerDataByte = value;
}
    
void NetworkConfig::setMinGasLimit(int value) {
    this->minGasLimit = value;
}

void NetworkConfig::setMinGasPrice(long value) {
    this->minGasPrice = value;
}

void NetworkConfig::setGasCostESDTTransfer(long value) {
    this->gasCostESDTTransfer = value;
}

void NetworkConfig::setGasCostESDTNFTTransfer(long value) {
    this->gasCostESDTNFTTransfer = value;
}

void NetworkConfig::setGasCostDataCopyPerByte(long value) {
    this->gasCostDataCopyPerByte = value;
}

const std::string& NetworkConfig::getChainId() {
    return this->chainId;
}

int NetworkConfig::getGasPerDataByte() {
    return this->gasPerDataByte;
}

int NetworkConfig::getMinGasLimit() {
    return this->minGasLimit;
}

long NetworkConfig::getMinGasPrice() {
    return this->minGasPrice;
}

long NetworkConfig::getGasCostESDTTransfer() {
    return this->gasCostESDTTransfer;
}

long NetworkConfig::getGasCostESDTNFTTransfer() {
    return this->gasCostESDTNFTTransfer;
}

long NetworkConfig::getGasCostDataCopyPerByte() {
    return this->gasCostDataCopyPerByte;
}
