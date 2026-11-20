add_subdirectory(kcm)

set(effect_SRCS
    Model.cc
    YetAnotherMagicLampEffect.cc
    plugin.cc
)

kconfig_add_kcfg_files(effect_SRCS
    YetAnotherMagicLampConfig.kcfgc
)

add_library(kwin4_effect_yetanothermagiclamp SHARED ${effect_SRCS})

# KWin 6.8 derives the plugin Id from the file name. Without this the file is
# libkwin4_effect_yetanothermagiclamp.so, its derived Id doesn't match the Id in
# metadata.json, and KWin refuses to load the effect.
set_target_properties(kwin4_effect_yetanothermagiclamp PROPERTIES PREFIX "")

target_link_libraries(kwin4_effect_yetanothermagiclamp
    Qt6::Core
    Qt6::Gui
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::CoreAddons
    KF6::WindowSystem
    KWin::kwin
)

install(
    TARGETS
        kwin4_effect_yetanothermagiclamp

    DESTINATION
        ${KDE_INSTALL_QTPLUGINDIR}/kwin/effects/plugins/
)
