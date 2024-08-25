/* eslint-disable */
/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 */

import React from 'react';
import type {PropsWithChildren} from 'react';
import {
  Alert,
  Button,
  Platform,
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
} from 'react-native';

import {
  Colors,
  DebugInstructions,
  Header,
  LearnMoreLinks,
  ReloadInstructions,
} from 'react-native/Libraries/NewAppScreen';

import RNFS from 'react-native-fs';
import { lnrpc } from './proto/lightning';
import * as base64 from "base64-js";

import NativeSampleModuleCxx from './tm/NativeSampleModuleCxx';

console.log("RNFS.DocumentDirectoryPath", RNFS.DocumentDirectoryPath);

type SectionProps = PropsWithChildren<{
  title: string;
}>;

function Section({children, title}: SectionProps): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  return (
    <View style={styles.sectionContainer}>
      <Text
        style={[
          styles.sectionTitle,
          {
            color: isDarkMode ? Colors.white : Colors.black,
          },
        ]}>
        {title}
      </Text>
      <Text
        style={[
          styles.sectionDescription,
          {
            color: isDarkMode ? Colors.light : Colors.dark,
          },
        ]}>
        {children}
      </Text>
    </View>
  );
}

function App(): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar
        barStyle={isDarkMode ? 'light-content' : 'dark-content'}
        backgroundColor={backgroundStyle.backgroundColor}
      />
      <ScrollView
        contentInsetAdjustmentBehavior="automatic"
        style={backgroundStyle}>
        <Header />
        <View
          style={{
            backgroundColor: isDarkMode ? Colors.black : Colors.white,
          }}>
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.start(`
--lnddir=${Platform.OS === "ios" ? RNFS.DocumentDirectoryPath : "/data/user/0/com.turbolnd/files"}
--noseedbackup
--nolisten
--bitcoin.active
--bitcoin.regtest
--bitcoin.node=neutrino
--feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\"
--routing.assumechanvalid
--tlsdisableautofill
--db.bolt.auto-compact
--db.bolt.auto-compact-min-age=0
--neutrino.connect=192.168.10.120:19444`)
                );
            }}
            title="start"
          />
          <Button
            onPress={async () => {
                const b64 = await NativeSampleModuleCxx.getInfo("")
                console.log("base64", b64);
                const getInfoResponse = lnrpc.GetInfoResponse.decode(base64.toByteArray(b64));
                console.log("getInfoResponse", getInfoResponse.toJSON());
            }}
            title="getInfo"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                const getInfoRequest = lnrpc.GetInfoRequest.encode({}).finish();
                const getInfoRequestBase64 = base64.fromByteArray(getInfoRequest);

                const b64 = await NativeSampleModuleCxx.getInfo(getInfoRequestBase64)
                const getInfoResponse = lnrpc.GetInfoResponse.decode(base64.toByteArray(b64));
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`)
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
                  await NativeSampleModuleCxx.getInfo("")
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`)
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfo loop"
          />
          <Button
            onPress={async () => {
                const b64 = await NativeSampleModuleCxx.listPeers("")
                console.log("base64", b64);
                const listPeersResponse = lnrpc.ListPeersResponse.decode(base64.toByteArray(b64));
                console.log("listPeersResponse", listPeersResponse.peers);

            }}
            title="listPeers"
          />
          <Button
            onPress={async () => {
                const connectPeerRequest = lnrpc.ConnectPeerRequest.encode({
                  addr: {
                    host: "192.168.10.120:9735",
                    pubkey: "033762daab2eddcb5d04101fb1dac955ffc23251d0b2664419fa07805b6fc8ee5d",
                  },
                  perm: true,
                }).finish();
                const connectPeerRequestBase64 = base64.fromByteArray(connectPeerRequest);
                console.log("Sending request", connectPeerRequest, connectPeerRequestBase64);

                const b64 = await NativeSampleModuleCxx.connectPeer(connectPeerRequestBase64)
                console.log("base64", b64);
                const listPeersResponse = lnrpc.ListPeersResponse.decode(base64.toByteArray(b64));
                console.log("listPeersResponse", listPeersResponse);

            }}
            title="connectPeer"
          />
          <Button
            onPress={async () => {
                const b64 = await NativeSampleModuleCxx.listChannels("")
                console.log("base64", b64);
                const listChannelsResponse = lnrpc.ListChannelsResponse.decode(base64.toByteArray(b64));
                console.log("listChannelsResponse", listChannelsResponse.toJSON());

            }}
            title="listChannels"
          />
          <Button
            onPress={async () => {
                const unsubscribe = NativeSampleModuleCxx.subscribeState(
                  (a) => {
                    console.log("callback from subscribeState", a);
                    const state = lnrpc.SubscribeStateResponse.decode(base64.toByteArray(a));
                    console.log("state", state);
                  },
                  (err) => {
                    console.log("error from subscribeState", err);
                  }
                );

                // setTimeout(() => {
                //   console.log("unsubscribe");
                //   unsubscribe();
                // }, 3000);
            }}
            title="subscribeState"
          />
          <Button
            onPress={async () => {
                const chanAcceptor = NativeSampleModuleCxx.channelAcceptor(
                  (dataBase64) => {
                    console.log("callback from channelAcceptor", dataBase64);
                    const channelAcceptorRequest = lnrpc.ChannelAcceptRequest.decode(base64.toByteArray(dataBase64));
                    console.log("channelAcceptorRequest", channelAcceptorRequest);

                    const channelAcceptorResponse = lnrpc.ChannelAcceptResponse.encode({
                      accept: true,
                      pendingChanId: channelAcceptorRequest.pendingChanId,
                    }).finish();
                    const channelAcceptorResponseBase64 = base64.fromByteArray(channelAcceptorResponse);

                    console.log("Sending response", channelAcceptorResponse, channelAcceptorResponseBase64);
                    chanAcceptor.send(channelAcceptorResponseBase64);
                  },
                  (err) => {
                    console.log("error from channelAcceptor", err);
                  }
                );
            }}
            title="channelAcceptor"
          />
          <Section title="Step One">
            Edit <Text style={styles.highlight}>App.tsx</Text> to change this
            screen and then come back to see your edits.
          </Section>
          <Section title="See Your Changes">
            <ReloadInstructions />
          </Section>
          <Section title="Debug">
            <DebugInstructions />
          </Section>
          <Section title="Learn More">
            Read the docs to discover what to do next:
          </Section>
          <LearnMoreLinks />
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
  highlight: {
    fontWeight: '700',
  },
});

export default App;
