/* //device/libs/android_runtime/android_os_Gpio.cpp
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "android_os_gpio"
#define LOG_NDEBUG 0

#include "JNIHelp.h"
#include "jni.h"
#include "android_runtime/AndroidRuntime.h"
#include <utils/misc.h>
#include <utils/Log.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#ifdef HAVE_ANDROID_OS      // just want PAGE_SIZE define
#include <asm/page.h>
#else
#include <sys/user.h>
#endif
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>

namespace android
{

static void throw_NullPointerException(JNIEnv *env, const char* msg)
{
    jclass clazz;
    clazz = env->FindClass("java/lang/NullPointerException");
    env->ThrowNew(clazz, msg);
}


static int readGpio_native(JNIEnv *env, jobject clazz, jstring path)
{
    int fd;
    int value;

    if (path == NULL) 
    {
        return -1;
    }
	else 
    {
    	const char *chars = env->GetStringUTFChars(path, NULL);
    	
        fd = open(chars, O_RDWR);
        if(fd < 0){
            ALOGE("fail in open file %s", chars);
            env->ReleaseStringUTFChars(path, chars);
            return -1;
        }
        
        char valueStr[32];
        memset(valueStr, 0, sizeof(valueStr));
        
        read(fd, (void *)valueStr, sizeof(valueStr)-1);
        //ALOGD("value str = %s", valueStr);
        
        char *end;
        value = strtol(valueStr, &end, 0);
        if(end == valueStr){
            ALOGE("Fail in convert string %s to number.", valueStr);
            env->ReleaseStringUTFChars(path, chars);
            close(fd);
            return -1;
        }

        env->ReleaseStringUTFChars(path, chars);
		close(fd);
        return value;
	}
}

static int writeGpio_native(JNIEnv *env, jobject clazz, jstring path, jstring value)
{
    int fd;

    if (path == NULL) 
    {
        return -1;
    }
	else 
    {
    	const char *chars = env->GetStringUTFChars(path, NULL);
    	const char *valueStr = env->GetStringUTFChars(value, NULL);

        fd = open(chars, O_RDWR);
        if(fd < 0){
            ALOGD("fail in open file %s", chars);
            env->ReleaseStringUTFChars(path, chars);
            env->ReleaseStringUTFChars(value, valueStr);
            return -1;
        }
        //ALOGD("value str = %s", valueStr);

        int ret = write(fd, valueStr, strlen(valueStr));
        //ALOGD("ret = %d", ret);
        
        env->ReleaseStringUTFChars(path, chars);
        env->ReleaseStringUTFChars(value, valueStr);
        close(fd);
        return 0;
	}
    
}

static JNINativeMethod method_table[] = {
    { "nativeWriteGpio", "(Ljava/lang/String;Ljava/lang/String;)I", (void*)writeGpio_native },
    { "nativeReadGpio", "(Ljava/lang/String;)I", (void*)readGpio_native },
};

int register_android_os_Gpio(JNIEnv *env)
{
    return AndroidRuntime::registerNativeMethods(
        env, "android/os/Gpio",
        method_table, NELEM(method_table));
}

};

