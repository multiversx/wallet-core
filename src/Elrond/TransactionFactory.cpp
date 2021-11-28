// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TransactionFactory.h"

#include "Codec.h"
#include "HexCoding.h"
#include "uint256.h"

using namespace TW;
using namespace TW::Elrond;

std::string prepareFunctionCall(const std::string& function, std::initializer_list<const std::string> arguments);

TransactionFactory::TransactionFactory(const NetworkConfig& networkConfig) {
    this->networkConfig = networkConfig;
}

Proto::TransactionMessage TransactionFactory::createEGLDTransfer(const Address& sender, const Address& receiver, uint256_t amount) {
    Proto::TransactionMessage message;

    message.set_sender(sender.string());
    message.set_receiver(receiver.string());
    message.set_value(toString(amount));
    message.set_gas_limit(this->networkConfig.getMinGasLimit());
    message.set_gas_price(this->networkConfig.getMinGasPrice());
    message.set_chain_id(this->networkConfig.getChainId());
    message.set_version(1);

    return message;
}

Proto::TransactionMessage TransactionFactory::createESDTTransfer(const Address& sender, const Address& receiver, const std::string& tokenIdentifier, uint256_t amount) {
    Proto::TransactionMessage message;

    std::string encodedTokenIdentifier = Codec::encodeStringTopLevel(tokenIdentifier);
    std::string encodedAmount = Codec::encodeBigIntTopLevel(amount);
    std::string data = prepareFunctionCall("ESDTTransfer", { encodedTokenIdentifier, encodedAmount });

    // Additional gas to account for eventual increases in gas requirements (thus avoid breaking changes in clients of TW-core).
    const long ADDITIONAL_GAS = 100000;

    long gasLimit = 
        this->networkConfig.getMinGasLimit() + 
        this->networkConfig.getGasCostESDTTransfer() + 
        this->networkConfig.getGasPerDataByte() * data.size() +
        ADDITIONAL_GAS;

    message.set_sender(sender.string());
    message.set_receiver(receiver.string());
    message.set_data(data);
    message.set_gas_limit(gasLimit);
    message.set_gas_price(this->networkConfig.getMinGasPrice());
    message.set_chain_id(this->networkConfig.getChainId());
    message.set_version(1);

    return message;
}

Proto::TransactionMessage TransactionFactory::createESDTNFTTransfer(const Address& sender, const Address& receiver, const std::string& collection, ulong nonce, uint256_t quantity) {
    Proto::TransactionMessage message;

    std::string encodedCollection = Codec::encodeStringTopLevel(collection);
    std::string encodedNonce = Codec::encodeUint64TopLevel(nonce);
    std::string encodedQuantity = Codec::encodeBigIntTopLevel(quantity);
    std::string encodedReceiver = Codec::encodeAddressTopLevel(receiver);
    std::string data = prepareFunctionCall("ESDTNFTTransfer", { encodedCollection, encodedNonce, encodedQuantity, encodedReceiver });

    // Additional gas to account for extra blockchain operations (e.g. data movement (between accounts) for NFTs), 
    // and for eventual increases in gas requirements (thus avoid breaking changes in clients of TW-core).
    const long ADDITIONAL_GAS = 500000;

    long gasLimit = 
        this->networkConfig.getMinGasLimit() + 
        this->networkConfig.getGasCostESDTNFTTransfer() + 
        this->networkConfig.getGasPerDataByte() * data.size() +
        ADDITIONAL_GAS;

    // For NFT, SFT and MetaESDT, transaction.sender == transaction.receiver.
    message.set_sender(sender.string());
    message.set_receiver(sender.string());

    message.set_data(data);
    message.set_gas_limit(gasLimit);
    message.set_gas_price(this->networkConfig.getMinGasPrice());
    message.set_chain_id(this->networkConfig.getChainId());
    message.set_version(1);

    return message;
}

/// E.g. prepareFunctionCall("callMe", { "aa", "bb", "cc" }) -> "callMe@aa@bb@cc".
std::string prepareFunctionCall(const std::string& function, std::initializer_list<const std::string> arguments) {
    const auto ARGUMENTS_SEPARATOR = "@";
    std::string result;

    result.append(function);

    for(auto argument : arguments)
    {
        result.append(ARGUMENTS_SEPARATOR);
        result.append(argument);
    }

    return result;
}
