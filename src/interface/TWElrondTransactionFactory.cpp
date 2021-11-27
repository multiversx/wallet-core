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

TWData *_Nonnull marshalProto(const Elrond::Proto::TransactionMessage& transaction);

struct TWElrondTransactionFactory *_Nonnull TWElrondTransactionFactoryCreate() {
    auto factory = TransactionFactory();
    return new TWElrondTransactionFactory{ factory };
}

void TWElrondTransactionFactoryDelete(struct TWElrondTransactionFactory *_Nonnull self) {
    assert(self != nullptr);
    delete self;
}

TWData *_Nonnull TWElrondTransactionFactoryCreateEGLDTransfer(
    struct TWElrondTransactionFactory *_Nonnull self,
    TWString *_Nonnull sender,
    TWString *_Nonnull receiver,
    TWString *_Nonnull amount
) {
    auto factory = self->impl;

    Address senderAddress, receiverAddress;
    Address::decode(TWStringUTF8Bytes(sender), senderAddress);
    Address::decode(TWStringUTF8Bytes(receiver), receiverAddress);

    auto transaction = factory.createEGLDTransfer(
        senderAddress, 
        receiverAddress, 
        uint256_t(TWStringUTF8Bytes(amount))
    );

    return marshalProto(transaction);
}

TWData *_Nonnull TWElrondTransactionFactoryCreateESDTTransfer(
    struct TWElrondTransactionFactory *_Nonnull self,
    TWString *_Nonnull sender,
    TWString *_Nonnull receiver,
    TWString *_Nonnull tokenIdentifier, 
    TWString *_Nonnull amount
) {
    auto factory = self->impl;

    Address senderAddress, receiverAddress;
    Address::decode(TWStringUTF8Bytes(sender), senderAddress);
    Address::decode(TWStringUTF8Bytes(receiver), receiverAddress);
    
    auto transaction = factory.createESDTTransfer(
        senderAddress,
        receiverAddress,
        TWStringUTF8Bytes(tokenIdentifier),
        uint256_t(TWStringUTF8Bytes(amount))
    );
    
    return marshalProto(transaction);
}

template <typename ProtoMessage>
TWData *_Nonnull marshalProto(const ProtoMessage& message) {
    long size = message.ByteSizeLong();
    Data raw(size);
    message.SerializeToArray(raw.data(), (int)size);
    auto result = TWDataCreateWithBytes(raw.data(), size);
    return result;
}
