1: Open Demo Project by Cocos Creator v1.8.2
 
2: Input Your appId in assets/Script/HelloWorld.js : var appId = #YOUR_APPID;

3:  Project->Build...->Build （This step is just want to sync js scripts in asset with build directory, Note:  do not need to compile it）

3: Download Agora Android video sdk and IOS video sdk.

4: Unzip Android sdk package, copy Android video sdk into build/jsb-link/frameworks/runtime-src/proj.android-studio/app/jni/agora/
   
5: Unzip IOS sdk package, copy IOS video sdk into build/jsb-link/frameworks/runtime-src/proj.ios_mac/agora-framework/agora-yuv-framework

6: copy cocos2d-x sdk into build/jsb-link/frameworks/runtime-src/  (if you can not find cocos2d-x sdk, you just need to create an empty project and build it (Project->Build...->Build ), you can find the cocos2d-x directory in this path: build/jsb-link/frameworks/runtime-src/  which project is create by yourself just now. At last, copy the cocos2d-x sdk into Agora Cocos Creator)

7: Open Android Studio Project in build/jsb-link/frameworks/runtime-src/proj.android-studio and build it.

9: Open XCode Project in build/jsb-link/frameworks/runtime-src/proj.ios_mac/ and build it.
