// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "WalletCore",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "WalletCore", targets: ["WalletCore"]),
        .library(name: "SwiftProtobuf", targets: ["SwiftProtobuf"])
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "WalletCore",
            url: "https://github.com/ElrondNetwork/wallet-core/releases/download/ios_build/WalletCore.xcframework.zip",
            checksum: "7c53487e40243d45ca0ef78260782b7f88ac27bdf05d938e45e30ec005d2f759"
        ),
        .binaryTarget(
            name: "SwiftProtobuf",
            url: "https://github.com/ElrondNetwork/wallet-core/releases/download/ios_build/SwiftProtobuf.xcframework.zip",
            checksum: "a474d12088719020c35005e4815fd02a37503dcdc1178461f1d6e5a3e905b072"
        )
    ]
)

