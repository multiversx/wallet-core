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

class TestElrondSigner {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    val accountABech32 = "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz"
    var accountASeedHex = "1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf"
    var accountAPubKeyHex = "fd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293"

    val accountBBech32 = "erd1cux02zersde0l7hhklzhywcxk4u9n4py5tdxyx7vrvhnza2r4gmq4vw35r"
    var accountBSeedHex = "e3a3a3d1ac40d42d8fd4c569a9749b65a1250dd3d10b6f4e438297662ea4850e"
    var accountBPubKeyHex = "c70cf50b238372fffaf7b7c5723b06b57859d424a2da621bcc1b2f317543aa36"

    @Test
    fun signGenericTransaction() {
        val transaction = Elrond.TransactionMessage.newBuilder()
            .setNonce(0)
            .setValue("0")
            .setSender(accountABech32)
            .setReceiver(accountBBech32)
            .setGasPrice(1000000000)
            .setGasLimit(50000)
            .setData("foo")
            .setChainId("1")
            .setVersion(1)
            .build()
        
        val privateKey = ByteString.copyFrom(PrivateKey(accountASeedHex.toHexByteArray()).data())

        val signingInput = Elrond.SigningInput.newBuilder()
            .setPrivateKey(privateKey)
            .setTransaction(transaction)
            .build()

        val output = AnySigner.sign(signingInput, CoinType.ELROND, Elrond.SigningOutput.parser())
        val expectedSignature = "b4f60c20ad6393bb3315853fe151e6c1ea5fadbeef059e9a4391a1fe8dd07aa955ec2330bb9461a1bb44a66688eaac8618c82f8a305afec5e5bb0aa5244c420c"

        assertEquals(expectedSignature, output.signature)
        assertEquals("""{"nonce":0,"value":"0","receiver":"$accountBBech32","sender":"$accountABech32","gasPrice":1000000000,"gasLimit":50000,"data":"Zm9v","chainID":"1","version":1,"signature":"$expectedSignature"}""", output.encoded)
    }
}
