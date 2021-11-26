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

TW_EXTERN_C_BEGIN

TW_EXPORT_CLASS
struct TWElrondTransactionFactory;

TW_EXPORT_STATIC_METHOD
struct TWElrondTransactionFactory *_Nonnull TWElrondTransactionFactoryCreate();

TW_EXPORT_METHOD
TWData *_Nonnull TWElrondTransactionFactoryCreateEGLDransfer(struct TWElrondTransactionFactory *_Nonnull thisFactory);

TW_EXPORT_METHOD
TWData *_Nonnull TWElrondTransactionFactoryCreateESDTTransfer(struct TWElrondTransactionFactory *_Nonnull thisFactory, TWString *_Nonnull sender, TWString *_Nonnull receiver, TWString *_Nonnull tokenIdentifier, TWString *_Nonnull amount);

TW_EXTERN_C_END
