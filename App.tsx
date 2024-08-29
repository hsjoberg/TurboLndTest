import React, { useState } from "react";
import {
  Alert,
  Button,
  SafeAreaView,
  ScrollView,
  Text,
  TextInput,
  View,
} from "react-native";

import { DocumentDirectoryPath } from "@dr.pogodin/react-native-fs";
import { lnrpc } from "./proto/lightning";
import * as base64 from "base64-js";

import NativeSampleModuleCxx from "./tm/NativeSampleModuleCxx";

function App(): React.JSX.Element {
  const [nodeUri, setNodeUri] = useState("");
  const [result, setResult] = useState("");
  return (
    <SafeAreaView>
      <ScrollView
        contentInsetAdjustmentBehavior="automatic"
        style={{ height: "100%", backgroundColor: "white" }}>
        <View>
          <Button
            onPress={async () => {
              console.log(
                await NativeSampleModuleCxx.start(`
--lnddir="${DocumentDirectoryPath}"
--noseedbackup
--nolisten
--bitcoin.active
--bitcoin.mainnet
--bitcoin.node=neutrino
--feeurl="https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json"
--routing.assumechanvalid
--tlsdisableautofill
--db.bolt.auto-compact
--db.bolt.auto-compact-min-age=0`),
              );
            }}
            title="start"
          />
          <Button
            onPress={async () => {
              const b64 = await NativeSampleModuleCxx.getInfo("");
              const getInfoResponse = lnrpc.GetInfoResponse.decode(
                base64.toByteArray(b64),
              );
              setResult(JSON.stringify(getInfoResponse.toJSON(), undefined, 2));
            }}
            title="getInfo"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                const getInfoRequest = lnrpc.GetInfoRequest.encode({}).finish();
                const getInfoRequestBase64 =
                  base64.fromByteArray(getInfoRequest);

                const b64 = await NativeSampleModuleCxx.getInfo(
                  getInfoRequestBase64,
                );
                const getInfoResponse = lnrpc.GetInfoResponse.decode(
                  base64.toByteArray(b64),
                );
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`);
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfo loop \w protobuf encoding/decoding"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                await NativeSampleModuleCxx.getInfo("");
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`);
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfo loop"
          />
          <Button
            onPress={async () => {
              const b64 = await NativeSampleModuleCxx.listPeers("");
              console.log("base64", b64);
              const listPeersResponse = lnrpc.ListPeersResponse.decode(
                base64.toByteArray(b64),
              );
              console.log("listPeersResponse", listPeersResponse.peers);
              setResult(
                JSON.stringify(listPeersResponse.toJSON(), undefined, 2),
              );
            }}
            title="listPeers"
          />
          <View style={{ flexDirection: "column" }}>
            <TextInput
              placeholder="pubkey@ip"
              value={nodeUri}
              onChangeText={setNodeUri}
              style={{ fontFamily: "monospace" }}
            />
            <Button
              onPress={async () => {
                const [pubkey, host] = nodeUri.split("@");
                const connectPeerRequest = lnrpc.ConnectPeerRequest.encode({
                  addr: {
                    host,
                    pubkey,
                  },
                  perm: true,
                }).finish();
                const connectPeerRequestBase64 =
                  base64.fromByteArray(connectPeerRequest);
                console.log(
                  "Sending request",
                  connectPeerRequest,
                  connectPeerRequestBase64,
                );

                const b64 = await NativeSampleModuleCxx.connectPeer(
                  connectPeerRequestBase64,
                );
                console.log("base64", b64);
                const connectPeerResponse = lnrpc.ConnectPeerResponse.decode(
                  base64.toByteArray(b64),
                );
                console.log("connectPeerResponse", connectPeerResponse);
                setResult(
                  JSON.stringify(connectPeerResponse.toJSON(), undefined, 2),
                );
              }}
              title="connectPeer"
            />
          </View>
          <Button
            onPress={async () => {
              const b64 = await NativeSampleModuleCxx.listChannels("");
              console.log("base64", b64);
              const listChannelsResponse = lnrpc.ListChannelsResponse.decode(
                base64.toByteArray(b64),
              );
              console.log(
                "listChannelsResponse",
                listChannelsResponse.toJSON(),
              );
              setResult(
                JSON.stringify(listChannelsResponse.toJSON(), undefined, 2),
              );
            }}
            title="listChannels"
          />
          <Button
            onPress={async () => {
              const unsubscribe = NativeSampleModuleCxx.subscribeState(
                "",
                dataBase64 => {
                  console.log("callback from subscribeState", dataBase64);
                  const state = lnrpc.SubscribeStateResponse.decode(
                    base64.toByteArray(dataBase64),
                  );
                  console.log("state", state);
                },
                err => {
                  console.log("error from subscribeState", err);
                },
              );

              // setTimeout(() => {
              //   console.log("unsubscribe");
              //     unsubscribe();
              // }, 3000);
            }}
            title="subscribeState"
          />
          <Button
            onPress={async () => {
              const chanAcceptor = NativeSampleModuleCxx.channelAcceptor(
                dataBase64 => {
                  console.log("callback from channelAcceptor", dataBase64);
                  const channelAcceptorRequest =
                    lnrpc.ChannelAcceptRequest.decode(
                      base64.toByteArray(dataBase64),
                    );
                  console.log("channelAcceptorRequest", channelAcceptorRequest);

                  const channelAcceptorResponse =
                    lnrpc.ChannelAcceptResponse.encode({
                      accept: true,
                      pendingChanId: channelAcceptorRequest.pendingChanId,
                    }).finish();
                  const channelAcceptorResponseBase64 = base64.fromByteArray(
                    channelAcceptorResponse,
                  );

                  console.log(
                    "Sending response",
                    channelAcceptorResponse,
                    channelAcceptorResponseBase64,
                  );
                  chanAcceptor.send(channelAcceptorResponseBase64);
                },
                err => {
                  console.log("error from channelAcceptor", err);
                },
              );
              // setTimeout(() => {
              //   console.log("stopping chanAcceptor");
              //   chanAcceptor.stop();
              // }, 3000);
            }}
            title="channelAcceptor"
          />
          <Text>{result}</Text>
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

export default App;
