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

const int TX_VERSION = 1;

TransactionFactory::TransactionFactory() : 
    TransactionFactory(NetworkConfig::GetDefault()) {
}

TransactionFactory::TransactionFactory(const NetworkConfig& networkConfig) : 
    networkConfig(networkConfig),
    gasEstimator(networkConfig) {
}

Proto::TransactionMessage TransactionFactory::createEGLDTransfer(const Proto::EGLDTransfer& transfer) {
    Proto::TransactionMessage message;

    uint32_t gasLimit = this->gasEstimator.forEGLDTransfer(0);

    message.set_nonce(transfer.nonce());
    message.set_sender(transfer.sender());
    message.set_sender_username(transfer.sender_username());
    message.set_receiver(transfer.receiver());
    message.set_receiver_username(transfer.receiver_username());
    message.set_value(transfer.amount());
    message.set_gas_limit(gasLimit);
    message.set_gas_price(coalesceGasPrice(transfer.gas_price()));
    message.set_chain_id(coalesceChainId(transfer.chain_id()));
    message.set_version(TX_VERSION);

    return message;
}

Proto::TransactionMessage TransactionFactory::createESDTTransfer(const Proto::ESDTTransfer& transfer) {
    Proto::TransactionMessage message;

    std::string encodedTokenIdentifier = Codec::encodeStringTopLevel(transfer.token_identifier());
    std::string encodedAmount = Codec::encodeBigIntTopLevel(transfer.amount());
    std::string data = prepareFunctionCall("ESDTTransfer", { encodedTokenIdentifier, encodedAmount });
    long gasLimit = this->gasEstimator.forESDTTransfer(uint32_t(data.size()));

    message.set_nonce(transfer.nonce());
    message.set_sender(transfer.sender());
    message.set_sender_username(transfer.sender_username());
    message.set_receiver(transfer.receiver());
    message.set_receiver_username(transfer.receiver_username());
    message.set_value("0");
    message.set_data(data);
    message.set_gas_limit(gasLimit);
    message.set_gas_price(coalesceGasPrice(transfer.gas_price()));
    message.set_chain_id(coalesceChainId(transfer.chain_id()));
    message.set_version(TX_VERSION);

    return message;
}

Proto::TransactionMessage TransactionFactory::createESDTNFTTransfer(const Proto::ESDTNFTTransfer& transfer) {
    Proto::TransactionMessage message;

    std::string encodedCollection = Codec::encodeStringTopLevel(transfer.token_collection());
    std::string encodedNonce = Codec::encodeUint64TopLevel(transfer.token_nonce());
    std::string encodedQuantity = Codec::encodeBigIntTopLevel(transfer.amount());
    std::string encodedReceiver = Codec::encodeAddressTopLevel(transfer.receiver());
    std::string data = prepareFunctionCall("ESDTNFTTransfer", { encodedCollection, encodedNonce, encodedQuantity, encodedReceiver });
    long gasLimit = this->gasEstimator.forESDTNFTTransfer(data.size());
    
    // For NFT, SFT and MetaESDT, transaction.sender == transaction.receiver.
    message.set_sender(transfer.sender());
    message.set_receiver(transfer.sender());
    message.set_value("0");

    message.set_data(data);
    message.set_gas_limit(gasLimit);
    message.set_gas_price(coalesceGasPrice(transfer.gas_price()));
    message.set_chain_id(coalesceChainId(transfer.chain_id()));
    message.set_version(TX_VERSION);

    return message;
}

uint64_t TransactionFactory::coalesceGasPrice(uint64_t gasPrice) {
    return gasPrice > 0 ? gasPrice : this->networkConfig.getMinGasPrice();
}

std::string TransactionFactory::coalesceChainId(std::string chainID) {
    return chainID.empty() ? this->networkConfig.getChainId() : chainID;
}

std::string TransactionFactory::prepareFunctionCall(const std::string& function, std::initializer_list<const std::string> arguments) {
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
