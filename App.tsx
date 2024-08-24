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

import NativeSampleModule from './tm/NativeSampleModule';

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
                  NativeSampleModule.start("", (t) => console.log(t)),
                );
            }}
            title="start lnd"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise(""),
                );
            }}
            title="startPromise"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise2(),
                );
            }}
            title="startPromise2"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise3(),
                );
            }}
            title="startPromise3"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise4(),
                );
            }}
            title="startPromise4"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise5(),
                );
            }}
            title="startPromise5"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise6(),
                );
            }}
            title="startPromise6"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.startPromise7(),
                );
            }}
            title="startPromise7"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.callback(() => console.log("callback from callback")),
                );
            }}
            title="callback"
          />
          <Button
            onPress={() => {
                for (let i = 0; i < 100; i++) {
                  console.log(
                    NativeSampleModule.callback(() => console.log("callback from callback")),
                  );
                }
            }}
            title="callback loop"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.promise(),
                );
            }}
            title="promise"
          />
          <Button
            onPress={async () => {
              for (let i = 0; i < 100; i++) {
                console.log(
                  await NativeSampleModule.promise(),
                );
              }
            }}
            title="promise loop"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModule.startPromiseCallback((a) => console.log("callback from startPromiseCallback")),
                );
            }}
            title="startPromiseCallback"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModule.startPromiseCallback2((a) => console.log("callback from startPromiseCallback2")),
                );
            }}
            title="startPromiseCallback2"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModule.startPromiseCallback3((a) => console.log("callback from startPromiseCallback3")),
                );
            }}
            title="startPromiseCallback3"
          />
          <Button
            onPress={async () => {
                console.log(
                  NativeSampleModule.getInfoCallback((a) => console.log("callback from getInfoCallback", a)),
                );
            }}
            title="getInfoCallback"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.getInfo(),
                );
            }}
            title="getInfo"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.getInfo4(),
                );
            }}
            title="getInfo4"
          />
          <Button
            onPress={async () => {
              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  await NativeSampleModule.getInfo4()
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
                  await NativeSampleModule.getInfo2(),
                );
            }}
            title="getInfo2"
          />
          <Button
            onPress={async () => {
                console.log(
                  await NativeSampleModule.getInfo3(),
                );
            }}
            title="getInfo3"
          />
          <Button
            onPress={async () => {
              const promised = async () => {
                return new Promise((resolve, reject) => {
                  NativeSampleModule.getInfoCallback((a) => resolve(a));
                });
              }

              const startTime = performance.now();
              for (let i = 0; i < 100; i++) {
                // console.log(
                  // NativeSampleModule.getInfoCallback((a) => console.log("callback from getInfoCallback", a));
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
                  await NativeSampleModule.getInfo()
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
                  await NativeSampleModule.getInfo2()
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
                  await NativeSampleModule.getInfo3()
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
                  await NativeSampleModule.reg(),
                );
            }}
            title="reg"
          />
          <Button
            onPress={async () => {
                  // const f = NativeSampleModule.reg();
                  console.log("foo",global.foo);
                  console.log(global.foo(() => console.log("callback foo")));
            }}
            title="foo"
          />

          <Button
            onPress={async () => {
                  // const f = NativeSampleModule.reg();
                  console.log(await NativeSampleModule.prom());
            }}
            title="prom"
          />
          <Button
            onPress={async () => {
                  // const f = NativeSampleModule.reg();
                  console.log(await NativeSampleModule.a());
            }}
            title="a"
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
