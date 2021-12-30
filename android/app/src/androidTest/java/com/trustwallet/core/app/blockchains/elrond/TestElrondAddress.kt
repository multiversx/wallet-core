// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

package com.trustwallet.core.app.blockchains.elrond

import com.trustwallet.core.app.utils.toHex
import com.trustwallet.core.app.utils.toHexByteArray
import org.junit.Assert.assertEquals
import org.junit.Test
import wallet.core.jni.*

class TestElrondAddress {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    private val accountABech32 = "erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz"
    private var accountASeedHex = "1a927e2af5306a9bb2ea777f73e06ecc0ac9aaa72fb4ea3fecf659451394cccf"
    private var accountAPubKeyHex = "0xfd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293"

    @Test
    fun testAddressFromPrivateKey() {
        val key = PrivateKey(accountASeedHex.toHexByteArray())
        val pubKey = key.publicKeyEd25519
        val address = AnyAddress(pubKey, CoinType.ELROND)

        assertEquals(accountAPubKeyHex, pubKey.data().toHex())
        assertEquals(accountABech32, address.description())
    }

    @Test
    fun testAddressFromPublicKey() {
        val pubKey = PublicKey(accountAPubKeyHex.toHexByteArray(), PublicKeyType.ED25519)
        val address = AnyAddress(pubKey, CoinType.ELROND)

        assertEquals(accountABech32, address.description())
    }

    @Test
    fun testAddressFromString() {
        val address = AnyAddress(accountABech32, CoinType.ELROND)
        
        assertEquals(accountABech32, address.description())
    }
}
