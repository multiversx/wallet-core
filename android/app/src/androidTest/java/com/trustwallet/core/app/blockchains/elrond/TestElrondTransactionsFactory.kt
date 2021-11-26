// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

package com.trustwallet.core.app.blockchains.elrond

import com.google.protobuf.ByteString
import com.trustwallet.core.app.utils.toHexByteArray
import org.junit.Assert.assertEquals
import org.junit.Test
import wallet.core.java.AnySigner
import wallet.core.jni.CoinType
import wallet.core.jni.PrivateKey
import wallet.core.jni.proto.Elrond

class TestElrondTransactionsFactory {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    @Test
    fun createESDTTransfer() {
        val factory = new Elrond.TransactionFactory()
        val transaction = Marshalizer.unmarshal(factory.createESDTTransfer(
            "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz",
            "erd1cux02zersde0l7hhklzhywcxk4u9n4py5tdxyx7vrvhnza2r4gmq4vw35r",
            "MYTOKEN-1234",
            "10000000000000"
        ))

        assertEquals("ESDTTransfer@4d59544f4b454e2d31323334@09184e72a000", transaction.data)
    }
}
