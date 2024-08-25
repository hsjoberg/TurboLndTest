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

import NativeSampleModuleCxx from './tm/NativeSampleModuleCxx';

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
            onPress={() => {
                console.log(
                  NativeSampleModuleCxx.start("", (t) => console.log(t)),
                );
            }}
            title="start lnd"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise(""),
                );
            }}
            title="startPromise"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise2(),
                );
            }}
            title="startPromise2"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise3(),
                );
            }}
            title="startPromise3"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise4(),
                );
            }}
            title="startPromise4"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise5(),
                );
            }}
            title="startPromise5"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise6(),
                );
            }}
            title="startPromise6"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.startPromise7(),
                );
            }}
            title="startPromise7"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.callback(() => console.log("callback from callback")),
                );
            }}
            title="callback"
          />
          <Button
            onPress={() => {
                for (let i = 0; i < 100; i++) {
                  console.log(
                    NativeSampleModuleCxx.callback(() => console.log("callback from callback")),
                  );
                }
            }}
            title="callback loop"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.promise(),
                );
            }}
            title="promise"
          />
          <Button
            onPress={async () => {
              for (let i = 0; i < 100; i++) {
                console.log(
                  await NativeSampleModuleCxx.promise(),
                );
              }
            }}
            title="promise loop"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModuleCxx.startPromiseCallback((a) => console.log("callback from startPromiseCallback")),
                );
            }}
            title="startPromiseCallback"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModuleCxx.startPromiseCallback2((a) => console.log("callback from startPromiseCallback2")),
                );
            }}
            title="startPromiseCallback2"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModuleCxx.startPromiseCallback3((a) => console.log("callback from startPromiseCallback3")),
                );
            }}
            title="startPromiseCallback3"
          />
          <Button
            onPress={async () => {
                const unsubscribe = NativeSampleModuleCxx.getInfoCallback((a) => console.log("callback from getInfoCallback", a), (err) => console.log("error from getInfoCallback", err));

                setTimeout(() => {
                  console.log("unsubscribe");
                  unsubscribe();
                }, 3000);
            }}
            title="getInfoCallback"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.getInfo(),
                );
            }}
            title="getInfo"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.getInfo4(),
                );
            }}
            title="getInfo4"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  await NativeSampleModuleCxx.getInfo4()
                // );
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`)
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfo4 loop"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.getInfo2(),
                );
            }}
            title="getInfo2"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.getInfo3(),
                );
            }}
            title="getInfo3"
          />
          <Button
            onPress={async () => {
              const promised = async () => {
                return new Promise((resolve, reject) => {
                  NativeSampleModuleCxx.getInfoCallback((a) => resolve(a));
                });
              }

              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  // NativeSampleModuleCxx.getInfoCallback((a) => console.log("callback from getInfoCallback", a));
                  await promised();
                // );
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`)
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfoCallback loop"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  await NativeSampleModuleCxx.getInfo()
                // );
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
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  await NativeSampleModuleCxx.getInfo2()
                // );
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`)
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfo2 loop"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  await NativeSampleModuleCxx.getInfo3()
                // );
              }
              const endTime = performance.now();
              const executionTime = endTime - startTime;

              console.log("done");
              console.log(`Execution time: ${executionTime} milliseconds`)
              if (!__DEV__) {
                Alert.alert(`Execution time: ${executionTime} milliseconds`);
              }
            }}
            title="getInfo3 loop"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModuleCxx.reg(),
                );
            }}
            title="reg"
          />
          <Button
            onPress={async () => {
                  // const f = NativeSampleModuleCxx.reg();
                  console.log("foo",global.foo);
                  console.log(global.foo(() => console.log("callback foo")));
            }}
            title="foo"
          />

          <Button
            onPress={async () => {
                  // const f = NativeSampleModuleCxx.reg();
                  console.log(await NativeSampleModuleCxx.prom());
            }}
            title="prom"
          />
          <Button
            onPress={async () => {
                  // const f = NativeSampleModuleCxx.reg();
                  console.log(NativeSampleModuleCxx.subscribeState((a) => console.log("callback from subscribeState", a), (err) => console.log("error from subscribeState", err)));
            }}
            title="subscribeState"
          />


          <Button
            onPress={async () => {
                const channelAcceptor = NativeSampleModuleCxx.channelAcceptor(
                  (a) => {
                    console.log("callback from channelAcceptor", a);
                  },
                  (err) => {
                    console.log("error from channelAcceptor", err)
                  });

                  console.log("channelAcceptor", channelAcceptor);

                  channelAcceptor.send("aGVq");
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
