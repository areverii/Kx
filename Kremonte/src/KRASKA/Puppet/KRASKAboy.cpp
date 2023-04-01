#include "KRASKAboy.h"

namespace KRASKA {

    static CPU& getCPU(CPU cpu_in) {
        CPU& temp = cpu_in;
        return temp;
    }

    static Video& getVideo(Video video_in) {
        Video& temp = video_in;
        return temp;
    }

    static MMU& getMMU(MMU mmu_in) {
        MMU& temp = mmu_in;
        return temp;
    }

    static Serial& getSerial(Serial serial_in) {
        Serial& temp = serial_in;
        return temp;
    }

    static Debugger& getDebugger(Debugger debugger_in) {
        Debugger& temp = debugger_in;
        return temp;
    }

    static Input& getInput(Input input_in) {
        Input& temp = input_in;
        return temp;
    }

    static Timer& getTimer(Timer timer_in) {
        Timer& temp = timer_in;
        return temp;
    }

    KRASKAboy::KRASKAboy(const std::vector<u8>& cartridge_data, Options& options,
        const std::vector<u8>& save_data)
        : cartridge(get_cartridge(cartridge_data, save_data)),
        cpu(getCPU(CPU(*this, options))),
        video(getVideo(Video(* this, options))),
        mmu(getMMU(MMU(*this, options))),
        serial(getSerial(Serial(options))),
        debugger(getDebugger(Debugger(*this, options))),
        input(getInput(Input())),
        timer(getTimer(Timer()))
    {
        /*Cartridge tempcartridge(get_cartridge(cartridge_data, save_data));
        cartridge = tempcartridge;
        CPU tempCPU(*this, options);
        cpu = tempCPU;
        Video tempVideo(*this, options);
        video = tempVideo;
        MMU tempmmu(*this, options);
        mmu = tempmmu;
        Serial tempSerial(*this, options);
        serial = tempSerial;
        Debugger tempDebugger(*this, options);
        debugger = tempDebugger;*/


        if (options.disable_logs) log_set_level(LogLevel::Error);

        log_set_level(options.trace
            ? LogLevel::Trace
            : LogLevel::Info
        );
    }

    void KRASKAboy::button_pressed(GbButton button) {
        input.button_pressed(button);
    }

    void KRASKAboy::button_released(GbButton button) {
        input.button_released(button);
    }

    void KRASKAboy::debug_toggle_background() {
        video.debug_disable_background = !video.debug_disable_background;
    }

    void KRASKAboy::debug_toggle_sprites() {
        video.debug_disable_sprites = !video.debug_disable_sprites;
    }

    void KRASKAboy::debug_toggle_window() {
        video.debug_disable_window = !video.debug_disable_window;
    }

    void KRASKAboy::run(
        const should_close_callback_t& _should_close_callback,
        const vblank_callback_t& _vblank_callback
    ) {
        should_close_callback = _should_close_callback;

        video.register_vblank_callback(_vblank_callback);

        while (!should_close_callback()) {
            tick();
        }

        debugger.set_enabled(false);
    }

    void KRASKAboy::tick() {
        KR_INFO("tick");
        debugger.cycle();

        auto cycles = cpu.tick();
        elapsed_cycles += cycles.cycles;

        video.tick(cycles);
        timer.tick(cycles.cycles);
    }

    auto KRASKAboy::get_cartridge_ram() const -> const std::vector<u8>& {
        return cartridge->get_cartridge_ram();
    }
}