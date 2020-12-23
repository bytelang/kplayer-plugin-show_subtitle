//
// Created by karaler on 2020/7/30.
// Author: karaler
// Description: 
// Others: 
// Copyright (c) 2020 Bytelang . All rights reserved.
//

#ifndef KPLAYER_KPVIDEOSHOWSUBTITLEPLUGIN_H
#define KPLAYER_KPVIDEOSHOWSUBTITLEPLUGIN_H

#include "adapter/KPPluginAdapter.h"
#include "util/KPHelper.h"

extern KPEvent<std::string> global_event_play_updated;

class KPVideoShowSubtitlePlugin : public KPPluginAdapter {
protected:
    void Task() override;
    bool stop = false;
public:
    explicit KPVideoShowSubtitlePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParamsObject plugin_params);
    ~KPVideoShowSubtitlePlugin() override = default;
    void KillTask() override;
    void InitTask() override;
};

// slot
extern "C" {
KPLAYER_PLUGIN_FUNC(KPVideoShowSubtitlePlugin);
}


#endif //KPLAYER_KPVIDEOSHOWSUBTITLEPLUGIN_H
