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
# KWin 6.3 (KF 6.13) takes the effect's id from the file name, so it must be
# kwin4_effect_yetanothermagiclamp.so: without "lib" it matches metadata.json's Id
# and KWin loads it. (Branch kwin-6.3, for Debian 13.)
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

# Remove a copy built without the fix above ("lib" prefix), which KWin 6.3 won't load.
install(CODE "file(REMOVE \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/${KDE_INSTALL_QTPLUGINDIR}/kwin/effects/plugins/libkwin4_effect_yetanothermagiclamp.so\")")
