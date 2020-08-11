//
// Created by karaler on 2020/7/30.
// Author: karaler
// Description: 
// Others: 
// Copyright (c) 2020 Bytelang . All rights reserved.
//

#include "KPVideoShowSubtitlePlugin.h"

KPVideoShowSubtitlePlugin::KPVideoShowSubtitlePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParams params) : KPPluginAdapter(identify_name, filter_name, filter_type) {

    //获取播放文件路径
    auto current_title = global_event_play.GetLastVariable();

    KPlayer::FileInfo file_info(current_title);

    // 赋值described
    std::stringstream filter_desc_stream;
    filter_desc_stream << "filename=" << file_info.GetBaseFilePath() << file_info.GetBaseFileName() << ".srt";
    filter_desc = filter_desc_stream.str();

    // 查找过滤器
    filter = avfilter_get_by_name("subtitles");
    if (filter == nullptr)
        throw KPFilterException("未知过滤器; filter name: subtitles");
}

void KPVideoShowSubtitlePlugin::Task() {

}

void KPVideoShowSubtitlePlugin::KillTask() {
}

void KPVideoShowSubtitlePlugin::InitTask() {
}

// slot
KPLAYER_PLUGIN_FUNC(KPVideoShowSubtitlePlugin) {
    return new KPVideoShowSubtitlePlugin("kplayer", "video_plugin_show_subtitle", KP_FILTER_TYPE_VIDEO, std::move(params));
}
