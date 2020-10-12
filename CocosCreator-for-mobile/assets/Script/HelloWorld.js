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
    },

    onLoad: function () {
        var appId = #YOUR_APPID;
        this.sprites = {};
        this.textures = {};
        const uids = new Set();
        this.uids = uids;
        agora && agora.init(appId);
        agora.setParameters("{\"rtc.log_filter\": 65535}");
        agora.setChannelProfile(0);
        agora.enableVideo();
        agora.enableVideoObserver();
        this.addSprite(this.localUid);
        this.initAgoraEvents();
        agora.joinChannel("", "1001", "", 0);
        console.log("[Agora] js cc.log console joinChannel");
        setInterval(this.updateTexture.bind(this), 40);
    },

    update: function (dt) {

    },

    onDestroy: function () {
        this.uninitAgoraEvents();
    },

    updateTexture() {
        var e = !0;
        for (var i, a = this.uids[Symbol.iterator](); !(e = (i = a.next()).done); e = !0) {
            var uid = i.value;
            if (this.textures[uid] != null) {
                var handler = this.textures[uid].getImpl().getHandle();
                agora.updateTexture(handler, uid);
            }
        }
    },

    initAgoraEvents: function() {
        agora.on('join-channel-success', this.onJoinChannelSuccess, this);
        agora.on('leave-channel', this.onLeaveChannel, this);
        agora.on('user-joined', this.onUserJoined, this);
        agora.on('user-offline', this.onUserOffline, this);
    },

    unInitAgoraEvents: function() {
        agora.off('join-channel-success', this.onJoinChannelSuccess);
        agora.off('leave-channel', this.onLeaveChannel);
        agora.off('user-joined', this.onUserJoined);
        agora.off('user-offline', this.onUserOffline);
    },

    onJoinChannelSuccess: function (channel, uid, elapsed) {
        console.log("[Agora] js onJoinChannelSuccess channel = " + channel + " ,uid = " + uid);
    },

    onLeaveChannel: function (stat) {
        console.log("[Agora] js onLeaveChannel ");
    },

    onUserJoined: function (uid, elapsed) {
        console.log("[Agora] js onUserJoined ");
        this.addSprite(uid);
    },

    onUserOffline: function (uid, reason) {
        this.removeSprite(uid);
    },

    createTexture: function(uid) {
        console.log("[Agora] js createTexture " + uid);
        var texture = new cc.Texture2D();
        texture.initWithData(null, cc.Texture2D.PixelFormat.RGBA32F, 360, 270);
        this.textures[uid] = texture;
    },

    addSprite: function(uid) {
        this.uids.add(uid);
        this.createTexture(uid);
        var sprite = this.sprites[uid];
        console.log("[Agora] js addSprite " + uid);
        if (sprite == null) {
            var spriteFrame = new cc.SpriteFrame();
            spriteFrame.setTexture(this.textures[uid]);
            var a = new cc.Node("Sprite");
            (sprite = a.addComponent(cc.Sprite)).spriteFrame = spriteFrame;
            a.x = 0;
            a.y = 0;
            a.setContentSize(this.headerW, this.headerH);
            a.parent = this.node;
            this.sprites[uid] = sprite;
            this.updateHeadersDisplay();
            console.log("[Agora] js addSprite new Sprite for user " + uid);
        }
    },

    removeSprite: function(uid) {
        if (this.sprites[uid] != null)
        {
            var node = this.sprites[uid].node;
            node.destroy();
            delete this.sprites[uid];
            delete this.textures[uid];
            this.uids.delete[uid];
        }
    },

    updateHeadersDisplay: function() {
        var screen = cc.director.getWinSize();
        var screenWidth = -screen.width / 2;
        var screenHeight = -screen.height / 2;
        var i = 0;
        for (var uid in this.sprites) {
            console.log("[Agora] js updateHeadersDisplay " + uid);
            var l = this.sprites[uid].node;
            if (uid == this.localUid) {
            } else {
                l.anchorX = 0;
                l.anchorY = 0;
                l.x = i * this.headerW + i * this.headerOffset + screenWidth;
                l.y = screenHeight;
                i++;
                console.log("[Agora] js updateHeadersDisplay  x = " + l.x + " ,y = " + l.y);
            }
        }
    }
  });
