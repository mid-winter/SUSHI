//
// OpenALによるWAV再生
//

// Windows:識別子minとmaxが乗っ取られるのを防ぐ
#define NOMINMAX
// Windows:cmathやmath.hをインクルードした時に
// M_PIとかを使えるようにする
#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include "wav.hpp"


int main() {
  // GLFWの初期化
  if (!glfwInit()) return -1;

  // GLFW Widnowを用意
  GLFWwindow* window = glfwCreateWindow(640, 480,
                                        "Play WAV fie",
                                        nullptr, nullptr);
  // Windowsを生成できなければ終了
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // 用意したWindowsでOpenGLが使えるようにする
  // これで、OpenGLの命令が有効になる
  glfwMakeContextCurrent(window);
  
  // 描画のタイミングを画面更新と同期
  glfwSwapInterval(1);


  // OpenALの初期化
  ALCdevice*  device  = alcOpenDevice(nullptr);
  ALCcontext* context = alcCreateContext(device, nullptr);
  alcMakeContextCurrent(context);


  // バッファの生成
  ALuint buffer_id;
  alGenBuffers(1, &buffer_id);

  // WAVデータを読み込む
  Wav sound("res/lovelive.wav");
  
  // 読み込んだWAVデータの波形をバッファにコピー
  alBufferData(buffer_id,
               // ステレオ or モノラル
               sound.isStereo() ? AL_FORMAT_STEREO16 
                                : AL_FORMAT_MONO16,
               sound.data(),               // リニアPCM形式データ
               sound.size(),               // サイズ(バイト数)
               sound.sampleRate());        // サンプリングレート

  // ソースの生成
  ALuint source_id;
  alGenSources(1, &source_id);
  
  // ソースに再生したいバッファを割り当てる
  alSourcei(source_id, AL_BUFFER, buffer_id);

  // ピッチ変更
  alSourcef(source_id, AL_PITCH, -1.0);
  // ループ再生ON
  alSourcei(source_id, AL_LOOPING, AL_TRUE);
  
  // ソースの再生開始
  alSourcePlay(source_id);  
  
  // Windowが閉じられるまで繰り返す
  while (!glfwWindowShouldClose(window)) {
    // 描画領域をクリア
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 画面とバックバッファを入れ替える
    glfwSwapBuffers(window);

    // キー入力などのイベント処理
    glfwPollEvents();
  }

  
  // ソースの破棄
  alDeleteSources(1, &source_id);

  // バッファの破棄
  alDeleteBuffers(1, &buffer_id);
  
  // OpenALの後始末
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(context);
  alcCloseDevice(device);

  
  // GLFWの後始末
  glfwTerminate();
  
  return 0;
}
