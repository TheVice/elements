
#include "InputStream.h"

#define TIME_OUT 5

jint InputStream::available(JNIEnv* env, jobject object)
{
	env->PushLocalFrame(TIME_OUT);
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "available", "()I");
	const jint availableValue = env->CallIntMethod(object, methodID);
	//
	env->PopLocalFrame(nullptr);
	return availableValue;
}

void InputStream::close(JNIEnv* env, jobject object)
{
	env->PushLocalFrame(TIME_OUT);
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "close", "()V");
	env->CallVoidMethod(object, methodID);
	env->PopLocalFrame(nullptr);
}

jint InputStream::read(JNIEnv* env, jobject object, jbyteArray buffer, jint bufferLength)
{
	env->PushLocalFrame(TIME_OUT);
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "read", "([BII)I");
	const jint offset = 0;
	const jint readCount = env->CallIntMethod(object, methodID, buffer, offset, bufferLength);
	//
	env->PopLocalFrame(nullptr);
	return readCount;
}
