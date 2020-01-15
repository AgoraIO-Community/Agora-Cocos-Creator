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

  rtcApiChannel.on("initialize", event => {
    console.log("initialize appid = " + event.detail);
    rtcEngine.initialize(event.detail)
  })

  rtcApiChannel.on("setRenderMode", event => {
    console.log("setRenderMode mode = " + event.detail);
    rtcEngine.setRenderMode(event.detail)
  })

  rtcApiChannel.on("joinChannel", event => {
    console.log("joinChannel channel = " + event.detail[1]);
    rtcEngine.joinChannel(event.detail[0], event.detail[1], event.detail[2], event.detail[3])
  })

  rtcApiChannel.on("setupLocalVideo", e => {
    console.log("setupLocalVideo view = " + e.detail);
    let div = document.querySelector(`#${e.detail}`)
    rtcEngine.setupLocalVideo(div)
  })

  rtcApiChannel.on("setupRemoteVideo", e => {
    console.log("setupRemoteVideo view = " + e.detail[1]);
    let div = document.querySelector(`#${e.detail[1]}`)
    rtcEngine.setupViewContentMode(e.detail[0], 1)
    rtcEngine.subscribe(e.detail[0], div)
  })

  rtcApiChannel.on("muteVideoStream", event => {
    console.log("muteVideoStream mute = " + event.detail);
    rtcEngine.muteLocalVideoStream(event.detail)
  })

  rtcApiChannel.on("muteAudioStream", event => {
    console.log("muteAudioStream mute = " + event.detail);
    rtcEngine.muteLocalAudioStream(event.detail)
  })

  rtcEngine.on("joinedChannel", (channel, uid, elapsed) => {
    console.log("onJoinedChannel " + channel + "  uid = " + uid);
    rtcCallbackChannel.emit("join-channel-success", [channel, uid, elapsed])
  })

  rtcEngine.on("userJoined", (uid, elapsed) => {
    console.log("userJoined " + "  uid = " + uid);
    rtcCallbackChannel.emit("user-joined", [uid, elapsed])
  })
})();