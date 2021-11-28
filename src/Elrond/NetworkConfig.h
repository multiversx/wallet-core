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
    int gasPerDataByte;
    int minGasLimit;
    long minGasPrice;

    /// GasSchedule entries of interest (only one at this moment), according to: https://github.com/ElrondNetwork/elrond-config-testnet/blob/master/gasSchedules.
    /// Here, for the sake of simplicity, we define the gas costs of interest directly in the class "NetworkConfig" 
    /// (that is, without defining extra nested structures such as "GasSchedule" and "BuiltInCosts").
    long gasCostESDTTransfer;
    long gasCostESDTNFTTransfer;
    long gasCostDataCopyPerByte;
public:
    NetworkConfig();
    void setChainId(const std::string& value);
    void setGasPerDataByte(int value);
    void setMinGasLimit(int value);
    void setMinGasPrice(long value);
    void setGasCostESDTTransfer(long value);
    void setGasCostESDTNFTTransfer(long value);
    void setGasCostDataCopyPerByte(long value);

    const std::string& getChainId();
    int getGasPerDataByte();
    int getMinGasLimit();
    long getMinGasPrice();
    long getGasCostESDTTransfer();
    long getGasCostESDTNFTTransfer();
    long getGasCostDataCopyPerByte();
};

} // namespace

/// Wrapper for C interface.
struct TWElrondNetworkConfig {
    TW::Elrond::NetworkConfig impl;
};
