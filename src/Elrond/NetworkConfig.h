// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <string>

namespace TW::Elrond {

/// A "NetworkConfig" object holds the network parameters relevant to creating transactions (e.g. minimum gas limit, minimum gas price).
class NetworkConfig {
    /// The following fields can (should) be fetched from https://api.elrond.com/network/config.
    /// However, a "NetworkConfig" object is initialized with proper default values for Elrond Mainnet (as of December 2021).
    std::string chainId;
    uint32_t gasPerDataByte;
    uint32_t minGasLimit;
    uint64_t minGasPrice;

    /// GasSchedule entries of interest (only one at this moment), according to: https://github.com/ElrondNetwork/elrond-config-mainnet/blob/master/gasSchedules.
    /// Here, for the sake of simplicity, we define the gas costs of interest directly in the class "NetworkConfig" 
    /// (that is, without defining extra nested structures such as "GasSchedule" and "BuiltInCosts").
    uint32_t gasCostESDTTransfer;
    uint32_t gasCostESDTNFTTransfer;
public:
    NetworkConfig();

    const std::string& getChainId();
    void setChainId(const std::string& value);
    
    uint32_t getGasPerDataByte();
    void setGasPerDataByte(uint32_t value);
    
    uint32_t getMinGasLimit();
    void setMinGasLimit(uint32_t value);
    
    uint64_t getMinGasPrice();
    void setMinGasPrice(uint64_t value);
    
    uint32_t getGasCostESDTTransfer();
    void setGasCostESDTTransfer(uint32_t value);

    uint32_t getGasCostESDTNFTTransfer();
    void setGasCostESDTNFTTransfer(uint32_t value);
};

} // namespace

/// Wrapper for C interface.
struct TWElrondNetworkConfig {
    TW::Elrond::NetworkConfig impl;
};
