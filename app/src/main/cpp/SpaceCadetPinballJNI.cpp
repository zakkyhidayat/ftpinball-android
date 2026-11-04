#include "SpaceCadetPinballJNI.h"
#include "../../../../SpaceCadetPinball/winmain.h"
#include "../../../../SpaceCadetPinball/Sound.h"
#include "../../../../SpaceCadetPinball/pinball.h"
#include "../../../../SpaceCadetPinball/control.h"
#include "../../../../SpaceCadetPinball/render.h"
#include "../../../../SpaceCadetPinball/pb.h"
#include "../../../../SpaceCadetPinball/score.h"
#include "../../../../SpaceCadetPinball/gdrv.h"
#include "../../../../SpaceCadetPinball/TPinballTable.h"
#include "../../../../SpaceCadetPinball/TPlunger.h"
#include <vector>
#include <jni.h>
#include <android/log.h>

static JavaVM* g_JavaVM = nullptr;
static jclass clazz = nullptr;
static JNIEnv *env = nullptr;

void SpaceCadetPinballJNI::show_error_dialog(std::string title, std::string message) {
    __android_log_print(ANDROID_LOG_ERROR, "SpaceCadetPinballJNI", "Error: %s, %s", title.c_str(), message.c_str());
}

void SpaceCadetPinballJNI::notifyGameState(int state) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "setState", "(I)V");

    env->CallStaticVoidMethod(clazz, mid, state);
}

void SpaceCadetPinballJNI::setBallInPlunger(bool isInPlunger) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "setBallInPlunger", "(Z)V");

    env->CallStaticVoidMethod(clazz, mid, isInPlunger);
}

void SpaceCadetPinballJNI::addHighScore(int score) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "addHighScore", "(I)V");

    env->CallStaticVoidMethod(clazz, mid, score);
}

int SpaceCadetPinballJNI::getHighScore() {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "getHighScore", "()I");

    return env->CallStaticIntMethod(clazz, mid);
}

void SpaceCadetPinballJNI::displayText(const char* text, int type) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "printString", "(Ljava/lang/String;I)V");

    jstring str = env->NewStringUTF(text);

    env->CallStaticVoidMethod(clazz, mid, str, type);
}

void SpaceCadetPinballJNI::postRemainingBalls(int balls) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "setRemainingBalls", "(I)V");

    env->CallStaticVoidMethod(clazz, mid, balls);
}

void SpaceCadetPinballJNI::clearText(int type) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "clearText", "(I)V");

    env->CallStaticVoidMethod(clazz, mid, type);
}

void SpaceCadetPinballJNI::postScore(int score) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "postScore", "(I)V");

    env->CallStaticVoidMethod(clazz, mid, score);
}

void SpaceCadetPinballJNI::postBallCount(int count) {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "postBallCount", "(I)V");

    env->CallStaticVoidMethod(clazz, mid, count);
}

void SpaceCadetPinballJNI::cheatsUsed() {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "cheatsUsed", "()V");

    env->CallStaticVoidMethod(clazz, mid);
}

void SpaceCadetPinballJNI::gameReady() {
    if (env == nullptr) g_JavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (clazz == nullptr) clazz = env->FindClass("com/fexed/spacecadetpinball/JNIEntryPoint");
    jmethodID mid = env->GetStaticMethodID(clazz, "gameIsReady", "()V");

    env->CallStaticVoidMethod(clazz, mid);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_initNative(JNIEnv *env, jobject thiz,
        jstring data_path, jstring dat_file, jboolean full_tilt) {
    winmain::BasePath = (char *) env->GetStringUTFChars(data_path, nullptr);
    const char *dat = env->GetStringUTFChars(dat_file, nullptr);
    winmain::DatOverride = dat;
    env->ReleaseStringUTFChars(dat_file, dat);
    winmain::FullTiltOverride = full_tilt;
    env->GetJavaVM(&g_JavaVM);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_setSoundEnabled(JNIEnv *env, jobject thiz, jboolean enabled) {
    Sound::Enable(enabled);
}

static void putGlyph(std::vector<jint>& out, gdrv_bitmap8* bmp)
{
    out.push_back(bmp->Width);
    out.push_back(bmp->Height);
    for (int y = 0; y < bmp->Height; ++y)
        for (int x = 0; x < bmp->Width; ++x)
        {
            ColorRgba c = bmp->BmpBufPtr1[y * bmp->Stride + x];
            out.push_back(c.Color == 0 ? 0 : static_cast<jint>(0xFF000000u | (c.rgba.Red << 16) | (c.rgba.Green << 8) | c.rgba.Blue));
        }
}

// The picture fonts of the table: ten score digits, then the message font as {height, gap, count, {code, w, h, argb...}}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_captureGameFont(JNIEnv *env, jobject thiz) {
    if (!pb::MainTable || !pb::MainTable->CurScoreStruct || !score::msg_fontp)
        return nullptr;
    std::vector<jint> out;
    for (int i = 0; i < 10; ++i)
    {
        auto bmp = pb::MainTable->CurScoreStruct->CharBmp[i];
        if (!bmp)
            return nullptr;
        putGlyph(out, bmp);
    }
    out.push_back(score::msg_fontp->Height);
    out.push_back(score::msg_fontp->GapWidth);
    size_t countAt = out.size();
    out.push_back(0);
    int count = 0;
    for (int c = 32; c < 128; ++c)
    {
        auto bmp = score::msg_fontp->Chars[c];
        if (!bmp)
            continue;
        out.push_back(c);
        putGlyph(out, bmp);
        ++count;
    }
    out[countAt] = count;
    jintArray arr = env->NewIntArray(static_cast<jsize>(out.size()));
    if (!arr)
        return nullptr;
    env->SetIntArrayRegion(arr, 0, static_cast<jsize>(out.size()), out.data());
    return arr;
}

// The painting of the table's sidebar (above its score boxes) as {width, height, argb...}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_captureSidebarArt(JNIEnv *env, jobject thiz) {
    if (!pb::MainTable || !render::vscreen)
        return nullptr;
    // the painting sits inside a frame of the sidebar: leave the frame and the black around it out
    int sideX = static_cast<int>(pb::MainTable->Width);
    int sideW = render::vscreen->Width - sideX;
    int x0 = sideX + sideW * 6 / 100;
    int x1 = render::vscreen->Width - sideW * 6 / 100;
    int y0 = render::vscreen->Height * 3 / 100;
    int y1 = render::vscreen->Height / 2;
    int w = x1 - x0, h = y1 - y0;
    if (w <= 0 || h <= 0)
        return nullptr;
    jintArray out = env->NewIntArray(2 + w * h);
    if (!out)
        return nullptr;
    std::vector<jint> buf(2 + w * h);
    buf[0] = w;
    buf[1] = h;
    for (int y = 0; y < h; ++y)
    {
        const ColorRgba* row = render::vscreen->BmpBufPtr1 + (y + y0) * render::vscreen->Stride + x0;
        for (int x = 0; x < w; ++x)
            buf[2 + y * w + x] = static_cast<jint>(0xFF000000u | (row[x].rgba.Red << 16) | (row[x].rgba.Green << 8) | row[x].rgba.Blue);
    }
    env->SetIntArrayRegion(out, 0, 2 + w * h, buf.data());
    return out;
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_getPlungerPower(JNIEnv *env, jobject thiz) {
    if (!pb::MainTable || !pb::MainTable->Plunger || pb::MainTable->Plunger->MaxPullback <= 0)
        return 0.0f;
    float power = pb::MainTable->Plunger->Boost / pb::MainTable->Plunger->MaxPullback;
    return power < 0.0f ? 0.0f : (power > 1.0f ? 1.0f : power);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_setSoundVolume(JNIEnv *env, jobject thiz, jint volume) {
    Sound::SetVolume(volume);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_putString(JNIEnv *env, jobject thiz, jint id, jstring str) {
    LPCSTR mstr = (*env).GetStringUTFChars(str, nullptr);
    pinball::set_rc_string(id, mstr);
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_fexed_spacecadetpinball_MainActivity_checkCheatsUsed(JNIEnv *env, jobject thiz) {
    return control::check_cheats();
}