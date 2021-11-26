// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWElrondTransactionFactory.h>

#include "Elrond/TransactionFactory.h"
#include "Data.h"

using namespace TW;
using namespace TW::Elrond;

TWData *_Nonnull marshalTransaction(const Elrond::Proto::TransactionMessage& transaction);

struct TWElrondTransactionFactory *_Nonnull TWElrondTransactionFactoryCreate() {
    auto factory = TWElrondTransactionFactory();
    return new TWElrondTransactionFactory{ factory };
}

void TWEthereumAbiFunctionDelete(struct TWElrondTransactionFactory *_Nonnull thisFactory) {
    assert(thisFactory != nullptr);
    delete thisFactory;
}

TWData *_Nonnull TWElrondTransactionFactoryCreateEGLDTransfer(
    struct TWElrondTransactionFactory *_Nonnull thisFactory
) {
    auto factory = thisFactory->impl;
    auto transaction = factory.createEGLDTransfer();

    return marshalTransaction(transaction);
}

TWData *_Nonnull TWElrondTransactionFactoryCreateESDTTransfer(
    struct TWElrondTransactionFactory *_Nonnull thisFactory,
    TWString *_Nonnull sender,
    TWString *_Nonnull receiver,
    TWString *_Nonnull tokenIdentifier, 
    TWString *_Nonnull amount
) {
    auto factory = thisFactory->impl;
    Address senderAddress, receiverAddress;
    Address::decode(TWStringUTF8Bytes(sender), senderAddress);
    Address::decode(TWStringUTF8Bytes(receiver), receiverAddress);
    
    auto transaction = factory.createESDTTransfer(
        senderAddress,
        receiverAddress,
        TWStringUTF8Bytes(tokenIdentifier),
        uint256_t(TWStringUTF8Bytes(amount))
    );
    
    return marshalTransaction(transaction);
}

TWData *_Nonnull marshalTransaction(const Elrond::Proto::TransactionMessage& transaction) {
    long size = transaction.ByteSizeLong();
    Data raw(size);
    transaction.SerializeToArray(raw.data(), size);
    auto result = TWDataCreateWithBytes(raw.data(), size);
    return result;
}
