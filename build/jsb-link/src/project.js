require = function l(n, s, r) {
function c(t, e) {
if (!s[t]) {
if (!n[t]) {
var o = "function" == typeof require && require;
if (!e && o) return o(t, !0);
if (u) return u(t, !0);
var i = new Error("Cannot find module '" + t + "'");
throw i.code = "MODULE_NOT_FOUND", i;
}
var a = s[t] = {
exports: {}
};
n[t][0].call(a.exports, function(e) {
return c(n[t][1][e] || e);
}, a, a.exports, l, n, s, r);
}
return s[t].exports;
}
for (var u = "function" == typeof require && require, e = 0; e < r.length; e++) c(r[e]);
return c;
}({
HelloWorld: [ function(e, t, o) {
"use strict";
cc._RF.push(t, "280c3rsZJJKnZ9RqbALVwtK", "HelloWorld");
cc.Class({
extends: cc.Component,
properties: {
appId: {
default: null,
type: cc.EditBox
},
channelName: {
default: null,
type: cc.EditBox
},
eb: {
default: null,
type: cc.EditBox
},
agoraClient: {
default: null,
type: Object
},
sprites: {
default: null,
type: Object
},
headerW: 120,
headerH: 90,
headerOffset: 10
},
onLoad: function() {
this.sprites = {};
this.uids = new Set();
this.agoraClient = new agora.HomeAgora();
this.agoraClient.setLocalJoinCallback(this.onLocalJoinCallback, this);
this.agoraClient.setLocalLeaveCallback(this.onLocalLeaveCallback, this);
this.agoraClient.setMuteLocalAudioCallback(this.onMuteLocalAudioCallback, this);
this.agoraClient.setUnmuteLocalAudioCallback(this.onUnmuteLocalAudioCallback, this);
this.agoraClient.setMuteLocalVideoCallback(this.onMuteLocalVideoCallback, this);
this.agoraClient.setUnmuteLocalVideoCallback(this.onUnmuteLocalVideoCallback, this);
this.agoraClient.setMuteRemoteVideoCallback(this.onMuteRemoteVideoCallback, this);
this.agoraClient.setUnmuteRemoteVideoCallback(this.onUnmuteRemoteVideoCallback, this);
this.agoraClient.setMuteRemoteAudioCallback(this.onMuteRemoteAudioCallback, this);
this.agoraClient.setUnmuteRemoteAudioCallback(this.onUnmuteRemoteAudioCallback, this);
this.agoraClient.setRemoteLeaveCallback(this.onRemoteLeaveCallback, this);
this.agoraClient.setRemoteJoinCallback(this.onRemoteJoinCallback, this);
setInterval(this.getTexture.bind(this), 2e3);
},
getTexture: function() {
var e = !0, t = !1, o = void 0;
try {
for (var i, a = this.uids[Symbol.iterator](); !(e = (i = a.next()).done); e = !0) {
var l = i.value, n = this.agoraClient.getTexture(l);
this.updateTexture(l, n);
}
} catch (e) {
t = !0;
o = e;
} finally {
try {
!e && a.return && a.return();
} finally {
if (t) throw o;
}
}
},
getAudioLevel: function() {
var e = !0, t = !1, o = void 0;
try {
for (var i, a = this.uids[Symbol.iterator](); !(e = (i = a.next()).done); e = !0) {
var l = i.value, n = this.agoraClient.getAudioLevel(l);
console.log("uid = " + l + "----audioLevel = " + n);
}
} catch (e) {
t = !0;
o = e;
} finally {
try {
!e && a.return && a.return();
} finally {
if (t) throw o;
}
}
},
getStats: function() {
var e = this.agoraClient.getStats();
console.log("duration = " + e.duration);
console.log("txBytes = " + e.txBytes);
console.log("rxBytes = " + e.rxBytes);
console.log("txAudioKBitrate = " + e.txAudioKBitrate);
console.log("rxAudioKBitrate = " + e.rxAudioKBitrate);
console.log("txVideoKBitrate = " + e.txVideoKBitrate);
console.log("rxVideoKBitrate = " + e.rxVideoKBitrate);
console.log("userCount = " + e.userCount);
console.log("cpuAppUsage = " + e.cpuAppUsage);
console.log("cpuTotalUsage = " + e.cpuTotalUsage);
console.log("sentBitrate = " + e.sentBitrate);
console.log("sentFrameRate = " + e.sentFrameRate);
var t = e.clients;
for (var o in t) {
console.log("uid = " + t[o].uid);
console.log("width = " + t[o].width);
console.log("height = " + t[o].height);
console.log("receivedBitrate = " + t[o].receivedBitrate);
console.log("receivedFrameRate = " + t[o].receivedFrameRate);
}
},
getNetworkQuality: function() {
var e = this.agoraClient.getNetworkQuality(0);
console.log("uid = " + e.uid);
console.log("txquality = " + e.txquality);
console.log("rxquality = " + e.rxquality);
},
onJoin: function() {
this.agoraClient.join(this.appId.string, this.channelName.string, 1e5, "370P_9", 0, 1, 1);
},
onUnmuteLocalVideo: function() {
this.agoraClient.unmuteLocalVideo();
},
onMuteLocalVideo: function() {
this.agoraClient.muteLocalVideo();
},
onUnmuteLocalAudio: function() {
this.agoraClient.unmuteLocalAudio();
},
onMuteLocalAudio: function() {
this.agoraClient.muteLocalAudio();
},
onUnmuteRemoteVideo: function() {
var e = parseInt(this.eb.string);
this.agoraClient.unmuteRemoteVideo(e);
},
onMuteRemoteVideo: function() {
var e = parseInt(this.eb.string);
this.agoraClient.muteRemoteVideo(e);
},
onUnmuteRemoteAudio: function() {
var e = parseInt(this.eb.string);
this.agoraClient.unmuteRemoteAudio(e);
},
onMuteRemoteAudio: function() {
var e = parseInt(this.eb.string);
this.agoraClient.muteRemoteAudio(e);
},
onLeave: function() {
this.agoraClient.leave();
},
onLocalJoinCallback: function(e) {
console.log("onLocalJoinCallback");
console.log(e);
var t = JSON.parse(e);
this.localUid = parseInt(t.data.uid);
},
onMuteLocalAudioCallback: function(e) {},
onUnmuteLocalAudioCallback: function(e) {},
onMuteLocalVideoCallback: function(e) {
console.log("onMuteLocalVideoCallback");
console.log(e);
this.uids.delete(this.localUid);
var t = this.sprites[this.localUid];
if (null != t) {
delete this.sprites[this.localUid];
t.node.removeFromParent();
this.updateHeadersDisplay();
}
},
onUnmuteLocalVideoCallback: function(e) {
console.log("onUnmuteLocalVideoCallback");
console.log(e);
this.uids.add(this.localUid);
},
onMuteRemoteVideoCallback: function(e) {
console.log("onUnmuteRemoteVideoCallback");
console.log(e);
var t = JSON.parse(e);
this.uids.delete(t.data.uid);
var o = this.sprites[t.data.uid];
if (null != o) {
delete this.sprites[t.data.uid];
o.node.removeFromParent();
this.updateHeadersDisplay();
}
},
onUnmuteRemoteVideoCallback: function(e) {
console.log("onMuteRemoteVideoCallback");
console.log(e);
var t = JSON.parse(e);
this.uids.add(t.data.uid);
},
onMuteRemoteAudioCallback: function(e) {
console.log("onMuteRemoteAudioCallback");
console.log(e);
},
onUnmuteRemoteAudioCallback: function(e) {
console.log("onUnmuteRemoteAudioCallback");
console.log(e);
},
onLocalLeaveCallback: function(e) {
this.localUid = null;
for (var t in this.sprites) {
this.sprites[t].node.removeFromParent();
}
this.sprites = {};
},
onRemoteLeaveCallback: function(e) {
console.log("uid=" + e + "离开了");
this.uids.delete(e);
var t = this.sprites[e];
if (null != t) {
t.node.removeFromParent(!0);
delete this.sprites[e];
this.updateHeadersDisplay();
}
},
onRemoteJoinCallback: function(e) {
console.log("uid=" + e + "上线了");
this.eb.string = e + "";
},
updateTexture: function(e, t) {
var o = this.sprites[e];
if (null == o) {
console.log("uid=" + e + "创建Sprite");
var i = new cc.SpriteFrame();
i.setTexture(t);
var a = new cc.Node("Sprite");
(o = a.addComponent(cc.Sprite)).spriteFrame = i;
a.x = 0;
a.y = 0;
a.setContentSize(this.headerW, this.headerH);
a.parent = this.node;
this.sprites[e] = o;
this.updateHeadersDisplay();
} else {
o.spriteFrame.setTexture(t);
o.node.setContentSize(this.headerW, this.headerH);
}
},
updateHeadersDisplay: function() {
var e = cc.director.getWinSize(), t = -e.width / 2, o = -e.height / 2, i = 0;
for (var a in this.sprites) {
var l = this.sprites[a].node;
if (a == this.localUid) {
l.anchorX = 0;
l.anchorY = 0;
l.x = e.width / 2 - this.headerW;
l.y = e.height / 2 - this.headerH;
} else {
l.anchorX = 0;
l.anchorY = 0;
l.x = i * this.headerW + i * this.headerOffset + t;
l.y = o;
i++;
}
}
}
});
cc._RF.pop();
}, {} ]
}, {}, [ "HelloWorld" ]);