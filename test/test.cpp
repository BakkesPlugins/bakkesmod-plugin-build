// Simple test plugin for BakkesMod
#include "bakkesmod/plugin/bakkesmodplugin.h"

class TestPlugin : public BakkesMod::Plugin::BakkesModPlugin {
public:
    virtual void onLoad() override {
        // Plugin initialization code
    }

    virtual void onUnload() override {
        // Plugin cleanup code
    }
};