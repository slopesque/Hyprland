#include "../../../keybinds/Submap.hpp"

namespace Config::Actions {

    namespace {
      using Keybinds::WSubmap;
      using Keybinds::SubmapList;
    }

    class CSubmapContext {
      public:
        CSubmapContext()                                   = default;
        CSubmapContext(CSubmapContext&&)                   = default;
        CSubmapContext&        operator=(CSubmapContext&&) = default;

        CSubmapContext         snapshot();

        bool                   contains(const std::string& submap) const;
        bool                   contains(const WSubmap& submap) const;
        std::optional<WSubmap> find(const std::string& submap) const;
        std::optional<WSubmap> find(const WSubmap& submap) const;
        bool                   empty() const;
        void                   add(WSubmap&& submap);
        void                   remove(const std::string& submap);
        void                   remove(const WSubmap& submap);
        void                   toggle(WSubmap&& submap);
        void                   reset();

        const SubmapList&      submaps() const;

      private:
        CSubmapContext(CSubmapContext&)                    = default;
        CSubmapContext&        operator=(CSubmapContext&)  = default;

        SubmapList m_submaps;
    };
}
