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

    private var aliceBech32 = "erd1qyu5wthldzr8wx5c9ucg8kjagg0jfs53s8nr3zpz3hypefsdd8ssycr6th"
    private var alicePubKeyHex = "0139472eff6886771a982f3083da5d421f24c29181e63888228dc81ca60d69e1"
    private var aliceSeedHex = "413f42575f7f26fad3317a778771212fdb80245850981e48b58a4f25e344e8f9"
    private var bobBech32 = "erd1spyavw0956vq68xj8y4tenjpq2wd5a9p2c6j8gsz7ztyrnpxrruqzu66jx"
   
    @Test
    fun signGenericTransaction() {
        val transaction = Elrond.TransactionMessage.newBuilder()
            .setNonce(0)
            .setValue("0")
            .setSender(aliceBech32)
            .setReceiver(bobBech32)
            .setGasPrice(1000000000)
            .setGasLimit(50000)
            .setData("foo")
            .setChainId("1")
            .setVersion(1)
            .build()
        
        val privateKey = ByteString.copyFrom(PrivateKey(aliceSeedHex.toHexByteArray()).data())

        val signingInput = Elrond.SigningInput.newBuilder()
            .setPrivateKey(privateKey)
            .setTransaction(transaction)
            .build()

        val output = AnySigner.sign(signingInput, CoinType.ELROND, Elrond.SigningOutput.parser())
        val expectedSignature = "b4f60c20ad6393bb3315853fe151e6c1ea5fadbeef059e9a4391a1fe8dd07aa955ec2330bb9461a1bb44a66688eaac8618c82f8a305afec5e5bb0aa5244c420c"

        assertEquals(expectedSignature, output.signature)
        assertEquals("""{"nonce":0,"value":"0","receiver":"$bobBech32","sender":"$aliceBech32","gasPrice":1000000000,"gasLimit":50000,"data":"Zm9v","chainID":"1","version":1,"signature":"$expectedSignature"}""", output.encoded)
    }

    @Test
    fun signEGLDTransfer() {
        val transaction = Elrond.EGLDTransfer.newBuilder()
            .setNonce(7)
            .setSender(aliceBech32)
            .setReceiver(bobBech32)
            .setAmount("1000000000000000000")
            .setChainId("1")
            .build()
        
        val privateKey = ByteString.copyFrom(PrivateKey(aliceSeedHex.toHexByteArray()).data())

        val signingInput = Elrond.SigningInput.newBuilder()
            .setPrivateKey(privateKey)
            .setEgldTransfer(transaction)
            .build()

        val output = AnySigner.sign(signingInput, CoinType.ELROND, Elrond.SigningOutput.parser())
        val expectedSignature = "7e1c4c63b88ea72dcf7855a54463b1a424eb357ac3feb4345221e512ce07c7a50afb6d7aec6f480b554e32cf2037082f3bc17263d1394af1f3ef240be53c930b"

        assertEquals(expectedSignature, output.signature)
        assertEquals("""{"nonce":7,"value":"1000000000000000000","receiver":"$bobBech32","sender":"$aliceBech32","gasPrice":1000000000,"gasLimit":50000,"chainID":"1","version":1,"signature":"$expectedSignature"}""", output.encoded)
    }

    @Test
    fun signESDTTransfer() {
        val transaction = Elrond.ESDTTransfer.newBuilder()
            .setNonce(7)
            .setSender(aliceBech32)
            .setReceiver(bobBech32)
            .setTokenIdentifier("MYTOKEN-1234")
            .setAmount("10000000000000")
            .setChainId("1")
            .build()
        
        val privateKey = ByteString.copyFrom(PrivateKey(aliceSeedHex.toHexByteArray()).data())

        val signingInput = Elrond.SigningInput.newBuilder()
            .setPrivateKey(privateKey)
            .setEsdtTransfer(transaction)
            .build()

        val output = AnySigner.sign(signingInput, CoinType.ELROND, Elrond.SigningOutput.parser())
        val expectedSignature = "9add6d9ac3f1a1fddb07b934e8a73cad3b8c232bdf29d723c1b38ad619905f03e864299d06eb3fe3bbb48a9f1d9b7f14e21dc5eaffe0c87f5718ad0c4198bb0c"
        val expectedData = "RVNEVFRyYW5zZmVyQDRkNTk1NDRmNGI0NTRlMmQzMTMyMzMzNEAwOTE4NGU3MmEwMDA="

        assertEquals(expectedSignature, output.signature)
        assertEquals("""{"nonce":7,"value":"0","receiver":"$bobBech32","sender":"$aliceBech32","gasPrice":1000000000,"gasLimit":425000,"data":"$expectedData","chainID":"1","version":1,"signature":"$expectedSignature"}""", output.encoded)
    }

    @Test
    fun signESDTNFTTransfer() {
        val transaction = Elrond.ESDTNFTTransfer.newBuilder()
            .setNonce(7)
            .setSender(aliceBech32)
            .setReceiver(bobBech32)
            .setTokenCollection("LKMEX-aab910")
            .setTokenNonce(4)
            .setAmount("184300000000000000")
            .setChainId("1")
            .build()
        
        val privateKey = ByteString.copyFrom(PrivateKey(aliceSeedHex.toHexByteArray()).data())

        val signingInput = Elrond.SigningInput.newBuilder()
            .setPrivateKey(privateKey)
            .setEsdtnftTransfer(transaction)
            .build()

        val output = AnySigner.sign(signingInput, CoinType.ELROND, Elrond.SigningOutput.parser())
        val expectedSignature = "cc935685d5b31525e059a16a832cba98dee751983a5a93de4198f6553a2c55f5f1e0b4300fe9077376fa754546da0b0f6697e66462101a209aafd0fc775ab60a"
        val expectedData = "RVNEVE5GVFRyYW5zZmVyQDRjNGI0ZDQ1NTgyZDYxNjE2MjM5MzEzMEAwNEAwMjhlYzNkZmEwMWFjMDAwQDgwNDlkNjM5ZTVhNjk4MGQxY2QyMzkyYWJjY2U0MTAyOWNkYTc0YTE1NjM1MjNhMjAyZjA5NjQxY2MyNjE4Zjg="

        assertEquals(expectedSignature, output.signature)
        assertEquals("""{"nonce":7,"value":"0","receiver":"$aliceBech32","sender":"$aliceBech32","gasPrice":1000000000,"gasLimit":937500,"data":"$expectedData","chainID":"1","version":1,"signature":"$expectedSignature"}""", output.encoded)
    }
}
