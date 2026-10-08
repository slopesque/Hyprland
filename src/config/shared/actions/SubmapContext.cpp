#include "SubmapContext.hpp"

#include <algorithm>
#include <utility>

using namespace Config::Actions;

SP<CSubmapContext> CSubmapContext::snapshot() {
    auto snapshot = makeShared<CSubmapContext>();
    snapshot->m_submaps.insert_range(m_submaps);
    return snapshot;
}

bool CSubmapContext::contains(const std::string& submap) const {
    const auto MATCH = std::ranges::find_if(m_submaps, [submap](const auto& s) { return s.second->name() == submap; });

    return MATCH != m_submaps.end();
}

std::optional<Keybinds::PSubmap> CSubmapContext::find(WP<IHID> submap) const {
    const auto MATCH = m_submaps.find(submap);

    if (MATCH == m_submaps.end())
        return std::nullopt;

    return MATCH->second;
}

std::vector<Keybinds::WSubmap> CSubmapContext::find(const Keybinds::CDeviceList& devices) const {
    std::vector<Keybinds::WSubmap> results;

    for (const std::string& device : devices.devices()) {
        const auto MATCH = std::ranges::find_if(m_submaps, [device](const auto& d) { return d.first->m_deviceName == device; });

        if (MATCH == m_submaps.end())
            continue;

        results.emplace_back(MATCH->second);
    }

    return results;
}

bool CSubmapContext::empty() const {
    return m_submaps.empty();
}

void CSubmapContext::add(Keybinds::PSubmap&& submap) {
    add(nullptr, std::move(submap));
}

void CSubmapContext::add(WP<IHID> device, Keybinds::PSubmap&& submap) {
    m_submaps.insert({device, std::move(submap)});
}

void CSubmapContext::remove(WP<IHID> submap) {
    m_submaps.erase(submap);
}

void CSubmapContext::toggle(Keybinds::PSubmap&& submap) {
    auto device = std::ranges::find_if(m_submaps, [submap](const auto& s) { return s.second->name() == submap->name(); });

    if (device == m_submaps.end()) {
        add(std::move(submap));
        return;
    }

    remove(device->first);
}

void CSubmapContext::reset() {
    m_submaps.clear();
}

const std::unordered_map<WP<IHID>, Keybinds::PSubmap>& CSubmapContext::submaps() const {
    return m_submaps;
}
