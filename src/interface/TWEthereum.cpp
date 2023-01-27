// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Data.h"
#include "Ethereum/EIP1014.h"
#include "Ethereum/EIP4337.h"
#include "Ethereum/EIP2645.h"
#include <TrustWalletCore/TWEthereum.h>

#include <string>

TWString* TWEthereumEip1014AddressCreate2(TWString* _Nonnull fromEthAddress, TWData* _Nonnull salt, TWData* _Nonnull initCodeHash) {
    const auto& ethAddressStr = *reinterpret_cast<const std::string*>(fromEthAddress);
    const auto& saltData = *reinterpret_cast<const TW::Data*>(salt);
    const auto& initCodeHashData = *reinterpret_cast<const TW::Data*>(initCodeHash);
    return new std::string(TW::Ethereum::create2AddressString(ethAddressStr, saltData, initCodeHashData));
}

TWString* TWEthereumEip2645GetPath(TWString* ethAddress, TWString* layer, TWString* application, TWString* index) {
    const auto& ethAddressStr = *reinterpret_cast<const std::string*>(ethAddress);
    const auto& layerStr = *reinterpret_cast<const std::string*>(layer);
    const auto& applicationStr = *reinterpret_cast<const std::string*>(application);
    const auto& indexStr = *reinterpret_cast<const std::string*>(index);
    return new std::string(TW::Ethereum::accountPathFromAddress(ethAddressStr, layerStr, applicationStr, indexStr));
}

TWString* TWEthereumEip4337GetDeploymentAddress(TWString* _Nonnull factoryAddress, TWString* _Nonnull logicAddress, TWString* _Nonnull ownerAddress) {
    const auto& factoryAddressStr = *reinterpret_cast<const std::string*>(factoryAddress);
    const auto& logicAddressStr = *reinterpret_cast<const std::string*>(logicAddress);
    const auto& ownerAddressStr = *reinterpret_cast<const std::string*>(ownerAddress);
    return new std::string(TW::Ethereum::getEIP4337DeploymentAddress(factoryAddressStr, logicAddressStr, ownerAddressStr));
}