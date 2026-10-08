#include "keybinds/DeviceList.hpp"

#include <unordered_map>

#include "../../../devices/IHID.hpp"
#include "../../../keybinds/Submap.hpp"

namespace Config::Actions {

    class CSubmapContext {
      public:
        CSubmapContext()                                                                   = default;
        CSubmapContext(CSubmapContext&)                                                    = delete;
        CSubmapContext(CSubmapContext&&)                                                   = default;
        CSubmapContext&                                        operator=(CSubmapContext&)  = delete;
        CSubmapContext&                                        operator=(CSubmapContext&&) = default;

        SP<CSubmapContext>                                     snapshot();

        bool                                                   contains(const std::string& submap) const;
        std::optional<Keybinds::PSubmap>                       find(WP<IHID> submap) const;
        std::vector<Keybinds::WSubmap>                         find(const Keybinds::CDeviceList& devices) const;
        bool                                                   empty() const;
        void                                                   add(WP<IHID> device, Keybinds::PSubmap&& submap);
        void                                                   add(Keybinds::PSubmap&& submap);
        void                                                   remove(WP<IHID> submap);
        void                                                   toggle(Keybinds::PSubmap&& submap);
        void                                                   reset();

        const std::unordered_map<WP<IHID>, Keybinds::PSubmap>& submaps() const;

      private:
        std::unordered_map<WP<IHID>, Keybinds::PSubmap> m_submaps;
    };
}
