#pragma once

#include "TWBase.h"

TW_EXTERN_C_BEGIN

TW_EXPORT_CLASS
struct TWScope;

TW_EXPORT_STATIC_METHOD
void TWScopeSetTestnet(struct TWScope *_Nonnull lhs);

TW_EXPORT_STATIC_METHOD
void TWScopeSetMainnet(struct TWScope *_Nonnull lhs);

TW_EXTERN_C_END
