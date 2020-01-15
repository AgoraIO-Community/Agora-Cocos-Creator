import {
    join
} from "path";
cc.Class({
    extends: cc.Component,

    properties: {
        label: {
            default: null,
            type: cc.Label
        },

        muteVideoBtn: {
            default: null,
            type: cc.Button
        },

        muteVideoLabel: {
            default: null,
            type: cc.Label
        },

        muteAudioBtn: {
            default: null,
            type: cc.Button
        },

        muteAudioLabel: {
            default: null,
            type: cc.Label,
        },

        muteVideoFlag: false,
        muteAudioFlag: false,
        appId: "",
        tag: "Agora_Log",
    },

    // use this for initialization
    onLoad: function () {
        this.initAgoraEvents(true);
        this.initClickEvents(true);
        agoraEngine.initialize(#YOUR_APPID);
        agoraEngine.setRenderMode(1);
        agoraEngine.setupLocalVideo("LocalVideoDiv");
        agoraEngine.joinChannel("", "1223", "", 0);
    },

    onDestroy: function() {
        this.initAgoraEvents(false);
        this.initClickEvents(false);
    },

    initClickEvents: function(initFlag) {
        if (initFlag) {
            this.muteVideoBtn.node.on('click', this.onMuteVideoClick, this);
            this.muteAudioBtn.node.on('click', this.OnMuteAudioClick, this);
        } else {
            this.muteVideoBtn.node.off('click', this.onMuteVideoClick, this);
            this.muteAudioBtn.node.off('click', this.OnMuteAudioClick, this);
        }
    },

    initAgoraEvents: function (initFlag) {
        if (agoraEngine && initFlag && agoraCallbackChannel) {
            agoraCallbackChannel.on('join-channel-success', this.onJoinChannelSuccess, this);
            agoraCallbackChannel.on('leave-channel', this.onLeaveChannel, this);
            agoraCallbackChannel.on('rejoin-channel-success', this.onRejoinChannelSuccess, this);
            agoraCallbackChannel.on('user-joined', this.onUserJoined, this);
            agoraCallbackChannel.on('user-offline', this.onUserOffline, this);
            agoraCallbackChannel.on('warning', this.onWarning, this);
            agoraCallbackChannel.on('error', this.onError, this);
        } else if (agoraEngine && !initFlag && agoraCallbackChannel) {
            agoraCallbackChannel.off('join-channel-success', this.onJoinChannelSuccess, this);
            agoraCallbackChannel.off('leave-channel', this.onLeaveChannel, this);
            agoraCallbackChannel.off('rejoin-channel-success', this.onRejoinChannelSuccess, this);
            agoraCallbackChannel.off('user-joined', this.onUserJoined, this);
            agoraCallbackChannel.off('user-offline', this.onUserOffline, this);
            agoraCallbackChannel.off('warning', this.onWarning, this);
            agoraCallbackChannel.off('error', this.onError, this);
        }
    },

    onMuteVideoClick: function() {
        this.muteVideoFlag = !this.muteVideoFlag;
        agoraEngine.muteVideoStream(this.muteVideoFlag);
        this.updateMuteVideoBtnUI();
        this.printfLog(this.tag, "onMuteVideoClick " + this.muteVideoFlag);
    },
    
    OnMuteAudioClick: function() {
        this.muteAudioFlag = !this.muteAudioFlag;
        agoraEngine.muteAudioStream(this.muteAudioFlag);
        this.updateMuteAudioBtnUI();
        this.printfLog(this.tag, "OnMuteAudioClick " + this.muteAudioFlag);
    },

    updateMuteAudioBtnUI: function() {
        this.printfLog(this.tag, "updateMuteAudioBtnUI");
        if (this.muteAudioFlag) {
            this.muteAudioLabel.string = "UnMuteAudio";
        } else {
            this.muteAudioLabel.string = "MuteAudio";
        }
    },

    updateMuteVideoBtnUI: function() {
        this.printfLog(this.tag, "updateMuteVideoBtnUI");
        if (this.muteVideoFlag) {
            this.muteVideoLabel.string = "UnMuteVideo";
        } else {
            this.muteVideoLabel.string = "MuteVideo";
        }
    },

    onUserJoined: function (event) {
        this.printfLog(this.tag, "receive message onUserJoined uid = " + event.detail[0] + " ,elapsed = " + event.detail[1]);
        agoraEngine.setupRemoteVideo(event.detail[0], "RemoteVideoDiv");
    },

    onUserOffline: function (event) {
        this.printfLog(this.tag, "receive message onUserOffline uid = " + event.detail[0] + " ,elapsed = " + event.detail[1]);
    },

    onJoinChannelSuccess: function (event) {
        this.printfLog(this.tag, "onJoinChannelSuccess channel = " + event.detail[0] + " ,uid = " + event.detail[1]);
    },

    onLeaveChannel: function (event) {
        this.printfLog(this.tag, "onLeaveChannel");
    },

    onRejoinChannelSuccess: function (event) {
        this.printfLog(this.tag, "onRejoinChannelSuccess channel = " + event.detail[0] + " ,uid = " + event.detail[1]);
    },

    onWarning: function (event) {
        this.printfLog(this.tag, "onWarning warn = " + event.detail[0] + " ,msg = " + event.detail[1]);
    },

    onError: function (event) {
        this.printfLog(this.tag, "onError warn = " + event.detail[0] + " ,msg = " + event.detail[1]);
    },

    printfLog: function(tag, message) {
        cc.log(tag + " " + message);
    }
});
