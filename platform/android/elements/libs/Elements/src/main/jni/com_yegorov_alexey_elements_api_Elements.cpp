
#include "com_yegorov_alexey_elements_api_Elements.h"
#include "AssetManager.h"
#include "android_asset_fs.h"
#include "assets/assets_storage.h"
#include "preferences.h"
#include "metrics.h"
#include "logging.h"

JNIEXPORT void JNICALL Java_com_yegorov_alexey_elements_api_Elements_initializeAssets
  (JNIEnv* env, jclass, jobject object)
{
    asset_fs::assets_.clear();
    //
    const auto assets = getAssetList(env, object, "");

    for (const auto& asset : assets)
    {
        const auto asset_content = AssetManager::open(env, object, asset.c_str());

        if (asset_content.empty())
        {
            asset_fs::assets_[asset] = "";
        }
        else
        {
            std::string content(asset_content.size(), '\0');
            memcpy(&content.front(), &asset_content.front(), asset_content.size());
            asset_fs::assets_[asset] = content;
        }
    }

    LOGI("initializeAssets");
    eps::assets_storage::instance().mount<asset_fs>("assets");
    eps::preferences::init<preferences>();
    eps::metrics::init<metrics>(1.0f);
}

JNIEXPORT void JNICALL Java_com_yegorov_alexey_elements_api_Elements_initializeAssetsAtCache
  (JNIEnv* env, jclass, jstring path_to_cache)
{
    asset_fs::assets_.clear();
    //
    const char * path_to_cache_ = env->GetStringUTFChars(path_to_cache, nullptr);
    std::string path(path_to_cache_);
    env->ReleaseStringUTFChars(path_to_cache, path_to_cache_);
    LOGI("initializeAssetsAtCache - %s", path.c_str());
    eps::assets_storage::instance().mount<asset_fs2>("assets", path);
    eps::preferences::init<preferences>();
    eps::metrics::init<metrics>(1.0f);
}
