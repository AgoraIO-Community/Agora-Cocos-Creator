require = function e(t, r, n) {
function a(i, s) {
if (!r[i]) {
if (!t[i]) {
var l = "function" == typeof require && require;
if (!s && l) return l(i, !0);
if (o) return o(i, !0);
var d = new Error("Cannot find module '" + i + "'");
throw d.code = "MODULE_NOT_FOUND", d;
}
var h = r[i] = {
exports: {}
};
t[i][0].call(h.exports, function(e) {
var r = t[i][1][e];
return a(r || e);
}, h, h.exports, e, t, r, n);
}
return r[i].exports;
}
for (var o = "function" == typeof require && require, i = 0; i < n.length; i++) a(n[i]);
return a;
}({
HelloWorld: [ function(e, t, r) {
"use strict";
cc._RF.push(t, "280c3rsZJJKnZ9RqbALVwtK", "HelloWorld");
cc.Class({
extends: cc.Component,
properties: {
agoraClient: {
default: null,
type: Object
},
agoraInst: {
default: null,
type: Object
},
sprites: {
default: null,
type: Object
},
uids: {
default: null,
type: Object
},
agoraTag: "[Agora] js",
headerW: 280,
headerH: 210,
headerOffset: 20
},
onLoad: function() {
var e = {};
this.sprites = e;
var t = new Set();
this.uids = t;
this.uids.add(0);
this.agoraInst = new agoraCreator();
this.agoraInst.initialize("5db0d12c40354100abd7a8a0adaa1fb8");
this.agoraInst.enableVideo();
this.agoraInst.enableVideoObserver();
this.agoraInst.joinChannel("", "10011", "", 0);
this.agoraInst.onLeaveChannel = function(e) {
console.log("[Agora] js  onLeaveChannel");
};
this.agoraInst.onJoinChannelSuccess = function(e, t, r) {
console.log("[Agora] js  onJoinChannelSuccess");
};
this.agoraInst.onUserJoined = function(e, r) {
t.add(e);
console.log("[Agora] js onUserJoined uid = %d", e);
};
this.agoraInst.onUserOffline = function(r, n) {
t.delete(r);
e[r] = null;
console.log("[Agora] js onUserOffline uid = %d", r);
};
setInterval(this.getTexture.bind(this), 40);
},
getTexture: function() {
console.log("[Agora] js getTexture");
var e = !0, t = !1, r = void 0;
try {
for (var n, a = this.uids[Symbol.iterator](); !(e = (n = a.next()).done); e = !0) {
var o = n.value, i = this.agoraInst.updateTexture(o);
this.updateTexture(o, i);
}
} catch (e) {
t = !0;
r = e;
} finally {
try {
!e && a.return && a.return();
} finally {
if (t) throw r;
}
}
},
updateTexture: function(e, t) {
var r = this.sprites[e];
if (null == r) {
console.log("uid=" + e + "创建Sprite");
var n = new cc.SpriteFrame();
n.setTexture(t);
var a = new cc.Node("Sprite");
(r = a.addComponent(cc.Sprite)).spriteFrame = n;
a.x = 0;
a.y = 0;
a.setContentSize(this.headerW, this.headerH);
a.parent = this.node;
this.sprites[e] = r;
this.updateHeadersDisplay();
} else {
r.spriteFrame.setTexture(t);
r.node.setContentSize(this.headerW, this.headerH);
}
},
updateHeadersDisplay: function() {
var e = cc.director.getWinSize(), t = -e.width / 2, r = -e.height / 2, n = 0;
for (var a in this.sprites) {
var o = this.sprites[a].node;
if (0 == a) {
o.anchorX = 0;
o.anchorY = 0;
o.x = e.width / 2 - this.headerW;
o.y = e.height / 2 - this.headerH;
} else {
o.anchorX = 0;
o.anchorY = 0;
o.x = n * this.headerW + n * this.headerOffset + t;
o.y = r;
n++;
}
}
}
});
cc._RF.pop();
}, {} ]
}, {}, [ "HelloWorld" ]);