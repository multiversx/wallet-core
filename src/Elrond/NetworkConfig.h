// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <string>

namespace TW::Elrond {

/// A "NetworkConfig" object holds the network parameters relevent to creating transactions (e.g. minimum gas limit, minimum gas price).
class NetworkConfig {
    /// The following fields can (should) be fetched from https://api.elrond.com/network/config.
    /// However, a "NetworkConfig" object is initialized with proper default values for Elrond Mainnet (as of December 2021).
    std::string chainId;
    uint gasPerDataByte;
    uint minGasLimit;
    uint64_t minGasPrice;

    /// GasSchedule entries of interest (only one at this moment), according to: https://github.com/ElrondNetwork/elrond-config-testnet/blob/master/gasSchedules.
    /// Here, for the sake of simplicity, we define the gas costs of interest directly in the class "NetworkConfig" 
    /// (that is, without defining extra nested structures such as "GasSchedule" and "BuiltInCosts").
    uint gasCostESDTTransfer;
    uint gasCostESDTNFTTransfer;
public:
    NetworkConfig();
    void setChainId(const std::string& value);
    void setGasPerDataByte(uint value);
    void setMinGasLimit(uint value);
    void setMinGasPrice(uint64_t value);
    void setGasCostESDTTransfer(uint value);
    void setGasCostESDTNFTTransfer(uint value);

    const std::string& getChainId();
    uint getGasPerDataByte();
    uint getMinGasLimit();
    uint64_t getMinGasPrice();
    uint getGasCostESDTTransfer();
    uint getGasCostESDTNFTTransfer();
};

} // namespace

/// Wrapper for C interface.
struct TWElrondNetworkConfig {
    TW::Elrond::NetworkConfig impl;
};
