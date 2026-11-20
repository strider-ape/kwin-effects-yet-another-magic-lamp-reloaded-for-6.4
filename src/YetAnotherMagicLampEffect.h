/*
 * Copyright (C) 2018 Vlad Zagorodniy <vladzzag@gmail.com>
 * Copyright (C) 2026 Roy Schroedel <dev@si13n7.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Own
#include "Model.h"
#include "common.h"

// kwineffects
#include <effect/offscreeneffect.h>

// Qt
#include <QPointer>

// std
#include <memory>

// The visible refs are held through shared_ptr and never assigned: in KWin 6.8,
// EffectWindowVisibleRef::operator= registers the hold under the *source*
// object's address, so assigning from a temporary drops the hold immediately
// and the window vanishes the moment minimize starts.
using VisibleRefPtr = std::shared_ptr<KWin::EffectWindowVisibleRef>;

struct AnimationData {
    Model model;
    VisibleRefPtr visibleRef;
};

class YetAnotherMagicLampEffect : public KWin::OffscreenEffect {
    Q_OBJECT

public:
    YetAnotherMagicLampEffect();
    ~YetAnotherMagicLampEffect() override;

    void reconfigure(ReconfigureFlags flags) override;

    void prePaintScreen(KWin::ScreenPrePaintData& data) override;
    void prePaintWindow(KWin::RenderView* view, KWin::EffectWindow* w, KWin::WindowPrePaintData& data) override;
    void postPaintScreen() override;

    bool paintWindow(const KWin::RenderTarget& renderTarget, const KWin::RenderViewport& viewport,
        KWin::EffectWindow* w, int mask, const KWin::Region& deviceRegion,
        KWin::WindowPaintData& data) override;

    bool isActive() const override;
    int requestedEffectChainPosition() const override;

    static bool supported();

protected:
    void apply(KWin::EffectWindow* window, int mask, KWin::WindowPaintData& data, KWin::WindowQuadList& quads) override;

private Q_SLOTS:
    void slotWindowAdded(KWin::EffectWindow* w);
    void slotMinimizedChanged(KWin::EffectWindow* w);
    void slotWindowDeleted(KWin::EffectWindow* w);
    void slotActiveFullScreenEffectChanged();

private:
    void startMinimize(KWin::EffectWindow* w);
    void startUnminimize(KWin::EffectWindow* w);

    Model::Parameters m_modelParameters;
    int m_gridResolution;

    QMap<KWin::EffectWindow*, AnimationData> m_animations;
    // Windows waiting for iconGeometry to become valid before animation starts
    QMap<KWin::EffectWindow*, VisibleRefPtr> m_pendingMinimize;
};

inline int YetAnotherMagicLampEffect::requestedEffectChainPosition() const
{
    return 50;
}
