/* eslint-disable @typescript-eslint/no-unused-vars */
import { TurboModule, TurboModuleRegistry } from "react-native";


type ProtobufBase64 = string;
interface WriteableStream {
  send: (data: ProtobufBase64) => boolean;
  stop: () => boolean;
}
type OnResponseCallback = (data: ProtobufBase64) => void;
type OnErrorCallback = (error: string) => void;
type UnsubscribeFromStream = () => void;

export interface Spec extends TurboModule {
  readonly start: (args: string) => Promise<string>;

  // Methods
  readonly getInfo: (data: ProtobufBase64) => Promise<ProtobufBase64>;
  readonly listPeers: (data: ProtobufBase64) => Promise<ProtobufBase64>;
  readonly connectPeer: (data: ProtobufBase64) => Promise<ProtobufBase64>;
  readonly listChannels: (data: ProtobufBase64) => Promise<ProtobufBase64>;

  // Read streams
  readonly subscribeState: (onResponse: OnResponseCallback, onError: OnErrorCallback) => UnsubscribeFromStream;

  // Bi-di streams
  readonly channelAcceptor: (onResponse: OnResponseCallback, onError: OnErrorCallback) => WriteableStream;

  // readonly reg: () => void;
  // readonly start: (config: string, onResponse: OnResponse) => void;
  // readonly startPromise: (config: string) => Promise<string>;
  // readonly startPromise2: () => Promise<string>;
  // readonly startPromise3: () => Promise<string>;
  // readonly startPromise4: () => Promise<string>;
  // readonly startPromise5: () => Promise<string>;
  // readonly startPromise6: () => Promise<string>;
  // readonly startPromise7: () => Promise<string>;
  // readonly callback: (callback: () => void) => void;
  // readonly promise: () => Promise<string>;
  // readonly startPromiseCallback: (callback: (str: string) => void) => void;
  // readonly startPromiseCallback2: (callback: (str: string) => void) => void;
  // readonly startPromiseCallback3: (callback: (str: string) => void) => void;
  // readonly getInfo: () => Promise<string>;
  // readonly getInfo4: () => Promise<string>;
  // readonly getInfo2: () => Promise<string>;
  // readonly getInfo3: () => Promise<string>;
  // readonly getInfoCallback: (onResponse: (str: string) => void, onError: (str: string) => void) => (() => void);
  // readonly prom: () => Promise<string>;

  // readonly subscribeState: (onResponse: (str: string) => void, onError: (str: string) => void) => (() => void);
  // readonly channelAcceptor: (onResponse: (str: string) => void, onError: (str: string) => void) => ChannelAcceptorMethods;
  // readonly arrayBuffer: (a: ArrayBuffer) => void;

  // readonly start2: (onResponse: OnResponse) => void;
  // readonly start2: (config: string) => Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>("NativeSampleModuleCxx");
