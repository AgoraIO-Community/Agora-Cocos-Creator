(function() {
    console.log("init agoraEngine");
    window.agoraEngine = new cc.EventTarget();
    window.agoraCallbackChannel = new cc.EventTarget();
    agoraEngine.initialize = function (appId) {
        agoraEngine.emit('initialize', appId);
    };

    agoraEngine.setRenderMode = function (renderMode) {
        agoraEngine.emit("setRenderMode", renderMode);
    };

    agoraEngine.setupLocalVideo = function (view) {
        agoraEngine.emit("setupLocalVideo", view);
    };

    agoraEngine.joinChannel = function (token, channelId, info, uid) {
        agoraEngine.emit('joinChannel', [token, channelId, info, uid]);
    };

    agoraEngine.muteVideoStream = function (mute) {
        agoraEngine.emit("muteVideoStream", mute);
    };

    agoraEngine.muteAudioStream = function (mute) {
        agoraEngine.emit("muteAudioStream", mute);
    };

    agoraEngine.setupRemoteVideo = function (uid, view) {
        agoraEngine.emit("setupRemoteVideo", [uid, view]);
    };
})();