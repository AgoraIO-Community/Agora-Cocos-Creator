window.__require = function e(a, o, r) {
function t(i, s) {
if (!o[i]) {
if (!a[i]) {
var u = i.split("/");
u = u[u.length - 1];
if (!a[u]) {
var g = "function" == typeof __require && __require;
if (!s && g) return g(u, !0);
if (n) return n(u, !0);
throw new Error("Cannot find module '" + i + "'");
}
}
var l = o[i] = {
exports: {}
};
a[i][0].call(l.exports, function(e) {
return t(a[i][1][e] || e);
}, l, l.exports, e, a, o, r);
}
return o[i].exports;
}
for (var n = "function" == typeof __require && __require, i = 0; i < r.length; i++) t(r[i]);
return t;
}({
HelloWorld: [ function(e, a, o) {
"use strict";
cc._RF.push(a, "280c3rsZJJKnZ9RqbALVwtK", "HelloWorld");
cc.Class({
extends: cc.Component,
properties: {
sprites: {
default: null,
type: Object
},
textures: {
default: null,
type: Object
},
uids: {
default: null,
type: Object
},
handler: -100,
headerW: 240,
headerH: 180,
headerOffset: 20,
localUid: 0,
appId: "5db0d12c40354100abd7a8a0adaa1fb8"
},
onLoad: function() {
this.sprites = {};
this.textures = {};
var e = new Set();
this.uids = e;
agora && agora.init(this.appId);
agora.setVideoProfile(52);
agora.setParameters('{"rtc.log_filter": 65535}');
agora.setChannelProfile(0);
agora.enableVideo();
agora.enableVideoObserver();
this.addSprite(this.localUid);
this.initAgoraEvents();
agora.joinChannel("", "1001", "", 0);
console.log("[Agora] js cc.log console joinChannel");
setInterval(this.updateTexture.bind(this), 40);
},
update: function(e) {},
onDestroy: function() {
this.uninitAgoraEvents();
},
updateTexture: function() {
for (var e, a = this.uids[Symbol.iterator](); !(e = a.next()).done; !0) {
var o = e.value;
if (null != this.textures[o]) {
var r = this.textures[o].getImpl().getHandle();
agora.updateTexture(r, o);
}
}
},
initAgoraEvents: function() {
agora.on("join-channel-success", this.onJoinChannelSuccess, this);
agora.on("leave-channel", this.onLeaveChannel, this);
agora.on("user-joined", this.onUserJoined, this);
agora.on("user-offline", this.onUserOffline, this);
},
unInitAgoraEvents: function() {
agora.off("join-channel-success", this.onJoinChannelSuccess);
agora.off("leave-channel", this.onLeaveChannel);
agora.off("user-joined", this.onUserJoined);
agora.off("user-offline", this.onUserOffline);
},
onJoinChannelSuccess: function(e, a, o) {
console.log("[Agora] js onJoinChannelSuccess channel = " + e + " ,uid = " + a);
},
onLeaveChannel: function(e) {
console.log("[Agora] js onLeaveChannel ");
},
onUserJoined: function(e, a) {
console.log("[Agora] js onUserJoined ");
this.addSprite(e);
},
onUserOffline: function(e, a) {
this.removeSprite(e);
},
createTexture: function(e) {
console.log("[Agora] js createTexture " + e);
var a = new cc.Texture2D();
a.initWithData(null, cc.Texture2D.PixelFormat.RGBA32F, 360, 270);
this.textures[e] = a;
},
addSprite: function(e) {
this.uids.add(e);
this.createTexture(e);
var a = this.sprites[e];
console.log("[Agora] js addSprite " + e);
if (null == a) {
var o = new cc.SpriteFrame();
o.setTexture(this.textures[e]);
var r = new cc.Node("Sprite");
(a = r.addComponent(cc.Sprite)).spriteFrame = o;
r.x = 0;
r.y = 0;
r.setContentSize(this.headerW, this.headerH);
r.parent = this.node;
this.sprites[e] = a;
this.updateHeadersDisplay();
console.log("[Agora] js addSprite new Sprite for user " + e);
}
},
removeSprite: function(e) {
if (null != this.sprites[e]) {
this.sprites[e].node.destroy();
delete this.sprites[e];
delete this.textures[e];
this.uids.delete[e];
}
},
updateHeadersDisplay: function() {
var e = cc.director.getWinSize(), a = -e.width / 2, o = -e.height / 2, r = 0;
for (var t in this.sprites) {
console.log("[Agora] js updateHeadersDisplay " + t);
var n = this.sprites[t].node;
if (t == this.localUid) ; else {
n.anchorX = 0;
n.anchorY = 0;
n.x = r * this.headerW + r * this.headerOffset + a;
n.y = o;
r++;
console.log("[Agora] js updateHeadersDisplay  x = " + n.x + " ,y = " + n.y);
}
}
}
});
cc._RF.pop();
}, {} ],
js_agora: [ function(e, a, o) {
"use strict";
cc._RF.push(a, "b8c3dahMdhOW6LKceMuULRU", "js_agora");
(function() {
window.agora = new cc.EventTarget();
agora.startTime = null;
if ("undefined" != typeof agoraCreator) {
null == agora.agoraCreatorInst && (agora.agoraCreatorInst = new agoraCreator());
agora.init = function(e) {
agora.agoraCreatorInst.initialize(e);
agora.agoraCreatorInst.onJoinChannelSuccess = function(e, a, o) {
agora.startTime = new Date();
cc.log("Agora(Native platform) service start using time : " + agora.startTime.toString());
agora.emit("join-channel-success", e, a, o);
};
agora.agoraCreatorInst.onRejoinChannelSuccess = function(e, a, o) {
agora.emit("rejoin-channel-success", e, a, o);
};
agora.agoraCreatorInst.onWarning = function(e, a) {
agora.emit("warning", e, a);
};
agora.agoraCreatorInst.onError = function(e, a) {
agora.emit("error", e, a);
};
agora.agoraCreatorInst.onAudioQuality = function(e, a, o, r) {
agora.emit("audio-quality", e, a, o, r);
};
agora.agoraCreatorInst.onAudioVolumeIndication = function(e, a, o) {
agora.emit("audio-volume-indication", e, a, o);
};
agora.agoraCreatorInst.onLeaveChannel = function(e) {
var a = new Date();
cc.log("Agora(Native platform) service stop use time : " + a.toString());
var o = a - agora.startTime;
cc.log("Agora(Native platform) service used time(s) ： " + Math.floor(o / 1e3));
agora.emit("leave-channel", e);
};
agora.agoraCreatorInst.onNetworkQuality = function(e, a, o) {
agora.emit("network-quality", e, a, o);
};
agora.agoraCreatorInst.onUserJoined = function(e, a) {
agora.emit("user-joined", e, a);
};
agora.agoraCreatorInst.onUserOffline = function(e, a) {
agora.emit("user-offline", e, a);
};
agora.agoraCreatorInst.onUserMuteAudio = function(e, a) {
agora.emit("user-mute-audio", e, a);
};
agora.agoraCreatorInst.onAudioRoutingChanged = function(e) {
agora.emit("audio-routing-changed", e);
};
agora.agoraCreatorInst.onConnectionLost = function() {
agora.emit("connection-lost");
};
agora.agoraCreatorInst.onConnectionInterrupted = function() {
agora.emit("connection-interrupted");
};
agora.agoraCreatorInst.onRequestToken = function() {
agora.emit("request-token");
};
agora.agoraCreatorInst.onConnectionBanned = function() {
agora.emit("connection-banned");
};
agora.agoraCreatorInst.onClientRoleChanged = function(e, a) {
agora.emit("client-role-changed", e, a);
};
};
agora.setChannelProfile = function(e) {
return agora.agoraCreatorInst.setChannelProfile(e);
};
agora.setClientRole = function(e) {
return agora.agoraCreatorInst.setClientRole(e);
};
agora.joinChannel = function(e, a, o, r) {
return agora.agoraCreatorInst.joinChannel(e, a, o, r);
};
agora.leaveChannel = function() {
return agora.agoraCreatorInst.leaveChannel();
};
agora.enableAudio = function() {
return agora.agoraCreatorInst.enableAudio();
};
agora.disableAudio = function() {
return agora.agoraCreatorInst.disableAudio();
};
agora.muteLocalAudioStream = function(e) {
return agora.agoraCreatorInst.muteLocalAudioStream(e);
};
agora.enableLocalAudio = function(e) {
return agora.agoraCreatorInst.enableLocalAudio(e);
};
agora.muteAllRemoteAudioStreams = function(e) {
return agora.agoraCreatorInst.muteAllRemoteAudioStreams(e);
};
agora.muteRemoteAudioStream = function(e, a) {
return agora.agoraCreatorInst.muteRemoteAudioStream(e, a);
};
agora.adjustRecordingSignalVolume = function(e) {
return agora.agoraCreatorInst.adjustRecordingSignalVolume(e);
};
agora.adjustPlaybackSignalVolume = function(e) {
return agora.agoraCreatorInst.adjustPlaybackSignalVolume(e);
};
agora.setDefaultAudioRouteToSpeakerphone = function(e) {
agora.agoraCreatorInst.setDefaultAudioRouteToSpeakerphone(e);
};
agora.setParameters = function(e) {
agora.agoraCreatorInst.setParameters(e);
};
agora.getVersion = function() {
return agora.agoraCreatorInst.getVersion();
};
agora.setLogFile = function(e) {
return agora.agoraCreatorInst.setLogFile(e);
};
agora.setLogFilter = function(e) {
return agora.agoraCreatorInst.setLogFilter(e);
};
agora.enableVideoObserver = function() {
return agora.agoraCreatorInst.enableVideoObserver();
};
agora.enableVideo = function() {
return agora.agoraCreatorInst.enableVideo();
};
agora.updateTexture = function(e, a) {
return agora.agoraCreatorInst.updateTexture(e, a);
};
agora.setVideoProfile = function(e) {
return agora.agoraCreatorInst.setVideoProfile(e);
};
}
})();
cc._RF.pop();
}, {} ]
}, {}, [ "HelloWorld", "js_agora" ]);