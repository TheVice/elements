/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_yegorov_alexey_elements_api_ElementsCompass */

#ifndef _Included_com_yegorov_alexey_elements_api_ElementsCompass
#define _Included_com_yegorov_alexey_elements_api_ElementsCompass
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_yegorov_alexey_elements_api_ElementsCompass
 * Method:    create
 * Signature: (Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_create
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_yegorov_alexey_elements_api_ElementsCompass
 * Method:    startup
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_startup
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     com_yegorov_alexey_elements_api_ElementsCompass
 * Method:    destroy
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_destroy
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_yegorov_alexey_elements_api_ElementsCompass
 * Method:    render
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_render
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_yegorov_alexey_elements_api_ElementsCompass
 * Method:    rotation
 * Signature: (IF)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_rotation
  (JNIEnv *, jclass, jint, jfloat);

#ifdef __cplusplus
}
#endif
#endif