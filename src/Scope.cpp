#include "Scope.h"

bool TW::Scope::_isMainnet = true;

bool TW::Scope::IsMainnet() {
    return TW::Scope::_isMainnet;
}

void TW::Scope::SetMainnet() {
    TW::Scope::_isMainnet = true;
}

void TW::Scope::SetTestnet() {
    TW::Scope::_isMainnet = false;
}
