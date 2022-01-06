// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../proto/Elrond.pb.h"
#include "Address.h"
#include "NetworkConfig.h"
#include "GasEstimator.h"
#include "Transactions.h"
#include "uint256.h"

namespace TW::Elrond {

class Transaction {
public:
    uint64_t nonce;
    std::string value;
    std::string receiver;
    std::string sender;
    std::string senderUsername;
    std::string receiverUsername;
    uint16_t gasPrice;
    uint64_t gasLimit;
    std::string data;
    std::string chainID;
    uint32_t version;
    uint32_t options;
    Transaction();
    // TODO: Perhaps make it protected, and define createTransaction() as a friend.
    virtual void populate(const Proto::SigningInput& signingInput, const NetworkConfig& networkConfig);
private:
    std::string prepareFunctionCall(const std::string& function, std::initializer_list<const std::string> arguments);
};

class GenericActionTransaction : public Transaction {
};

/// This should be used to transfer EGLD.
/// For reference, see: https://docs.elrond.com/developers/signing-transactions/signing-transactions/#general-structure.
class EGLDTransferTransaction : public Transaction {
};

/// This should be used to transfer regular ESDTs (fungible tokens).
/// For reference, see: https://docs.elrond.com/developers/esdt-tokens/#transfers
///
/// The "regular" ESDT tokens held by an account can be fetched from https://api.elrond.com/accounts/{address}/tokens.
class ESDTTransferTransaction : public Transaction {
};

/// This should be used to transfer NFTs, SFTs and Meta ESDTs.
/// For reference, see: https://docs.elrond.com/developers/nft-tokens/#transfers
///
/// The semi-fungible and non-fungible tokens held by an account can be fetched from https://api.elrond.com/accounts/{address}/nfts?type=SemiFungibleESDT,NonFungibleESDT.
/// The Meta ESDTs (a special kind of SFTs) held by an account can be fetched from https://api.elrond.com/accounts/{address}/nfts?type=MetaESDT.
///
/// The fields "transfer.token_collection" and "transfer.token_nonce" are found as well in the HTTP response of the API call (as "collection" and "nonce", respectively).
class ESDTNFTTransferTransaction : public Transaction {
};

/// Creates the appropriate transaction object, with respect to the "oneof" field (substructure) of Proto::SigningInput.
Transaction createTransaction(const Proto::SigningInput& signingInput);
Transaction createTransaction(const Proto::SigningInput& signingInput, const NetworkConfig& networkConfig);

} // namespace
