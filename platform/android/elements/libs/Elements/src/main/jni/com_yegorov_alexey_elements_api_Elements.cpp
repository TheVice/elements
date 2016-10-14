
#include "com_yegorov_alexey_elements_api_Elements.h"
#include "AssetManager.h"
#include "android_asset_reader.h"
#include "preferences.h"
#include "metrics.h"

JNIEXPORT void JNICALL Java_com_yegorov_alexey_elements_api_Elements_initializeAssets
  (JNIEnv* env, jclass, jobject object)
{
    android_asset_reader::assets_.clear();
    //
    const auto assets = getAssetList(env, object, "");

    for (const auto& asset : assets)
    {
        const auto asset_content = AssetManager::open(env, object, asset.c_str());

        if (asset_content.empty())
        {
            android_asset_reader::assets_[asset] = "";
        }
        else
        {
            std::string content(asset_content.size(), '\0');
            memcpy(&content.front(), &asset_content.front(), asset_content.size());
            android_asset_reader::assets_[asset] = content;
        }
    }

    eps::assets_storage::init<android_asset_reader>();
    eps::preferences::init<preferences>();
    eps::metrics::init<metrics>(1.0f);
}
