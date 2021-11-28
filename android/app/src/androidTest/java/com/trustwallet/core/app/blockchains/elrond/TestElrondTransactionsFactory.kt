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
import wallet.core.java.Marshalizer
import wallet.core.jni.CoinType
import wallet.core.jni.PrivateKey
import wallet.core.jni.proto.Elrond
import wallet.core.jni.ElrondNetworkConfig
import wallet.core.jni.ElrondTransactionFactory

class TestElrondTransactionsFactory {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    val aliceBech32 = "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz"
    val bobBech32 = "erd1cux02zersde0l7hhklzhywcxk4u9n4py5tdxyx7vrvhnza2r4gmq4vw35r"

    @Test
    fun createEGLDransfer() {
        val networkConfig = ElrondNetworkConfig()
        val factory = ElrondTransactionFactory(networkConfig)

        val transaction = Marshalizer.unmarshalProto(factory.createEGLDTransfer(
            aliceBech32,
            bobBech32,
            "1000000000000000000"
        ), Elrond.TransactionMessage.parser())

        assertEquals(aliceBech32, transaction.sender)
        assertEquals(bobBech32, transaction.receiver)
        assertEquals("", transaction.data)
        assertEquals("1000000000000000000", transaction.value)
        assertEquals(1000000000, transaction.gasPrice)
        assertEquals(50000, transaction.gasLimit)
        assertEquals(1, transaction.version)
    }

    @Test
    fun createESDTTransfer() {
        val networkConfig = ElrondNetworkConfig()
        val factory = ElrondTransactionFactory(networkConfig)
        
        val transaction = Marshalizer.unmarshalProto(factory.createESDTTransfer(
            aliceBech32,
            bobBech32,
            "MYTOKEN-1234",
            "10000000000000"
        ), Elrond.TransactionMessage.parser())

        assertEquals(aliceBech32, transaction.sender)
        assertEquals(bobBech32, transaction.receiver)
        assertEquals("ESDTTransfer@4d59544f4b454e2d31323334@09184e72a000", transaction.data)
        assertEquals("", transaction.value)
        assertEquals(1000000000, transaction.gasPrice)
        assertEquals(1, transaction.version)
    }
}
