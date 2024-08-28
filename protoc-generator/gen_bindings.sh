#!/bin/sh
protoc --plugin=protoc-gen-custom=/Users/coco/Projects/Blixt/TurboLnd/protoc-generator/protoc-gen-cpp-functions.ts \
--custom_out=./build \
--proto_path=../proto \
lightning.proto walletunlocker.proto stateservice.proto autopilotrpc/autopilot.proto chainrpc/chainnotifier.proto invoicesrpc/invoices.proto neutrinorpc/neutrino.proto peersrpc/peers.proto routerrpc/router.proto signrpc/signer.proto verrpc/verrpc.proto walletrpc/walletkit.proto watchtowerrpc/watchtower.proto wtclientrpc/wtclient.proto
