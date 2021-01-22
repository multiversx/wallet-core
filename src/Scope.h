#pragma once

namespace TW {

class Scope {
  private:
    static bool _isMainnet;

  public:
    static bool IsMainnet();

    /// Enables the testnet-mode when generating addresses, for coins that supports this.
    /// For the moment, only handles BNB (which uses hrp = 'bnb' for mainnet and hrp = 'tbnb' for testnet).
    static void SetTestnet();

    /// Enables the testnet-mode when generating addresses, for coins that supports this.
    static void SetMainnet();
};
} // namespace TW

/// Wrapper for C interface.
struct TWScope {
    TW::Scope impl;
};
