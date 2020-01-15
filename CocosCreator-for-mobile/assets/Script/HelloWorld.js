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
        headerOffset: 20,
    },
    onLoad: function () {
        var appId = #YOUR_APPID;
        var sprites = {};
        this.sprites = sprites;
        const uids = new Set();
        this.uids = uids;
        this.uids.add(0);
        this.agoraInst = new agoraCreator();
        this.agoraInst.initialize(appId);
        this.agoraInst.enableVideo();
        this.agoraInst.enableVideoObserver();
        this.agoraInst.joinChannel("", "10011", "", 0);

        this.agoraInst.onLeaveChannel = function (rtcStats) {
            console.log("[Agora] js  onLeaveChannel");
        };

        this.agoraInst.onJoinChannelSuccess = function (channelName, uid, elapsed) {
            console.log("[Agora] js  onJoinChannelSuccess");
        };

        this.agoraInst.onUserJoined = function (uid, elapsed) {
            uids.add(uid);
            console.log("[Agora] js onUserJoined uid = %d", uid);
        };

        this.agoraInst.onUserOffline = function (uid, reason) {
            uids.delete(uid);
            sprites[uid] = null;
            console.log("[Agora] js onUserOffline uid = %d", uid);
        };

        setInterval(this.getTexture.bind(this), 40);
    },

    getTexture: function () {
        console.log("[Agora] js getTexture");
        var e = !0, t = !1, o = void 0;
        try {
            for (var i, a = this.uids[Symbol.iterator](); !(e = (i = a.next()).done); e = !0) {
                var l = i.value, n = this.agoraInst.updateTexture(l);
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

    updateTexture: function (uid, texture) {
        var r = this.sprites[uid];
        if (null == r) {
            var n = new cc.SpriteFrame();
            n.setTexture(texture);
            var a = new cc.Node("Sprite");
            (r = a.addComponent(cc.Sprite)).spriteFrame = n;
            a.x = 0;
            a.y = 0;
            a.setContentSize(this.headerW, this.headerH);
            a.parent = this.node;
            this.sprites[uid] = r;
            this.updateHeadersDisplay();
        } else {
            r.spriteFrame.setTexture(texture);
            r.node.setContentSize(this.headerW, this.headerH);
        }
    },

    updateHeadersDisplay: function () {
        var e = cc.director.getWinSize(), t = -e.width / 2, r = -e.height / 2, n = 0;
        for (var a in this.sprites) {
            if (this.sprites[a] != null)
            {
                var i = this.sprites[a].node;
                if (a == 0) {
                    i.anchorX = 0;
                    i.anchorY = 0;
                    i.x = e.width / 2 - this.headerW;
                    i.y = e.height / 2 - this.headerH;
                } else {
                    i.anchorX = 0;
                    i.anchorY = 0;
                    i.x = n * this.headerW + n * this.headerOffset + t;
                    i.y = r;
                    n++;
                }
            }
        }
    }
});