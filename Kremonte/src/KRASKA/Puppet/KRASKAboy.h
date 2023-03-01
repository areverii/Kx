#pragma once

/*#include "../KRASKAboy/Base/Debugger.h"
#include "../KRASKAboy/Base/Input.h"
#include "../KRASKAboy/CPU/CPU.h"
#include "../KRASKAboy/CPU/Serial.h"
#include "../KRASKAboy/CPU/Timer.h"
#include "../KRASKAboy/Video/Video.h"
#include "../KRASKAboy/Base/Options.h"
#include "../KRASKAboy/Util/KRboy_Log.h"*/
#include "../KRASKAboy/Base/KRASKAboy_comp.h"

#include <memory>
#include <functional>

namespace KRASKA {

    class CPU;
    class Video;
    class MMU;
    class Input;
    class Serial;
    class Timer;
    class Debugger;
    class Cartridge;
    class Options;
    //class vblank_callback_t;
    using vblank_callback_t = std::function<void(const FrameBuffer&)>;
    using should_close_callback_t = std::function<bool()>;

    class KRASKAboy {
    public:
        KRASKAboy(const std::vector<u8>& cartridge_data, Options& options,
            const std::vector<u8>& save_data = {});
        //KRASKAboy(const KRASKAboy&) = delete;
        //KRASKAboy& operator=(const KRASKAboy&) = delete;
        //~KRASKAboy() = default;

        //KRASKAboy(const std::vector<u8>& cartridge_data, Options& options,
        //    const std::vector<u8>& save_data = {});

        void run(
            const should_close_callback_t& _should_close_callback,
            const vblank_callback_t& _vblank_callback
        );

        void button_pressed(GbButton button);
        void button_released(GbButton button);

        void debug_toggle_background();
        void debug_toggle_sprites();
        void debug_toggle_window();

        auto get_cartridge_ram() const -> const std::vector<u8>&;

    private:
        void tick();

        std::shared_ptr<Cartridge> cartridge;

        CPU& cpu;
        friend class CPU;

        Video& video;
        friend class Video;

        MMU& mmu;
        friend class MMU;

        Input& input;
        Serial& serial;
        Timer& timer;

        Debugger& debugger;
        friend class Debugger;

        uint elapsed_cycles = 0;

        should_close_callback_t should_close_callback;
    };
}