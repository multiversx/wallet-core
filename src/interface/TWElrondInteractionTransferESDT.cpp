// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWElrondInteractionTransferESDT.h>

#include "Elrond/Interactions.h"
#include "Elrond/Address.h"
#include "Data.h"

using namespace TW;
using namespace TW::Elrond;

struct TWElrondInteractionTransferESDT *_Nonnull TWElrondInteractionTransferESDTCreate() {
    auto interaction = InteractionTransferESDT();
    return new TWElrondInteractionTransferESDT{ interaction };
}

void TWElrondInteractionTransferESDTSetSender(struct TWElrondInteractionTransferESDT *_Nonnull self, TWData *_Nonnull sender) {
    auto interaction = self->impl;
    auto senderAsData = *static_cast<const Data*>(sender);
    interaction.setSender(Address(senderAsData));
}

TWString *_Nonnull TWElrondInteractionTransferESDTGetSender(struct TWElrondInteractionTransferESDT *_Nonnull self) {
    auto interaction = self->impl;
    return TWStringCreateWithRawBytes(interaction.sender.string())
}

void TWElrondInteractionTransferESDTSetReceiver(struct TWElrondInteractionTransferESDT *_Nonnull self, TWData *_Nonnull receiver) {
    auto interaction = self->impl;
    auto receiverAsData = *static_cast<const Data*>(receiver);
    interaction.setReceiver(Address(receiverAsData));
}

void TWElrondInteractionTransferESDTSetTransfer(struct TWElrondInteractionTransferESDT *_Nonnull self, TWString *_Nonnull tokenIdentifier, TWString *_Nonnull amount) {
    auto interaction = self->impl;
    interaction.setTransfer(TWStringUTF8Bytes(tokenIdentifier), TWStringUTF8Bytes(amount));
}

TWData *_Nonnull TWElrondInteractionTransferESDTBuildTransaction(struct TWElrondInteractionTransferESDT *_Nonnull self) {
    auto interaction = self->impl;
    auto transactionMessage = interaction.buildTransaction();
    
    // Question for review: is this the correct way to return an Elrond::Proto::TransactionMessage to a Swift / kt caller?
    Data transactionMessageRaw(transactionMessage.ByteSizeLong());
    transactionMessage.SerializeToArray(transactionMessageRaw.data(), (int)transactionMessageRaw.size());
    auto result = TWDataCreateWithBytes(transactionMessageRaw.data(), transactionMessageRaw.size());
    return result;
}
