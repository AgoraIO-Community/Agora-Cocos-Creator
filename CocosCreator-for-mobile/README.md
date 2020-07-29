1: Open Demo Project by Cocos Creator v2.2.1

2: Input Your appId in assets/Script/HelloWorld.js : var appId = #YOUR_APPID;

3: Project->Build...->Build （This step is just want to sync js scripts in asset with build directory, Note: do not need to compile it）

4: Download Agora Android video sdk and IOS video sdk.

5: Unzip Android sdk package, copy Android video sdk into build/jsb-link/frameworks/runtime-src/proj.android-studio/app/jni/agoraEngine/

copy the files which are in include dir into build/jsb-link/frameworks/runtime-src/Classes/agoraEngine/include/agora

6: Unzip IOS sdk package, copy IOS video sdk into build/jsb-link/frameworks/runtime-src/proj.ios_mac/agora-framework/

7: Open Android Studio Project in build/jsb-link/frameworks/runtime-src/proj.android-studio and build it.

8: Open XCode Project in build/jsb-link/frameworks/runtime-src/proj.ios_mac/ and build it.
