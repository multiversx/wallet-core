// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Codec.h"

#include "HexCoding.h"

using namespace TW;
using namespace TW::Elrond;

std::string Codec::encodeStringTopLevel(std::string value) {
    std::string encodedValue = hex(TW::data(value));
    return encodedValue;
}

// For reference, see https://docs.elrond.com/developers/developer-reference/elrond-serialization-format/#arbitrary-width-big-numbers.
std::string Codec::encodeBigIntTopLevel(uint256_t value) {
    // First, load the 256-bit value into a "Data" object.
    auto valueAsData = Data();
    encode256BE(valueAsData, value, 256);

    // Strip the redundant leading zeros (if any).
    std::string encodedValue = hex(valueAsData);
    encodedValue.erase(0, encodedValue.find_first_not_of('0'));

    // Make sure the result has even length (valid hex).
    if (encodedValue.size() % 2 != 0) {
        encodedValue.insert(0, 1, '0');
    }

    return encodedValue;
}
