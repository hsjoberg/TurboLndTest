#!/bin/sh
protoc --plugin=protoc-gen-cpp-functions=/Users/coco/Projects/Blixt/TurboLnd/protoc-generator/protoc-gen-cpp-functions.js \
--cpp-functions_out=. \
--proto_path=../proto \
lightning.proto walletunlocker.proto stateservice.proto autopilotrpc/autopilot.proto chainrpc/chainnotifier.proto invoicesrpc/invoices.proto neutrinorpc/neutrino.proto peersrpc/peers.proto routerrpc/router.proto signrpc/signer.proto verrpc/verrpc.proto walletrpc/walletkit.proto watchtowerrpc/watchtower.proto wtclientrpc/wtclient.proto
