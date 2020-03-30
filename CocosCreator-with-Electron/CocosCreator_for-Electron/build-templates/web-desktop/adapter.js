(function() {
  console.log("init agoraEngine");

  if(!window.agoraEngine) {
    console.error("no agoraEngine found")
    return
  }

  let AgoraRtcEngine
  try {
    AgoraRtcEngine = require("agora-electron-sdk").default
  } catch(e) {
    console.error(e.message)
  }

  if(!AgoraRtcEngine) {
    console.error(`failed to load AgoraRtcEngine`)
    return
  }

  let rtcApiChannel = window.agoraEngine
  let rtcCallbackChannel = window.agoraCallbackChannel
  let rtcEngine = new AgoraRtcEngine()

  rtcApiChannel.on("initialize", (appid) => {
    console.log("initialize appid = " + appid);
    rtcEngine.initialize(appid)
  })

  rtcApiChannel.on("setRenderMode", (mode) => {
    console.log("setRenderMode mode = " + mode);
    rtcEngine.setRenderMode(mode)
  })

  rtcApiChannel.on("joinChannel", (token, channelId, info, uid) => {
    console.log("joinChannel channel = " + channelId);
    rtcEngine.joinChannel(token, channelId, info, uid)
  })

  rtcApiChannel.on("setupLocalVideo", (view) => {
    console.log("setupLocalVideo view = " + view);
    let div = document.querySelector(`#${view}`)
    rtcEngine.setupLocalVideo(div)
  })

  rtcApiChannel.on("setupRemoteVideo", (uid, view) => {
    console.log("setupRemoteVideo view = " + uid);
    let div = document.querySelector(`#${view}`)
    rtcEngine.setupViewContentMode(uid, view)
    rtcEngine.subscribe(uid, div)
  })

  rtcApiChannel.on("muteVideoStream", (mute) => {
    console.log("muteVideoStream mute = " + mute);
    rtcEngine.muteLocalVideoStream(mute)
  })

  rtcApiChannel.on("muteAudioStream", (mute) => {
    console.log("muteAudioStream mute = " + mute);
    rtcEngine.muteLocalAudioStream(mute)
  })

  rtcEngine.on("joinedChannel", (channel, uid, elapsed) => {
    console.log("onJoinedChannel " + channel + "  uid = " + uid);
    rtcCallbackChannel.emit("join-channel-success", channel, uid, elapsed)
  })

  rtcEngine.on("userJoined", (uid, elapsed) => {
    console.log("userJoined " + "  uid = " + uid);
    rtcCallbackChannel.emit("user-joined", uid, elapsed)
  })
})();