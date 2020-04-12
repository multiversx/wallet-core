// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Signer.h"
#include "Address.h"
#include "Serialization.h"
#include "../PublicKey.h"
#include "HexCoding.h"

using namespace TW;
using namespace TW::Elrond;


Proto::SigningOutput Signer::sign(const Proto::SigningInput &input) noexcept {
    auto privateKey = PrivateKey(input.private_key());
    string payload = Elrond::serializeMessageToSignableString(input.transfer());
    Data payloadAsData = TW::data(payload);
    auto signature = privateKey.sign(payloadAsData, TWCurveED25519);
    string encodedSignature = hex(signature);

    auto protoOutput = Proto::SigningOutput();
    protoOutput.set_encoded(encodedSignature);
    return protoOutput;
}
