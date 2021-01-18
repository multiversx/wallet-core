#pragma once

namespace TW {

class Scope {
  private:
    static bool _isMainnet;

  public:
    static bool IsMainnet();
    static void SetTestnet();
    static void SetMainnet();
};
} // namespace TW

/// Wrapper for C interface.
struct TWScope {
    TW::Scope impl;
};
