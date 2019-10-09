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
        headerOffset: 10,
    },
    onLoad: function () {
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
        setInterval(this.getTexture.bind(this), 2000);
        // setInterval(this.getAudioLevel.bind(this), 2000);
        // setInterval(this.getNetworkQuality.bind(this), 2000);
    },
    getTexture: function () {
        // console.log("setTimeout getTexture");
        for(var uid of this.uids){
            var t = this.agoraClient.getTexture(uid);
            this.updateTexture(uid, t);
        }
    },
    getAudioLevel: function () {
        for(var uid of this.uids){
            var audioLevel = this.agoraClient.getAudioLevel(uid);
            console.log("uid = " + uid + "----audioLevel = " + audioLevel);
        }
    },
    getStats: function () {
        var stats = this.agoraClient.getStats();
        console.log("duration = " + stats.duration);
        console.log("txBytes = " + stats.txBytes);
        console.log("rxBytes = " + stats.rxBytes);
        console.log("txAudioKBitrate = " + stats.txAudioKBitrate);
        console.log("rxAudioKBitrate = " + stats.rxAudioKBitrate);
        console.log("txVideoKBitrate = " + stats.txVideoKBitrate);
        console.log("rxVideoKBitrate = " + stats.rxVideoKBitrate);
        console.log("userCount = " + stats.userCount);
        console.log("cpuAppUsage = " + stats.cpuAppUsage);
        console.log("cpuTotalUsage = " + stats.cpuTotalUsage);
        console.log("sentBitrate = " + stats.sentBitrate);
        console.log("sentFrameRate = " + stats.sentFrameRate);
        var obj = stats.clients;
        for(var p in obj) {
            console.log("uid = " + obj[p].uid);
            console.log("width = " + obj[p].width);
            console.log("height = " + obj[p].height);
            console.log("receivedBitrate = " + obj[p].receivedBitrate);
            console.log("receivedFrameRate = " + obj[p].receivedFrameRate);
        }
    },
    getNetworkQuality: function () {
        var networkQuality = this.agoraClient.getNetworkQuality(0);
        console.log("uid = " + networkQuality.uid);
        console.log("txquality = " + networkQuality.txquality);
        console.log("rxquality = " + networkQuality.rxquality);
    },
    onJoin: function () {
        this.agoraClient.join(this.appId.string, this.channelName.string, 100000, "370P_9", 0, 1, 1);
    },
    onUnmuteLocalVideo: function () {
        this.agoraClient.unmuteLocalVideo();
    },
    onMuteLocalVideo: function () {
        this.agoraClient.muteLocalVideo();
    },
    onUnmuteLocalAudio: function () {
        this.agoraClient.unmuteLocalAudio();
    },
    onMuteLocalAudio: function () {
        this.agoraClient.muteLocalAudio();
    },
    onUnmuteRemoteVideo: function () {
        var uid = parseInt(this.eb.string);
        this.agoraClient.unmuteRemoteVideo(uid);
    },
    onMuteRemoteVideo: function () {
        var uid = parseInt(this.eb.string);
        this.agoraClient.muteRemoteVideo(uid);
    },
    onUnmuteRemoteAudio: function () {
        var uid = parseInt(this.eb.string);
        this.agoraClient.unmuteRemoteAudio(uid);
    },
    onMuteRemoteAudio: function () {
        var uid = parseInt(this.eb.string);
        this.agoraClient.muteRemoteAudio(uid);
    },
    onLeave: function () {
        this.agoraClient.leave();
    },
    onLocalJoinCallback: function(res) {
        console.log("onLocalJoinCallback");
        console.log(res);
        var obj = JSON.parse(res);
        this.localUid = parseInt(obj.data.uid);
    },
    onMuteLocalAudioCallback: function(res) {
        // console.log("onMuteLocalAudioCallback");
        // console.log(res);
        // this.uids.add(this.localUid);
    },
    onUnmuteLocalAudioCallback: function(res) {
        // console.log("onUnmuteLocalAudioCallback");
        // console.log(res);
        // this.uids.add(this.localUid);
    },
    onMuteLocalVideoCallback: function(res) {
        console.log("onMuteLocalVideoCallback");
        console.log(res);
        this.uids.delete(this.localUid);
        var sp = this.sprites[this.localUid];
        if (sp != null) {
            delete this.sprites[this.localUid];
            sp.node.removeFromParent();
            this.updateHeadersDisplay();
        }
    },
    onUnmuteLocalVideoCallback: function(res) {
        console.log("onUnmuteLocalVideoCallback");
        console.log(res);
        this.uids.add(this.localUid);
    },
    onMuteRemoteVideoCallback: function(res) {
        console.log("onUnmuteRemoteVideoCallback");
        console.log(res);
        var obj = JSON.parse(res);
        this.uids.delete(obj.data.uid);
        var sp = this.sprites[obj.data.uid];
        if (sp != null) {
            delete this.sprites[obj.data.uid];
            sp.node.removeFromParent();
            this.updateHeadersDisplay();
        }
    },
    onUnmuteRemoteVideoCallback: function(res) {
        console.log("onMuteRemoteVideoCallback");
        console.log(res);
        var obj = JSON.parse(res);
        this.uids.add(obj.data.uid);
    },
    onMuteRemoteAudioCallback: function(res) {
        console.log("onMuteRemoteAudioCallback");
        console.log(res);
    },
    onUnmuteRemoteAudioCallback: function(res) {
        console.log("onUnmuteRemoteAudioCallback");
        console.log(res);
    },
    onLocalLeaveCallback: function(res) {
        this.localUid = null;
        for(var uid in this.sprites){
            var sprite = this.sprites[uid];
            sprite.node.removeFromParent();
        }
        this.sprites = {};
    },
    onRemoteLeaveCallback: function(uid) {
        console.log("uid=" + uid + "离开了");
        this.uids.delete(uid);
        var sp = this.sprites[uid];
        if (sp != null) {
            sp.node.removeFromParent(true);
            delete this.sprites[uid];
            this.updateHeadersDisplay();
        }
    },
    onRemoteJoinCallback: function (uid) {
        console.log("uid=" + uid + "上线了");
        this.eb.string = uid + "";
        // this.uids.add(uid);
    },
    updateTexture: function (uid, texture) {
        var sp = this.sprites[uid];
        if (sp == null) {
            console.log("uid=" + uid + "创建Sprite");
            var spriteFrame = new cc.SpriteFrame();
            spriteFrame.setTexture(texture);
            var node = new cc.Node('Sprite');
            sp = node.addComponent(cc.Sprite);
            sp.spriteFrame = spriteFrame;
            node.x = 0;
            node.y = 0;
            node.setContentSize(this.headerW, this.headerH);
            node.parent = this.node;
            // this.agoraClient.addHeader(uid, sp);
            this.sprites[uid] = sp;
            this.updateHeadersDisplay();
        } else {
            //更新帧数据
            sp.spriteFrame.setTexture(texture);
            sp.node.setContentSize(this.headerW, this.headerH);
        }
    },
    updateHeadersDisplay: function () {
        var size = cc.director.getWinSize();
        var originX = -(size.width/2);
        var originY = -(size.height/2);
        var xOffset = 0;
        for(var uid in this.sprites){
            var sprite = this.sprites[uid];
            var node = sprite.node;
            if (uid == this.localUid) {
                node.anchorX = 0;
                node.anchorY = 0;
                node.x = size.width/2 - this.headerW;
                node.y = size.height/2 - this.headerH;
            } else {
                node.anchorX = 0;
                node.anchorY = 0;
                node.x = xOffset * this.headerW + xOffset * this.headerOffset + originX;
                node.y = originY;
                xOffset++;
            }
        }
    },
});
