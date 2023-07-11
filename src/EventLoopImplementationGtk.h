/*
 * Copyright (c) 2022-2023, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2023, Matthew Jakeman <mattjakemandev@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/HashMap.h>
#include <AK/NonnullOwnPtr.h>
#include <AK/OwnPtr.h>
#include <LibCore/EventLoopImplementation.h>
#include <glib-object.h>

namespace Ladybird {

class EventLoopManagerGtk final : public Core::EventLoopManager {
public:
    EventLoopManagerGtk();
    virtual ~EventLoopManagerGtk() override;
    virtual NonnullOwnPtr<Core::EventLoopImplementation> make_implementation() override;

    virtual int register_timer(Core::Object&, int milliseconds, bool should_reload, Core::TimerShouldFireWhenNotVisible) override;
    virtual bool unregister_timer(int timer_id) override;

    virtual void register_notifier(Core::Notifier&) override;
    virtual void unregister_notifier(Core::Notifier&) override;

    virtual void did_post_event() override;

    // FIXME: These APIs only exist for obscure use-cases inside SerenityOS. Try to get rid of them.
    virtual int register_signal(int, Function<void(int)>) override { return 0; }
    virtual void unregister_signal(int) override { }

private:
};

class EventLoopImplementationGtk final : public Core::EventLoopImplementation {
public:
    static NonnullOwnPtr<EventLoopImplementationGtk> create() { return adopt_own(*new EventLoopImplementationGtk); }

    virtual ~EventLoopImplementationGtk() override;

    virtual int exec() override;
    virtual size_t pump(PumpMode) override;
    virtual void quit(int) override;
    virtual void wake() override;
    virtual void post_event(Core::Object& receiver, NonnullOwnPtr<Core::Event>&&) override;

    // FIXME: These APIs only exist for obscure use-cases inside SerenityOS. Try to get rid of them.
    virtual void unquit() override { }
    virtual bool was_exit_requested() const override { return false; }
    virtual void notify_forked_and_in_child() override { }

    void set_main_loop() { dbgln("GLib Event Loop only supports being main!"); }

private:
    friend class EventLoopManagerGtk;

    EventLoopImplementationGtk();
    bool is_main_loop() const { return true; }

    GMainLoop *m_event_loop;
    int m_error_code;
};

}
