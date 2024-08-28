#pragma once

#if __has_include(<React-Codegen/AppSpecsJSI.h>) // CocoaPod headers on Apple
#include <React-Codegen/AppSpecsJSI.h>
#elif __has_include("AppSpecsJSI.h") // CMake headers on Android
#include "AppSpecsJSI.h"
#endif
#include <memory>
#include <string>

#include <react/bridging/Promise.h>
#include "Promise.h"
#include "Function.h"

namespace facebook::react {

class NativeSampleModuleCxx : public NativeSampleModuleCxxCxxSpec<NativeSampleModuleCxx> {
 public:
  explicit NativeSampleModuleCxx(std::shared_ptr<CallInvoker> jsInvoker);

  static void promiseOnResponseStatic(void* context, const char* data, int length);
  static void promiseOnErrorStatic(void* context, const char* error);
  static void callbackOnResponseStatic(void* context, const char* data, int length);
  static void callbackOnErrorStatic(void* context, const char* error);


  facebook::react::AsyncPromise2<std::string> start(jsi::Runtime &rt, jsi::String args);

  facebook::react::AsyncPromise2<std::string> walletBalance(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> channelBalance(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> getTransactions(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> estimateFee(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> sendCoins(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listUnspent(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeTransactions(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> sendMany(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> newAddress(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signMessage(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> verifyMessage(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> connectPeer(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> disconnectPeer(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listPeers(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribePeerEvents(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> getInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> getRecoveryInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> pendingChannels(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listChannels(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeChannelEvents(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> closedChannels(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> openChannelSync(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function openChannel(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> batchOpenChannel(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> fundingStateStep(jsi::Runtime &rt, jsi::String data);

  jsi::Object channelAcceptor(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function closeChannel(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> abandonChannel(jsi::Runtime &rt, jsi::String data);

  jsi::Object sendPayment(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> sendPaymentSync(jsi::Runtime &rt, jsi::String data);

  jsi::Object sendToRoute(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> sendToRouteSync(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> addInvoice(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listInvoices(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> lookupInvoice(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeInvoices(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> decodePayReq(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listPayments(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> deletePayment(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> deleteAllPayments(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> describeGraph(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> getNodeMetrics(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> getChanInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> getNodeInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> queryRoutes(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> getNetworkInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> stopDaemon(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeChannelGraph(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> debugLevel(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> feeReport(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> updateChannelPolicy(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> forwardingHistory(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> exportChannelBackup(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> exportAllChannelBackups(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> verifyChanBackup(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> restoreChannelBackups(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeChannelBackups(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> bakeMacaroon(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listMacaroonIDs(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> deleteMacaroonID(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> listPermissions(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> checkMacaroonPermissions(jsi::Runtime &rt, jsi::String data);

  jsi::Object registerRPCMiddleware(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> sendCustomMessage(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeCustomMessages(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> listAliases(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> lookupHtlcResolution(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> genSeed(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> initWallet(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> unlockWallet(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> changePassword(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function subscribeState(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> getState(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> autopilotStatus(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> autopilotModifyStatus(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> autopilotQueryScores(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> autopilotSetScores(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function chainNotifierRegisterConfirmationsNtfn(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function chainNotifierRegisterSpendNtfn(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function chainNotifierRegisterBlockEpochNtfn(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function invoicesSubscribeSingleInvoice(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> invoicesCancelInvoice(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> invoicesAddHoldInvoice(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> invoicesSettleInvoice(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> invoicesLookupInvoiceV2(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitStatus(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitAddPeer(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitDisconnectPeer(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitIsBanned(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitGetBlockHeader(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitGetBlock(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitGetCFilter(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> neutrinoKitGetBlockHash(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> peersUpdateNodeAnnouncement(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function routerSendPaymentV2(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function routerTrackPaymentV2(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function routerTrackPayments(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> routerEstimateRouteFee(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerSendToRoute(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerSendToRouteV2(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerResetMissionControl(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerQueryMissionControl(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerXImportMissionControl(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerGetMissionControlConfig(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerSetMissionControlConfig(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerQueryProbability(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> routerBuildRoute(jsi::Runtime &rt, jsi::String data);

  facebook::jsi::Function routerSubscribeHtlcEvents(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function routerSendPayment(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::jsi::Function routerTrackPayment(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  jsi::Object routerHtlcInterceptor(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);

  facebook::react::AsyncPromise2<std::string> routerUpdateChanStatus(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerSignOutputRaw(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerComputeInputScript(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerSignMessage(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerVerifyMessage(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerDeriveSharedKey(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerMuSig2CombineKeys(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerMuSig2CreateSession(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerMuSig2RegisterNonces(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerMuSig2Sign(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerMuSig2CombineSig(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> signerMuSig2Cleanup(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> versionerGetVersion(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitListUnspent(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitLeaseOutput(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitReleaseOutput(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitListLeases(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitDeriveNextKey(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitDeriveKey(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitNextAddr(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitListAccounts(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitRequiredReserve(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitListAddresses(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitSignMessageWithAddr(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitVerifyMessageWithAddr(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitImportAccount(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitImportPublicKey(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitImportTapscript(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitPublishTransaction(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitSendOutputs(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitEstimateFee(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitPendingSweeps(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitBumpFee(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitListSweeps(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitLabelTransaction(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitFundPsbt(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitSignPsbt(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> walletKitFinalizePsbt(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerGetInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerClientAddTower(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerClientRemoveTower(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerClientListTowers(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerClientGetTowerInfo(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerClientStats(jsi::Runtime &rt, jsi::String data);

  facebook::react::AsyncPromise2<std::string> watchtowerClientPolicy(jsi::Runtime &rt, jsi::String data);


  facebook::react::AsyncPromise2<std::string> promiseLeakTest(jsi::Runtime &rt, jsi::String data);
};

} // namespace facebook::react
