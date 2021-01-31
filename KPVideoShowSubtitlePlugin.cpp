//
// Created by karaler on 2020/7/30.
// Author: karaler
// Description: 
// Others: 
// Copyright (c) 2020 Bytelang . All rights reserved.
//

#include "KPVideoShowSubtitlePlugin.h"

KPVideoShowSubtitlePlugin::KPVideoShowSubtitlePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParamsObject plugin_params_object) : KPPluginAdapter(identify_name, filter_name, filter_type, plugin_params_object) {

    //获取播放文件路径
    auto              current_title = global_event_play_updated.GetLastVariable();
    KPlayer::FileInfo file_info(current_title);

    // 字幕文件路径
    std::string subtitle_file_path;

    std::string       srt_file_path = file_info.GetBaseFilePath() + file_info.GetBaseFileName() + ".srt";
    KPlayer::FileInfo srt_file_info(srt_file_path);

    std::string       ass_file_path = file_info.GetBaseFilePath() + file_info.GetBaseFileName() + ".ass";
    KPlayer::FileInfo ass_file_info(ass_file_path);

    if (srt_file_info.Exists()) {
        subtitle_file_path = srt_file_path;
    }
    if (ass_file_info.Exists()) {
        subtitle_file_path = ass_file_path;
    }

    if (subtitle_file_path.empty()) {
        throw KPFilterException("字幕文件加载失败；ass与srt同名字幕文件不存在 path: " + file_info.GetBaseFilePath() + file_info.GetBaseFileName());
    }

    // 赋值described
    std::stringstream filter_desc_stream;
    filter_desc_stream << "filename=" << srt_file_path;
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
    return new KPVideoShowSubtitlePlugin("kplayer", "video_plugin_show_subtitle", KP_FILTER_TYPE_VIDEO, std::move(plugin_params));
}
