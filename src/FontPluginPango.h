/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2023, Matthew Jakeman <mattjakemandev@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RefPtr.h>
#include <AK/Vector.h>
#include <LibWeb/Platform/FontPlugin.h>

namespace Ladybird {

class FontPluginGTK final : public Web::Platform::FontPlugin {
public:
    FontPluginGTK(bool is_layout_test_mode);
    virtual ~FontPluginGTK();

    virtual Gfx::Font& default_font() override;
    virtual Gfx::Font& default_fixed_width_font() override;
    virtual DeprecatedString generic_font_name(Web::Platform::GenericFont) override;

    void update_generic_fonts();

private:
    Vector<DeprecatedString> m_generic_font_names;
    RefPtr<Gfx::Font> m_default_font;
    RefPtr<Gfx::Font> m_default_fixed_width_font;
    bool m_is_layout_test_mode { false };
};

}
