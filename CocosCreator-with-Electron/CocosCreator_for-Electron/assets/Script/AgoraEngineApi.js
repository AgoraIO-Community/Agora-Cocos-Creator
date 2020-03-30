(function() {
    console.log("init agoraEngine");
    window.agoraEngine = new cc.EventTarget();
    window.agoraCallbackChannel = new cc.EventTarget();
    agoraEngine.initialize = function (appId) {
        console.log("AgoraEngineApi initialize " + appId);
        agoraEngine.emit('initialize', appId);
    };

    agoraEngine.setRenderMode = function (renderMode) {
        console.log("AgoraEngineApi setRenderMode " + renderMode);
        agoraEngine.emit("setRenderMode", renderMode);
    };

    agoraEngine.setupLocalVideo = function (view) {
        console.log("AgoraEngineApi setRenderMode " + view);
        agoraEngine.emit("setupLocalVideo", view);
    };

    agoraEngine.joinChannel = function (token, channelId, info, uid) {
        console.log("AgoraEngineApi joinChannel " + channelId);
        agoraEngine.emit('joinChannel', token, channelId, info, uid);
    };

    agoraEngine.muteVideoStream = function (mute) {
        console.log("AgoraEngineApi muteVideoStream " + mute);
        agoraEngine.emit("muteVideoStream", mute);
    };

    agoraEngine.muteAudioStream = function (mute) {
        console.log("AgoraEngineApi muteAudioStream " + mute);
        agoraEngine.emit("muteAudioStream", mute);
    };

    agoraEngine.setupRemoteVideo = function (uid, view) {
        console.log("AgoraEngineApi muteAudioStream uid" + uid);
        agoraEngine.emit("setupRemoteVideo", [uid, view]);
    };
})();