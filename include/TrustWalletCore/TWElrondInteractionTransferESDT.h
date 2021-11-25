// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "TWBase.h"
#include "TWString.h"
#include "TWData.h"
#include "TWAnyAddress.h"
#include "TWElrondProto.h"

TW_EXTERN_C_BEGIN

TW_EXPORT_CLASS
struct TWElrondInteractionTransferESDT;

TW_EXPORT_STATIC_METHOD
struct TWElrondInteractionTransferESDT *_Nonnull TWElrondInteractionTransferESDTCreate();

TW_EXPORT_METHOD
void TWElrondInteractionTransferESDTSetSender(struct TWElrondInteractionTransferESDT *_Nonnull self, TWData *_Nonnull sender);

TW_EXPORT_METHOD
void TWElrondInteractionTransferESDTSetReceiver(struct TWElrondInteractionTransferESDT *_Nonnull self, TWData *_Nonnull receiver);

TW_EXPORT_METHOD
void TWElrondInteractionTransferESDTSetTransfer(struct TWElrondInteractionTransferESDT *_Nonnull self, TWString *_Nonnull tokenIdentifier, TWString *_Nonnull amount);

// TW_EXPORT_METHOD
// TW_Elrond_Proto_TransactionMessage *_Nonnull TWElrondInteractionTransferESDTBuildTransaction(struct TWElrondInteractionTransferESDT *_Nonnull self);

TW_EXTERN_C_END
