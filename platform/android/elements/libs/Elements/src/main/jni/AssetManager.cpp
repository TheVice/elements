
#include "AssetManager.h"
#include "InputStream.h"

#define TIME_OUT 5

void AssetManager::close(JNIEnv* env, jobject object)
{
	env->PushLocalFrame(TIME_OUT);
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "close", "()V");
	env->CallVoidMethod(object, methodID);
	env->PopLocalFrame(nullptr);
}

std::vector<std::string> AssetManager::getLocales(JNIEnv* env, jobject object)
{
	env->PushLocalFrame(TIME_OUT);
	//
	std::vector<std::string> locales;
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "getLocales", "()[Ljava/lang/String;");
	//
	const jobjectArray array = (jobjectArray)env->CallObjectMethod(object, methodID);

	if (array)
	{
		const jsize count = env->GetArrayLength(array);
		locales.reserve(count);
		locales.resize(count);

		for (jsize i = 0; i < count; ++i)
		{
			jboolean isCopy;
			const jstring pointer = (jstring)env->GetObjectArrayElement(array, i);
			const char *localString = env->GetStringUTFChars(pointer, &isCopy);
			locales[i] = std::string(localString);
			env->ReleaseStringUTFChars(pointer, localString);
		}
	}

	env->PopLocalFrame(nullptr);
	return locales;
}

std::vector<std::string> AssetManager::list(JNIEnv* env, jobject object, const char* path)
{
	env->PushLocalFrame(TIME_OUT);
	//
	std::vector<std::string> assets;
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "list", "(Ljava/lang/String;)[Ljava/lang/String;");
	//
	const jstring jstringPath = env->NewStringUTF(path);
	const jobjectArray array = (jobjectArray)env->CallObjectMethod(object, methodID, jstringPath);
	env->DeleteLocalRef(jstringPath);

	if (array)
	{
		const jsize count = env->GetArrayLength(array);
		assets.reserve(count);
		assets.resize(count);

		for (jsize i = 0; i < count; ++i)
		{
			jboolean isCopy;
			const jstring pointer = (jstring)env->GetObjectArrayElement(array, i);
			const char *localString = env->GetStringUTFChars(pointer, &isCopy);
			assets[i] = std::string(localString);
			env->ReleaseStringUTFChars(pointer, localString);
		}
	}

	env->PopLocalFrame(nullptr);
	return assets;
}

std::vector<int8_t> AssetManager::open(JNIEnv* env, jobject object, const char* fileName)
{
	env->PushLocalFrame(TIME_OUT);
	//
	std::vector<int8_t> fileContent;
	//
	const jclass clazz = env->GetObjectClass(object);
	const jmethodID methodID = env->GetMethodID(clazz, "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
	//
	const jstring jstringPath = env->NewStringUTF(fileName);
	const jobject inputStreamObject = env->CallObjectMethod(object, methodID, jstringPath);

	if (env->ExceptionCheck())
	{
		env->ExceptionClear();
		env->DeleteLocalRef(jstringPath);
		return fileContent;
	}

	env->DeleteLocalRef(jstringPath);

	if (inputStreamObject)
	{
		const jint bufferLength = InputStream::available(env, inputStreamObject);
		jbyteArray buffer = env->NewByteArray(bufferLength);
		jint readCount = 0;
		fileContent.reserve(bufferLength);
		fileContent.clear();

		while (-1 != (readCount = InputStream::read(env, inputStreamObject, buffer, bufferLength)))
		{
			jbyte* pointer = env->GetByteArrayElements(buffer, 0);
			fileContent.insert(fileContent.end(), pointer, pointer + readCount);
		}

		env->DeleteLocalRef(buffer);

		InputStream::close(env, inputStreamObject);
	}

	env->PopLocalFrame(nullptr);
	return fileContent;
}

void walk(JNIEnv* env, jobject object, const std::string& parent_path, std::vector<std::string>& paths)
{
	env->PushLocalFrame(TIME_OUT);
	//
	const auto assets = AssetManager::list(env, object, parent_path.c_str());

	if (!assets.empty())
	{
		const auto parent_path_length = parent_path.size();

		for (const auto &asset : assets)
		{
			const auto asset_path_length = asset.size();
			std::string fullPath(parent_path_length + asset_path_length + 1, '\0');
			fullPath.clear();

			if (parent_path_length)
			{
				fullPath.insert(fullPath.end(), parent_path.begin(), parent_path.end());
				fullPath.push_back('/');
			}

			fullPath.insert(fullPath.end(), asset.begin(), asset.end());
			walk(env, object, fullPath, paths);
		}
	}
	else
	{
		paths.push_back(parent_path);
	}

	env->PopLocalFrame(nullptr);
}

std::vector<std::string> getAssetList(JNIEnv* env, jobject object, const std::string& path)
{
	env->PushLocalFrame(TIME_OUT);
	//
	std::vector<std::string> paths(512);
	paths.clear();
	//
	walk(env, object, path, paths);
	//
	env->PopLocalFrame(nullptr);
	return paths;
}
