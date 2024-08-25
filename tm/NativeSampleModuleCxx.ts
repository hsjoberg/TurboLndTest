/* eslint-disable @typescript-eslint/no-unused-vars */
import { TurboModule, TurboModuleRegistry } from "react-native";


type OnResponse = () => void;
type OnError = (error: string) => void;

type Unsubscribe = () => void;


interface ChannelAcceptorMethods {
  send: (data: string) => boolean;
  stop: () => boolean;
}


export interface Spec extends TurboModule {
  readonly reg: () => void;
  readonly start: (config: string, onResponse: OnResponse) => void;
  readonly startPromise: (config: string) => Promise<string>;
  readonly startPromise2: () => Promise<string>;
  readonly startPromise3: () => Promise<string>;
  readonly startPromise4: () => Promise<string>;
  readonly startPromise5: () => Promise<string>;
  readonly startPromise6: () => Promise<string>;
  readonly startPromise7: () => Promise<string>;
  readonly callback: (callback: () => void) => void;
  readonly promise: () => Promise<string>;
  readonly startPromiseCallback: (callback: (str: string) => void) => void;
  readonly startPromiseCallback2: (callback: (str: string) => void) => void;
  readonly startPromiseCallback3: (callback: (str: string) => void) => void;
  readonly getInfo: () => Promise<string>;
  readonly getInfo4: () => Promise<string>;
  readonly getInfo2: () => Promise<string>;
  readonly getInfo3: () => Promise<string>;
  readonly getInfoCallback: (onResponse: (str: string) => void, onError: (str: string) => void) => (() => void);
  readonly prom: () => Promise<string>;

  readonly subscribeState: (onResponse: (str: string) => void, onError: (str: string) => void) => (() => void);
  readonly channelAcceptor: (onResponse: (str: string) => void, onError: (str: string) => void) => ChannelAcceptorMethods;
  // readonly arrayBuffer: (a: ArrayBuffer) => void;

  // readonly start2: (onResponse: OnResponse) => void;
  // readonly start2: (config: string) => Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>("NativeSampleModuleCxx");
