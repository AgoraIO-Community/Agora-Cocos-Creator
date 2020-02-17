(function () {
    window.agora = new cc.EventTarget();
    agora.startTime = null;
    if ((typeof agoraCreator) !== "undefined") {
        if (agora.agoraCreatorInst == null) agora.agoraCreatorInst = new agoraCreator();
        agora.init = function (appid) {
            agora.agoraCreatorInst.initialize(appid);
            agora.agoraCreatorInst.onJoinChannelSuccess = function (channel, uid, elapsed) {
                agora.startTime = new Date();
                cc.log('Agora(Native platform) service start using time : ' + agora.startTime.toString());
                agora.emit('join-channel-success', channel, uid, elapsed);
            };
            agora.agoraCreatorInst.onRejoinChannelSuccess = function (channel, uid, elapsed) {
                agora.emit('rejoin-channel-success', channel, uid, elapsed);
            };
            agora.agoraCreatorInst.onWarning = function (warn, msg) {
                agora.emit('warning', warn, msg);
            };
            agora.agoraCreatorInst.onError = function (err, msg) {
                agora.emit('error', err, msg);
            };
            agora.agoraCreatorInst.onAudioQuality = function (uid, quality, delay, lost) {
                agora.emit('audio-quality', uid, quality, delay, lost);
            };
            agora.agoraCreatorInst.onAudioVolumeIndication = function (speakers, speakerNumber, totalVolume) {
                agora.emit('audio-volume-indication', speakers, speakerNumber, totalVolume);
            };
            agora.agoraCreatorInst.onLeaveChannel = function (stat) {
                var endTime = new Date();
                cc.log('Agora(Native platform) service stop use time : ' + endTime.toString());
                let usedTime = endTime - agora.startTime;
                cc.log('Agora(Native platform) service used time(s) ： ' + Math.floor(usedTime / 1000));
                agora.emit('leave-channel', stat);
            };
            agora.agoraCreatorInst.onNetworkQuality = function (uid, txQuality, rxQuality) {
                agora.emit('network-quality', uid, txQuality, rxQuality);
            };
            agora.agoraCreatorInst.onUserJoined = function (uid, elapsed) {
                agora.emit('user-joined', uid, elapsed);
            };
            agora.agoraCreatorInst.onUserOffline = function (uid, reason) {
                agora.emit('user-offline', uid, reason);
            };
            agora.agoraCreatorInst.onUserMuteAudio = function (uid, muted) {
                agora.emit('user-mute-audio', uid, muted);
            };
            agora.agoraCreatorInst.onAudioRoutingChanged = function (routing) {
                agora.emit('audio-routing-changed', routing);
            };
            agora.agoraCreatorInst.onConnectionLost = function () {
                agora.emit('connection-lost');
            };
            agora.agoraCreatorInst.onConnectionInterrupted = function () {
                agora.emit('connection-interrupted');
            };
            agora.agoraCreatorInst.onRequestToken = function () {
                agora.emit('request-token');
            };
            agora.agoraCreatorInst.onConnectionBanned = function () {
                agora.emit('connection-banned');
            };
            agora.agoraCreatorInst.onClientRoleChanged = function (oldRole, newRole) {
                agora.emit('client-role-changed', oldRole, newRole);
            };
        };
        agora.setChannelProfile = function (profile) {
            return agora.agoraCreatorInst.setChannelProfile(profile);
        };
        agora.setClientRole = function (role) {
            return agora.agoraCreatorInst.setClientRole(role);
        };
        agora.joinChannel = function (token, channelId, info, uid) {
            return agora.agoraCreatorInst.joinChannel(token, channelId, info, uid);
        };
        agora.leaveChannel = function () {
            return agora.agoraCreatorInst.leaveChannel();
        };
        agora.enableAudio = function () {
            return agora.agoraCreatorInst.enableAudio();
        };
        agora.disableAudio = function () {
            return agora.agoraCreatorInst.disableAudio();
        };
        agora.muteLocalAudioStream = function (mute) {
            return agora.agoraCreatorInst.muteLocalAudioStream(mute);
        };
        agora.enableLocalAudio = function (enabled) {
            return agora.agoraCreatorInst.enableLocalAudio(enabled);
        };
        agora.muteAllRemoteAudioStreams = function (mute) {
            return agora.agoraCreatorInst.muteAllRemoteAudioStreams(mute);
        };
        agora.muteRemoteAudioStream = function (uid, mute) {
            return agora.agoraCreatorInst.muteRemoteAudioStream(uid, mute);
        };
        agora.adjustRecordingSignalVolume = function (volume) {
            return agora.agoraCreatorInst.adjustRecordingSignalVolume(volume);
        };
        agora.adjustPlaybackSignalVolume = function (volume) {
            return agora.agoraCreatorInst.adjustPlaybackSignalVolume(volume);
        };
        agora.setDefaultAudioRouteToSpeakerphone = function (bVal) { //？
            agora.agoraCreatorInst.setDefaultAudioRouteToSpeakerphone(bVal);
        };
        agora.setParameters = function (profile) { //？
            agora.agoraCreatorInst.setParameters(profile);
        };
        agora.getVersion = function () {
            return agora.agoraCreatorInst.getVersion();
        };
        agora.setLogFile = function (filePath) {
            return agora.agoraCreatorInst.setLogFile(filePath);
        };
        agora.setLogFilter = function (filter) {
            return agora.agoraCreatorInst.setLogFilter(filter);
        };
        agora.enableVideoObserver = function() {
            return agora.agoraCreatorInst.enableVideoObserver();
        };
        agora.enableVideo = function() {
            return agora.agoraCreatorInst.enableVideo();
        };
        agora.updateTexture = function(handler, uid) {
            return agora.agoraCreatorInst.updateTexture(handler, uid);
        };
        agora.setVideoProfile = function(profile) {
            return agora.agoraCreatorInst.setVideoProfile(profile);
        };
    }
})();
