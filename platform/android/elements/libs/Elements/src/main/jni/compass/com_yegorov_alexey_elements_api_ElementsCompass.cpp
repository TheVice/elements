
#include "com_yegorov_alexey_elements_api_ElementsCompass.h"

#include "logging.h"
#include "renderer_factory.h"
#include "compass_renderer.h"
#include "com_yegorov_alexey_elements_api_Elements.h"

using CompassRendererFactory = renderer_factory<compass_renderer>;
static CompassRendererFactory factory_;

JNIEXPORT jint JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_create
  (JNIEnv* env, jclass clazz, jobject object)
{
	int id = factory_.open();
	Java_com_yegorov_alexey_elements_api_Elements_initializeAssets(env, clazz, object);
	LOGI("[API][Compass] create renderer (%d)", id);
	return id;
}

JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_startup
  (JNIEnv *, jclass, jint id, jint width, jint height)
{
	const auto renderer = factory_.get(id);

	if (renderer != nullptr)
	{
		const auto isStartUp = renderer->startup(eps::math::uvec2(width, height));

		if (isStartUp)
		{
			LOGI("[API][Compass] success startup renderer (%d)", id);
		}
		else
		{
			LOGE("[API][Compass] startup failed: renderer (%d) return false", id);
		}

		return isStartUp;
	}

	LOGE("[API][Compass] startup failed: renderer (%d) is null", id);
	return false;
}

JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_destroy
  (JNIEnv *, jclass, jint id)
{
	if (!factory_.close(id))
	{
		LOGE("[API][Compass] destroy failed: renderer (%d) is null", id);
		return false;
	}

	LOGI("[API][Compass] destroy renderer (%d)", id);
	return true;
}

JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_render
  (JNIEnv *, jclass, jint id)
{
	const auto renderer = factory_.get(id);

	if (renderer != nullptr)
	{
		renderer->render();
		return true;
	}

	LOGE("[API][Compass] rendering failed: renderer (%d) is null", id);
	return false;
}

JNIEXPORT jboolean JNICALL Java_com_yegorov_alexey_elements_api_ElementsCompass_rotation
  (JNIEnv *, jclass, jint id, jfloat omega)
{
	const auto renderer = factory_.get(id);

	if (renderer != nullptr)
	{
		renderer->set_rotation(omega);
		return true;
	}

	LOGE("[API][Compass] rotation failed: renderer (%d) is null", id);
	return false;
}
